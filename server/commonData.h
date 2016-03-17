#ifndef COMMONDATA_H
#define COMMONDATA_H
#define BUFFER_SIZE  1024*3
#define TEMP_SIZE    1024*3

#define  DEFAULT_PORT    1664    //默认端口
#define  Default_DATABASE "qm.db"  //默认数据库
#define  Default_BACKUP_DATABASE "./db/backupDB"  //默认备份数据库
#define  SOCKET_QUEUE_NUM   20   //Listen的队列长度
#define  EPOLL_MAXEVENTS 64	    //epoll_wait的最多返回的events个数
#define  EPOLL_TIMEOUT   5000    //epoll_wait的timeout milliseconds
#define  MAXEPOLLSIZE 10000

/*************************************************************************************/
/*              全局变量定义                                                                   */
/*************************************************************************************/
extern char   temp[TEMP_SIZE];//临时存储空间
extern char   buffer[BUFFER_SIZE];//缓冲区定义为1024字节的大小
extern char * head;//socket通信头部标志信息

/*************************************************************************************/
/*              宏、类型定义                                                                   */
/************************************************************************************/
struct user//employee结构体
{
	char *name;
	char *pwd;
	char *position;
	char *plantNo;
	char *workTypeNo;
}User;


typedef struct employee
{
    char acHeader[4];
	int  iEmployeeNo;
	char acName[20];
	char acPwd[10];
	int  iPosition;
	int  iPlantNo;
	int  iworkTypeNo;
	int  iflag;
}Employee;


#endif

