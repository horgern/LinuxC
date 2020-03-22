#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
pthread_mutex_t queue_lock; 	
pthread_cond_t	queue_ready; 


void *routine(void * argc)
{
	int ret = 0;
	struct timespec tsp;
    struct timeval now;
	gettimeofday(&now, NULL);
	tsp.tv_sec = now.tv_sec;
	tsp.tv_nsec = now.tv_usec * 1000;
	tsp.tv_sec += 2;


	pthread_mutex_lock(&queue_lock);
printf("cond begin lock\n");

	ret = pthread_cond_timedwait(&queue_ready, &queue_lock, &tsp);
printf("ret : %d\n", ret);

	if(156384712 + 16 == ret) {
		printf("Thread %lu wait timeout.", pthread_self());
		return NULL;
	}
	printf("response cond\n");
	pthread_mutex_unlock(&queue_lock);

}

int main()
{
    if (pthread_mutex_init(&queue_lock, NULL) !=0) {
        printf("pthread_mutex_init error.");
    }
    if (pthread_cond_init(&queue_ready, NULL) !=0 ) {
        printf("pthread_cond_init error.");
    }

	pthread_t pid;
	pthread_create(&pid, NULL, &routine, NULL);
	sleep(4);
	//pthread_mutex_lock(&queue_lock);
	pthread_cond_signal(&queue_ready);
	printf("sinal cond\n");
	sleep(20);
	//pthread_mutex_unlock(&queue_lock);
	
}
