#include "console_cmd_test.h"

void CMDProInterfaceTestUsage()
{
	printf("[%s-%d] :\n", __func__, __LINE__);

	printf(" -2 [x] \t test network\n");
	printf(" -3 [x] \t test tpool\n");
}

V_RET CMDProInterfaceTest(const COMMAND_PKT *pParams, V_CHAR *pcAck)
{
	V_INT len = 0;
	int opt;

	if (0 == pParams->n) {
		CMDProInterfaceTestUsage();
		
	} else if (1 == pParams->n) {
		opt = atoi(pParams->p[0]);
		printf("[%s-%d] opt<%d> <%s>\n", __func__, __LINE__, opt, pParams->p[1]);
		switch(opt) {
			case 0:	
			case 1:	
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
			default:
				printf("[%s-%d] no supported opt<%d>\n", __func__, __LINE__, opt);
		}
	}

	sprintf(pcAck+len, "%s success\n", __FUNCTION__);
	return V_OK;
}

