#include <stdio.h>
int main(void)
{
    int i;
    int *p;
    int a[5];
    for(i=0;i<5;i++) {
		
		a[i]=i;
    }
    p=(int*)a+4;
    for(i=1;i<=4;i++)
    {
        printf("%d\t[%d]\n",p[-i], a[-i]);
    }
    return 0;
}

