#ifndef PARSESTRINF_H
#define PARSESTRINF_H

#include <stdlib.h> 
#include <sqlite3.h>
#include <stdio.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>

int parseCount(char *);//Ĭ�Ͽո��ַ���������������
int getCount(char *,char);//���ݷָ��ַ���������������
char * parseHead(char *);//Ĭ�Ͽո��ַ�����ȡsocketͨ���ַ������ͷ����Ϣ
char * getHead(char * ,char );//���ݷָ��ַ�����ȡsocketͨ���ַ������ͷ����Ϣ
char * skip(char * ,int );
void rever(char s[]);

#endif

