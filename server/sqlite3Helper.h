#ifndef SQLITE3HELPER_H
#define SQLITE3HELPER_H
#define CONNSTR_LEN   50
extern char connStr[CONNSTR_LEN];//连接的数据库名称
extern char acBackupDBDir[CONNSTR_LEN];
extern char acDBDir[CONNSTR_LEN];
sqlite3 * open_sqlite3();//打开数据库，建立数据库连接
int closeSqlite3(sqlite3 *conn);//关闭数据库
sqlite3 * OpenMemorySqlite3();//创建内存数据库
int CloseMemorySqlite3(sqlite3 *conn);//关闭内存数据库
int loadOrSaveDb(sqlite3 *pInMemeory, const char *zFilename, int isSave)  ;
int BackupDB(char * pcObjectDir);//备份数据库
int GetDBDir(char * pcDBDir);//获得数据库存储路径
int DeleteEmployee(char * pcUserName);
int UpdateEmployee(char *pcEmployeeNo,char * pcName, char * pcPwd,int iPositionNo,int iPlantNo,int iWorkTypeNo);
int InsertEmployee(char *pcEmployeeNo,char * pcName, char * pcPwd,int iPositionNo,int iPlantNo,int iWorkTypeNo);
int InsertRes(int iResMakerNo,char * pcResText, 
	char * pcPostion,int * piResNo);

void getEmployeesByPlantNo(int );//获得其所在车间的所有员工信息
void get_employee_table();//获得员工信息表
int GetRessByPositionNo(char * pcPositionNo);
void get_plant_table( );//获得车间表信息
void get_quality_table( );//获得品质表信息
void get_workType_table();//获得工种号
void get_classNoByDate(char * beginCalendar,char * endCalendar);//获得指定日期的班次号
int get_employeeNo(char *);//根据员工姓名，获得员工号 
int get_workTypeNo(char * pcProductName);//根据工种名称，获得工种号
int get_plantNo(char * pcPlantName);
int get_positionNo(char * pcPositionName);
char parseQualityNo(int qualityNo);//根据品质号获得品质等级
int get_newestclassNo();//获得最新的班次号
int create_newclass(char *);//获得品质管理员员工号，创建一个班次
int InsertIntoClass(int m_iEmployeeNo,int iPlantNo,char * pcClassRange);
int IsInsertedIntoDetail(int classNo,int employeeNo,int workTypeNo);
int getClassesByTime(char * beginCalendar,char * endCalendar);
int work_over(int iClassNo );//班函数，根据班次号，自动完成下班信息记录
int cuDetail(int ,int,int ,char *);//update详细表（detail）中的具体数据（concreteData）,成功返回1，失败返回0
int cdDetail(int ,int ,int );//获得最新的详细表20条记录
int ciDetail(int classNo,int workTypeNo,char * beginCalendar,char * endCalendar);
int insertDetail(int ,int ,int);//在详细表中，插入1条记录，具体数据先设为"0" 
#endif
