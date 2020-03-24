#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



#include "scope.h"



int main()
{
	ScopeAAATest();
	ScopeBBBTest();
	ScopeCCCTest();
	
}

/*
define 的作用域在一个编译单元内。即一个.c或者.cpp

如果是头文件包含，将头文件的所有内容替入该编译单元中，则比较好理解

如果编译生成了库，那么库里面的宏定义能被开启吗

*/
