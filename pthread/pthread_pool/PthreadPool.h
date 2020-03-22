#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>


#define DEFAULT_TIME 		1        /*默认时间10s*/
#define MIN_WAIT_TASK_NUM 	10       /*当任务数超过了它，就该添加新线程了*/
#define DEFAULT_THREAD_NUM 	10       /*每次创建或销毁的线程个数*/
 
  



 /*任务*/
typedef struct {
   void *(*function)(void *);
   void *arg;
} ThreadPoolTask_t;
 
/*线程池管理*/
typedef struct {
   pthread_mutex_t lock;                 /* 锁住整个结构体 */
   pthread_mutex_t thread_counter;       /* 用于使用忙线程数时的锁 */
   pthread_cond_t  queue_not_full;       /* 条件变量，任务队列不为满 */
   pthread_cond_t  queue_not_empty;      /* 任务队列不为空 */
 
   pthread_t *threads;                   /* 存放线程的tid,实际上就是管理线程 数组 */
   pthread_t admin_tid;                  /* 管理者线程tid */
   ThreadPoolTask_t *task_queue;         /* 任务队列 */
 
   /*线程池信息*/
   int min_thr_num;                      /* 线程池中最小线程数 */
   int max_thr_num;                      /* 线程池中最大线程数 */
   int live_thr_num;                     /* 线程池中存活的线程数 */
   int busy_thr_num;                     /* 忙线程，正在工作的线程 */
   int wait_exit_thr_num;                /* 需要销毁的线程数 */
 
   /*任务队列信息*/
   int queue_front;                      /* 队头 */
   int queue_rear;                       /* 队尾 */
   int queue_size; 
 
   /* 存在的任务数 */
   int queue_max_size;                   /* 队列能容纳的最大任务数 */
 
   /*状态*/
   int shutdown;                         /* true为关闭 */
}ThreadPool_t;
 
 
/*  函数原型  */
 
/*创建线程池*/
ThreadPool_t *ThreadPoolCreate(int min_thr_num, int max_thr_num, int queue_max_size);
/*释放线程池*/
int ThreadPoolFree(ThreadPool_t *pool);
/*销毁线程池*/
int ThreadPoolDestroy(ThreadPool_t *pool);
/*管理线程*/
void *AdminThread(void *thread_pool);
/*线程是否存在*/
int IsThreadAlive(pthread_t tid);
/*工作线程*/
void *TaskThread(void *thread_pool);
/*向线程池的任务队列中添加一个任务*/
int ThreadPoolAddTask(ThreadPool_t *pool, void *(*function)(void *arg), void *arg);


#ifdef __cplusplus
}
#endif

#endif
