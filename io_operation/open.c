#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int main()
{

	int fd = open("open.txt", O_RDWR | O_CREAT);
	int nwrite = 0;
	while(1) 
	{
		sleep(1);
		nwrite = write(fd, "open test\n", sizeof("open test\n"));
		if (nwrite < 0) {
			printf("%d  : %s", errno, strerror(errno));
		} else {
			printf("write open ok\n");
		}
	}
	close(fd);
}
