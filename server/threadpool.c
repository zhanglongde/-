
/*********************************************/
//
// 			DATE:	2012-8-3
// 			TIME:	下午2:42:21
// 			author: sky
// 			file:	simple_pool.c
// 			todo:	TODO
//
/**********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include "threadpool.h"

//////////////////////
//具体实现如下
///////////////////////

void pool_init(int thread_max_num)
{
	pool = (Thread_pool *) malloc(sizeof(Thread_pool));

	pthread_mutex_init(&(pool->pool_mutex), NULL );
	pthread_cond_init(&(pool->pool_cond), NULL );

	pool->is_destory = 0; //0代表不销毁
	pool->worker_queue_head = NULL;
	pool->thread_max_num = thread_max_num;
	pool->cur_queue_size = 0;
	pool->thread_id = (pthread_t *) malloc(sizeof(pthread_t) * thread_max_num);
	int i = 0;
	for (; i < thread_max_num; i++)
	{
		pthread_create(&(pool->thread_id[i]), NULL, thread_routine, NULL );
	}

}

void * thread_routine(void *args)
{
	printf("starting thread 0x%x\n", pthread_self());
	while (1)
	{
		/*如果等待队列为0并且不销毁线程池，则处于阻塞状态; 注意
         pthread_cond_wait是一个原子操作，等待前会解锁，唤醒后会加锁*/
		pthread_mutex_lock(&(pool->pool_mutex));
		while (pool->cur_queue_size == 0 && !pool->is_destory)
		{
			printf("thread 0x%x is waiting\n", pthread_self());
			pthread_cond_wait(&(pool->pool_cond), &(pool->pool_mutex));
		}
		  /*线程池要销毁了*/
		if (pool->is_destory)
		{
			pthread_mutex_unlock(&(pool->pool_mutex));
			printf("thread 0x%x will exit\n", pthread_self());
			pthread_exit(NULL );
		}
		printf("thread 0x%x is starting to work\n", pthread_self());

		assert(pool->cur_queue_size!=0);
		assert(pool->worker_queue_head!=NULL);

		pool->cur_queue_size--;
		Thread_worker *worker = pool->worker_queue_head;
		pool->worker_queue_head = worker->next;
		pthread_mutex_unlock(&(pool->pool_mutex));
		/*调用回调函数，执行任务*/
		(*(worker->process_interface))(worker->arg);
		free(worker);
		worker = NULL;
	}
	pthread_exit(NULL );
}

int pool_add_worker(void *(*process)(void * args), void*args)
{
	Thread_worker *new_worker = (Thread_worker *) malloc(sizeof(Thread_worker));
	new_worker->process_interface = process;
	new_worker->arg = args;
	new_worker->next = NULL;

	  /*将任务加入到等待队列中*/
	pthread_mutex_lock(&(pool->pool_mutex));
	Thread_worker *member = pool->worker_queue_head;
	if (member != NULL )
	{
		while (member->next != NULL )
			member = member->next;
		member->next = new_worker;
	}
	else
	{
		pool->worker_queue_head = new_worker;
	}
	assert(pool->worker_queue_head!=NULL);

	pool->cur_queue_size++;
	pthread_mutex_unlock(&(pool->pool_mutex));
	 /*好了，等待队列中有任务了，唤醒一个等待线程；*/
	pthread_cond_signal(&(pool->pool_cond));
	return 0;
}

int pool_destory()
{
	if (pool->is_destory)
		return -1;
	pool->is_destory = 1;
	 /*唤醒所有等待线程，线程池要销毁了*/
	pthread_cond_broadcast(&(pool->pool_cond));

	int i;
	for (i = 0; i < pool->thread_max_num; i++)
		pthread_join(pool->thread_id[i], NULL );
	/*销毁各种变量*/
	free(pool->thread_id);

	Thread_worker *temp = NULL;
	while (pool->worker_queue_head != NULL )
	{
		temp = pool->worker_queue_head;
		pool->worker_queue_head = pool->worker_queue_head->next;
		free(temp);
	}

	pthread_mutex_destroy(&(pool->pool_mutex));
	pthread_cond_destroy(&(pool->pool_cond));

	free(pool);
	pool = NULL;
	return 0;
}

///////////////////////////////////////
//下面的代码就是如何调用thread pool
///////////////////////////////////////

void * my_process(void *arg)
{
	printf("Thread_id is 0x%x , working on task %d\n", pthread_self(),
			*(int *) arg);

	sleep(1);
	return NULL ;
}
#if 0
int main(int argc, char *argv[])
{
	pool_init(3);

	int *working_num = (int *) malloc(sizeof(int) * 5);
	int i = 0;
	for (; i < 5; i++)
	{
		working_num[i] = i;
		pool_add_worker(my_process, &working_num[i]);
	}

	sleep(5);
	pool_destory();
	free(working_num);
	return 0;
}

#endif


