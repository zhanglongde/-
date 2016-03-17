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

int parseCount(char *);//默认空格字符，分析参数个数
int getCount(char *,char);//根据分割字符，分析参数个数
char * parseHead(char *);//默认空格字符，截取socket通信字符数组的头部信息
char * getHead(char * ,char );//根据分割字符，截取socket通信字符数组的头部信息
char * skip(char * ,int );
void rever(char s[]);

#endif

