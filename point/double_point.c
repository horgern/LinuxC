#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int i;
	char *double_p;
} DoublePoint_t;

DoublePoint_t double_p_s;
void TestPoint(char *p)
{
	double_p_s.double_p = p;
	
}

int main()
{
	//char **real_q = NULL;
	//char *real_p = NULL;
	char t = 'C';
	//real_p = &t;
	TestPoint(&t);
	printf("double_p_s.double_p : %c\n", *(double_p_s.double_p));
}