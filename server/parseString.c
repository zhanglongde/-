#include <stdlib.h> 
#include <sqlite3.h>
#include <stdio.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include "parseString.h"


/*************************************************************************************/
/*              截取socket通信字符数组的头部信息                                                */
/*              形参：来自客户端字符数组指针                                                     */
/*              回参：头部字符数组指针                                                           */
/*************************************************************************************/
char * parseHead(char * buf)
{
	char * t=buf;
	int i=0;
	 if(strchr(t,' ')==NULL){return t;}else{t=buf;}
	 while(*buf!=' ')
	{
	  i++;
	  buf++;
	}
	t[i]='\0';
	return t;
}
/*************************************************************************************/
/*              截取socket通信字符数组的头部信息                                                */
/*              形参：来自客户端字符数组指针  ,分割字符                                          */
/*              回参：头部字符数组指针                                                           */
/*************************************************************************************/
char * getHead(char * buf,char c)
{
	char * t=buf;
	int i=0;
	 if(strchr(t,c)==NULL){return t;}else{t=buf;}
	 while(*buf!=c)
	{
	  i++;
	  buf++;
	}
	t[i]='\0';
	return t;
}
/*************************************************************************************/
/*              分析socket通信字符数组的参数个数                                               */
/*              形参：来自客户端字符数组指针                                                    */
/*              回参：来自客户端字符数组的参数个数                                               */
/*************************************************************************************/
  int parseCount(char * buf)
{
	int count=0;
	while(*buf!='\0')
	{
		if((*buf==' ')&&(*(buf+1)!='\0')) count++;
		buf++;
	}
	return count;
}

  int getCount(char * buf,char c)
{
	int count=0;
	while(*buf!='\0')
	{
		if((*buf==c)&&(*(buf+1)!='\0')) count++;
		buf++;
	}
	return count+1;
}

char *skip(char * buf,int n)
{
	int m;
	for(m=0;m<n;m++)
	{//skip n ' 's;
	while(*buf!=' ')
	{
		if((*buf=='\0'))
		return "Can not find related parameter";
		buf++;            
	}
	buf++;
  }
  return buf;
}

/*************************************************************************************/
/*              将整型变量转化为字符数组                                                         */
/*              形参：整型变量数值，存放转化成功后的字符数组                                      */
/*              回参：无                                                                       */
/*************************************************************************************/
void itoa(int n, char *s){ 
  int m=0,k=n;
  while(k>0) 
  {
  m++;
  k=k/10;
  }
//分解生成逆序字符串  
  s[m]='\0';
  while(n>0)
  {
   s[m-1]=n%10+'0';;//将取出的最低位整数转化为其所对应的数组
   m--;
   n=n/10;
  }
}

