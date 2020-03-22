#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <errno.h>
#include <pthread.h>

#define MAX_WAITING_TASKS	3000
#define MAX_ACTIVE_THREADS	100

#define BUFSIZE			300
#define PATHSIZE		300



struct task
{
	
	void *arg;
	void *(*do_task)(void *arg);
	
	struct task *next;
};


typedef struct thread_pool
{
	pthread_mutex_t lock;
	pthread_cond_t  cond;

	bool shutdown;  // 线程池是否要销毁

	struct task *task_list;

	pthread_t *tids;

	unsigned max_waiting_tasks;
	unsigned waiting_tasks;
	unsigned active_threads;

	int max_index;
	
}thread_pool;


bool init_pool(thread_pool *pool, unsigned int threads_number);
bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *task);
int  add_thread(thread_pool *pool, unsigned int additional_threads_number);
int  remove_thread(thread_pool *pool, unsigned int removing_threads_number);
bool destroy_pool(thread_pool *pool);

void *routine(void *arg);


#endif