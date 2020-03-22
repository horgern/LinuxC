#include <stdio.h>
#include <unistd.h>

int main()
{


#ifdef __unix
	printf("Unix\n");
#endif 
#ifdef __linux
    printf("Linux\n");
#endif
/*#ifdef __sun
    #ifdef __sparc
            printf("Sun SPARC\n");
    #else
         printf("Sun X86\n");
    #endif
#endif
	#ifdef _AIX
            printf("AIX\n");
	#endif
 
#else
 
#ifdef WINVER
    printf("Windows\n");
#endif
 
#endif
*/
}
