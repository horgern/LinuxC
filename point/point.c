#include <stdio.h>
#include <unistd.h>

int main()
{
	int a = 8;
	int *p = &a;
	int *q = p;
	
	p = NULL;
	printf("*q[%d]\n", *q);
//	printf("*p[%d]\n", *p);
	*q = 7;
	printf("a = %d\n", a);
}
