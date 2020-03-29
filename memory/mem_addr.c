#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME 	s"chz"
#define AGE		18
int g_global = 0;

void Test()
{
	printf("[%s][%d]\n", __func__, __LINE__);
}

int main()
{
	int i = 0;
	printf("g_global [%p]\n", &g_global);
	printf("i [%p]\n", &i);
	printf("Test() [%p]\n", &Test);
}

