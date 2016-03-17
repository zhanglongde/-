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
#include <unistd.h>
#include "sqlite3Helper.h"
#include "commonData.h"
#include "Debug.h"

#define SQL_SIZE  400
#define RATE_LEN 100
#define CONCRETE_LEN 100
#define ORDER_LEN  60

char temp[TEMP_SIZE];          //��ʱ�洢�ռ�
char buffer[BUFFER_SIZE];     //����������Ϊ1024�ֽڵĴ�С

/*************************************************************************************
Function Name:    open_sqlite3
*Description:     ���������ݿ����ƣ������ݿ⣬�������ݿ�����  
*Parameter:       ��                                                                                   
*ReturnCode:      ���ݿ������ַ��� 
*Author:          ������
*Revisor:         ������
*Date:            2013-04-17
************************************************************************************/
sqlite3 * open_sqlite3()
{
	sqlite3 *conn = NULL;  
	if (SQLITE_OK != sqlite3_open(connStr, &conn))
	{
	    printf("can not open the database.\n");
	    return 0;
	}
	return conn;
}
sqlite3 * OpenMemorySqlite3()
{
	sqlite3 *memoryDb=NULL;  
	if (SQLITE_OK==loadOrSaveDb(memoryDb, connStr, 0)){
		return memoryDb;
	}
	else{
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////   
//����˵��:    
//pInMemory: ָ���ڴ����ݿ�ָ��   
//zFilename: ָ���ļ����ݿ�Ŀ¼���ַ���ָ��    
//isSave  0: ���ļ����ݿ����뵽�ڴ����ݿ� 1�����ڴ����ݿⱸ�ݵ��ļ����ݿ�   
////////////////////////////////////////////////////////////////////////////////////////////  
int loadOrSaveDb(sqlite3 *pInMemeory, const char *zFilename, int isSave)   
{   
         int rc;   
         sqlite3 *pFile;    
         sqlite3_backup *pBackup;    
         sqlite3 *pTo;    
         sqlite3 *pFrom;    
         rc = sqlite3_open(zFilename, &pFile);   
         if(rc == SQLITE_OK)   
         {  
                   pFrom = (isSave?pInMemeory:pFile);  
                   pTo = (isSave?pFile:pInMemeory);    
                   pBackup = sqlite3_backup_init(pTo,"main",pFrom,"main");    
                   if(pBackup)  
                   {  
                            (void)sqlite3_backup_step(pBackup,-1);  
                            (void)sqlite3_backup_finish(pBackup);  
                   }    
                   rc = sqlite3_errcode(pTo);    
         }   
         (void)sqlite3_close(pFile);   
         return rc;  
}  

int closeSqlite3(sqlite3 *conn)
{
    if(conn==NULL)
	{
		return -1;
		printf("close Sqlite3 error.\n");
    }
   sqlite3_close(conn);
   return 1;
}
int CloseMemorySqlite3(sqlite3 *memoryDb)
{
    if(memoryDb==NULL)
	{	
		printf("close Sqlite3 error.\n");
		return -1;
    }
   
   if(SQLITE_OK==loadOrSaveDb(memoryDb, connStr, 1))
   	{
		printf("close MemorySqlite3 error.\n");
   	}
   sqlite3_close(memoryDb);
   return 1;
}

int GetDBDir(char * pcDBDir)
{
   strcpy(pcDBDir,connStr);
   return 1;
}
int BackupDB(char * pcObjectDir)
{
     char acOrder[ORDER_LEN]={0};
	 if(access(pcObjectDir,F_OK)==-1)//������
	 {
	    sprintf(acOrder,"mkdir -pm 777 %s",pcObjectDir);
	 	if(system(acOrder)!=0){
		return 0;
	 		}
	 }
	 if((access(pcObjectDir,R_OK)==-1)&&(access(pcObjectDir,W_OK)==-1)&&(access(pcObjectDir,X_OK)==-1))
	 {//Ȩ�޲���
		return 0;
	 }
	 memset(acOrder,ORDER_LEN,0);
	 sprintf(acOrder,"cp %s %s",connStr,pcObjectDir);
	 // sqlite3 qm.db ".backup main test.db"
	 //Debug("acOrder:%s",acOrder);
	int iRet=system(acOrder);
	 if(iRet!=0){
	 	return 0;}
	 //Debug("iRet:%d",iRet);
	 return 1;
}
int GetRessByPositionNo(char * pcPositionNo)
{
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"*sr^");
	int result=1;int iRect=0;
	char sql[SQL_SIZE]={0};
	char * errmsg = NULL;
	char **dbResult; 	
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	sprintf(sql, "select resNo,name,resText from res,employee where employee.employeeNo=res.resMakerNo  and positionNo=%s;",pcPositionNo);
	Debug("sql:%s",sql);
	result = sqlite3_get_table( conn,sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{   Debug("result:%d",result);
		iRect=1;
		index = nColumn; 
		for(  i = 0; i < nRow ; i++ )
		{
		     for( j = 0 ; j < nColumn; j++ )
		     {
			   strcat(buffer,dbResult[index]);
			   if(j < nColumn-1){strcat(buffer,"~");}
			    ++index; 
				Debug("buffer:%s",buffer);
		     }
			 if(i<nRow-1)
		     strcat(buffer,"|");Debug("buffer:%s",buffer);
		}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return iRect;
}


//ɾ��һ��Ա��
int DeleteEmployee(char * pcUserName)
{
	sqlite3 *conn = open_sqlite3(); 
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
        //ע����Ϣֻ��Ա���š��û��������룬������ϢΪ�գ�����Ա����Ϊ����ֵ
	sprintf(sql, "delete from employee where name='%s';",pcUserName);
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg)){
	    printf("operate failed: %s\n", err_msg);
            return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn)){
	    printf("can not close the database: %s\n", sqlite3_errmsg(conn));
            return 0;
	}
	sqlite3_free(err_msg);
	return 1;
}
//�༭Ա����Ϣ
int UpdateEmployee(char *pcEmployeeNo,char * pcName, 
	char * pcPwd,int iPositionNo,int iPlantNo,int iWorkTypeNo)
{
	sqlite3 *conn = open_sqlite3(); 
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
        //ע����Ϣֻ��Ա���š��û��������룬������ϢΪ�գ�����Ա����Ϊ����ֵ
	sprintf(sql, "update employee set name='%s' , pwd='%s' , position=%d , plantNo=%d , workTypeNo=%d where employeeNo=%s;",
	pcName,pcPwd,iPositionNo,iPlantNo,iWorkTypeNo,pcEmployeeNo);
	Debug("sql:%s",sql);
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg)){
	    printf("operate failed: %s\n", err_msg);
            return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn)){
	    printf("can not close the database: %s\n", sqlite3_errmsg(conn));
            return 0;
	}
	sqlite3_free(err_msg);
	return 1;
}
int InsertEmployee(char *pcEmployeeNo,char * pcName, 
	char * pcPwd,int iPositionNo,int iPlantNo,int iWorkTypeNo)
{
    sqlite3 *conn = open_sqlite3(); 
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
		//ע����Ϣֻ��Ա���š��û��������룬������ϢΪ�գ�����Ա����Ϊ����ֵ
	sprintf(sql, "update employee set name='%s' , pwd='%s' , position=%d , plantNo=%d , workTypeNo=%d where employeeNo=%s;",
	pcName,pcPwd,iPositionNo,iPlantNo,iWorkTypeNo,pcEmployeeNo);
	Debug("sql:%s",sql);
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg)){
		printf("operate failed: %s\n", err_msg);
			return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn)){
		printf("can not close the database: %s\n", sqlite3_errmsg(conn));
			return 0;
	}
	sqlite3_free(err_msg);
	return 1;
}
int InsertRes(int iResMakerNo,char * pcResText, 
	char * pcPostion,int * piResNo)
{
    sqlite3 *conn = open_sqlite3(); 
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
		//ע����Ϣֻ��Ա���š��û��������룬������ϢΪ�գ�����Ա����Ϊ����ֵ
	sprintf(sql, "insert into res values(NULL,%d,'%s','%s');",
	iResMakerNo,pcResText,pcPostion);
	Debug("sql:%s",sql);
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg)){
		printf("operate failed: %s\n", err_msg);
			return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn)){
		printf("can not close the database: %s\n", sqlite3_errmsg(conn));
			return 0;
	}
	sqlite3_free(err_msg);
	int iResNo=sqlite3_last_insert_rowid(conn);
	Debug("iResNo:%d",iResNo);
	*piResNo=iResNo;
	closeSqlite3(conn);
	return 1;
}



int getEmployeeByNameAndPwd(Employee* pstEmployee)
{
	int iUserNum=0;
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char **dbResult; 
	int iRow=0, iColumn=0;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select count(*),* from employee where name='%s' and pwd='%s'",pstEmployee->acName,pstEmployee->acPwd);
	int iReturnVal = sqlite3_get_table( conn, sql, &dbResult, &iRow, &iColumn, &errmsg );
	if( SQLITE_OK == iReturnVal )
	{
		iUserNum=atoi(dbResult[iColumn]);
		if(iUserNum<1)
			return 0;
		else if(iUserNum==1)//������û������ݽṹ
		{
			pstEmployee->iEmployeeNo=atoi(dbResult[iColumn+1]);
		    strcpy(pstEmployee->acName,dbResult[iColumn+2]);
			strcpy(pstEmployee->acPwd,dbResult[iColumn+3]);
			pstEmployee->iPosition=atoi(dbResult[iColumn+4]);
			pstEmployee->iPlantNo=atoi(dbResult[iColumn+5]);
			pstEmployee->iworkTypeNo=atoi(dbResult[iColumn+6]);
			pstEmployee->iflag=1;//��¼�ɹ�
		}
		else
		{
			printf("Too many users\n");
			return 0;
		}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	closeSqlite3(conn);
	return 1;
}


/*************************************************************************************/
/*              �����β�ֵ����������ڳ��������Ա����Ϣ�����������ڻ�����buffer������          */
/*              �βΣ�Ʒ�ʹ���Ա���ڵĳ����                                                    */
/*              �زΣ���                                                                       */
/************************************************************************************/
/*dbResult ���ֶ�ֵ�������ģ��ӵ�0�������� nColumn - 1���������ֶ����ƣ��ӵ� nColumn ������ʼ��
  ���涼���ֶ�ֵ������һ����ά�ı���ͳ�����б�ʾ������һ����ƽ����ʽ����ʾ                         */
void getEmployeesByPlantNo(int plantNo)
{  
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"/se ");
	int result;
	char sql[SQL_SIZE]={0};
	char * errmsg = NULL;
	char **dbResult; 	//�� char ** ���ͣ�����*��
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	sprintf(sql, "select employeeNo,name,productName from employee left join  workType on employee.workTypeNo=workType.workTypeNo where plantNo='%d';",plantNo);
	result = sqlite3_get_table( conn,sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    // dbResult ǰ���һ���������ֶ����ƣ��� nColumn ������ʼ��������������
	index = nColumn; 
	
	if(nRow<=1)
		{
		strcat(buffer,"n");
		return ;
		}
	Debug("dbResult[nColumn]:%s",dbResult[nColumn]);
	for(  i = 0; i < nRow ; i++ )
	{
	     for( j = 0 ; j < nColumn; j++ )
	     {
		   //�ֶ���:dbResult[j]    �ֶ�ֵ:dbResult[index]
		   strcat(buffer,dbResult[index]);
		   if(j < nColumn-1){strcat(buffer,",");}
		    ++index; 
	     }
	     strcat(buffer,";");
	}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
}
void get_employee_table()
{  
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"*se ");
	int result;
	char sql[SQL_SIZE]={0};
	char * errmsg = NULL;
	char **dbResult; 	
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	sprintf(sql, "select employeeNo,name,pwd,positionName,plantName,productName from employee ,position,plant, workType where employee.workTypeNo=workType.workTypeNo and employee.employeeNo=plant.plantNo and employee.position=position.positionNo;");
	result = sqlite3_get_table( conn,sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    
	index = nColumn; 
	for(  i = 0; i < nRow ; i++ )
	{
	     for( j = 0 ; j < nColumn; j++ )
	     {
		   strcat(buffer,dbResult[index]);
		   if(j < nColumn-1){strcat(buffer,",");}
		    ++index; 
	     }
		 if(i<nRow-1)
	     strcat(buffer,";");
	}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
}

/*************************************************************************************/
/*              ������г������Ϣ�����������ڻ�����buffer������                              */
/*              �βΣ���                                                                      */
/*              �زΣ���                                                                      */
/************************************************************************************/
void get_plant_table()
{ 
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"/sp ");
	int result;
	char * errmsg = NULL;
	char **dbResult;
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	result = sqlite3_get_table( conn, "select plant.plantNo,plantName,name from plant,employee where managerNo=employeeNo ", &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
	index = nColumn; 
	for(  i = 0; i < nRow ; i++ )
	{
	     for( j = 0 ; j < nColumn; j++ )
	     {
		   strcat(buffer,dbResult[index]);
		   if(j < nColumn-1){strcat(buffer,",");}
		    ++index; 
	     }
	     strcat(buffer,";");
	}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
}

/*************************************************************************************/
/*              �������Ʒ�ʵ���Ϣ�����������ڻ�����buffer������                              */
/*              �βΣ���                                                                      */
/*              �زΣ���                                                                      */
/************************************************************************************/
void get_quality_table()
{  
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"/sq ");
	int result;
	char *errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	result = sqlite3_get_table( conn, "select qualityNo,drawback,productName from quality,workType where quality.workTypeNo=workType.workTypeNo", &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
	index = nColumn;
	for(  i = 0; i < nRow ; i++ )
	{
	     for( j = 0 ; j < nColumn; j++ )
	     {
		   strcat(buffer,dbResult[index]);
		   if(j < nColumn-1){strcat(buffer,",");}
		   ++index; 
	     }
	     strcat(buffer,";");
	}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
}
/*************************************************************************************/
/*              ��ù��ֺ�                                                                       */
/*              �βΣ���                                                                      */
/*              �زΣ���                                                                      */
/************************************************************************************/
void get_workType_table()//��
{
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"/st ");
	int result;
	char *errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	result = sqlite3_get_table( conn, "select * from workType ", &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
	index = nColumn;
	for(  i = 0; i < nRow ; i++ )
	{
	     for( j = 0 ; j < nColumn; j++ )
	     {
		   strcat(buffer,dbResult[index]);
		   if(j < nColumn-1){strcat(buffer,",");}
		   ++index; 
	     }
	     strcat(buffer,";");
	}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
}
/*************************************************************************************/
/*              ���//���ָ��ʱ��εİ�κ�                                                    */
/*              �βΣ���ʼ���ڡ���������                                                        */
/*              �زΣ���                                                                      */
/************************************************************************************/
void get_classNoByDate(char * beginCalendar,char * endCalendar)
{       //printf("beginCalendar2:%s\tendCalendar2:%s",beginCalendar,endCalendar);
	//memset(buffer,0,sizeof(buffer));	
	int result;
	char sql[200];
	char * errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	int i , j,index;
	sqlite3 *conn = open_sqlite3(); 
	sprintf(sql,"select classNo,beginTime,endTime from class where ('%s'<endTime) and (endTime<='%s') ",beginCalendar,endCalendar);
        strcpy(buffer,"/sg|");
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
	index = nColumn;
	for(  i = 0; i < nRow ; i++ )
	{
	     for( j = 0 ; j < nColumn; j++ )
	     {
		   strcat(buffer,dbResult[index]);
		   if(j < nColumn-1){strcat(buffer,",");}
		   ++index; 
	     }
	     strcat(buffer,";");
	}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
}
/*************************************************************************************/
/*              ����Ա�����������Ա����                                                        */
/*              �βΣ�Ա������                                                                 */
/*              �زΣ�Ա����                                                                   */
/************************************************************************************/
int get_employeeNo(char * username)
{  
    if(username==NULL||*username=='\0') return 0;Debug("username:%c ",*username);
	int employeeNo;
	int result;char sql[SQL_SIZE];
	char * errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select employeeNo from employee where name='%s';",username);
	Debug("sql:%s",sql);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
		employeeNo=atoi(dbResult[nColumn]);
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return employeeNo;
}
/*************************************************************************************/
/*              ���ݹ������ƣ���ù��ֺ�                                                       */
/*              �βΣ���������                                                                 */
/*              �زΣ����ֺ�                                                                   */
/************************************************************************************/
int get_workTypeNo(char * pcProductName)
{  
	int workTypeNo=0;
	int result;char sql[SQL_SIZE]={0};
	char * errmsg = NULL;
	char **dbResult; 
	int nRow=0, nColumn=0;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select workTypeNo from workType where productName='%s';",pcProductName);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result ){
		workTypeNo=atoi(dbResult[nColumn]);
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return workTypeNo;
}
/*************************************************************************************/
/*              ���ݳ������ƣ���ó����                                                       */
/*              �βΣ���������                                                                 */
/*              �زΣ������                                                                   */
/************************************************************************************/
int get_plantNo(char * pcPlantName)
{  
	int iPlantNo=0;
	int result;char sql[SQL_SIZE]={0};
	char * errmsg = NULL;
	char **dbResult; 
	int nRow=0, nColumn=0;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select plantNo from plant where plantName='%s';",pcPlantName);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result ){
		iPlantNo=atoi(dbResult[nColumn]);
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return iPlantNo;
}

/*************************************************************************************/
/*              ����ְλ���ƣ����ְλ��                                                       */
/*              �βΣ�ְλ����                                                                 */
/*              �زΣ�ְλ��                                                                   */
/************************************************************************************/
int get_positionNo(char * pcPositionName)
{  
	int iPositionNo=0;
	int result;char sql[SQL_SIZE]={0};
	char * errmsg = NULL;
	char **dbResult; 
	int nRow=0, nColumn=0;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select positionNo from position where positionName='%s';",pcPositionName);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result ){
		iPositionNo=atoi(dbResult[nColumn]);
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return iPositionNo;
}



/*************************************************************************************/
/*              ������µİ�κ�                                                                */
/*              �βΣ���                                                                       */
/*              �زΣ���κ�                                                                   */
/************************************************************************************/
int get_newestclassNo()
{  
	int classNo;
	int result;char sql[200];
	char * errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	sqlite3 *conn = open_sqlite3();
	sprintf(sql, "select  classNo from class order by classNo desc limit 0,1;");
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    
		classNo=atoi(dbResult[nColumn]);
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return classNo;
}

/*************************************************************************************/
/*              ���Ʒ�ʹ���ԱԱ���ţ�����һ�����                                               */
/*              �βΣ�Ʒ�ʹ���Ա�û���                                                          */
/*              �زΣ������α�ļ�¼����1��ʾ�ɹ���0��ʾʧ��                                   */
/************************************************************************************/
int create_newclass(char * pcEmployeeName)
{       
    int m_iEmployeeNo=1;
    m_iEmployeeNo=get_employeeNo(pcEmployeeName);
 	sqlite3 *conn = open_sqlite3();  
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
        int count=1;
	sprintf(sql, "insert into class values(NULL,%d,datetime(CURRENT_TIMESTAMP,'localtime'),datetime(CURRENT_TIMESTAMP,'localtime'),'afternoon','p001','N');",m_iEmployeeNo);
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg))
	{
	    printf("operate failed: %s\n", err_msg);
        return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn))
	{
	    printf("can not close the database: %s\n", sqlite3_errmsg(conn));
        return 0;
	}
	sqlite3_free(err_msg);
	return count;
}

int InsertIntoClass(int m_iEmployeeNo,int m_iPlantNo,char * m_pcClassRange)
{       
 	sqlite3 *conn = open_sqlite3();  
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
    int count=1;
	sprintf(sql, "insert into class values(NULL,%d,datetime('now'),datetime('now'),'%s',%d,'N');",m_iEmployeeNo,m_pcClassRange,m_iPlantNo);
	
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg))
	{
	    printf("operate failed: %s\n", err_msg);
        return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn))
	{
	    printf("can not close the database: %s\n", sqlite3_errmsg(conn));
        return 0;
	}
	sqlite3_free(err_msg);
	return count;
}


/*************************************************************************************/
/*              �����°ຯ�������ݰ�κţ��Զ�����°���Ϣ��¼                                    */
/*              �βΣ���κ�                                                                   */
/*              �زΣ����°�α�ļ�¼����1��ʾ�ɹ���0��ʾʧ��                                   */
/************************************************************************************/
int work_over(int iClassNo)
{
 	sqlite3 *conn = open_sqlite3(); 
	char *err_msg = NULL;  
	char sql[SQL_SIZE];
    int count=1;
	sprintf(sql, "update class set endtime=datetime('now'),crStatus='Y' where classNo=%d ",iClassNo);
	Debug(sql);
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg))
	{
	    printf("operate failed: %s\n", err_msg);
        return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn))
	{
	    printf("can not close the database: %s\n", sqlite3_errmsg(conn));
        return 0;
	}
    sqlite3_free(err_msg);
    return count;
}

/*************************************************************************************/
/*              �����β�ֵ������ϸ���У����¾�������                                             */
/*              �βΣ���κš�������Ʒ��Ա���š����ֺ�                                           */
/*              �زΣ����³ɹ��ļ�¼��������1Ϊ�ɹ�������0Ϊʧ��                                 */
/************************************************************************************/
int cuDetail(int classNo,int employeeNo,int workTypeNo,char * concreteData)
{       
 	sqlite3 *conn = open_sqlite3();  
	char * err_msg = NULL;
	char sql[SQL_SIZE];
    int count=1;
   // 
   int iIsInserted=IsInsertedIntoDetail(classNo,employeeNo,workTypeNo);
   Debug("iIsInserted:%d",iIsInserted);
	if(iIsInserted>=1)
		{
			sprintf(sql,"update detail set concreteData ='%s' where classNo=%d and employeeNo=%d and workTypeNo=%d ;",concreteData,classNo,employeeNo,workTypeNo);
		}
	else
		{
		
		sprintf(sql,"insert into detail values(%d,%d,%d,'%s');",classNo,employeeNo,workTypeNo,concreteData);
		
	}
    //Debug
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg))
	{
	    printf("operate failed: %s\n", err_msg);
        return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn))
	{
	    printf("Can not close the database: %s\n", sqlite3_errmsg(conn));
        return 0;
	}
    sqlite3_free(err_msg);
    return count;
}
//
int IsInsertedIntoDetail(int classNo,int employeeNo,int workTypeNo)
{
	sqlite3 *conn = open_sqlite3();  
	char * errmsg= NULL;  
	char sql[SQL_SIZE];
	int count=1;
	char **dbResult; 
	int nRow, nColumn;
    sprintf(sql,"select  count(*) from detail where classNo=%d and employeeNo=%d and workTypeNo=%d;",classNo,employeeNo,workTypeNo);
	Debug(sql);
	int result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    
		if(nRow<1)//û�м�¼
		{return 0;}
		else
		{
				return atoi(dbResult[nColumn]);
		}
	}
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return 0;
}

/*************************************************************************************/
/*�����β�ֵ������ϸ���У���þ������� ��
����ѯ�������ڻ�����buffer�����У�
����鲻�����������򷵻�0*/
/*              �βΣ���κš�������Ʒ��Ա���š����ֺ�                                           */
/*              �زΣ����ݿ�����ɹ��ļ�¼��������1Ϊ�ɹ�������0Ϊʧ��                            */
/************************************************************************************/
int cdDetail(int classNo,int employeeNo,int workTypeNo)
{       //���buffer,���ڴ�ž�������
	memset(buffer,0,sizeof(buffer));
	//�������ݿ�����
	sqlite3 *conn = open_sqlite3();  
	char * errmsg= NULL;  
	char sql[SQL_SIZE];
	int count=1;
	char **dbResult; 
	int nRow, nColumn;
    sprintf(sql,"select  concreteData from detail where classNo=%d and employeeNo=%d and workTypeNo=%d;",classNo,employeeNo,workTypeNo);
	//Debug("SQL:%s",sql);
	int result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    
		if(nRow<1)
		{return 0;}
		//dbResult[nColumn]���ָ���ַ�������ַ�ָ����뿽�����趨��ȫ�ֱ���buffer�����У�
		//�������Խ����������ʱ��ʱ����ͬʱ���ٵ����⣬����һ�������е�ָ������
		strcpy(buffer,dbResult[nColumn]);
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
    return count;
}
//ȡ���µ�5����¼
int cwDetail()
{   
	memset(buffer,0,BUFFER_SIZE);
	sqlite3 *conn = open_sqlite3();  
	char * errmsg= NULL;  
	char sql[SQL_SIZE]={0};
	int count=1;
	char **dbResult; 
	int nRow, nColumn,i,j,index;
    sprintf(sql,"select  classNo,name,productName,concreteData from detail,employee,workType where  detail.employeeNo=employee.employeeNo and detail.workTypeNo=workType.workTypeNo order by classNo desc limit 0,5;");
	int result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    
		if(nRow<1)//û�м�¼
		{return 0;}
		index = nColumn;
		for(  i = 0; i < nRow ; i++ )
		{	
		     for( j = 0 ; j < nColumn; j++ )
		     { 	   
			   if(j < nColumn-1)
			   { printf("%s\t",dbResult[index]);
			  	 strcat(buffer,dbResult[index]);strcat(buffer,"#");
			   }//�зָ���
               else//���һ�д����������
               {    
			      calRateByConcreteData(dbResult[index]);
			   }
			   ++index; 
		     }
              if(i < nRow -1)
		     {strcat(buffer,"|");}//��¼�ָ���
		}
        strcat(buffer,"\n\0");
	}
	else
	{
		return 0;
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
    return count;
}
int starCwDetail()
{   
	memset(buffer,0,BUFFER_SIZE);
	sqlite3 *conn = open_sqlite3();  
	char * errmsg= NULL;  
	char sql[SQL_SIZE]={0};
	int count=1;
	char **dbResult; 
	int nRow, nColumn,i,j,index;
    sprintf(sql,"select  classNo,detail.employeeNo,name,plantName,productName,concreteData from detail,employee,workType,plant where  detail.employeeNo=employee.employeeNo and detail.workTypeNo=workType.workTypeNo and employee.plantNo=plant.plantNo order by classNo desc limit 0,7;");
	//Debug("sql:%s",sql);
	int result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{    
		if(nRow<1)//û�м�¼
		{return 0;}
		index = nColumn;
		for(  i = 0; i < nRow ; i++ )
		{	
		     for( j = 0 ; j < nColumn; j++ )
		     { 	   
			   if(j < nColumn-1)
			   { printf("%s\t",dbResult[index]);
			  	 strcat(buffer,dbResult[index]);strcat(buffer,"#");
			   }//�зָ���
               else//���һ�д����������
               {    
			      getQualityNameByConcreteData(dbResult[index]);
			   }
			   ++index; 
		     }
              if(i < nRow -1)
		     {strcat(buffer,"|");}//��¼�ָ���
		}
        strcat(buffer,"\n\0");
	}
	else
	{
		return 0;
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
    return count;
}

int getQualityNameByConcreteData(char * pcConcreteData)
{
	char acConcreteData[CONCRETE_LEN]={0};
	strcpy(acConcreteData,pcConcreteData);
	char * s=acConcreteData;
	if(*s=='0')//û����ϸ��¼���
	{strcat(buffer, "0");return 0;}
	while(*s!='\0')
    { 
		memset(temp,0,sizeof(temp));				
		strcpy(temp,s);
		char * th=getHead(temp,';');
		s=strchr(s,';')+1;
		char *pcQamount=strchr(th,',')+1;//��ӦƷ�ʺŵĲ�Ʒ����
        int qualityNo=atoi(getHead(th,','));//Ʒ�ʺ�
        char acQualityName[40]={0};
		getQualityName(qualityNo,acQualityName);//����Ʒ�ʺţ����Ʒ�ʷ���
		strcat(buffer,acQualityName);strcat(buffer,",");
		strcat(buffer,pcQamount);strcat(buffer,";");
	}
}

//���ݾ������ݷ������������ʣ���д����������
int calRateByConcreteData(char * pcConcreteData)
{
	char acConcreteData[CONCRETE_LEN]={0};
	strcpy(acConcreteData,pcConcreteData);
	char * s=acConcreteData;
	int amount=0,A=0,B=0,C=0,D=0;
	char acRate[RATE_LEN]={0};
	float aRate,bRate,cRate,dRate=0.0;			  
	if(*s=='0')//û����ϸ��¼���
	{sprintf(acRate, "0%%,0%%,0%%,0%%,0");strcat(buffer,acRate);
	return 0;}
	while(*s!='\0')
    { 
		memset(temp,0,sizeof(temp));				
		strcpy(temp,s);
		char * th=getHead(temp,';');
		s=strchr(s,';')+1;
		int qamount=atoi(strchr(th,',')+1);//��ӦƷ�ʺŵĲ�Ʒ����
        int qualityNo=atoi(getHead(th,','));//Ʒ�ʺ�
		char cRateType=parseQualityNo(qualityNo);//����Ʒ�ʺţ����Ʒ�ʷ���
		switch (cRateType)
		{
			case 'A':A=A+qamount;amount=amount+qamount;break;
			case 'B':B=B+qamount;amount=amount+qamount;break;
			case 'C':C=C+qamount;amount=amount+qamount;break;
			case 'D':D=D+qamount;amount=amount+qamount;break;
			default:break;
		}
        aRate=(float)A/(float)amount*100;
		bRate=(float)B/(float)amount*100;
		cRate=(float)C/(float)amount*100;
		dRate=(float)D/(float)amount*100;
    }
	sprintf(acRate, "%.2f,%.2f,%.2f,%.2f,%d",aRate,bRate,cRate,dRate,amount);
	strcat(buffer,acRate);
	//printf("\t %s\n",acRate);
	return 1;
}

int getClassesByTime(char * beginCalendar,char * endCalendar)
{
	sqlite3 *conn = open_sqlite3();  
	char * errmsg= NULL;  
	char sql[SQL_SIZE*2];
	int count=1;
	char **dbResult; 
	int nRow, nColumn,i,j,index; 	
	sprintf(sql,"select classNo,qmEmployeeNo,Name,beginTime,endTime,classRange,plantName,crStatus from class,employee,plant where class.qmEmployeeNo =employee.employeeNo and class.plantNo=plant.plantNo and('%s'<beginTime) and (endTime<='%s')",beginCalendar,endCalendar);
	//Debug("sql:%s",sql);
	memset(buffer,0,sizeof(buffer));
	int result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{   //Debug("SQLITE_OK "); 
		if(nRow<1)//û�м�¼
		{return 0;}
		index = nColumn;
		for(  i = 0; i < nRow ; i++ )
		{	
		     for( j = 0 ; j < nColumn; j++ )
		     { 
		      strcat(buffer,dbResult[index]);
		       if(j < nColumn-1)
			   {
					
					strcat(buffer,"#");
		     	}
			   	++index; 
			 }	
			 if(i < nRow -1)
		     {strcat(buffer,"|");}//��¼�ָ���
		     //Debug("buffer:%s",buffer);
		     //strcat(buffer,"|");
		}	
	}
	else
	{
		return 0;
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
    return count;
}

/*************************************************************************************/
/*�����β�ֵ��C#���������� ������ѯ�������ڻ�����buffer�����У�
����鲻�����������򷵻�0          */
/*              �βΣ���κš�������Ʒ��Ա���š����ֺ� ����ʼ���ڡ���������                        */
/*              �زΣ����ݿ�����ɹ��ļ�¼��������1Ϊ�ɹ�������0Ϊʧ��                            */
/************************************************************************************/
int ciDetail(int classNo,int workTypeNo,char * beginCalendar,char * endCalendar)
{       
	sqlite3 *conn = open_sqlite3();  
	char * errmsg= NULL;  
	char sql[SQL_SIZE*2];
	int count=1;
	char **dbResult; 
	int nRow, nColumn,i,j,index;
    if((classNo==0)&&(workTypeNo==0))
    {  	
		sprintf(sql,"select  detail.classNo,name,productName,concreteData from detail,class,employee,workType where  detail.employeeNo=employee.employeeNo and detail.workTypeNo=workType.workTypeNo and detail.classNo=class.classNo and ('%s'<beginTime) and (endTime<='%s')",beginCalendar,endCalendar);
		//Debug("SQL:%s",sql);
	}
	else if((classNo!=0)&&(workTypeNo==0))
    {
	 	sprintf(sql,"select  detail.classNo,name,productName,concreteData from detail,class,employee,workType where  detail.employeeNo=employee.employeeNo and detail.workTypeNo=workType.workTypeNo and  detail.classNo=class.classNo and detail.classNo=%d and ('%s'<beginTime) and (endTime<='%s');",classNo,beginCalendar,endCalendar);
	}
    else if((classNo==0)&&(workTypeNo!=0))
	{
	   sprintf(sql,"select  detail.classNo,name,productName,concreteData from detail,class,employee,workType where  detail.employeeNo=employee.employeeNo and detail.workTypeNo=workType.workTypeNo and detail.classNo=class.classNo and detail.workTypeNo=%d and ('%s'<beginTime) and (endTime<='%s');",workTypeNo,beginCalendar,endCalendar);
	}
    else
	{
		sprintf(sql,"select  detail.classNo,name,productName,concreteData from detail,class,employee,workType where  detail.employeeNo=employee.employeeNo and detail.workTypeNo=workType.workTypeNo and detail.classNo=class.classNo and detail.classNo=%d and detail.workTypeNo=%d and ('%s'<beginTime) and (endTime<='%s');",classNo,workTypeNo,beginCalendar,endCalendar);
	}
	memset(buffer,0,sizeof(buffer));
	int result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{   //Debug("SQLITE_OK "); 
		if(nRow<1)//û�м�¼
		{return 0;}
		index = nColumn;
		for(  i = 0; i < nRow ; i++ )
		{	
		     for( j = 0 ; j < nColumn; j++ )
		     { 	   
			   if(j < nColumn-1)
			   { printf("%s\t",dbResult[index]);
			  	 strcat(buffer,dbResult[index]);strcat(buffer,"#");
			   }//�зָ���
               else//���һ�д����������
               {    
			      calRateByConcreteData(dbResult[index]);
			   }
			   ++index; 
		     }
              if(i < nRow -1)
		     {strcat(buffer,"|");}//��¼�ָ���
		}
        strcat(buffer,"\n\0");
	}
	else
	{
		return 0;
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
    return count;
}
/*************************************************************************************/
/*              ����Ʒ�ʺŻ��Ʒ�ʵȼ�                                                          */
/*              �βΣ�Ʒ�ʺ�                                                                   */
/*              �زΣ�Ʒ�ʵȼ�                                                                  */
/*************************************************************************************/
char parseQualityNo(int qualityNo)
{
    char range;
	int result;char sql[SQL_SIZE];
	char * errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select drawback from quality where qualityNo='%d';",qualityNo);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
		range=*(dbResult[nColumn]);
		switch(range)
		{
			case 'A':return 'A';break;
			case 'B':return 'B';break;
			case 'C':return 'C';break;
			case 'D':return 'D';break;
			default:return 'Z';break;
		}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return 'Z';
}

int getQualityName(int qualityNo,char * pcQualityName)
{
	int result;char sql[SQL_SIZE];
	char * errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	sqlite3 *conn = open_sqlite3();  
	sprintf(sql, "select drawback from quality where qualityNo='%d';",qualityNo);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
		strcpy(pcQualityName,dbResult[nColumn]);
	}
	else
	{
		return 0;
	}
	sqlite3_free(errmsg);
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	return 1;
}

/*************************************************************************************/
/*              ����ϸ���У�����1����¼��������������Ϊ"0"                                  */
/*              �βΣ���κš�������Ʒ��Ա���š����ֺ�                                           */
/*              �زΣ�����ɹ��ļ�¼��������1Ϊ�ɹ�������0Ϊʧ��                                 */
/************************************************************************************/
int insertDetail(int classNo,int employeeNo,int workTypeNo)
{       
 	sqlite3 *conn = open_sqlite3();  
	char * err_msg = NULL;
	char sql[SQL_SIZE];
        int count=1;
	sprintf(sql, "insert into detail values(%d,%d,%d,'%s');",classNo,employeeNo,workTypeNo,"0");
	if (SQLITE_OK != sqlite3_exec(conn,sql,0,0, &err_msg))
	{
	    printf("operate failed: %s\n", err_msg);
            return 0;
	}
	if (SQLITE_OK != sqlite3_close(conn))
	{
	    printf("Can not close the database: %s\n", sqlite3_errmsg(conn));
            return 0;
	}
	sqlite3_free(err_msg);
	return count;
}
