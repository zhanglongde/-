#include <sqlite3.h>
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h> 
#include <time.h>
#include "process.h"
#include "commonData.h"

char  temp[TEMP_SIZE];          //��ʱ�洢�ռ�
char  buffer[BUFFER_SIZE];      //����������Ϊ1024�ֽڵĴ�С

//����socketͨ��Э���ʶ������25��
char * pcProtocol[PROTOCOL_NUM]={
[SL_CL]="/cl",[SL_CR]="/cr",[SL_CQ]="/cq",[SL_CP]="/cp",[SL_CC]="/cc",
[SL_SC]="/sc",[SL_CO]="/co",[SL_SO]="/so",[SL_CD]="/cd",[SL_SD]="/sd",
[SL_CU]="/cu",[SL_SU]="/su",[SL_CE]="/ce",[SL_SE]="/se",[SL_CW]="/cw",
[SL_SW]="/sw",[SL_CI]="/ci",[SL_SI]="/si",[SL_CG]="/cg",[SL_SG]="/sg",
[SL_CT]="/ct",[SL_ST]="/st",[ST_CL]="*cl",[ST_CE]="*ce",[ST_CW]="*cw"
};
Employee stEmployee={{0},0,{0},{0},0,0,0,0};

void processStream()
{
	   memset(temp,0,sizeof(temp));
       strcpy(temp,buffer);
	   head=parseHead(temp);
	   //head=&buffer[0];
       //����ͷ����Ϣִ�����Ӧ�Ĳ���
	   switch(head[2])
        {       
		  	case 'l':cl();break;//"/cl"
          	case 'r':cr();break;//"/cr"
          	case 'q':cq();break;//"/cq"
			case 'p':cp();break;//"/cp"
			case 'c':cc();break;//"/cc"
			case 'o':co();break;//"/co"  �°�
			case 'd':cd();break;//"/cd"
			case 'u':cu();break;//"/cu"
			case 'e':ce();break;//"/ce"
        	case 'w':cw();break;//"cw"
        	case 'i':ci();break;//"ci"  ��������
			case 'g':cg();break;//"cg"
			case 't':ct();break;//"ct"
			case 'b':cb();break;
        	default:illegal();break;
        } 
}

void processStruct()
{
	switch(buffer[2])
    {       
	  	case 'l':starLogin();break;
	  	case 'e':starGetAllEmployees();break;
		case 'w':starCw();break;
		case 'd':starCd();break;//ɾ��һ���û�
		case 'u':starCu();break;//�༭Ա����Ϣ
		case 'r':starCr();break;//��ý������
		case 'b':starCb();break;//�������ݿ�
		case 'g':starCg();break;//������ݿ�·��
		case 'i':starCi();break;//����һ���û�
		case 'x':starCx();break;//����һ���������
    	default:illegal();break;
     } 
}
void starCx()
{
	//�жϲ�������
	int iCount=getCount(buffer,'|');
	if(iCount>4 || iCount<1){
		memset(buffer,0,BUFFER_SIZE);
		Debug("number of parameter error:%d\n",iCount);  
		strcpy(buffer,"*su number of parameter error");
	}
	else{
		char * pcResMakerName=(char *)malloc(sizeof(char)*20);
		char * pcResText=(char *)malloc(sizeof(char)*1024);
		char * pcPosition=(char *)malloc(sizeof(char)*10);
		char *pc=strchr(buffer,'|');
		if(pc==NULL) return;
		char * pcFirst=pc+1;
		strcpy(temp,pcFirst);
		strcpy(pcResMakerName,getHead(temp,'|'));
		pc=strchr(pcFirst,'|');
		if(pc==NULL) return;
		char * pcSecond=pc+1;//Debug("pcSecond:%s",pcSecond);
		strcpy(temp,pcSecond);
		strcpy(pcResText,getHead(temp,'|'));
		pc=strchr(pcSecond,'|');
		if(pc==NULL) return;
		char * pcThird=pc+1;
		strcpy(pcPosition,pcThird);
		int ResMakerNo=get_employeeNo(pcResMakerName);
		
		memset(buffer,0,BUFFER_SIZE);
		if(ResMakerNo==0){
			strcpy(buffer,"*sx n ResMakerNo");return;}
		int iResNo=0;
		int iResult=InsertRes(ResMakerNo,pcResText,pcPosition,&iResNo);
		memset(buffer,0,BUFFER_SIZE);
		if(iResult==0){
			strcpy(buffer,"*sx n");}
		else{
            sprintf(buffer,"*sx y %d",iResNo);}
		free(pcResMakerName);
		free(pcResText);
		free(pcPosition);
	}
}
//��õ�ǰ���ݿ�λ��
void starCg()
{
	memset(temp,TEMP_SIZE,0);
	if(GetDBDir(temp)==1){
		sprintf(buffer,"*sg y %s",temp);
	}
	else{ 
		sprintf(buffer,"*sg n");
	}
}
//�������ݿ�
void starCb()
{
	//�жϲ�������
	int iCount=getCount(buffer,'|');
	if(iCount!=2){
			Debug("number_of_parameter_error :%d\n",iCount);  
			strcpy(buffer,"*sr number_of_parameter_error");
	}
	else{
		//���Ŀ���ļ���
		strcpy(temp,strchr(buffer,'|')+1);
		if(BackupDB(temp)==1){
			sprintf(buffer,"*sb y");
		}
		else{ 
			sprintf(buffer,"*sb n");
		}
	}
}
void starCr()
{
	//�жϲ�������
	int iCount=getCount(buffer,'|');
	if(iCount!=2){
			Debug("number of parameter error :%d\n",iCount);  
			strcpy(buffer,"*sr number of parameter error");
	}
	else{
		//����û���
		strcpy(temp,strchr(buffer,'|')+1);
		if(GetRessByPositionNo(temp)==1){
			//sprintf(buffer,"*sr y");
		}
		else{ 
			sprintf(buffer,"*sr n");
		}
	}
}
//*cd Ա����
//*sd y����*sd n
void starCd()
{   
	//�жϲ�������
	int iCount=getCount(buffer,'|');
	if(iCount!=2){
			Debug("number of parameter error :%d\n",iCount);  
			strcpy(buffer,"*sd number of parameter error");
	}
	else{
		//����û���
		strcpy(temp,strchr(buffer,'|')+1);
		if(DeleteEmployee(temp)==1){
			sprintf(buffer,"*sd y");
		}
		else{ 
			sprintf(buffer,"*sd n");
		}
	}
}
//�����û���Ϣ
//*cu  Ա���� |Ա����| ����|ְλ����|��������|��Ʒ���� 
//*su y���� *su n �����Ҳ���ְλ�����䡢��Ʒ
void starCu()
{
	//�жϲ�������
	int iCount=getCount(buffer,'|');
	if(iCount>7 || iCount<1){
		memset(buffer,0,BUFFER_SIZE);
		Debug("number of parameter error:%d\n",iCount);  
		strcpy(buffer,"*su number of parameter error");
	}
	else{
		char * pcEmployeeNo=(char *)malloc(sizeof(char)*20);
		char * pcName=(char *)malloc(sizeof(char)*20);
		char * pcPwd=(char *)malloc(sizeof(char)*10);
		char * pcPositionName=(char *)malloc(sizeof(char)*10);
		char * pcPlantName=(char *)malloc(sizeof(char)*10);
		char * pcProductName=(char *)malloc(sizeof(char)*10);
		char * pcFirst=strchr(buffer,'|')+1;
		strcpy(temp,pcFirst);
		strcpy(pcEmployeeNo,getHead(temp,'|'));
		char * pcSecond=strchr(pcFirst,'|')+1;//Debug("pcSecond:%s",pcSecond);
		strcpy(temp,pcSecond);
		strcpy(pcName,getHead(temp,'|'));
		char * pcThird=strchr(pcSecond,'|')+1;
		strcpy(temp,pcThird);
		strcpy(pcPwd,getHead(temp,'|'));
		char * pcForth=strchr(pcThird,'|')+1;
		strcpy(temp,pcForth);
		strcpy(pcPositionName,getHead(temp,'|'));
		char * pcFifth=strchr(pcForth,'|')+1;
		strcpy(temp,pcFifth);
		strcpy(pcPlantName,getHead(temp,'|'));
		char * pcSixth=strchr(pcFifth,'|')+1;
		strcpy(pcProductName,pcSixth);
		int iPositionNo=get_positionNo(pcPositionName);
		Debug("pcPlantName:%s  pcProductName:%s",pcPlantName,pcProductName);
		memset(buffer,0,BUFFER_SIZE);
		if(iPositionNo==0){
			strcpy(buffer,"*su n positionName");return ;}
		int iPlantNo=get_plantNo(pcPlantName);{
			strcpy(buffer,"*su n plantName");return;}
		int iWorkTypeNo=get_workTypeNo(pcProductName);{
			strcpy(buffer,"*su n productName");return;}
		int iResult=UpdateEmployee(pcEmployeeNo,pcName,pcPwd,iPositionNo,iPlantNo,iWorkTypeNo);
		memset(buffer,0,BUFFER_SIZE);
		if(iResult==0){
			strcpy(buffer,"*su n");}
		else{
            strcpy(buffer,"*su y");}
		free(pcEmployeeNo);
		free(pcName);
		free(pcPwd);
		free(pcPositionName);
		free(pcPlantName);
		free(pcProductName);
	}
}

void starCi()
{
	//�жϲ�������
	int iCount=getCount(buffer,'|');
	if(iCount>7 || iCount<1){
		memset(buffer,0,BUFFER_SIZE);
		Debug("number of parameter error:%d\n",iCount);  
		strcpy(buffer,"*su number of parameter error");
	}
	else{
		char * pcEmployeeNo=(char *)malloc(sizeof(char)*20);
		char * pcName=(char *)malloc(sizeof(char)*20);
		char * pcPwd=(char *)malloc(sizeof(char)*10);
		char * pcPositionName=(char *)malloc(sizeof(char)*10);
		char * pcPlantName=(char *)malloc(sizeof(char)*10);
		char * pcProductName=(char *)malloc(sizeof(char)*10);
		char * pcFirst=strchr(buffer,'|')+1;
		strcpy(temp,pcFirst);
		strcpy(pcEmployeeNo,getHead(temp,'|'));
		char * pcSecond=strchr(pcFirst,'|')+1;//Debug("pcSecond:%s",pcSecond);
		strcpy(temp,pcSecond);
		strcpy(pcName,getHead(temp,'|'));
		char * pcThird=strchr(pcSecond,'|')+1;
		strcpy(temp,pcThird);
		strcpy(pcPwd,getHead(temp,'|'));
		char * pcForth=strchr(pcThird,'|')+1;
		strcpy(temp,pcForth);
		strcpy(pcPositionName,getHead(temp,'|'));
		char * pcFifth=strchr(pcForth,'|')+1;
		strcpy(temp,pcFifth);
		strcpy(pcPlantName,getHead(temp,'|'));
		char * pcSixth=strchr(pcFifth,'|')+1;
		strcpy(pcProductName,pcSixth);
		int iPositionNo=get_positionNo(pcPositionName);
		Debug("pcPlantName:%s  pcProductName:%s",pcPlantName,pcProductName);
		memset(buffer,0,BUFFER_SIZE);
		if(iPositionNo==0){
			strcpy(buffer,"*su n positionName");}
		int iPlantNo=get_plantNo(pcPlantName);{
			strcpy(buffer,"*su n plantName");}
		int iWorkTypeNo=get_workTypeNo(pcProductName);{
			strcpy(buffer,"*su n productName");}
		int iResult=InsertEmployee(pcEmployeeNo,pcName,pcPwd,iPositionNo,iPlantNo,iWorkTypeNo);
		memset(buffer,0,BUFFER_SIZE);
		if(iResult==0){
			strcpy(buffer,"*si n");}
		else{
            strcpy(buffer,"*si y");}
		free(pcEmployeeNo);
		free(pcName);
		free(pcPwd);
		free(pcPositionName);
		free(pcPlantName);
		free(pcProductName);
	}
}


void cb()
{
	//int getClassesByTime(char * beginCalendar,char * endCalendar);
	int count=getCount(buffer,'|');//check number of parameter is right or not 
	Debug("count:%d",count);
	if(count!=2)
	{	memset(buffer,0,BUFFER_SIZE);
		strcpy(buffer,"/sb n");
		strcat(buffer,"\n\0");
		if(count!=1){printf("number of parameter from client error\n\tnumber of parameter:%d",count); }
	}
	else
	{  
		char * beginCalendar=(char *)malloc(sizeof(char)*20);
		char * endCalendar=(char *)malloc(sizeof(char)*20);
		char * beginCalendar_=strchr(buffer,' ')+1;
		strcpy(temp,beginCalendar_);
		strcpy(beginCalendar,getHead(temp,'|'));
		char * endCalendar_=strchr(beginCalendar_,'|')+1;
		strcpy(endCalendar,endCalendar_);Debug("Debug");
		int iResult=getClassesByTime(beginCalendar,endCalendar);
		free(beginCalendar);
		free(endCalendar);
		strcpy(temp,buffer);
		memset(buffer,0,BUFFER_SIZE);
		//Debug("iResult:%d",iResult);
		if(iResult==1)
		{
			strcpy(buffer,"/sb@");strcat(buffer,temp);
			Debug("buffer sended:s%",buffer);
		}
		else
		{
			strcpy(buffer,"/sb n");
			strcat(buffer,"\n\0");
		}
	}
}

void starLogin()
{	
    memcpy(&stEmployee,buffer,sizeof(stEmployee));
	Debug("employeeNo:%d\t name:%s \tpwd:%s\n",
			stEmployee.iEmployeeNo,stEmployee.acName,stEmployee.acPwd);
	getEmployeeByNameAndPwd(&stEmployee);
	memcpy(buffer,&stEmployee,sizeof(Employee));
	Debug("after query !employeeNo:%d\t name:%s \tpwd:%s\tflag:%d\n",
			stEmployee.iEmployeeNo,stEmployee.acName,stEmployee.acPwd,stEmployee.iflag);
}

void starGetAllEmployees()
{
	get_employee_table();
}

/*************************************************************************************/
/*              ������֤���뺯���������β�ֵ����ѯ��صļ�¼��                                    */
/*              �βΣ��û���������                                                              */
/*              �زΣ��鵽�ļ�¼����1��ʾ�û����������Ӧ�ļ�¼��Ϊ1��0��ʾ�Ҳ����û�              */
/************************************************************************************/
int checkLogin(char * name, char * pwd,int * position)
{   
	int count=0;
	int result;char sql[200];
	char * errmsg = NULL;
	char **dbResult; 
	int nRow, nColumn;
	sqlite3 *conn = open_sqlite3();  
	// ����ָ����ʽ��ƴ��SQL���
	sprintf(sql, "select count(*),position from employee where name='%s' and pwd='%s'",name,pwd);
	Debug("sql:%s",sql);
	result = sqlite3_get_table( conn, sql, &dbResult, &nRow, &nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
		count=atoi(dbResult[nColumn]);
		if(count==1)
			*position=atoi(dbResult[nColumn+1]);
		else
			*position=0;
	}
	sqlite3_free_table( dbResult );
	sqlite3_close(conn);
	Debug("position:%d",*position);
	return count;
}



/*************************************************************************************/
/*              ����ע�ắ���������β�ֵ������1����¼                                            */
/*              �βΣ��û���������                                                              */
/*              �زΣ�����ļ�¼����1��ʾע��ɹ���0��ʾע��ʧ��                                 */
/************************************************************************************/
int reister(char * name , char * pwd)
{
 	sqlite3 *conn = open_sqlite3(); 
	char *err_msg = NULL;  
	char sql[200];
        int count=1;
        //ע����Ϣֻ��Ա���š��û��������룬������ϢΪ�գ�����Ա����Ϊ����ֵ
	sprintf(sql, "insert into employee values(NULL,'%s','%s',NULL,NULL,NULL);",name,pwd);
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
/*              �Ƿ�ͨ��Э�鴦��                                                               */
/*              �βΣ���                                                                       */
/*              �زΣ���                                                                       */
/************************************************************************************/
void illegal()
{       
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"/illegal");
}
void cl()
{
	//if head is "cl" that is client end apply "login" command
	int count=parseCount(buffer);//check number of parameter is right or not
	if(count!=2)
	{
			printf("number of parameter error\n");  
			strcpy(buffer,"/sl number of parameter error");
	}
	char * indexFirst=strchr(buffer,' ')+1;
	strcpy(temp,indexFirst);
	char * name=parseHead(temp);
    char * pwd=(char *)malloc(sizeof(char)*20);
	strcpy(pwd,strchr(indexFirst,' ')+1);
	int iPosition=0;
	if(checkLogin(name,pwd,&iPosition)==1)
	{
		//strcpy(buffer,"/sl y ");
		sprintf(buffer,"/sl y %d",iPosition);
	}
	else
	{ 
		//strcpy(buffer,"/sl n");
		sprintf(buffer,"/sl n %d",iPosition);
	}
    free(pwd);
}


void ce()
{
     int count=parseCount(buffer);//check number of parameter is right or not
     if(count!=1)
     {
    	 printf("number of parameter error"); 
     	 strcpy(buffer,"/se n");
     }
     char * pNo=strchr(buffer,' ')+1;
     int plantNo=atoi(pNo);
     getEmployeesByPlantNo(plantNo);
}

void cr()
{

 	     struct user us;
             int count=parseCount(buffer);//check number of parameter is right or not
             if(count!=5){printf("number of parameter error\n");  strcpy(buffer,"/sr number of parameter error");}
             char * indexFirst=strchr(buffer,' ')+1;
             strcpy(temp,indexFirst);
             us.name=parseHead(temp);
             char * indexSecond=strchr(indexFirst,' ')+1;
	     strcpy(temp,indexSecond);
             us.pwd=parseHead(temp);
             //us.pwd=indexSecond;
             if(reister(us.name,us.pwd))
             {strcpy(buffer,"/sr y");}
             else
             { strcpy(buffer,"/sr n");}
}

void cq()
{
	get_quality_table();
}
void cp()
{
	get_plant_table();
}
void cg()
{
        //��������
	int count=getCount(buffer,'|');//check number of parameter is right or not
	if(count!=2){printf("number of parameter error");  strcpy(buffer,"/sg number of parameter error");}
	char * indexFirst=strchr(buffer,' ')+1;
        //strcat(indexFirst,'\0');
	strcpy(temp,indexFirst);
	char * beginCalendar=getHead(temp,'|');   
	//printf("beginCalendar1:%s",beginCalendar);
        //strncpy(temp,indexFirst,19);
	char * endCalendar=strchr(indexFirst,'|')+1;
	//printf("temp1:%s",temp);
       // printf("beginCalendar1:%s\tendCalendar1:%s",beginCalendar,endCalendar);
	get_classNoByDate(beginCalendar,endCalendar);//���ָ�����ڵİ�κ�
}
void ct()
{
	get_workType_table();//��ù��ֺ�
}
//�������
void cc()
{
	int count=parseCount(buffer);//check number of parameter is right or not
	if(count!=2)
	{printf("number of parameter from client error\n");  strcpy(buffer,"/sc number of parameter error");
	return ;
	}
	char * pcEmployeeName_=strchr(buffer,' ')+1;
	strcpy(temp,pcEmployeeName_);
	int iEmployeeNo=get_employeeNo(parseHead(temp));
	
	int iPlantNo=atoi(strchr(pcEmployeeName_,' ')+1);
	//strcpy(temp,pcPlantNo);
	//int iWorkypeNo=get_workTypeNo(temp);
	
	char acClassRange[30]={0};
	   time_t rawtime;
	   struct tm * timeinfo;
	   time ( &rawtime );
	   timeinfo = localtime ( &rawtime );
	    if(timeinfo->tm_hour>=12)
	   		strcpy(acClassRange,"amClass");
	   	else 
			strcpy(acClassRange,"pmClass");
	//Debug("timeinfo->tm_sec:%d",timeinfo->tm_sec);
	if(InsertIntoClass(iEmployeeNo,iPlantNo,acClassRange))
	{
		int classNo=get_newestclassNo();
			
			memset(buffer,0,BUFFER_SIZE);
			strcpy(buffer,"/sc");
			strcat(buffer," ");
			char  * s=(char *)malloc(sizeof(char)*20);
			itoa(classNo,s);
			//Debug(s);
			strcat(buffer,s);
			free(s);
	}
	else
	{
		strcpy(buffer,"/sc");
		strcat(buffer," n");
	}
	
}
//�°�
void co()
{
	Debug(buffer);
	int count=parseCount(buffer);//check number of parameter is right or not
    char * indexFirst=strchr(buffer,' ')+1;
	int iClassNo=atoi(parseHead(indexFirst));
	//memset(temp,0,TEMP_SIZE);
	//strcapy();
	//Debug(indexFirst);
	//Debug("iClassNo:",iClassNo);
     if((count==1)&&(work_over(iClassNo)!=0))
     {
       memset(buffer,0,BUFFER_SIZE);
       strcpy(buffer,"/so");
       strcat(buffer," y");
     }
     else
     {
     	memset(buffer,0,BUFFER_SIZE);
        strcpy(buffer,"/so");
        strcat(buffer," n");
        if(count!=1)
		{Debug("number of parameter from client error\n"); }
     }
}
void cd()
{
    int count=parseCount(buffer);//check number of parameter is right or not 
    Debug("count:%d\n",count);
    if(count!=3)
    {
       strcpy(buffer,"/sd");
       strcat(buffer," n");
       if(count!=1)
	   {
	   		printf("number of parameter from client error\n");
	   }
     }
     else
     {  
        char * classNo_=strchr(buffer,' ')+1;
        strcpy(temp,classNo_);
		int classNo=atoi(parseHead(temp));//printf("OK");
        char * employeeNo_=strchr(classNo_,' ')+1; 
        strcpy(temp,employeeNo_);
		int employeeNo=atoi(parseHead(temp));
        char *workTypeNo_=strchr(employeeNo_,' ')+1; 
        strcpy(temp,workTypeNo_);
		
		//int workTypeNo=get_workTypeNo(parseHead(temp));
		int workTypeNo=get_workTypeNo(temp);
        int count=cdDetail(classNo,employeeNo,workTypeNo);
        strcpy(temp,buffer);
        memset(buffer,0,sizeof(buffer));
        if(count)
        {
        	strcpy(buffer,"/sd");strcat(buffer," ");strcat(buffer,temp);
		}
        else
        {
	         int result=insertDetail(classNo,employeeNo,workTypeNo);
	         if(result)
	         {
	         	strcpy(buffer,"/sd");strcat(buffer," ");strcat(buffer,"0");
			 }
	         else
			 {
			 	strcpy(buffer,"/sd");strcat(buffer," ");strcat(buffer,"n");
			 }
        }
      } 
}
void cu()
{
	int count=parseCount(buffer);//check number of parameter is right or not 
	if(count!=4)//�����������ԣ���������������ͷ��
	{
		strcpy(buffer,"/su");
		strcat(buffer," n");
		if(count!=1){printf("number of parameter from client error\n"); }
	}
	else
	{  
		char * classNo_=strchr(buffer,' ')+1;
		strcpy(temp,classNo_);
		int classNo=atoi(parseHead(temp));
		char * employeeNo_=strchr(classNo_,' ')+1; 
		strcpy(temp,employeeNo_);
		int employeeNo=atoi(parseHead(temp));
		char *workTypeName_=strchr(employeeNo_,' ')+1; 
		strcpy(temp,workTypeName_);
		//int workTypeNo=atoi(parseHead(temp));
		int workTypeNo=get_workTypeNo(parseHead(temp));
		char * detail=strchr(workTypeName_,' ')+1; 
		int result=cuDetail(classNo,employeeNo,workTypeNo,detail);
		memset(buffer,0,sizeof(buffer));
		if(result)
		{strcpy(buffer,"/su");strcat(buffer," y");}
		else
		{strcpy(buffer,"/su");strcat(buffer," n");}
	}  
}
void cw()//�鿴�������а�����
{
  int count=parseCount(buffer);//check number of parameter is right or not 
  if(count!=0)
  {
	    strcpy(buffer,"/sw");
	    strcat(buffer," \n\0");
	    if(count!=1)
		{
			printf("number of parameter from client error\n"); 
		}
   }
   else
   {  
        int count=cwDetail();
        strcpy(temp,buffer);
        memset(buffer,0,sizeof(buffer));
        if(count)
        {
        	strcpy(buffer,"/sw");
			strcat(buffer," ");
			strcat(buffer,temp);
		}
         else
        {
  			strcpy(buffer,"/sw");
			strcat(buffer," ");
			strcat(buffer,"n\n\0");
		}
    } 
}

void starCw()//�鿴�������в�Ʒ������¼���
{
  int count=parseCount(buffer);//check number of parameter is right or not 
  if(count!=0)
  {
	    strcpy(buffer,"*sw");
	    strcat(buffer," \n\0");
	    if(count!=1)
		{
			printf("number of parameter from client error\n"); 
		}
   }
   else
   {  
        int count=starCwDetail();
        strcpy(temp,buffer);
        memset(buffer,0,sizeof(buffer));
        if(count)
        {
        	strcpy(buffer,"*sw");
			strcat(buffer," ");
			strcat(buffer,temp);
		}
         else
        {
  			strcpy(buffer,"*sw");
			strcat(buffer," ");
			strcat(buffer,"no data\n\0");
		}
    } 
}
void ci()//C#�ˣ���������
{
	int count=getCount(buffer,'|');//check number of parameter is right or not 
	if(count!=4)
	{
		strcpy(buffer,"/si");
		strcat(buffer,"\n\0");
		if(count!=1){printf("number of parameter from client error\n\tnumber of parameter:%d",count); }
	}
	else
	{  
		char * classNo_=strchr(buffer,' ')+1;
		strcpy(temp,classNo_);
		int classNo=atoi(getHead(temp,'|'));
		char *workTypeNo_=strchr(classNo_,'|')+1; 
		strcpy(temp,workTypeNo_);
		//int workTypeNo=atoi(parseHead(temp));
		int workTypeNo=atoi(getHead(temp,'|'));                
		char * beginCalendar_=strchr(workTypeNo_,'|')+1;
		strcpy(temp,beginCalendar_);
		char * beginCalendar=(char *)malloc(sizeof(char)*20);
		char * endCalendar=(char *)malloc(sizeof(char)*20);
		strcpy(beginCalendar,getHead(temp,'|'));
		strcpy(endCalendar,strchr(beginCalendar_,'|')+1);
		//char * endCalendar=getHead(temp,'|');
		Debug("%d-%d-%s-%s",classNo,workTypeNo,beginCalendar,endCalendar);
		//printf("endCalendar1:%s",endCalendar);
		strcpy(temp,endCalendar);//printf("temp1:%s",temp);
		int count=ciDetail(classNo,workTypeNo,beginCalendar,temp);
		free(beginCalendar);
		free(endCalendar);
		strcpy(temp,buffer);
		memset(buffer,0,sizeof(buffer));
		//Debug("count:%d",count);
		if(count)
		{strcpy(buffer,"/si");strcat(buffer," ");strcat(buffer,temp);}
		 else
		{
			strcpy(buffer,"/si");strcat(buffer," ");strcat(buffer,"no data\n\0");
		}
	} 
}


