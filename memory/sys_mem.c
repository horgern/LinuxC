#include <stdio.h>
#include <sys/sysinfo.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#if 0	//for note
struct sysinfo
{
    long uptime;             /* Seconds since boot */
    unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
    unsigned long totalram;  /* Total usable main memory size */
    unsigned long freeram;   /* Available memory size */
    unsigned long sharedram; /* Amount of shared memory */
    unsigned long bufferram; /* Memory used by buffers */
    unsigned long totalswap; /* Total swap space size */
    unsigned long freeswap;  /* swap space still available */
    unsigned short procs;    /* Number of current processes */
    unsigned long totalhigh; /* Total high memory size */
    unsigned long freehigh;  /* Available high memory size */
    unsigned int mem_unit;   /* Memory unit size in bytes */
    char _f[20-2*sizeof(long)-sizeof(int)]; /* Padding for libc5 */
};

#endif

int main()
{
    struct sysinfo si;
    sysinfo(&si);
    printf("Totalram:%lu\n", si.totalram);
    printf("Available:%lu\n", si.freeram);

	printf("Totalram:%.1f\n", (float)si.totalram / 1024 / 1024 / 1024);
    printf("Available:%.1f\n", (float)si.freeram / 1024 / 1024 / 1024);


	char *p = malloc(si.totalram);
	if (p == NULL) {
		perror("malloc");
	}
	printf("malloc %lu success\n", si.totalram);
	*(p+si.totalram) = 'c';
	printf("[%c]\n", *(p+si.totalram));
	pause();
    return 0;
}

