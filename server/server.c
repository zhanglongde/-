/*************************************************************************************
              
*FileName:       server.c                                                  
*Description:    服务器主程序
*Date:           2012-04-07
*Author:         张龙德     
*Revisor:        张龙德

*************************************************************************************/
#include <stdlib.h> 
#include <sqlite3.h>
#include <stdio.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "commonData.h"
#include "parseString.h"
#include "mySocket.h"
#include "sqlite3Helper.h"
#include "process.h"
#include "threadpool.h"
#include "Debug.h"


#define DEFAULT_PORT        2013    //默认端口
#define  SOCKET_QUEUE_NUM   20
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

char  temp[TEMP_SIZE];          //临时存储空间
char  buffer[BUFFER_SIZE];      //缓冲区定义为1024字节的大小
char  *head;                    //socket通信头部标志信息

/************建立socket的数据结构******************/
int sockfd;                       //监听套接字
struct sockaddr_in server_addr;   //服务器套接字
struct sockaddr_in client_addr;  //客户端套接字
/*************************************************/

void Prepare (int argc, char *argv[]);
void * talk_to_client(void *new_fd)
{
       int new_server_socket = (int)new_fd;
	   pthread_mutex_lock(&mymutex); 
       //从客户端读取socket通信的字符数组，存放于缓冲区buffer中
       bzero(buffer, BUFFER_SIZE);
       readfrom(new_server_socket,buffer);
       printf("string received from client:%s\n",buffer);
       //截取socket通信头部信息 
       memset(temp,0,sizeof(temp));
       strcpy(temp,buffer);
	   head=parseHead(temp);
       //根据头部信息执行相对应的操作
	   switch(head[2])
        {       
		  	case 'l':cl();break;//"/cl"
          	case 'r':cr();break;//"/cr"
          	case 'q':cq();break;//"/cq"
			case 'p':cp();break;//"/cp"
			case 'c':cc();break;//"/cc"
			case 'o':co();break;//"/co"
			case 'd':cd();break;//"/cd"
			case 'u':cu();break;//"/cu"
			case 'e':ce();break;//"/ce"
        	case 'w':cw();break;//"cw"
        	case 'i':ci();break;//"ci"
			case 'g':cg();break;//"cg"
			case 't':ct();break;//"ct"
        	default:illegal();break;
        } 
        //将操作数据库之后的结果，返回给客户端
        writeto(new_server_socket ,buffer);
		pthread_mutex_unlock(&mymutex);
	    close(new_server_socket);//关闭绑定套接字
	    pthread_exit(NULL);
}

/*************************************************************************************/
/*              main函数                                                                      */
/*              形参：参数个数，存放参数的字符串数组                                             */
/*              回参：1                                                               */
/************************************************************************************/
int main(int argc, char *argv[]) 
{    
 	//建立客户端连接之前的准备工作
	Prepare (argc, argv);
	while(1)//服务器端要一直运行 
	{  
	   #if 0
       DisplayCurTime();
	   #endif
       socklen_t sin_size;              //套接字长度
	   sin_size=sizeof(struct sockaddr_in);//获得监听套接字的长度
	   //接受一个到server_socket代表的socket的一个连接
        //如果没有连接请求,就等待到有连接请求--这是accept函数的特性
        //accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
        //new_server_socket代表了服务器和客户端之间的一个通信通道
        //accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中
       int new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size);                       //绑定套接字
	   if(new_fd<0) 
	   { 
	     	fprintf(stderr,"Accept error:%s\n",strerror(errno)); 
	     	break; 
	   } 
	   else
	   {
          	pthread_t child_thread;
        	pthread_attr_t child_thread_attr;
        	pthread_attr_init(&child_thread_attr);
        	pthread_attr_setdetachstate(&child_thread_attr,PTHREAD_CREATE_DETACHED);//设置线程属性为分离线程
        	if( pthread_create(&child_thread,&child_thread_attr,talk_to_client, (void *)new_fd) < 0 )
            	printf("pthread_create Failed : %s\n",strerror(errno));
	   }
	   #if 0
	   //打印连接到本服务器的网络地址
	   fprintf(stdout,"Server get connection from %s\n", (char *)inet_ntoa(client_addr.sin_addr));
       #endif
	}      
    close(sockfd); //关闭监听用的socket
   return 0;
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
	if(argc!=2) //运行服务器端程序需要两个命令行参数，1是可执行程序名字，2是端口号
	{ 
	  fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
	  exit(1); 
	} 
	//验证端口号正确性
	if((portnumber=atoi(argv[1]))<0) 
	{ 
	   fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
	   exit(1); 
	} 
	/* 服务器端开始建立socket描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{ 
          fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
          exit(1); 
	}
	/* 服务器端填充 sockaddr结构 */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); 
        server_addr.sin_family=AF_INET; 	      
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
        server_addr.sin_port=htons(portnumber); 
	/* 捆绑sockfd描述符 */
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{      
	  fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
	  exit(1); 
	}
	/* 监听sockfd描述符 */ 
	if(listen(sockfd,SOCKET_QUEUE_NUM)==-1) 
	{    
	  fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
	  exit(1); 
	} 
}



