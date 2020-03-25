#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//左对齐
void PrintByJustifyLeft()
{
	printf("|%-10s|%-10s|%-10s|\n", "name", "age", "company");
	printf("|%-10s|%-10d|%-10s|\n", "chz", 18, "china");

}

//右对齐
void PrintByJustifyRight()
{
	printf("|%10s|%10s|%10s|\n", "name", "age", "company");
	printf("|%10s|%10d|%10s|\n", "chz", 18, "china");

}

//保留多少位，不足以0补齐
void PrintSaveBytes()
{
	printf("|%.03f|\n", (float)10 / 3);		//保留小数点后位数
	printf("|%03d|\n", 3);					//保留多少位，不足在前面补0
	printf("|%010d|\n", 3);
}

int main()
{

	PrintByJustifyLeft();
	printf("=========================\n");
	PrintByJustifyRight();

	printf("\n\n=========================\n\n");

	PrintSaveBytes();
}
