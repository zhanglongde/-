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
#define SL_CE 12  //ĳ���������Ա�����
#define SL_SE 13
#define SL_CW 14  //��ȡ��������°�ε�20����ϸ���¼
#define SL_SW 15  //
#define SL_CI 16  //�����ƶ���ʽ����������ϸ���еļ�¼
#define SL_SI 17
#define SL_CG 18   //    /cg ��ʼʱ��|����ʱ��
#define SL_SG 19   //    /sg ��κ�1|��κ�2|��κ�3          ��ȡһ��ʱ���ڵİ�κ�
#define SL_CT 20   //   ��ȡ���ֱ�
#define SL_ST 21   //  /st ���ֺ�1����������1�����ֺ�2����������2�����ֺ�3����������3��......
#define ST_CL 22
#define ST_CE 23
#define ST_CW 24
extern char * flag[PROTOCOL_NUM];//����ͨ��Э��

void processStream();
void processStruct();
void starLogin();
void starGetAllEmployees();
int  checkLogin(char * , char *,int * piPosition );//�����¼�ɹ��򷵻�1����¼ʧ�ܷ���0
int reister(char * ,char *);//����ע�ắ��
//int IsInsertedIntoDetail(int classNo,int employeeNo,int workTypeNo);
void illegal();//�Ƿ�ͨ��Э�鴦��
//�������ݿ�
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
