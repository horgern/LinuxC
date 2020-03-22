#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "PthreadPool.h"
int g_exit = 0;
pthread_t g_tid = 0; //FIX ME
void KillPthread(int s)
{
	printf("[%s-%d]======tid : 0x%x=======\n", __func__, __LINE__, (unsigned int)pthread_self());
	
	
	//pthread_exit(NULL);
	
	//pthread_cancel(pthread_self());
}

void KillMainPthread(int s)
{
	printf("[%s-%d]======tid : 0x%x=======\n", __func__, __LINE__, (unsigned int)pthread_self());
	

	//pthread_cancel(pthread_self());
}

void *GetPtheadPid(void *buf)
{
	int i = 0, j = 0;
	//char exit = 0;
	//signal(SIGINT, KillPthread);
	//while(1) 
	for (j = 0; j < 10; j++)
	{
		
		printf("[%s-%d] ---- [%d]======tid : 0x%x=======\n", __func__, __LINE__, i, (unsigned int)pthread_self());
		i++;
		sleep(1);
		/*if (exit = getchar() == 'E') {
			break;
		}*/
		/*if (g_exit == 1) {
			break;
		}*/
	}

	return NULL;
}

int main()
{
	int i = 0;
	/* 线程池初始化，其管理者线程及工作线程都会启动 */
	ThreadPool_t *pPool = ThreadPoolCreate(MIN_WAIT_TASK_NUM, 100, 100);
	printf("threadpool init ... ... \n");
	//printf("[%s-%d] --- thread 0x%x ======== \n", __func__, __LINE__, (unsigned int)pthread_self());
	//printf("[%s-%d] --- getpid 0x%x ======== \n", __func__, __LINE__, (unsigned int)getpid());
	//signal(SIGINT, KillMainPthread);
	g_tid = pthread_self();

	
	/* 接收到任务后添加 */
	/*ThreadPoolAddTask(pPool, GetPtheadPid, NULL);
	ThreadPoolAddTask(pPool, GetPtheadPid, NULL);
	ThreadPoolAddTask(pPool, GetPtheadPid, NULL);*/
	for (i = 0; i < 50; i++) {
		ThreadPoolAddTask(pPool, GetPtheadPid, NULL);
	}
	// ... ...


	sleep(20);
	/* 销毁 */
	ThreadPoolDestroy(pPool);
	return 1;
}
