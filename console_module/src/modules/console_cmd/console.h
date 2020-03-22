/*****************************************************************
** 文件名: console.h
 
** 创建人: 
** 日  期: 
** 描  述: 
** 版  本: 

** 修改人:
** 日  期:
** 修改描述:
** 版  本: 
******************************************************************/

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "v_types.h"
#include "v_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************
* 宏定义
******************************************************************/

/*		终端字符颜色		*/
#define STDIO_FONT_BLACK	"\033[40;30m"
#define STDIO_FONT_RED		"\033[40;31m"
#define STDIO_FONT_GREEN	"\033[40;32m"
#define STDIO_FONT_YELLOW	"\033[40;33m"
#define STDIO_FONT_BLUE		"\033[40;34m"
#define STDIO_FONT_PURPLE	"\033[40;35m"
#define STDIO_FONT_CYAN		"\033[40;36m"
#define STDIO_FONT_WHITE	"\033[40;37m"
	
#define STDIO_FONT_FOCUS	"\033[47;30m"
	
#define STDIO_FONT_HIGHLIGHT		"\033[1m"
#define STDIO_FONT_BOTTOMLINE		"\033[4m"
#define STDIO_FONT_IVERT_COLOR		"\033[7m"
#define STDIO_FONT_FLASH			"\033[5m"
#define STDIO_FONT_MODE_OFF			"\033[0m"


/*	控制台字体颜色效果*/
#define CONSOLE_ERROR_COLOR		STDIO_FONT_RED
#define CONSOLE_WARN_COLOR		STDIO_FONT_YELLOW
#define CONSOLE_MSG_COLOR		STDIO_FONT_GREEN
#define CONSOLE_DEBUG_COLOR		STDIO_FONT_WHITE
#define CONSOLE_INPUT_COLOR		STDIO_FONT_CYAN
#define CONSOLE_HIGHLIGHT_COLOR	STDIO_FONT_HIGHLIGHT
#define CONSOLE_MODE_OFF		STDIO_FONT_MODE_OFF

#ifndef COMMAND_LINK_PATH
#define COMMAND_LINK_PATH ("./cmd_bin")
#endif

#ifndef COMLINK_PATH
#define COMLINK_PATH	  ("../build")
#endif
/*****************************************************************
*DEBUG流程样例
*    ================================

DECLARE_DEBUG_REGION(subsystem);

DEFINE_DEBUG_SUBSYSTEM_INFO_DEFAULT(subsystem)


V_RET Subsystem_Init(V_VOID)
{
	REGISTER_DEBUG_SUBSYSTEM(subsystem);
	return V_OK;
}

******************************************************************/

/*DEBUG 管理注册函数*/
#define DECLARE_DEBUG_REGION_EX(subsystem,debug)	\
		 static DEBUG_NODE_S DEBUG_##subsystem={{NULL,NULL},debug,#subsystem,subsystem##_Info}

#define DECLARE_DEBUG_REGION(subsystem)	DECLARE_DEBUG_REGION_EX(subsystem,V_TRUE)


#define REGISTER_DEBUG_SUBSYSTEM(subsystem)	\
	do{ Console_Debug_Register(&DEBUG_##subsystem); } while(0)

/*DEBUG Info 打印函数定义*/
#define DEFINE_DEBUG_SUBSYSTEM_INFO_DEFAULT(subsystem)	\
		V_RET subsystem##_Info(V_VOID)	\
		{	\
			Console_Msg("%s:No info to print.\n",#subsystem);	\
			return V_OK;	\
		}	\


/*打印宏，伪函数*/
#define Console_Error(format, args...)	\
		do{ Console_Print(CONSOLE_ERROR_COLOR,"ERROR",CONSOLE_ERROR_COLOR,__FUNCTION__,format, ##args); }while(0)
#define Console_Warn(format, args...)	\
		do{ Console_Print(CONSOLE_WARN_COLOR,"WARN",CONSOLE_WARN_COLOR,__FUNCTION__,format, ##args); }while(0)
#define Console_Debug(subsystem,format, args...)	\
		do{ 	\
			if(DEBUG_##subsystem.bEnable)	\
			{	\
				Console_Print(CONSOLE_DEBUG_COLOR,"DEBUG",CONSOLE_DEBUG_COLOR,__FUNCTION__,format, ##args); 	\
			}	\
		}while(0)
			
#define Console_Msg(format, args...)	\
		do{ Console_Print(NULL,NULL,CONSOLE_MSG_COLOR,NULL,format, ##args); }while(0)

#define DEBUG_HERE	do{ Console_Print(CONSOLE_WARN_COLOR,"DEBUG",CONSOLE_WARN_COLOR,__FUNCTION__,"in line %d\n",__LINE__); }while(0)

#define COMMAND_STRING_LEN_MAX	32
#define COMMAND_PARAMS_NUM_MAX	16
#define COMMAND_PARAMS_LEN_MAX	32

/*****************************************************************
* 结构定义
******************************************************************/
typedef struct
{
	V_INT n;
	V_CHAR cmd[COMMAND_STRING_LEN_MAX];
	V_CHAR p[COMMAND_PARAMS_NUM_MAX][COMMAND_PARAMS_LEN_MAX];
}COMMAND_PKT;

typedef V_RET (*FN_COMMAND)(const COMMAND_PKT *pParams,V_CHAR *pcAck);

typedef struct 
{
	struct V_LIST_HEAD node;
	V_BOOL bEnable;
	V_CHAR *pcName;
	V_RET	(*fnPrintInfo)(V_VOID);
}DEBUG_NODE_S;

/*****************************************************************
* 函数原型声明
******************************************************************/



/*****************************************************************
  Function: 	 控制台模块初始化函数
  Description:	  初始化控制台模块。
  Input:		bDebug,	debug 模式是否打开
  Return:		 操作成功，则返回0，无则返回<0		

******************************************************************/
V_RET Console_Init(V_BOOL bDebug);



/*****************************************************************
  Function:     控制台模块销毁函数
  Description:    销毁控制台模块，关闭处理线程。
  Return:        操作成功，则返回0，无则返回<0      

******************************************************************/
V_RET Console_Deinit(V_VOID);


/*****************************************************************
  Function: 	 控制台模块打印函数
  Description:	  控制台模块打印函数
  Input:		pcTitleColor,	标题颜色
  			pcTitle,		标题字符串
  			pcStringColor,	正文颜色
  			pcSubTitle,	副标题字符串
  			pcFormat,	格式说明符，正则表达式
  Return:		 操作成功，则返回0，无则返回<0		

******************************************************************/
V_RET Console_Print(const V_CHAR *pcTitleColor,const V_CHAR *pcTitle,
	const V_CHAR *pcStringColor,const V_CHAR *pcSubTitle,const V_CHAR *pcFormat, ...);


/*****************************************************************
  Function:      控制台模块命令处理函数
  Description:    控制台模块阻塞等待命令到来并处理。
  Return:        操作成功，则返回0，无则返回<0      

******************************************************************/
V_RET Console_Loop(V_VOID);


/*****************************************************************
  Function:      控制台模块命令注册函数
  Description:    控制台模块命令注册函数
  Input:		pcCommand,	命令行字符串
  			fnFunction,	命令对应的执行函数
  			pcHelp,		命令对应的帮助信息
  Return:        操作成功，则返回0，无则返回<0      

******************************************************************/
V_RET Console_CMD_Register(const V_CHAR *pcCommand,FN_COMMAND fnFunction,const V_CHAR *pcHelp);

/*****************************************************************
  Function: 	 模块注册到DEBUG管理
  Description:	 模块注册到DEBUG管理
  Input:		pSubsystem,	模块的DEBUG结构体
  Return:		 操作成功，则返回0，无则返回<0		

******************************************************************/
V_RET Console_Debug_Register(DEBUG_NODE_S *pSubsystem);

/*****************************************************************
  Function: 	 打印当前时间
  Description:	  打印当前时间
  Input:		
******************************************************************/
V_VOID Console_Print_Time(const V_CHAR *pcTitle);

#ifdef __cplusplus
}
#endif

#endif



