#include "scope.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef DPrint
#define DPrint(format, ...) printf(format, ##__VA_ARGS__)
#endif




void ScopeCCCTest()
{

	DPrint("[%s][%s][%d]\n", __FILE__, __func__, __LINE__);
}

