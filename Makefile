GCC = gcc
STRIP = strip

#SOURCE = pthread_pool/PthreadPool.c test/PthreadMain.c
SOURCE = file_operation/FileOperation.c test/main.c console_printf/ConsolePrintf.c

TARGET = main #PthreadTest

$(TARGET): $(SOURCE)
	$(GCC) $^ -o $@ -lpthread
#	$(GCC) $^ -o $@ 



