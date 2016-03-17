#ifndef COMMONDATA_H
#define COMMONDATA_H
#define BUFFER_SIZE  1024*3
#define TEMP_SIZE    1024*3

#define  DEFAULT_PORT    1664    //Ĭ�϶˿�
#define  Default_DATABASE "qm.db"  //Ĭ�����ݿ�
#define  Default_BACKUP_DATABASE "./db/backupDB"  //Ĭ�ϱ������ݿ�
#define  SOCKET_QUEUE_NUM   20   //Listen�Ķ��г���
#define  EPOLL_MAXEVENTS 64	    //epoll_wait����෵�ص�events����
#define  EPOLL_TIMEOUT   5000    //epoll_wait��timeout milliseconds
#define  MAXEPOLLSIZE 10000

/*************************************************************************************/
/*              ȫ�ֱ�������                                                                   */
/*************************************************************************************/
extern char   temp[TEMP_SIZE];//��ʱ�洢�ռ�
extern char   buffer[BUFFER_SIZE];//����������Ϊ1024�ֽڵĴ�С
extern char * head;//socketͨ��ͷ����־��Ϣ

/*************************************************************************************/
/*              �ꡢ���Ͷ���                                                                   */
/************************************************************************************/
struct user//employee�ṹ��
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

