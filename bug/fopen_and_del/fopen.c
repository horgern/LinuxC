#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>


void SignalHandler(int signal)
{
	printf("signal : %d\n", signal);
}

int main()
{
	signal(SIGPIPE, SignalHandler);
	signal(SIGABRT, SignalHandler);
	signal(SIGSEGV, SignalHandler);
	signal(SIGHUP, SignalHandler);
	signal(SIGQUIT, SignalHandler);
	FILE *fp = fopen("./fopen.txt", "ab+");
	int n_write = 0;
	while(1)
	{
		n_write = fwrite("test\n", 6, 1, fp);
		if (n_write < 0) {
			printf("[%d] : %s\n", errno, strerror(errno));
		} else {
			printf("write ok\n");
		}
		sleep(1);	
		fflush(fp);
	}	
	
	fclose(fp);
}
