clude "thread_pool.h"

void handler(void *arg)
{
	pthread_mutex_unlock((pthread_mutex_t *)arg);
}


void *routine(void *arg)
{
	thread_pool *pool = (thread_pool *)arg;
	struct task *p;
	
	while(1)
	{
		pthread_cleanup_push(handler, (void *)&pool->lock);//注册一个回调函数，线程异常退出时解锁
		pthread_mutex_lock(&pool->lock);
		
		while(pool->waiting_tasks == 0 && !pool->shutdown)
		{
			pthread_cond_wait(&pool->cond, &pool->lock);
		}
		
		// 没活干，而且要销毁线程池，那么最简单，直接走人
		if(pool->waiting_tasks == 0 && pool->shutdown == true)
		{
			pthread_mutex_unlock(&pool->lock);
			pthread_exit(NULL); // CANNOT use 'break';
		}

		// 取任务
		p = pool->task_list->next;
		
		pool->task_list->next = p->next;
		pool->waiting_tasks--;
		printf("[%s][%d]: waiting_task: %d\n", __FUNCTION__,
			__LINE__, pool->waiting_tasks);
		
		pthread_mutex_unlock(&pool->lock);
		pthread_cleanup_pop(0);//注销该函数
		
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);//线程不可取消，直到程序运行到这里
		(p->do_task)(p->arg);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);//线程可取消，发送cancel命令后立即取消
		
		free(p);
	}
	
	pthread_exit(NULL);
}


bool init_pool(thread_pool *pool, unsigned int threads_number)
{
	pthread_mutex_init(&pool->lock, NULL);
	pthread_cond_init(&pool->cond, NULL);
	
	pool->shutdown = false;
	
	// 搞一个空链表
	pool->task_list = malloc(sizeof(struct task));
	if(pool->task_list == NULL)
	{
		perror("allocate memory error");
		return false;
	}
	pool->task_list->next = NULL;

	pool->tids = calloc(MAX_ACTIVE_THREADS, sizeof(pthread_t));
	if(pool->tids == NULL)
	{
		perror("allocate memory error");
		return false;
	}

	pool->max_waiting_tasks = MAX_WAITING_TASKS;
	pool->waiting_tasks  = 0;
	pool->active_threads = 0;

	int i;
	for(i=0; i<threads_number; i++)
	{
		if(pthread_create(&((pool->tids)[i]), NULL,
					routine, (void *)pool) != 0)
		{
			perror("create threads error");
			return false;
		}
		pool->active_threads++;
		pool->max_index = i;
	}

	return true;
}


bool add_task(thread_pool *pool,
	      void *(*do_task)(void *arg), void *arg)
{
	// 创建一个任务节点，这是一段非临界区代码，尽量不要放在锁里面
	struct task *new_task = malloc(sizeof(struct task));
	if(new_task == NULL)
	{
		perror("allocate memory error");
		return false;
	}
	new_task->do_task = do_task;
	new_task->arg = arg;
	new_task->next = NULL;
	
	
	//============ LOCK =============//
	pthread_mutex_lock(&pool->lock);
	//===============================//

	if(pool->waiting_tasks >= MAX_WAITING_TASKS)
	{
		pthread_mutex_unlock(&pool->lock);

		fprintf(stderr, "too many tasks.\n");
		free(new_task);

		return false;
	}
	
	// 将节点放入任务链表
	struct task *tmp = pool->task_list;
	while(tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = new_task;
	pool->waiting_tasks++;
	
	//=========== UNLOCK ============//
	pthread_mutex_unlock(&pool->lock);
	//===============================//
	
	pthread_cond_signal(&pool->cond);
	return true;
}


int add_thread(thread_pool *pool, unsigned additional_threads)
{
	if(additional_threads == 0)
		return 0;

	unsigned total_threads =
			pool->active_threads + additional_threads;

	int i, actual_increment = 0;
	for(i = pool->active_threads;
	    i < total_threads && i < MAX_ACTIVE_THREADS;
	    i++)
	{
		if(pthread_create(&((pool->tids)[i]),
					NULL, routine, (void *)pool) != 0)
		{
			perror("add threads error");

			// no threads has been created, return fail
			if(actual_increment == 0)
				return -1;

			break;
		}
		actual_increment++; 

		pool->max_index = i;
	}

	pool->active_threads += actual_increment;
	return actual_increment;
}


int remove_thread(thread_pool *pool, unsigned int removing_threads)
{
	if(removing_threads == 0)
		return pool->active_threads;

	int remaining_threads = pool->active_threads - removing_threads;
	remaining_threads = remaining_threads > 0 ? remaining_threads : 1;

	int i;
	for(i=pool->active_threads-1; i>remaining_threads-1; i--)
	{
		errno = pthread_cancel(pool->tids[i]);

		if(errno != 0)
			break;
	}


	if(i == pool->active_threads-1)
		return -1;
		
	else
	{
		pool->active_threads = i+1;
		return i+1;
	}
}



bool destroy_pool(thread_pool *pool)
{
	// 1, activate all threads
	pool->shutdown = true;
	pthread_cond_broadcast(&pool->cond);
	

	// 2, wait for their exiting
	int i;
	for(i=0; i<pool->max_index; i++)
	{
		errno = pthread_join(pool->tids[i], NULL);
		if(errno != 0)
		{
			printf("join tids[%d] error: %s\n",
					i, strerror(errno));
		}
	}

	// 3, free memories
	free(pool->task_list);
	free(pool->tids);
	free(pool);

	return true;
}
























	