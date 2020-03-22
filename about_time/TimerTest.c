/*#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigalrm_fn(int sig)
{
    printf("sig: %d alarm!\n", sig);
    alarm(1);//定时发送信号
    return;
}
int main(void)
{
    signal(SIGALRM, sigalrm_fn);
    alarm(1);//开启定时信号
    while(1) {
		sleep(10);//这里加sleep没有作用
		printf("you click the enter\n");
	}		
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
int sec;
void sigroutine(int signo){
	switch (signo){
		case SIGALRM:
			printf("Catch a signal -- SIGALRM %d\n", signo);
			signal(SIGALRM, sigroutine);
			break;
		case SIGVTALRM:
			printf("Catch a signal -- SIGVTALRM %d\n", signo);
			signal(SIGVTALRM, sigroutine);
			break;
	}
	return;
}
int main()
{
	struct itimerval value, ovalue, value2; 		 //(1)
	sec = 5;
	printf("process id is %d\n", getpid());
	signal(SIGALRM, sigroutine);
	signal(SIGVTALRM, sigroutine);
	value.it_value.tv_sec = 1;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;
   setitimer(ITIMER_REAL, &value, &ovalue);    //(2)
	value2.it_value.tv_sec = 0;
	value2.it_value.tv_usec = 500000;
	value2.it_interval.tv_sec = 0;
	value2.it_interval.tv_usec = 500000;
	setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
	for(;;)
		;
}
*/

#include <stdio.h>
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int msleep(long ms) {

   struct timeval tv;

   tv.tv_sec = 0;

   tv.tv_usec = ms * 1000;

   return select(0, NULL, NULL, NULL, &tv);

}

int main()
{

	int res = msleep(2000);
	printf("res = %d\n", res);

}
