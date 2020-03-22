//***************************************************************************************
//
//! \file console_cmd.c
//! 
//!
//! \author    chenhz
//! \version   V1.0
//! \date      2020-03-08
//! \copyright GNU Public License V1.0
//
//! \note modules interface test
//***************************************************************************************
#include "console_cmd_test.h"


void ModTest_App(void)
{
	Console_Msg("[%s-%d] invoke --\n", __func__, __LINE__);

	Console_CMD_Register("proInterfaceTest", CMDProInterfaceTest, "test Interface");  

}


void SignalHandleKill(int param)
{
	
	printf("[%s-%d] param:%d\n", __func__, __LINE__, param);
}


int main(int argc, char **argv)
{
	/*解析命令行*/
	V_BOOL bDebug = V_TRUE;
	//V_BOOL bSafeMode = V_FALSE;
	int c;
	const struct option long_options[] = 
	{
		{"debug", no_argument, NULL, 0},
		{"safe", no_argument, NULL, 0},
		{0, 0, 0, 0}
	};

	while((c = getopt_long(argc, argv, "ds", long_options, NULL)) != -1) {
		switch(c) {
			case 'd':{
				bDebug = V_TRUE;
				Console_Msg("###debug mode###\n");
				break;
			}
			case 's':{
				//bSafeMode = V_TRUE;
				Console_Msg("###safe mode###\n");
				break;
			}
			default:{
				break;
			}
		}
	}


	signal(SIGQUIT	,SignalHandleKill);
	signal(SIGTERM	,SignalHandleKill);
	signal(SIGSTOP	,SignalHandleKill);
	signal(SIGINT	,SignalHandleKill);//SIGPIPE
	signal(SIGPIPE	,SignalHandleKill);//SIGPIPE
		

	Console_Msg("[%s-%s] Booting cmd_test:\n", __DATE__, __TIME__);
	Console_Init(bDebug);

	Console_Msg("[%s-%s] ModTest_App test:\n", __DATE__, __TIME__);
	ModTest_App();

	Console_Msg("Unit Init OK\n");
	Console_Loop();
	return 0;
}



