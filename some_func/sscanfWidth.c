#include <stdio.h>
typedef struct {
    char name[32];        //基站名称
    char vnet_type[32];   //VNet机型
    char user[32];        //用户名
    char pwd[32];         //密码
    char station_ip[32];  //基站IP地址
    char server_ip[32];   //服务器IP地址
    int  station_id;      //基站ID
    int  source_id;       //基站数据源节点
    int  station_port;    //基站端口
    int  server_port;     //服务器端口
    int  status;          //基站连接状态
}StationInfo_t, *pStationInfo_t;

void GetStationStatus(StationInfo_t station_info)
{
    //打印基站配置信息;
    printf("---------------------------\n"
           "Station ID: %d\n"
           "Station Name: %s\n"
           "VNet Type: %s\n"
           "Station IP: %s\n"
           "Station Port: %d\n"
           "User Name: %s\n"
           "Password: %s\n"
           "Source ID: %d\n"
           "Server IP: %s\n"
           "Server Port: %d\n"
           "Status: %d\n"
           "---------------------------\n",
           station_info.station_id,
           station_info.name,
           station_info.vnet_type,
           station_info.station_ip,
           station_info.station_port,
           station_info.user,
           station_info.pwd,
           station_info.source_id,
           station_info.server_ip,
           station_info.server_port,
           station_info.status);
}
/*
int GetPidByName(char *pidname, long *pid)
{
    DIR *dir;
    struct dirent *next;

    dir = opendir("/proc");
    if (!dir) {
        printf("Cannot open /proc\n");
        return -1;
    }
    while ((next = readdir(dir)) != NULL) {
        FILE *status;
        char filename[50];
        char buffer[50];
        char name[50];

        if (strcmp(next->d_name, "..") == 0 || strcmp(next->d_name, ".") == 0)
            continue;
        if (!isdigit(*next->d_name))
            continue;
        sprintf(filename, "/proc/%s/status", next->d_name);
        if (!(status = fopen(filename, "r")))
            continue;
        if (fgets(buffer, 49, status) == NULL) {
            fclose(status);
            continue;
        }
        fclose(status);
		printf("buffer : %s\n", buffer);
        sscanf(buffer, "%*s %s", name);
        if (strcmp(name, pidname) == 0) {
            if (NULL != pid)
                *pid = (long)strtol(next->d_name, NULL, 0);
            break;
        }
    }
    closedir(dir);
    if (NULL == next)
        return 0;
    else
        return 1;
}
*/
int main()
{
	char p[] = "sta = 123456";

	int i = 0;
	sscanf(p, "sta = %10d", &i);
	printf("i = %d\n", i);
	char q[] = "STA1=ZHDQA:VNet-T,172.16.31.157:8000,user999:zhdgps,SOURCE:115200,SERVER:172.16.33.240:6109";
	StationInfo_t p_stations_info[10];
	i = 0;
	sscanf(q, "STA%10d=%20[^:]:%20[^,],%20[^:]:%10d,%20[^:]:%20[^,],SOURCE:%10d,SERVER:%20[^:]:%10d",
               &(p_stations_info[i].station_id),
               p_stations_info[i].name,
               p_stations_info[i].vnet_type,
               p_stations_info[i].station_ip,
               &(p_stations_info[i].station_port),
               p_stations_info[i].user,
               p_stations_info[i].pwd,
               &(p_stations_info[i].source_id),
               p_stations_info[i].server_ip,
               &(p_stations_info[i].server_port));

	GetStationStatus(p_stations_info[0]);

	char a[] = "Name:	whilechzwxztclz";
	char name[32] = {0};
	sscanf(a, "%*s %s", name);
	printf("name : %s\n", name);
//	GetPidByName();

}

