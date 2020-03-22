#include <stdio.h>
#include <pthread.h>

typedef struct {
	int num;
	char array[20];
} PthreadTestPara_t;
PthreadTestPara_t p_struct[20] = {0};


int g_num = 0;
void *PthreadGetDataFromArray(void *argv)
{
	PthreadTestPara_t  *p = (PthreadTestPara_t *)argv;
	pthread_mutex_t lock;
	pthread_mutex_lock(&lock);

	printf("pthread[%x] : num : %d\n", (unsigned int)pthread_self(), p->num);
	
	g_num = p->num;
	printf("pthread[%x] : g_num : %d\n",  (unsigned int)pthread_self(), g_num);
	sleep(3 * p->num);
	pthread_mutex_unlock(&lock);

}

int main()
{
	pthread_t pid;
	int i = 0;
	for (i = 0; i < 5; i++) {
		p_struct[i].num = i;
		pthread_create(&pid, NULL, PthreadGetDataFromArray, (void *)&(p_struct[i]));
		pthread_detach(pid);
	}
	sleep(50);
	return 0;
}
