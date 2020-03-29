/********************************************************************************
 *枚举说明 ，enum week{ Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun } day;
			可以等于enum week{ Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun }; int day;
 ********************************************************************************/

#include <stdio.h>
int main(){
    enum week{ Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun } day;
    scanf("%d", &day);
    switch(day){
        case Mon: puts("Monday"); break;
        case Tues: puts("Tuesday"); break;
        case Wed: puts("Wednesday"); break;
        case Thurs: puts("Thursday"); break;
        case Fri: puts("Friday"); break;
        case Sat: puts("Saturday"); break;
        case Sun: puts("Sunday"); break;
        default: puts("Error!");
    }
    return 0;
}

