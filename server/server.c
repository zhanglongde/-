/*************************************************************************************
              
*FileName:       server.c                                                  
*Description:    ������������
*Date:           2012-04-07
*Author:         ������     
*Revisor:        ������

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


#define DEFAULT_PORT        2013    //Ĭ�϶˿�
#define  SOCKET_QUEUE_NUM   20
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

char  temp[TEMP_SIZE];          //��ʱ�洢�ռ�
char  buffer[BUFFER_SIZE];      //����������Ϊ1024�ֽڵĴ�С
char  *head;                    //socketͨ��ͷ����־��Ϣ

/************����socket�����ݽṹ******************/
int sockfd;                       //�����׽���
struct sockaddr_in server_addr;   //�������׽���
struct sockaddr_in client_addr;  //�ͻ����׽���
/*************************************************/

void Prepare (int argc, char *argv[]);
void * talk_to_client(void *new_fd)
{
       int new_server_socket = (int)new_fd;
	   pthread_mutex_lock(&mymutex); 
       //�ӿͻ��˶�ȡsocketͨ�ŵ��ַ����飬����ڻ�����buffer��
       bzero(buffer, BUFFER_SIZE);
       readfrom(new_server_socket,buffer);
       printf("string received from client:%s\n",buffer);
       //��ȡsocketͨ��ͷ����Ϣ 
       memset(temp,0,sizeof(temp));
       strcpy(temp,buffer);
	   head=parseHead(temp);
       //����ͷ����Ϣִ�����Ӧ�Ĳ���
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
        //���������ݿ�֮��Ľ�������ظ��ͻ���
        writeto(new_server_socket ,buffer);
		pthread_mutex_unlock(&mymutex);
	    close(new_server_socket);//�رհ��׽���
	    pthread_exit(NULL);
}

/*************************************************************************************/
/*              main����                                                                      */
/*              �βΣ�������������Ų������ַ�������                                             */
/*              �زΣ�1                                                               */
/************************************************************************************/
int main(int argc, char *argv[]) 
{    
 	//�����ͻ�������֮ǰ��׼������
	Prepare (argc, argv);
	while(1)//��������Ҫһֱ���� 
	{  
	   #if 0
       DisplayCurTime();
	   #endif
       socklen_t sin_size;              //�׽��ֳ���
	   sin_size=sizeof(struct sockaddr_in);//��ü����׽��ֵĳ���
	   //����һ����server_socket�����socket��һ������
        //���û����������,�͵ȴ�������������--����accept����������
        //accept��������һ���µ�socket,���socket(new_server_socket)����ͬ���ӵ��Ŀͻ���ͨ��
        //new_server_socket�����˷������Ϳͻ���֮���һ��ͨ��ͨ��
        //accept���������ӵ��Ŀͻ�����Ϣ��д���ͻ��˵�socket��ַ�ṹclient_addr��
       int new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size);                       //���׽���
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
        	pthread_attr_setdetachstate(&child_thread_attr,PTHREAD_CREATE_DETACHED);//�����߳�����Ϊ�����߳�
        	if( pthread_create(&child_thread,&child_thread_attr,talk_to_client, (void *)new_fd) < 0 )
            	printf("pthread_create Failed : %s\n",strerror(errno));
	   }
	   #if 0
	   //��ӡ���ӵ����������������ַ
	   fprintf(stdout,"Server get connection from %s\n", (char *)inet_ntoa(client_addr.sin_addr));
       #endif
	}      
    close(sockfd); //�رռ����õ�socket
   return 0;
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
	if(argc!=2) //���з������˳�����Ҫ���������в�����1�ǿ�ִ�г������֣�2�Ƕ˿ں�
	{ 
	  fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
	  exit(1); 
	} 
	//��֤�˿ں���ȷ��
	if((portnumber=atoi(argv[1]))<0) 
	{ 
	   fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
	   exit(1); 
	} 
	/* �������˿�ʼ����socket������ */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{ 
          fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
          exit(1); 
	}
	/* ����������� sockaddr�ṹ */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); 
        server_addr.sin_family=AF_INET; 	      
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
        server_addr.sin_port=htons(portnumber); 
	/* ����sockfd������ */
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{      
	  fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
	  exit(1); 
	}
	/* ����sockfd������ */ 
	if(listen(sockfd,SOCKET_QUEUE_NUM)==-1) 
	{    
	  fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
	  exit(1); 
	} 
}



