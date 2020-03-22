#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	char *p = malloc(128);
	if (NULL == p) {
		printf("=======\n");
		return -1;
	}
	memset(p, '\0', 128);	
	p[1] = 39;
	printf("p = %d\n", p[1]);
	p = realloc(p, 256);
	if (NULL == p) {
		printf("++++++++\n");
		return -1;
	}
	
	printf("p[1] = %d\n", p[1]);
	
}
