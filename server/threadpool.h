
/*
*�̳߳����������к͵ȴ���������һ��Thread_worker
*�������������������������һ������ṹ
*/
typedef struct worker
{
	 /*�ص���������������ʱ����ô˺�����ע��Ҳ��������������ʽ*/
	void *(*process_interface)(void * arg);
	void *arg;
	struct worker * next;

} Thread_worker;

typedef struct
{
	pthread_mutex_t pool_mutex;
	pthread_cond_t pool_cond;

	/*������е�ͷָ��*/
	Thread_worker *worker_queue_head;

	/*�Ƿ������̳߳�*/
	int is_destory;
	pthread_t * thread_id;
	int thread_max_num;
	int cur_queue_size;

} Thread_pool;

//�˴�������һ��pool��ȫ�ֱ���
Thread_pool *pool = NULL;

//////////////////////////////////
//
//function:pool_init
//arguments:thread_max_num
//TODO:��ʼ�����ӳ�
//
///////////////////////////////////
void pool_init(int thread_max_num);

//////////////////////////////////
//
//function:pool_add_worker
//arguments:void *(*process)(void *args), void *args
//TODO:�������
//
///////////////////////////////////
int pool_add_worker(void *(*process)(void *args), void *args);

void *thread_routine(void * args);

//////////////////////////////////
//
//function:pool_destory
//arguments:
//TODO:�������ӳ�
//
///////////////////////////////////
int pool_destory();


