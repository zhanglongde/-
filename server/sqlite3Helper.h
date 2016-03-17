#ifndef SQLITE3HELPER_H
#define SQLITE3HELPER_H
#define CONNSTR_LEN   50
extern char connStr[CONNSTR_LEN];//���ӵ����ݿ�����
extern char acBackupDBDir[CONNSTR_LEN];
extern char acDBDir[CONNSTR_LEN];
sqlite3 * open_sqlite3();//�����ݿ⣬�������ݿ�����
int closeSqlite3(sqlite3 *conn);//�ر����ݿ�
sqlite3 * OpenMemorySqlite3();//�����ڴ����ݿ�
int CloseMemorySqlite3(sqlite3 *conn);//�ر��ڴ����ݿ�
int loadOrSaveDb(sqlite3 *pInMemeory, const char *zFilename, int isSave)  ;
int BackupDB(char * pcObjectDir);//�������ݿ�
int GetDBDir(char * pcDBDir);//������ݿ�洢·��
int DeleteEmployee(char * pcUserName);
int UpdateEmployee(char *pcEmployeeNo,char * pcName, char * pcPwd,int iPositionNo,int iPlantNo,int iWorkTypeNo);
int InsertEmployee(char *pcEmployeeNo,char * pcName, char * pcPwd,int iPositionNo,int iPlantNo,int iWorkTypeNo);
int InsertRes(int iResMakerNo,char * pcResText, 
	char * pcPostion,int * piResNo);

void getEmployeesByPlantNo(int );//��������ڳ��������Ա����Ϣ
void get_employee_table();//���Ա����Ϣ��
int GetRessByPositionNo(char * pcPositionNo);
void get_plant_table( );//��ó������Ϣ
void get_quality_table( );//���Ʒ�ʱ���Ϣ
void get_workType_table();//��ù��ֺ�
void get_classNoByDate(char * beginCalendar,char * endCalendar);//���ָ�����ڵİ�κ�
int get_employeeNo(char *);//����Ա�����������Ա���� 
int get_workTypeNo(char * pcProductName);//���ݹ������ƣ���ù��ֺ�
int get_plantNo(char * pcPlantName);
int get_positionNo(char * pcPositionName);
char parseQualityNo(int qualityNo);//����Ʒ�ʺŻ��Ʒ�ʵȼ�
int get_newestclassNo();//������µİ�κ�
int create_newclass(char *);//���Ʒ�ʹ���ԱԱ���ţ�����һ�����
int InsertIntoClass(int m_iEmployeeNo,int iPlantNo,char * pcClassRange);
int IsInsertedIntoDetail(int classNo,int employeeNo,int workTypeNo);
int getClassesByTime(char * beginCalendar,char * endCalendar);
int work_over(int iClassNo );//�ຯ�������ݰ�κţ��Զ�����°���Ϣ��¼
int cuDetail(int ,int,int ,char *);//update��ϸ��detail���еľ������ݣ�concreteData��,�ɹ�����1��ʧ�ܷ���0
int cdDetail(int ,int ,int );//������µ���ϸ��20����¼
int ciDetail(int classNo,int workTypeNo,char * beginCalendar,char * endCalendar);
int insertDetail(int ,int ,int);//����ϸ���У�����1����¼��������������Ϊ"0" 
#endif
