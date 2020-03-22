#include <stdio.h>
#include <stdlib.h>


int main()
{

	int i = 0;
	for (i = 0; i < 5; i++) {
		if (i != 1 || i != 2) {
			printf("[1] i = %d\n", i);//全部打印
			
		} 
		
	}
	printf("================================\n");

	for (i = 0; i < 5; i++) {

		if (i == 1 && i == 2) {
			printf("[2] i = %d\n", i);//不打印
			
		} 
		
	}
	printf("================================\n");

	for (i = 0; i < 5; i++) {
		if (i != 1 && i != 2) {
			printf("[3] i = %d\n", i);//除掉这两个打印
			
		} 
		
	}
	printf("================================\n");

	for (i = 0; i < 5; i++) {

		if (i == 1 || i == 2) {
			printf("[4] i = %d\n", i);//打印两个
		} 
	}



}


