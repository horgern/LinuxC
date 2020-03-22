#include <stdio.h>
#include <stdlib.h>
/*C语言预处理器定义的一些宏 
__LINE__  当时行号（预处理器正在执行的那一时刻），十进制数 
__FUNCTION__ 当时函数，字符串 
__FILE__当时文件，字符串 
__DATE__当时日期，字符串 
__TIME__当时时间，字符串 
等 
*/  

int SystemParamTest()
{
	printf("date[%s] time[%s] file[%s] func[%s] line[%d]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
}

/*
该时间，记录的是编译生成的时间，日期！
[root@localhost marco]# ./system_macro
date[Mar 21 2020] time[23:51:00] file[system_macro.c] func[SystemParamTest] line[14]
*/

int main()
{
	SystemParamTest();
}