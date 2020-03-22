#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <signal.h>


#define COMMAND_LINK_SEND_PIPE	"/tmp/cmd_link_snd"
#define COMMAND_LINK_ACK_PIPE	"/tmp/cmd_link_ack"

#define COMMAND_STRING_LEN_MAX	32
#define COMMAND_PARAMS_NUM_MAX	16
#define COMMAND_PARAMS_LEN_MAX	32
typedef struct
{
	int n;
	char cmd[COMMAND_STRING_LEN_MAX];
	char p[COMMAND_PARAMS_NUM_MAX][COMMAND_PARAMS_LEN_MAX];
}COMMAND_PKT;

static int fd_snd = 0, fd_ack = 0;

void SignalHandleKill(int param)
{
	if(fd_snd)
	{
		close(fd_snd);
	}
	
	if(fd_ack)
	{
		close(fd_ack);
	}
	printf("command link killed!\n");
}

int main(int argc, char* argv[])
{
	int ret,i;
	COMMAND_PKT cmd;
	char ack[2048] = {0};
	char *pcString;

	signal(SIGQUIT  ,SignalHandleKill);
	signal(SIGTERM  ,SignalHandleKill);
	signal(SIGSTOP  ,SignalHandleKill);
	signal(SIGINT   ,SignalHandleKill);

	fd_snd = open(COMMAND_LINK_SEND_PIPE,O_WRONLY);
	if(fd_snd < 0)
	{
		printf("Can not Open snd link:%s,ret=%d\n",COMMAND_LINK_SEND_PIPE,fd_snd);
		return fd_snd;
	}

	printf("[%s-%d] argc(%d) argv0<%s> \n", __func__, __LINE__, argc, argv[0]);
	
	memset(&cmd,0,sizeof(cmd));
	cmd.n = argc - 1;
	pcString = rindex(argv[0],'/');
	if(pcString == NULL)
	{
		pcString = argv[0];
	}
	else
	{
		pcString++;
	}
	memcpy(cmd.cmd,pcString,strlen(pcString));
	for(i = 1; i < argc; i++)
	{
		memcpy(cmd.p[i-1],argv[i],strlen(argv[i]));
	}

	ret = write(fd_snd,&cmd,sizeof(cmd));
	if(ret != sizeof(cmd))
	{
		printf("Can not snd cmd:%s\n",cmd.cmd);
		goto cleanup;
	}
	close(fd_snd);
	fd_snd = 0;

	fd_ack = open(COMMAND_LINK_ACK_PIPE,O_RDONLY);
	if(fd_ack < 0)
	{
		printf("Can not Open ack link:%s,ret=%d\n",COMMAND_LINK_ACK_PIPE,fd_ack);
		return fd_ack;
	}

	memset(ack,0,sizeof(ack));
	ret = read(fd_ack,ack,sizeof(ack));
	if(ret <= 0)
	{
		printf("Read ack failed!ret=%d\n",ret);
		goto cleanup;
	}

	printf("venus:%s\n",ack);

	close(fd_ack);

	ret = 0;
	
cleanup:
	if(fd_snd)
	{
		close(fd_snd);
	}
	
	if(fd_ack)
	{
		close(fd_ack);
	}
	return ret;
}


