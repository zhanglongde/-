/*************************************************************************************
              
*FileName:       mtmserver.c                                                  
*Description:    ������������
*Date:             2012-04-07
*Author:          ������     
*Revisor:         ������

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

pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;  //������
char  temp[TEMP_SIZE];          //��ʱ�洢�ռ�
char  buffer[BUFFER_SIZE];      //����������Ϊ1024�ֽڵĴ�С
char  *head;                    //socketͨ��ͷ����־��Ϣ

int kdpfd, curfds;
int nfds;                         
socklen_t sin_size; 			 //�׽��ֳ���
struct epoll_event ev;
struct epoll_event events[MAXEPOLLSIZE];

char connStr[CONNSTR_LEN]={"./db/qm.db"};//���ӵ����ݿ�����
char acDBDir[CONNSTR_LEN]={"./db"};
char acBackupDBDir[CONNSTR_LEN]={"./db/backupDB"};//���ӵ����ݿ�����

/************����socket�����ݽṹ******************/
int sockfd;                       //�����׽���
                      //���׽���
struct sockaddr_in server_addr;   //�������׽���
struct sockaddr_in client_addr;  //�ͻ����׽���
struct rlimit rt;//��Դ����
/*************************************************/

void Prepare (int argc, char *argv[]);
void * talk_to_client(void *new_fd);
int main(int argc, char *argv[]) 
{  
	DisplayCurTime();
    int i=0;//����ѭ����
 	//�����ͻ�������֮ǰ��׼������
	Prepare (argc, argv);
	/* ���� epoll ������Ѽ��� socket ���뵽 epoll ������ */
    kdpfd = epoll_create(MAXEPOLLSIZE);
	sin_size=sizeof(struct sockaddr_in);//��ü����׽��ֵĳ���
    ev.events = EPOLLIN|EPOLLET;;//��Ӧ���ļ��������ɶ������¼�����
    ev.data.fd = sockfd;
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) 
	{
        fprintf(stderr, "epoll set insertion error: fd=%d\n", sockfd);
        exit(EXIT_FAILURE);
    } 
	Debug("kdpfd:%d\t listenning socket number:%d\n",kdpfd,sockfd);
    //curfds = 1;//����¼���
	while(1)//��������Ҫһֱ���� 
	{  
	   #if 0
       DisplayCurTime();
	   #endif
	     /* �ȴ����¼����� */
	   /*ÿ��ѭ����������epoll_wait����*/
        nfds = epoll_wait(kdpfd, events, EPOLL_MAXEVENTS, EPOLL_TIMEOUT);//-1�����Ƶȴ�
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
        /* ���������¼� */
        for (i = 0; i < nfds; ++i) 
		{
            if (events[i].data.fd == sockfd) // ����¼�⵽һ��HTTP�û����ӵ��󶨵�HTTP�˿����������ӡ�
			{  
                int new_fd=accept(sockfd, (struct sockaddr *) &client_addr,&sin_size);
				if (new_fd < 0) 
				{
                    fprintf(stderr,"Accept error:%s\n",strerror(errno)); 
                    continue;
                    #if 0
                    if ( (errno == EAGAIN) || (errno == EWOULDBLOCK) ) 
					{
						 //non-blockingģʽ������connection��������while (1)
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
					//��ӡ���ӵ����������������ַ
					fprintf(stdout,"Server get connection from %s\n", (char *)inet_ntoa(client_addr.sin_addr));
	                setSockNonBlock(new_fd);
	                ev.events = EPOLLIN | EPOLLET;
	                ev.data.fd = new_fd;
	                if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_fd, &ev) < 0) 
					{   
	                    fprintf(stderr, "Add  socket '%d' to epoll failed��%s\n",new_fd, strerror(errno));
	                    exit(EXIT_FAILURE);
	                }
	                //curfds++;//�ۼ�����¼���
                }
            }
			else //��⵽new_fd
			{
				pthread_t child_thread;
				pthread_attr_t child_thread_attr;
				pthread_attr_init(&child_thread_attr);
				pthread_attr_setdetachstate(&child_thread_attr,PTHREAD_CREATE_DETACHED);//�����߳�����Ϊ�����߳�
				if( pthread_create(&child_thread,&child_thread_attr,talk_to_client, (void *)events[i].data.fd) < 0 )
					printf("pthread_create Failed : %s\n",strerror(errno));
#if 0				
                ret = handle_message(events[n].data.fd);
                if (ret < 1 && errno != 11) //11��EAGAIN
				{
                    if(epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd,&ev) < 0)
             		{
             			fprintf(stderr, "�� socket '%d' �� epoll ɾ��ʧ�ܣ�%s\n",events[n].data.fd, strerror(errno));
             		}
                    curfds--;
      				close(events[n].data.fd);
                }
#endif
            }
        }
	}      
    close(sockfd); //�رռ����õ�socket
   return 0;
}

void * talk_to_client(void *new_fd)
{
       int new_server_socket = (int)new_fd;
	   pthread_mutex_lock(&mymutex); 
       //�ӿͻ��˶�ȡsocketͨ�ŵ��ַ����飬����ڻ�����buffer��
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
		    close(new_server_socket);//�رհ��׽���
		}
		#endif
	    pthread_mutex_unlock(&mymutex);
	    pthread_exit(NULL);
}


/***************************************************************************************
* Function Name :  Prepare
*
* Description   :  �����г���ʹ�÷��������÷������˿ں�
*
* Date          :  2012��9��10
*
* Parameter     : argc:�����в�������;argv:�����в����б�
*
* Return Code   : ��//����sockfd������ 
* Author        : ������ 
****************************************************************************************/
void  Prepare (int argc, char *argv[])
{
    int portnumber;                  //�˿ں�
     //��֤�����������
	if(argc!=4) //���з������˳�����Ҫ���������в�����1�ǿ�ִ�г������֣�2�Ƕ˿ں�
	{ 
	  if(argc==1||argc==2||argc==3)//����Ĭ�϶˿ں�
	  {
	     portnumber=DEFAULT_PORT;
		 strcpy(connStr,Default_DATABASE);
		 strcpy(acBackupDBDir,acDBDir);
	 	 printf("Set default_port_number:%d \nDefault_database:%s\n",portnumber,Default_DATABASE); 
	  }
	  else//��������
	  {
        fprintf(stderr,"Usage:%s portnumber\n",argv[0]);
	 	exit(EXIT_FAILURE);
	  }
	} 
    else
    {
		//��֤�˿ں���ȷ��
		if((portnumber=atoi(argv[1]))<0) 
		{ 
	  		fprintf(stderr,"Usage:%s portnumber\n",argv[0]);
	   		exit(EXIT_FAILURE);
	     } 
		strcpy(connStr,argv[2]);
		strcpy(acBackupDBDir,argv[3]);
		Debug("Set port_number:%d\ndatabase:%s\nacBackupDBDir:%s",portnumber,connStr,acBackupDBDir); 
    }
	/* ��������򿪵�����ļ��� */
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
	{
        perror("setrlimit");
		//exit(EXIT_FAILURE);
    }
	/* �������˿�ʼ����socket������ */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{ 
          fprintf(stderr,"Socket error:%s\n",strerror(errno));
          exit(EXIT_FAILURE);
	}
	/*����socket���ԣ��˿ڿ�������*/
    int opt=SO_REUSEADDR;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    /*����socketΪ������ģʽ*/
	setSockNonBlock(sockfd);
	
	/* ����������� sockaddr�ṹ */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); 
    server_addr.sin_family=AF_INET; 	      
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
    server_addr.sin_port=htons(portnumber); 
	/* ����sockfd������ */
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{      
	  fprintf(stderr,"Bind error:%s\n",strerror(errno)); 
	  exit(EXIT_FAILURE);
	}
	/* ����sockfd������ */ 
	if(listen(sockfd,SOCKET_QUEUE_NUM)==-1) 
	{    
	  fprintf(stderr,"Listen error:%s\n",strerror(errno)); 
	  exit(EXIT_FAILURE);
	} 
}




