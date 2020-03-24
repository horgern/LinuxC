#include "scope.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef DPrint
#define DPrint(format, ...) printf("<%s:%s-%d> " format"\n",\
    __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#endif




void ScopeBBBTest()
{

	DPrint("[%s][%s][%d]", __FILE__, __func__, __LINE__);
}

