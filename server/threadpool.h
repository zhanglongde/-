
/*
*线程池里所有运行和等待的任务都是一个Thread_worker
*由于所有任务都在链表里，所以是一个链表结构
*/
typedef struct worker
{
	 /*回调函数，任务运行时会调用此函数，注意也可声明成其它形式*/
	void *(*process_interface)(void * arg);
	void *arg;
	struct worker * next;

} Thread_worker;

typedef struct
{
	pthread_mutex_t pool_mutex;
	pthread_cond_t pool_cond;

	/*任务队列的头指针*/
	Thread_worker *worker_queue_head;

	/*是否销毁线程池*/
	int is_destory;
	pthread_t * thread_id;
	int thread_max_num;
	int cur_queue_size;

} Thread_pool;

//此处声明了一个pool的全局变量
Thread_pool *pool = NULL;

//////////////////////////////////
//
//function:pool_init
//arguments:thread_max_num
//TODO:初始化连接池
//
///////////////////////////////////
void pool_init(int thread_max_num);

//////////////////////////////////
//
//function:pool_add_worker
//arguments:void *(*process)(void *args), void *args
//TODO:添加任务
//
///////////////////////////////////
int pool_add_worker(void *(*process)(void *args), void *args);

void *thread_routine(void * args);

//////////////////////////////////
//
//function:pool_destory
//arguments:
//TODO:销毁连接池
//
///////////////////////////////////
int pool_destory();


