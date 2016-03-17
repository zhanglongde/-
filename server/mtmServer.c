/*************************************************************************************
              
*FileName:       mtmserver.c                                                  
*Description:    服务器主程序
*Date:             2012-04-07
*Author:          张龙德     
*Revisor:         张龙德

*************************************************************************************/
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <time.h>
#include <sys/socket.h>
#include <sqlite3.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/resource.h> 
#include "commonData.h"
#include "parseString.h"
#include "mySocket.h"
#include "sqlite3Helper.h"
#include "process.h"
#include "Debug.h"

pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;  //互斥锁
char  temp[TEMP_SIZE];          //临时存储空间
char  buffer[BUFFER_SIZE];      //缓冲区定义为1024字节的大小
char  *head;                    //socket通信头部标志信息

int kdpfd, curfds;
int nfds;                         
socklen_t sin_size; 			 //套接字长度
struct epoll_event ev;
struct epoll_event events[MAXEPOLLSIZE];

char connStr[CONNSTR_LEN]={"./db/qm.db"};//连接的数据库名称
char acDBDir[CONNSTR_LEN]={"./db"};
char acBackupDBDir[CONNSTR_LEN]={"./db/backupDB"};//连接的数据库名称

/************建立socket的数据结构******************/
int sockfd;                       //监听套接字
                      //绑定套接字
struct sockaddr_in server_addr;   //服务器套接字
struct sockaddr_in client_addr;  //客户端套接字
struct rlimit rt;//资源限制
/*************************************************/

void Prepare (int argc, char *argv[]);
void * talk_to_client(void *new_fd);
int main(int argc, char *argv[]) 
{  
	DisplayCurTime();
    int i=0;//用于循环用
 	//建立客户端连接之前的准备工作
	Prepare (argc, argv);
	/* 创建 epoll 句柄，把监听 socket 加入到 epoll 集合里 */
    kdpfd = epoll_create(MAXEPOLLSIZE);
	sin_size=sizeof(struct sockaddr_in);//获得监听套接字的长度
    ev.events = EPOLLIN|EPOLLET;;//对应的文件描述符可读且有事件发生
    ev.data.fd = sockfd;
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) 
	{
        fprintf(stderr, "epoll set insertion error: fd=%d\n", sockfd);
        exit(EXIT_FAILURE);
    } 
	Debug("kdpfd:%d\t listenning socket number:%d\n",kdpfd,sockfd);
    //curfds = 1;//最大事件数
	while(1)//服务器端要一直运行 
	{  
	   #if 0
       DisplayCurTime();
	   #endif
	     /* 等待有事件发生 */
	   /*每次循环调用依次epoll_wait侦听*/
        nfds = epoll_wait(kdpfd, events, EPOLL_MAXEVENTS, EPOLL_TIMEOUT);//-1无限制等待
        if (nfds < 0) 
		{
           perror("epoll_wait error\n");
           continue;
        }
		else if (nfds == 0) 
		{
		   fprintf(stderr, "no socket ready for read within %d secs\n", EPOLL_TIMEOUT / 1000);
		   continue;
		}
		Debug("kdpfd:%d\t nfds:%d\t curfds:%d",kdpfd,nfds,curfds);
        /* 处理所有事件 */
        for (i = 0; i < nfds; ++i) 
		{
            if (events[i].data.fd == sockfd) // 如果新监测到一个HTTP用户连接到绑定的HTTP端口则建立新连接。
			{  
                int new_fd=accept(sockfd, (struct sockaddr *) &client_addr,&sin_size);
				if (new_fd < 0) 
				{
                    fprintf(stderr,"Accept error:%s\n",strerror(errno)); 
                    continue;
                    #if 0
                    if ( (errno == EAGAIN) || (errno == EWOULDBLOCK) ) 
					{
						 //non-blocking模式下无新connection请求，跳出while (1)
						 break;
					}
					else 
					{
						 perror("accept failed");
						 exit(EXIT_FAILURE);
					 }
					#endif
                } 
				else
				{
					//打印连接到本服务器的网络地址
					fprintf(stdout,"Server get connection from %s\n", (char *)inet_ntoa(client_addr.sin_addr));
	                setSockNonBlock(new_fd);
	                ev.events = EPOLLIN | EPOLLET;
	                ev.data.fd = new_fd;
	                if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_fd, &ev) < 0) 
					{   
	                    fprintf(stderr, "Add  socket '%d' to epoll failed！%s\n",new_fd, strerror(errno));
	                    exit(EXIT_FAILURE);
	                }
	                //curfds++;//累加最大事件数
                }
            }
			else //检测到new_fd
			{
				pthread_t child_thread;
				pthread_attr_t child_thread_attr;
				pthread_attr_init(&child_thread_attr);
				pthread_attr_setdetachstate(&child_thread_attr,PTHREAD_CREATE_DETACHED);//设置线程属性为分离线程
				if( pthread_create(&child_thread,&child_thread_attr,talk_to_client, (void *)events[i].data.fd) < 0 )
					printf("pthread_create Failed : %s\n",strerror(errno));
#if 0				
                ret = handle_message(events[n].data.fd);
                if (ret < 1 && errno != 11) //11即EAGAIN
				{
                    if(epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd,&ev) < 0)
             		{
             			fprintf(stderr, "把 socket '%d' 从 epoll 删除失败！%s\n",events[n].data.fd, strerror(errno));
             		}
                    curfds--;
      				close(events[n].data.fd);
                }
#endif
            }
        }
	}      
    close(sockfd); //关闭监听用的socket
   return 0;
}

void * talk_to_client(void *new_fd)
{
       int new_server_socket = (int)new_fd;
	   pthread_mutex_lock(&mymutex); 
       //从客户端读取socket通信的字符数组，存放于缓冲区buffer中
       bzero(buffer, BUFFER_SIZE);
	   //DebugString("before read!");
	   int iReadBytes=readfrom(new_server_socket,buffer);
       #if 1
       switch(buffer[0])
       	{
			case '/':processStream();break;
			case '*':processStruct();break;
			default:illegal();break;
       	}
         int iWriteBytes=writeto(new_server_socket ,buffer);
        //int iWriteBytes=myWrite(new_server_socket ,buffer,BUFFER_SIZE);
		//Debug("after write:%d \tiWriteBytes:%d",new_server_socket,iWriteBytes);
		//if (iWriteBytes< 1 && errno != EAGAIN) 
		{   Debug("close socket :%d \tiWriteBytes:%d",new_server_socket,iWriteBytes);
#if 0
			if(epoll_ctl(kdpfd, EPOLL_CTL_DEL,new_server_socket,&ev) < 0)
	        {
	             fprintf(stderr, "delete socket '%d' from epoll  failed:%s\n",new_server_socket,strerror(errno));
	        }
#endif	        	
		    close(new_server_socket);//关闭绑定套接字
		}
		#endif
	    pthread_mutex_unlock(&mymutex);
	    pthread_exit(NULL);
}


/***************************************************************************************
* Function Name :  Prepare
*
* Description   :  命令行程序使用方法，设置服务器端口号
*
* Date          :  2012－9－10
*
* Parameter     : argc:命令行参数个数;argv:命令行参数列表
*
* Return Code   : 无//监听sockfd描述符 
* Author        : 张龙德 
****************************************************************************************/
void  Prepare (int argc, char *argv[])
{
    int portnumber;                  //端口号
     //验证输入参数个数
	if(argc!=4) //运行服务器端程序需要两个命令行参数，1是可执行程序名字，2是端口号
	{ 
	  if(argc==1||argc==2||argc==3)//设置默认端口号
	  {
	     portnumber=DEFAULT_PORT;
		 strcpy(connStr,Default_DATABASE);
		 strcpy(acBackupDBDir,acDBDir);
	 	 printf("Set default_port_number:%d \nDefault_database:%s\n",portnumber,Default_DATABASE); 
	  }
	  else//参数错误
	  {
        fprintf(stderr,"Usage:%s portnumber\n",argv[0]);
	 	exit(EXIT_FAILURE);
	  }
	} 
    else
    {
		//验证端口号正确性
		if((portnumber=atoi(argv[1]))<0) 
		{ 
	  		fprintf(stderr,"Usage:%s portnumber\n",argv[0]);
	   		exit(EXIT_FAILURE);
	     } 
		strcpy(connStr,argv[2]);
		strcpy(acBackupDBDir,argv[3]);
		Debug("Set port_number:%d\ndatabase:%s\nacBackupDBDir:%s",portnumber,connStr,acBackupDBDir); 
    }
	/* 设置允许打开的最大文件数 */
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
	{
        perror("setrlimit");
		//exit(EXIT_FAILURE);
    }
	/* 服务器端开始建立socket描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{ 
          fprintf(stderr,"Socket error:%s\n",strerror(errno));
          exit(EXIT_FAILURE);
	}
	/*设置socket属性，端口可以重用*/
    int opt=SO_REUSEADDR;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    /*设置socket为非阻塞模式*/
	setSockNonBlock(sockfd);
	
	/* 服务器端填充 sockaddr结构 */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); 
    server_addr.sin_family=AF_INET; 	      
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
    server_addr.sin_port=htons(portnumber); 
	/* 捆绑sockfd描述符 */
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{      
	  fprintf(stderr,"Bind error:%s\n",strerror(errno)); 
	  exit(EXIT_FAILURE);
	}
	/* 监听sockfd描述符 */ 
	if(listen(sockfd,SOCKET_QUEUE_NUM)==-1) 
	{    
	  fprintf(stderr,"Listen error:%s\n",strerror(errno)); 
	  exit(EXIT_FAILURE);
	} 
}




