#include <stdio.h>
#include <unistd.h>
int main()
{

	int res = symlink("./testLink", "./zhd");
	printf("res = %d\n", res);
}
