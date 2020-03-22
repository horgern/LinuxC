#include <stdio.h>
#include <unistd.h>
#define COLOR_END                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r"



int PrintColorTest(void)
{
    printf("This is a character control test!\n" );
    sleep(3);
    printf("[%2u]" CLEAR "CLEAR\n" COLOR_END, __LINE__);

    printf("[%2u]" BLACK "BLACK " L_BLACK "L_BLACK\n" COLOR_END, __LINE__);
    printf("[%2u]" RED "RED " L_RED "L_RED\n" COLOR_END, __LINE__);
    printf("[%2u]" GREEN "GREEN " L_GREEN "L_GREEN\n" COLOR_END, __LINE__);
    printf("[%2u]" BROWN "BROWN " YELLOW "YELLOW\n" COLOR_END, __LINE__);
    printf("[%2u]" BLUE "BLUE " L_BLUE "L_BLUE\n" COLOR_END, __LINE__);
    printf("[%2u]" PURPLE "PURPLE " L_PURPLE "L_PURPLE\n" COLOR_END, __LINE__);
    printf("[%2u]" CYAN "CYAN " L_CYAN "L_CYAN\n" COLOR_END, __LINE__);
    printf("[%2u]" GRAY "GRAY " WHITE "WHITE\n" COLOR_END, __LINE__);

    printf("[%2u]\e[1;31;40m Red \e[0m\n",  __LINE__);

    printf("[%2u]" BOLD "BOLD\n" COLOR_END, __LINE__);
    printf("[%2u]" UNDERLINE "UNDERLINE\n" COLOR_END, __LINE__);
    printf("[%2u]" BLINK "BLINK\n" COLOR_END, __LINE__);
    printf("[%2u]" REVERSE "REVERSE\n" COLOR_END, __LINE__);
    printf("[%2u]" HIDE "HIDE\n" COLOR_END, __LINE__);

    printf("Cursor test begins!\n" );
    printf("=======!\n" );
    
    printf("[%2u]" "\e[2ACursor up 2 lines\n" COLOR_END, __LINE__);
    
    printf("[%2u]" "\e[2BCursor down 2 lines\n" COLOR_END, __LINE__);
    
    printf("[%2u]" "\e[?25lCursor hide\n" COLOR_END, __LINE__);
    
    printf("[%2u]" "\e[?25hCursor display\n" COLOR_END, __LINE__);
    

    printf("Test ends!\n" );
    sleep(3);
    printf("[%2u]" "\e[2ACursor up 2 lines\n" COLOR_END, __LINE__);
    
    printf("[%2u]" "\e[KClear from cursor downward\n" COLOR_END, __LINE__);

    return 0 ;
}
int main()
{
	
	printf("[%2u]" RED "RED " L_RED "L_RED\n" COLOR_END, __LINE__);
}
