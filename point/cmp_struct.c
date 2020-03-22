#include <string.h>
#include <stdio.h>

int main()
{
	double a = 0.0222;
	double b = 0.0227;
	int i = 0;
	i = memcpy((char *)(&a), (char *)(&b), sizeof(a));
	printf("i = %d\n", i);

}
