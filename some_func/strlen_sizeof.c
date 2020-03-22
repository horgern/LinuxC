#include <stdio.h>
#include <string.h>
#include <strings.h>


int main()
{
	char str[] = "0123456789";//default more len of string than 1 
	printf("strlen : %d\n", strlen(str));
	printf("sizeof : %d\n", sizeof(str));

	printf("=========================\n");
	char str11[20] = "0123456789";
	printf("strlen : %d\n", strlen(str11));
	printf("sizeof : %d\n", sizeof(str11));

	printf("=========================\n");
	char str22[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
	printf("strlen : %d\n", strlen(str22));
	printf("sizeof : %d\n", sizeof(str22));

	printf("=========================\n");
	int p[12] = {0};
	printf("%d\n", sizeof(p));	
}
