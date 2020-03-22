#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *Malloc()
{
	char *p = calloc(1, 1024);

	memcpy(p, "chz", 3);
	return p;
}

void Malloc_Error(char *p)
{
	p = calloc(1, 1024);

	memcpy(p, "name", 4);
}
void Malloc_Right(char **p)
{
	*p = calloc(1, 1024);

	memcpy(*p, "name", 4);
}


int main()
{
	char *p = NULL;
	p = Malloc(p);
	printf("%s\n", p);
	free(p);
	p = NULL;
	Malloc_Error(p);
	printf("p = %s\n", p);
	free(p);


	char *q = NULL;
	Malloc_Right(&q);
	printf("q : %s\n", q);
	return 0;
}
