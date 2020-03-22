#include <stdio.h>
#include <stdlib.h>

#define DIVIDE2(n)	 	 ( n >> 1 )
#define DIVIDE4(n)		 ( n >> 2 )
#define DIVIDE8(n)	 	 ( n >> 3 )
#define DIVIDE16(n)	 	 ( n >> 4 )
#define DIVIDE32(n)	 	 ( n >> 5 )
#define DIVIDE64(n)	 	 ( n >> 6 )
#define DIVIDE128(n)	 ( n >> 7 )
#define DIVIDE256(n)	 ( n >> 8 )
#define DIVIDE512(n)	 ( n >> 9 )
#define DIVIDE1024(n)	 ( n >> 10 )

#define MULTIPLY2(n)	 	 ( n << 1 )
#define MULTIPLY4(n)		 ( n << 2 )
#define MULTIPLY8(n)	 	 ( n << 3 )
#define MULTIPLY16(n)	 	 ( n << 4 )
#define MULTIPLY32(n)	 	 ( n << 5 )
#define MULTIPLY64(n)	 	 ( n << 6 )
#define MULTIPLY128(n)	 ( n << 7 )
#define MULTIPLY256(n)	 ( n << 8 )
#define MULTIPLY512(n)	 ( n << 9 )
#define MULTIPLY1024(n)	 ( n << 10 )

int MacrOperationTest()
{
	int n = 1024;
	
	printf("\n\n======================================\n\n");
	printf("DIVIDE2(%d) --> %d\n", n, DIVIDE2(n));
	printf("DIVIDE4(%d) --> %d\n", n, DIVIDE4(n));
	printf("DIVIDE8(%d) --> %d\n", n, DIVIDE8(n));
	printf("DIVIDE16(%d) --> %d\n", n, DIVIDE16(n));
	printf("DIVIDE32(%d) --> %d\n", n, DIVIDE32(n));
	printf("DIVIDE64(%d) --> %d\n", n, DIVIDE64(n));
	printf("DIVIDE128(%d) --> %d\n", n, DIVIDE128(n));
	printf("DIVIDE256(%d) --> %d\n", n, DIVIDE256(n));
	printf("DIVIDE512(%d) --> %d\n", n, DIVIDE512(n));
	printf("DIVIDE1024(%d) --> %d\n", n, DIVIDE1024(n));
	printf("\n\n======================================\n\n");
	n = 1;
	printf("MULTIPLY2(%d) --> %d\n", n, MULTIPLY2(n));
	printf("MULTIPLY4(%d) --> %d\n", n, MULTIPLY4(n));
	printf("MULTIPLY8(%d) --> %d\n", n, MULTIPLY8(n));
	printf("MULTIPLY16(%d) --> %d\n", n, MULTIPLY16(n));
	printf("MULTIPLY32(%d) --> %d\n", n, MULTIPLY32(n));
	printf("MULTIPLY64(%d) --> %d\n", n, MULTIPLY64(n));
	printf("MULTIPLY128(%d) --> %d\n", n, MULTIPLY128(n));
	printf("MULTIPLY256(%d) --> %d\n", n, MULTIPLY256(n));
	printf("MULTIPLY512(%d) --> %d\n", n, MULTIPLY512(n));
	printf("MULTIPLY1024(%d) --> %d\n", n, MULTIPLY1024(n));
	printf("\n\n======================================\n\n");
}

int main()
{
	MacrOperationTest();
}