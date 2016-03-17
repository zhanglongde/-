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
read函数是负责从fd中读取内容.当读成功时，read返回实际所读的字节数，如果返回的值是0表示已经读到文件的结束了，
小于0表示出现了错误。如果错误为EINTR说明读是由中断引起的，如果是ECONNREST表示网络连接出了问题。

write函数将buf中的nbytes字节内容写入文件描述符fd.成功时返回写的字节数。失败时返回-1，并设置errno变量。
在网络程序中，当我们向套接字文件描述符写时有俩种可能。
1)write的返回值大于0，表示写了部分或者是全部的数据。
2)返回的值小于0，此时出现了错误。我们要根据错误类型来处理。
如果错误为EINTR表示在写的时候出现了中断错误。如果为EPIPE表示网络连接出现了问题(对方已经关闭了连接)。

*/

/*************************************************************************************/
/*              通过socket，从客户端读取1024字节数据，存放于缓冲区buffer中                     */
/*              形参：socket标志符，缓冲区buffer                                        */
/*              回参：                                                                       */
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
/*              通过socket，从缓冲区buffer中读取1024字节数据，传给客户端                       */
/*              形参：socket标志符，缓冲区buffer                                        */
/*              回参：                                                                      */
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
			if (errno == EAGAIN || errno == EINTR)   //如果设置了非阻塞，返回errno 为EAGAIN，继续读；如果遇到中断也继续读            
			{                
				continue;            
			}           
			else            
			{                
				return -1;  //出错          
			}        
		}        
		else if (rn < size_len)   //读了部分，继续读     
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
			if (errno == EAGAIN || errno == EINTR)   //如果设置了非阻塞，返回errno 为EAGAIN，继续写；如果遇到中断也继续写            
			{               
				continue;            
			}            
			else            
			{                
				return -1;            
			}       
		}else if (sn < size_len)  //写了部分，继续写      
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
