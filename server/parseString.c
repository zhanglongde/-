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
/*              ��ȡsocketͨ���ַ������ͷ����Ϣ                                                */
/*              �βΣ����Կͻ����ַ�����ָ��                                                     */
/*              �زΣ�ͷ���ַ�����ָ��                                                           */
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
/*              ��ȡsocketͨ���ַ������ͷ����Ϣ                                                */
/*              �βΣ����Կͻ����ַ�����ָ��  ,�ָ��ַ�                                          */
/*              �زΣ�ͷ���ַ�����ָ��                                                           */
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
/*              ����socketͨ���ַ�����Ĳ�������                                               */
/*              �βΣ����Կͻ����ַ�����ָ��                                                    */
/*              �زΣ����Կͻ����ַ�����Ĳ�������                                               */
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
/*              �����ͱ���ת��Ϊ�ַ�����                                                         */
/*              �βΣ����ͱ�����ֵ�����ת���ɹ�����ַ�����                                      */
/*              �زΣ���                                                                       */
/*************************************************************************************/
void itoa(int n, char *s){ 
  int m=0,k=n;
  while(k>0) 
  {
  m++;
  k=k/10;
  }
//�ֽ����������ַ���  
  s[m]='\0';
  while(n>0)
  {
   s[m-1]=n%10+'0';;//��ȡ�������λ����ת��Ϊ������Ӧ������
   m--;
   n=n/10;
  }
}

