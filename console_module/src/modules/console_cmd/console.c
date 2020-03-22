/*****************************************************************
** 文件名: console.c

** 创建人:
** 日  期:
** 描  述:
** 版  本:

** 修改人:
** 日  期:
** 修改描述:
** 版  本:
******************************************************************/

#include "v_types.h"
#include "v_list.h"
#include "console.h"
#include "mod_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

/*****************************************************************
* 宏定义
******************************************************************/
#define CONSOLE_CMD_LEN_MAX		128

#define SHELL_MODE_SPELL		"shell"			/*从CONSOLE模式进入SHELL模式的命令*/

#define COMMAND_LINK_SEND_PIPE	"/tmp/cmd_link_snd"
#define COMMAND_LINK_ACK_PIPE	"/tmp/cmd_link_ack"


/*****************************************************************
* 结构定义
******************************************************************/
typedef struct
{
        struct V_LIST_HEAD node;
        V_CHAR *pcCommand;
        FN_COMMAND fnFunction;
        V_CHAR *pcHelp;
}CONSOLE_COMMAND;

typedef enum
{
        MODE_CONSOLE,
        MODE_SHELL,
        MODE_LOGIN
}CONSOLE_MODE_E;

/*****************************************************************
* 全局变量定义
******************************************************************/


/*****************************************************************
* 静态变量定义
******************************************************************/
static LIST_HEAD(sCmdList);

static V_BOOL sbDebug = V_FALSE;

static LIST_HEAD(sDebugList);

/*****************************************************************
* 内部函数定义
******************************************************************/


/*****************************************************************
* 接口函数定义
******************************************************************/

V_RET _CMD_CreateCmdLink(const V_CHAR *pcName)
{
        int ret_val = 0;
        V_CHAR pcPath[128] = {0};
        V_CHAR pcCmdPath[128] = {0};

        //文件夹不存在时创建
        if (0 != access(COMMAND_LINK_PATH, F_OK)) {
                ret_val = mkdir(COMMAND_LINK_PATH, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
                if (ret_val < 0) {
                        printf("[%s][%d] ----> %s not exist, and mkdir error.", __func__, __LINE__, COMMAND_LINK_PATH);
                }
        }

        sprintf(pcPath,"%s/%s", COMMAND_LINK_PATH, pcName);
        sprintf(pcCmdPath,"%s/command_link", COMLINK_PATH);

        return symlink(pcCmdPath, pcPath);	//FIX ME
}

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
        const V_CHAR *pcStringColor,const V_CHAR *pcSubTitle,const V_CHAR *pcFormat, ...)
{
        V_VA_LIST ap;

        if(pcTitle && pcTitleColor)
        {
                printf("%s%s%s:",CONSOLE_HIGHLIGHT_COLOR,pcTitleColor,pcTitle);
        }

        printf("%s%s",CONSOLE_MODE_OFF,pcStringColor);
        if(pcSubTitle)
        {
                printf("%s:",pcSubTitle);
        }

        va_start(ap, pcFormat);
        vprintf(pcFormat, ap);
        va_end(ap);

        printf(CONSOLE_INPUT_COLOR);

        return V_OK;
}


/*****************************************************************
  Function:      控制台模块命令处理函数
  Description:    控制台模块阻塞等待命令到来并处理。
  Return:        操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_Loop(V_VOID)
{
        V_INT fdSnd,fdAck;
        V_INT ret;
        COMMAND_PKT pktCmd;
        V_BOOL bQuit;
        CONSOLE_COMMAND *pstCommand;
        CONSOLE_COMMAND *pstThis = NULL;
        struct V_LIST_HEAD *pNode;
        static V_CHAR pcAck[1024*16];

        fd_set readfds;
        struct timeval tv;

        bQuit = V_FALSE;

        while(!bQuit)
        {
                fdSnd = open(COMMAND_LINK_SEND_PIPE, O_RDONLY);
                if(fdSnd < 0)
                {
                        Console_Error("Can not Open snd link:%s,ret=%d\n", COMMAND_LINK_SEND_PIPE, fdSnd);
                        return fdSnd;
                }

                FD_ZERO(&readfds);
                FD_SET(fdSnd, &readfds);
                tv.tv_sec = 3;
                tv.tv_usec = 0;
                ret = select(fdSnd+1, &readfds, NULL, NULL, &tv);
                if(ret < 0)
                {
                        Console_Error("select error:%d\n",ret);
                        continue;
                }
                if(ret == 0)
                {
                        Console_Error("select timeout\n");
                        continue;
                }
                //Get Input command pkt
                ret = read(fdSnd,&pktCmd,sizeof(pktCmd));
                if(ret <= 0)
                {
                        //Console_Error("read failed:%d\n",ret);
                        //sleep(1);
                        continue;
                }

                close(fdSnd);
                fdSnd = 0;

                //find match command and exec it
                pstThis = NULL;
                V_LIST_FOR_EACH(pNode,&sCmdList)
                {
                        pstCommand = V_LIST_ENTRY(pNode,CONSOLE_COMMAND,node);
                        if(strcmp(pstCommand->pcCommand,pktCmd.cmd) == 0)
                        {
                                pstThis = pstCommand;
                                break;
                        }
                }

                //exec command
                memset(pcAck,0,sizeof(pcAck));
                sprintf(pcAck,"no reply\n");
                if(pstThis == NULL)
                {
                        sprintf(pcAck,"No Such Command! to list exist command,try 'cmddump'.\n");
                }
                else
                {
                        pstThis->fnFunction(&pktCmd,pcAck);
                }

                fdAck = open(COMMAND_LINK_ACK_PIPE,O_WRONLY);
                if(fdAck < 0)
                {
                        Console_Error("Can not Open ack link:%s,ret=%d\n",COMMAND_LINK_ACK_PIPE,fdAck);
                        return fdAck;
                }

                //reply the ack
                ret = write(fdAck,pcAck,strlen(pcAck));
                if(ret < strlen(pcAck))
                {
                        Console_Error("Can not reply strings to command link!\n");
                }
                close(fdAck);
                fdAck = 0;

                usleep(10000);
        }

        if(fdSnd)
        {
                close(fdSnd);
        }
        if(fdAck)
        {
                close(fdAck);
        }

        return V_OK;
}

/*****************************************************************
  Function:      控制台模块命令注册函数
  Description:    控制台模块命令注册函数
  Input:		pcCommand,	命令行字符串
                        fnFunction,	命令对应的执行函数
                        pcHelp,		命令对应的帮助信息
  Return:        操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_CMD_Register(const V_CHAR *pcCommand,FN_COMMAND fnFunction,const V_CHAR *pcHelp)
{
        CONSOLE_COMMAND *pstCommand;

        pstCommand = (CONSOLE_COMMAND *)malloc(sizeof(CONSOLE_COMMAND));
        if(pstCommand == NULL)
        {
                Console_Error("Console_CMD_Register Failed!\n");
                return V_ERROR;
        }

        pstCommand->fnFunction = fnFunction;
        pstCommand->pcCommand = (V_CHAR *)pcCommand;
        pstCommand->pcHelp = (V_CHAR*)pcHelp;
        V_ListAddTail(&pstCommand->node, &sCmdList);

        _CMD_CreateCmdLink(pcCommand);
        return V_OK;
}

/*****************************************************************
  Function:      控制台模块打印命令列表
  Description:    控制台模块打印命令列表
    Return:        操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_CMD_Dump(const COMMAND_PKT *pParams,V_CHAR *pcAck)
{
        CONSOLE_COMMAND *pstCommand;
        struct V_LIST_HEAD *pNode;
        V_UINT32 dwIndex = 0;
        V_INT len = 0;

        len += sprintf(pcAck+len,"Dumping Cmd:\n");
        V_LIST_FOR_EACH(pNode,&sCmdList)
        {
                pstCommand = V_LIST_ENTRY(pNode,CONSOLE_COMMAND,node);
                len += sprintf(pcAck+len,"%-8lu%-32s%-32s\n",dwIndex++,pstCommand->pcCommand,pstCommand->pcHelp);
        }
        len += sprintf(pcAck+len,"-=END=-\n");

        return V_OK;
}

V_RET Daemon(void)
{
        pid_t pid;

        /* parent exits , child continues */
        if((pid = fork()) < 0)
        {
                return V_ERROR;
        }
        else if(pid != 0)
        {
                exit(0);
        }

        setsid(); /* become session leader */
#if 0
        for(i=0;i< 3 ;++i) /* close STDOUT, STDIN, STDERR, */
        {
                close(i);
        }
#endif
        umask(0); /* clear file mode creation mask */

        return V_OK;
}


/*****************************************************************
  Function: 	 模块注册到DEBUG管理
  Description:	 模块注册到DEBUG管理
  Input:		pSubsystem,	模块的DEBUG结构体
  Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_Debug_Register(DEBUG_NODE_S *pSubsystem)
{
        if(pSubsystem == NULL)
        {
                return V_ERROR;
        }

        pSubsystem->bEnable = sbDebug;

        V_ListAddTail(&pSubsystem->node, &sDebugList);

        return V_OK;
}


/*****************************************************************
  Function: 	 DEBUG设置
  Description:	DEBUG设置使能
  Input:		pcName,	模块的名字
                        bEnable,	使能位
  Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET _Debug_Subsystem_Enable(const V_CHAR *pcName,V_BOOL bEnable)
{
        struct V_LIST_HEAD *pNode;
        DEBUG_NODE_S *pSubsystem;

        V_LIST_FOR_EACH(pNode,&sDebugList)
        {
                pSubsystem = V_LIST_ENTRY(pNode,DEBUG_NODE_S,node);
                if(strcmp(pSubsystem->pcName,pcName) == 0)
                {
                        Console_Msg("%s debug %s\n",pcName,bEnable ? "enabled" : "disabled");
                        pSubsystem->bEnable = bEnable;
                        return V_OK;
                }
        }
        Console_Error("No subsystem %s\n",pcName);

        return V_ERROR;
}

/*****************************************************************
  Function: 	 DEBUG打印子系统信息
  Description:	DEBUG打印子系统信息
  Input:		pcName,	模块的名字
  Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET _Debug_Subsystem_Info(const V_CHAR *pcName)
{
        struct V_LIST_HEAD *pNode;
        DEBUG_NODE_S *pSubsystem;

        V_LIST_FOR_EACH(pNode, &sDebugList)
        {
                pSubsystem = V_LIST_ENTRY(pNode,DEBUG_NODE_S,node);
                if(strcmp(pSubsystem->pcName,pcName) == 0)
                {
                        if(pSubsystem->fnPrintInfo)
                        {
                                pSubsystem->fnPrintInfo();
                        }
                        return V_OK;
                }
        }
        Console_Error("No subsystem %s\n",pcName);

        return V_ERROR;
}


/*****************************************************************
  Function: 	 DEBUG链表打印
  Description:	DEBUG链表打印
   Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET _Debug_Subsystem_List(V_VOID)
{
        struct V_LIST_HEAD *pNode;
        DEBUG_NODE_S *pSubsystem;
        V_UINT32 dwIndex = 0;

        Console_Msg("Debug list dump:\n");
        V_LIST_FOR_EACH(pNode,&sDebugList)
        {
                pSubsystem = V_LIST_ENTRY(pNode,DEBUG_NODE_S,node);

                Console_Msg("%-8d%-16s%-16s\n",dwIndex++,
                        pSubsystem->pcName,pSubsystem->bEnable ? "enabled" : "disabled");
        }
        Console_Msg("\n");

        return V_OK;
}

V_RET Console_Debug_CMD_Help(V_VOID)
{
        Console_Msg("Usage: debug [OPTION...] [subsytem] \n");
        Console_Msg("debug can enable/disbale debug messages of subsystem;\n");
        Console_Msg("and print subsystem infos.\n");
        Console_Msg("Examples: \n");
        Console_Msg("\tdebug -h\t#print debug help\n");
        Console_Msg("\tdebug -l\t#list all subsystems\n");
        Console_Msg("\tdebug -enable event\t#enable subsystem event to pring debug msgs\n");
        Console_Msg("\tdebug -info event\t#print subsystem event information\n");
        Console_Msg("OPTIONs:\n");
        Console_Msg("-h \thelp infos\n");
        Console_Msg("-l \tlist all subsystems\n");
        Console_Msg("-enable [subsystem]\tenable print debug msg\n");
        Console_Msg("-disable [subsystem]\tdisable print debug msg\n");
        Console_Msg("-info [subsystem] \tprint subsystem event information\n");
        Console_Msg("\n");

        return V_OK;
}

/*****************************************************************
  Function: 	 DEBUG调试命令回调
  Description:	 DEBUG调试命令回调
  Input:		dwParam,	后续参数字符串
   Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_Debug_CMD(const COMMAND_PKT *pParams,V_CHAR *pcAck)
{
        if(strcmp(pParams->p[0],"-h") == 0)
        {
                Console_Debug_CMD_Help();
                return V_OK;
        }
        else if(strcmp(pParams->p[0],"-l") == 0)
        {
                _Debug_Subsystem_List();
                return V_OK;
        }
        else if(strcmp(pParams->p[0],"-enable") == 0)
        {
                return _Debug_Subsystem_Enable(pParams->p[1],V_TRUE);
        }
        else if(strcmp(pParams->p[0],"-disable") == 0)
        {
                return _Debug_Subsystem_Enable(pParams->p[1],V_FALSE);
        }
        else if(strcmp(pParams->p[0],"-info") == 0)
        {
                return _Debug_Subsystem_Info(pParams->p[1]);
        }
        else
        {
                Console_Msg("Illegal command format!\n");
                Console_Debug_CMD_Help();
                return V_ERROR;
        }
}

/*****************************************************************
  Function: 	 打印当前时间
  Description:	  打印当前时间
  Input:
******************************************************************/
V_VOID Console_Print_Time(const V_CHAR *pcTitle)
{
        struct timeval tv;
        gettimeofday (&tv ,NULL);

        if(pcTitle)
        {
                //Console_Msg("%s:",pcTitle);
        }
        //Console_Msg(" %d.%06d\n",tv.tv_sec,tv.tv_usec);
}

/*****************************************************************
  Function: 	 控制台模块初始化函数
  Description:	  初始化控制台模块。
  Input:		bDebug,	debug 模式是否打开
  Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_Init(V_BOOL bDebug)
{
        sbDebug = bDebug;

        INIT_LIST_HEAD(&sCmdList);
        INIT_LIST_HEAD(&sDebugList);

        unlink(COMMAND_LINK_SEND_PIPE);
        unlink(COMMAND_LINK_ACK_PIPE);
        mkfifo(COMMAND_LINK_SEND_PIPE,0777);
        mkfifo(COMMAND_LINK_ACK_PIPE,0777);

        Daemon();

        Console_CMD_Register("cmddump",Console_CMD_Dump,"Dump Commands list");
        Console_CMD_Register("vdebug",Console_Debug_CMD,"venus debug cmd");

        return V_OK;
}


/*****************************************************************
  Function: 	控制台模块销毁函数
  Description:	  销毁控制台模块，关闭处理线程。
  Return:		 操作成功，则返回0，无则返回<0

******************************************************************/
V_RET Console_Deinit(V_VOID)
{
        return V_OK;
}

