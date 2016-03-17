#include <stdlib.h> 
#include <stdio.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include "commonData.h"
#include "Debug.h"

/*
read�����Ǹ����fd�ж�ȡ����.�����ɹ�ʱ��read����ʵ���������ֽ�����������ص�ֵ��0��ʾ�Ѿ������ļ��Ľ����ˣ�
С��0��ʾ�����˴����������ΪEINTR˵���������ж�����ģ������ECONNREST��ʾ�������ӳ������⡣

write������buf�е�nbytes�ֽ�����д���ļ�������fd.�ɹ�ʱ����д���ֽ�����ʧ��ʱ����-1��������errno������
����������У����������׽����ļ�������дʱ�����ֿ��ܡ�
1)write�ķ���ֵ����0����ʾд�˲��ֻ�����ȫ�������ݡ�
2)���ص�ֵС��0����ʱ�����˴�������Ҫ���ݴ�������������
�������ΪEINTR��ʾ��д��ʱ��������жϴ������ΪEPIPE��ʾ�������ӳ���������(�Է��Ѿ��ر�������)��

*/

/*************************************************************************************/
/*              ͨ��socket���ӿͻ��˶�ȡ1024�ֽ����ݣ�����ڻ�����buffer��                     */
/*              �βΣ�socket��־����������buffer                                        */
/*              �زΣ�                                                                       */
/*************************************************************************************/
int readfrom(int new_fd,char * buffer)
{
	int iBytes=read(new_fd,buffer,BUFFER_SIZE);
	if(iBytes==-1) 
	{ 
		fprintf(stderr,"Read Error:%s\n",strerror(errno)); 
	}
	else
	{
		 printf("string received from client:%s\n",buffer);
	}
	Debug("iBytes=%d",iBytes);
    if(buffer[iBytes-1]=='\n')
    {
   		buffer[iBytes-1]='\0';
    }//android
    else buffer[iBytes]='\0';   //linux
    return iBytes;
}

/*************************************************************************************/
/*              ͨ��socket���ӻ�����buffer�ж�ȡ1024�ֽ����ݣ������ͻ���                       */
/*              �βΣ�socket��־����������buffer                                        */
/*              �زΣ�                                                                      */
/*************************************************************************************/
int writeto(int new_fd ,char * buffer)
{
    //sleep(5);
    int iBytes=write(new_fd,buffer,BUFFER_SIZE);
	if(iBytes==-1) 
	{ 
		fprintf(stderr,"Write Error:%s\n",strerror(errno)); 
	}
	else
	{
		printf("string sended to client is:%s\n",buffer);
	}
	return iBytes;
} 

int myRead(int fd, void *sp, size_t size_len)
{    
	int readlen = 0;    
	int rn = 0;    
	while (readlen < size_len)    
	{   printf("%d,%d\n",readlen,rn);    
		rn = read(fd, sp + readlen, size_len - readlen); 
		printf("2222%d,%d\n",readlen,rn); 
		if (rn < 0)        
		{            
			if (errno == EAGAIN || errno == EINTR)   //��������˷�����������errno ΪEAGAIN������������������ж�Ҳ������            
			{                
				continue;            
			}           
			else            
			{                
				return -1;  //����          
			}        
		}        
		else if (rn < size_len)   //���˲��֣�������     
		{   
			if (rn == 0)            
			{                //no data                
				return readlen;            
			}            
			readlen += rn;        
		}        
		else        
		{            
			readlen = rn;        
		}   
	}    
	return readlen;
}

int myWrite(int fd, void *sp, size_t size_len)
{    
	int sendlen = 0;    
	int sn = 0;    
	while (sendlen < size_len)    
	{        
		sn = write(fd, sp + sendlen, size_len - sendlen);        
		if (sn < 0)        
		{            
			if (errno == EAGAIN || errno == EINTR)   //��������˷�����������errno ΪEAGAIN������д����������ж�Ҳ����д            
			{               
				continue;            
			}            
			else            
			{                
				return -1;            
			}       
		}else if (sn < size_len)  //д�˲��֣�����д      
		{            
			sendlen += sn;        
		}        
		else        
		{            
			sendlen = sn;        
		}    
	}   
	return sendlen;
}

int Socket(int domain, int type)
{        
	int sockfd = 0;        
	sockfd = socket(domain, type, 0);        
	if (sockfd < 0)         
	{                 
		return -1;         
	}                   
	return sockfd;
}

int Bind(int sockfd, const struct sockaddr *net_addr, socklen_t addrlen)
{    
	if (!net_addr)    
	{           
		printf("when binding, net_addr is NULL\n");        
		return -1;     
	}       
	if (bind(sockfd, net_addr, addrlen) < 0)    
	{           
		printf("fail to bind ipaddr\n");       
		return -1;     
	}       
	return 0;
}


int Listen(int sockfd, int listenNum)
{    
	if (listen(sockfd, listenNum) < 0)    
	{        
		printf("fail to listen socket\n");        
		return -1;    
	}    
	return 0;
}

void setSockNonBlock(int sock) 
{
   int flags;
   flags = fcntl(sock, F_GETFL, 0);
   if (flags < 0) 
   	{
	   perror("fcntl(F_GETFL) failed");
	   exit(EXIT_FAILURE);
   }
   if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) 
   	{
	   perror("fcntl(F_SETFL) failed");
	   exit(EXIT_FAILURE);
   }
}
