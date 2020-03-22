#include <stdio.h>

void GetStaticNum(int flag)
{
	static int num;
	if (flag == 0) {
		num = 0;
	}
	num ++;

	printf("num = %d\n", num);
}

int main()
{
	GetStaticNum(0);
	GetStaticNum(1);
	GetStaticNum(1);
	GetStaticNum(1);
	GetStaticNum(1);
	
}
