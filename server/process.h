#ifndef PROCESS_H
#define PROCESS_H

#define PROTOCOL_NUM  25
#define SL_CL 0
#define SL_CR 1
#define SL_CQ 2
#define SL_CP 3
#define SL_CC 4
#define SL_SC 5
#define SL_CO 6
#define SL_SO 7
#define SL_CD 8
#define SL_SD 9
#define SL_CU 10
#define SL_SU 11
#define SL_CE 12  //某车间的所有员工情况
#define SL_SE 13
#define SL_CW 14  //获取服务端最新班次的20条详细表记录
#define SL_SW 15  //
#define SL_CI 16  //按照制定格式条件搜索详细表中的记录
#define SL_SI 17
#define SL_CG 18   //    /cg 开始时间|结束时间
#define SL_SG 19   //    /sg 班次号1|班次号2|班次号3          获取一段时间内的班次号
#define SL_CT 20   //   获取工种表
#define SL_ST 21   //  /st 工种号1，工种名称1；工种号2，工种名称2；工种号3，工种名称3；......
#define ST_CL 22
#define ST_CE 23
#define ST_CW 24
extern char * flag[PROTOCOL_NUM];//声明通信协议

void processStream();
void processStruct();
void starLogin();
void starGetAllEmployees();
int  checkLogin(char * , char *,int * piPosition );//如果登录成功则返回1，登录失败返回0
int reister(char * ,char *);//定义注册函数
//int IsInsertedIntoDetail(int classNo,int employeeNo,int workTypeNo);
void illegal();//非法通信协议处理
//备份数据库
void starCb();
void starCg();

void starCd();
void starCu();
void starCr();

void cb();

void cl();
void cr();
void cq();
void cp();
void cc();
void co();
void cd();
void cu();
void ce();
void cw();
void ci();
void cg();
void ct();
/*************************************************************************************/

#endif
