#ifndef _CONSOLE_CMD_TEST_H_
#define _CONSOLE_CMD_TEST_H_


#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include "console.h"
#include "mod_config.h"


void CMDProInterfaceTestUsage();
V_RET CMDProInterfaceTest(const COMMAND_PKT *pParams, V_CHAR *pcAck);

#endif