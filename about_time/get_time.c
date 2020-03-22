#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

/*******************************************************************************
 * 名称：GetLocalTimeZone
 * 功能：获取本地时区，和本机设置相关
 * 输入：无
 *		 
 * 输出：无
 *		 
 *		 
 * 返回：本地时区
 *		 
 * 说明：+ 为东区，- 为西区
*******************************************************************************/
int GetLocalTimeZone()
{
	int timezone = 0;
	time_t loc_t, utc_t;
	struct tm tm_loc, tm_utc;
	time(&loc_t);	//获取Epoch 时间
	time(&utc_t);	//获取Epoch 时间

	localtime_r(&loc_t, &tm_loc);	//获取子午线时区所在的时间，得到的值在tm_loc, loc_t此时值不变

	gmtime_r(&utc_t, &tm_utc);		//获取本地UTC时，得到的值在tm_utc, utc_t此时值不变
	
	loc_t = mktime(&tm_loc);		//将 struct tm 转化为 time_t 类型，方便计算
	utc_t = mktime(&tm_utc); 		//将 struct tm 转化为 time_t 类型，方便计算
	//printf("[%s][%d] ---- loc_t[%lu] utc_t[%lu]", __func__, __LINE__, loc_t, utc_t);
	

	timezone = (loc_t - utc_t) / 3600;

	return timezone;
}


void GetTimeOfDayUsage()
{
	struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("second:%lu\n",tv.tv_sec);  //秒
    printf("millisecond:%lu\n",tv.tv_sec*1000 + tv.tv_usec/1000);  //毫秒
    printf("microsecond:%lu\n",tv.tv_sec*1000000 + tv.tv_usec);  //微秒



	//字符串表示时间 如 Mon Mar 16 22:33:38 2020
    printf("gettimeofday --> %s\n", ctime(&tv.tv_sec));  //秒
}

void GetUTCTimeUsage()
{
	time_t utc_time;
	struct tm utc_tm;
	
	time(&utc_time);				//获取Epoch时间
	gmtime_r(&utc_time, &utc_tm);	//获取本地utc时
	utc_time = mktime(&utc_tm); 	//将 struct tm 转化为 time_t 类型，方便计算

	printf("gmtime_r     second:%ld\n", utc_time);  
	//字符串表示时间 如 Mon Mar 16 22:33:38 2020
	printf("gmtime_r	 --> %s\n", ctime(&utc_time));	//毫秒

}

void GetLocalTimeUsage()
{
	time_t local_time;
	struct tm local_tm;

	time(&local_time);						//获取Epoch时间
	localtime_r(&local_time, &local_tm);	//获取本地时
	local_time = mktime(&local_tm);			//将 struct tm 转化为 time_t 类型，方便计算

	printf("localtime_r  second:%ld\n", local_time);  //秒
	//字符串表示时间 如 Mon Mar 16 22:33:38 2020
	printf("localtime_r  --> %s\n", ctime(&local_time));  //秒

}

int main()
{
	GetUTCTimeUsage();
	GetLocalTimeUsage();
	GetTimeOfDayUsage();
	
    return 0;
}

