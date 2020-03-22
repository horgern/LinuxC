#include "gpio.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <time.h>
#include <linux/input.h>

#include <string.h>
#include <strings.h>

/***********************************函数定义*************************************/
/*******************************************************************************
 * 名称:IO_Ctrl
 * 功能:IO开关控制函数
 * 形参:char ioport --> 控制管脚,
 *     char value --> 管脚值: 0 - 下拉，1 - 上拉
 * 返回:默认
 * 说明:无
*******************************************************************************/
void IO_Ctrl(char *ioport, char value)
{
	char dev_comm[80] = {0};
	sprintf(dev_comm, "echo \"none\">%s/%s/trigger", GPIOPATH, ioport);
	system(dev_comm);
	usleep(100000);

	memset(dev_comm, 0, sizeof(dev_comm));
	sprintf(dev_comm, "echo \"%d\">%s/%s/brightness", value, GPIOPATH, ioport);
	system(dev_comm);

#if DEBUG_GPIO
	printf("IO_Ctrl:%s\n", dev_comm);
#endif
	
	return;
}

/*******************************************************************************
 * 名称:Led_Ctrl
 * 功能:IO开关控制函数
 * 形参:char ledport --> LED管脚,
 *     int ms --> 闪烁值，以ms为单位，0为闭关, -1 为亮
 * 返回:默认
 * 说明:无
*******************************************************************************/
void Led_Ctrl(char *ledport, int ms)
{
	char dev_comm[80] ={0};

	if (ms > 0) {
		ms = ms / 2;
		sprintf(dev_comm, "echo \"timer\">%s/%s/trigger", GPIOPATH, ledport);
		system(dev_comm);
		usleep(100000);

		memset(dev_comm, 0, sizeof(dev_comm));
		sprintf(dev_comm, "echo \"%d\">%s/%s/delay_on", ms, GPIOPATH, ledport);
		system(dev_comm);

		usleep(100000);
		memset(dev_comm, 0, sizeof(dev_comm));
		sprintf(dev_comm, "echo \"%d\" >%s/%s/delay_off", ms, GPIOPATH, ledport);
		system(dev_comm);
	} else {
		sprintf(dev_comm, "echo \"none\">%s/%s/trigger", GPIOPATH, ledport);
		system(dev_comm);
		usleep(100000);
		memset(dev_comm, 0, sizeof(dev_comm));
		if (ms == 0) {
			sprintf(dev_comm, "echo \"0\">%s/%s/brightness", GPIOPATH, ledport);
		} else if (ms == -1) {
			sprintf(dev_comm, "echo \"1\">%s/%s/brightness", GPIOPATH, ledport);
		}
		system(dev_comm);
	}
	//printf("%s\n", dev_comm);
	return;
}

void Led_Ctrl_All(char enabled)
{
	IO_Ctrl(LED_GPS_G, enabled);
	IO_Ctrl(LED_GPS_R, enabled);
	Led_Ctrl(LED_REC_G, enabled);
	Led_Ctrl(LED_REC_R, enabled);
	Led_Ctrl(LED_PWR_G, enabled);
	Led_Ctrl(LED_PWR_R, enabled);
	Led_Ctrl(LED_LAN_R, enabled);
	Led_Ctrl(LED_LAN_G, enabled);
}

void Led_Ctrl_Color(LedTypeEnum_t led_type, LedColorEnum_t led_color, LedModeEnum_t led_mode)
{
	char led_type_G[64] = {0};
	char led_type_R[64] = {0};
	
	switch (led_type) {
		case LED_GPS: strcpy(led_type_G, LED_GPS_G); strcpy(led_type_R, LED_GPS_R); break;
		case LED_REC: strcpy(led_type_G, LED_REC_G); strcpy(led_type_R, LED_REC_R); break;
		case LED_LAN: strcpy(led_type_G, LED_LAN_G); strcpy(led_type_R, LED_LAN_R); break;
		case LED_PWR: strcpy(led_type_G, LED_PWR_G); strcpy(led_type_R, LED_PWR_R); break;
	}

	//if (led_type == LED_GPS) 
	{
		if (led_color == LED_RED) {
			Led_Ctrl(led_type_G, 0);
			switch (led_mode) {
				case LED_CLOSE: Led_Ctrl(led_type_R, 0); break;
				case LED_SLOW: Led_Ctrl(led_type_R, 500); break;
				case LED_FAST: Led_Ctrl(led_type_R, 998); break;
				case LED_OPEN: Led_Ctrl(led_type_R, -1); break;
				default :  Led_Ctrl(led_type_R, 0); break;
			}
		} else if (led_color == LED_GREEN) {
			Led_Ctrl(led_type_R, 0);
			switch (led_mode) {
				case LED_CLOSE: Led_Ctrl(led_type_G, 0); break;
				case LED_SLOW: Led_Ctrl(led_type_G, 500); break;
				case LED_FAST: Led_Ctrl(led_type_G, 998); break;
				case LED_OPEN: Led_Ctrl(led_type_G, -1); break;
				default :  Led_Ctrl(led_type_G, 0); break;
			}
		} else if (led_color == LED_YELLOW) {
			switch (led_mode) {
				case LED_CLOSE: Led_Ctrl(led_type_G, 0); Led_Ctrl(led_type_R, 0); break;
				case LED_SLOW: Led_Ctrl(led_type_G, 500); Led_Ctrl(led_type_R, 500); break;
				case LED_FAST: Led_Ctrl(led_type_G, 998); Led_Ctrl(led_type_R, 998); break;
				case LED_OPEN: Led_Ctrl(led_type_G, -1); Led_Ctrl(led_type_R, -1); break;
				default :  Led_Ctrl(led_type_G, 0); Led_Ctrl(led_type_R, 0); break;
			}
		}
	}
}


struct input_event ReadKeyEvent(struct timeval timeout)
{
    int fd = 0, ret = 0;
    fd_set read_input;
    struct input_event  event_t;
    struct timeval t;
    t.tv_sec  = timeout.tv_sec;
    t.tv_usec = timeout.tv_usec;


    if ((fd = open("/dev/input/event0",O_RDONLY)) < 0) {
		printf("%s, %s : open button error\r\n", __FILE__, __func__);
    }

    FD_ZERO(&read_input);
    FD_SET(fd,&read_input);

    ret = select(FD_SETSIZE, &read_input, (fd_set *)0, (fd_set *)0, &t);

    switch(ret) {
        case 0:  /* 超时 */
            event_t.code = TIMEOUT_KEY_CODE;
            event_t.type = EV_KEY;
            break;

        case -1: /* 错误 */
            printf("%s, %s : select key error\r\n", __FILE__, __func__);
            break;

        default: /* 读取按键 */
			memset(&event_t,0,sizeof(struct input_event));
            if (read(fd,&event_t,sizeof(struct input_event)) < 0) {
				printf("%s, %s : read key event error\r\n", __FILE__, __func__);
            }
            break;
    }

    close(fd);
    return event_t;
}
/*****************************************************************************
 函 数 名  : ReturnKeyResult
 功能描述  : 返回按键操作结果
 输入参数  : void
 输出参数  : 无
 返 回 值  : KeyResult_t
*****************************************************************************/
KeyResult_t ReturnKeyResult(char ClickFlag)
{
	float  time_t=0;
    struct timeval tmp1, tmp2, tmp3;
	struct input_event event1, event2, event3, event4;
    KeyResult_t result;

    while (1) {
		memset(&event1,0,sizeof(struct input_event));
		memset(&event2,0,sizeof(struct input_event));
    	memset(&event3,0,sizeof(struct input_event));
    	memset(&event4,0,sizeof(struct input_event));

		tmp3.tv_sec = TIMEOUT_10_S;
		tmp3.tv_usec = 0;
        time_t = 0;

        event1 = ReadKeyEvent(tmp3);

		/* 无按键按下，超时处理 */
        if (event1.code == TIMEOUT_KEY_CODE) {
            result.status = KEY_TIMEOUT;
            break;
        }

		/* 判断按键是否按下 */
        if ((event1.type != EV_KEY) || (event1.value != KEY_PRESS)) {
			continue;
        }

        event2 = ReadKeyEvent(tmp3);

		/* 判断按键是否松开，并且与按下的按键是同一个键 */
        if ((event2.type != EV_KEY) || (event2.code != event1.code) || (event2.value != KEY_BOUNCE)) {
            continue;
        }

		/* 计算按键按下与松开的时间戳 */
        tmp1.tv_sec  = event2.time.tv_sec  - event1.time.tv_sec;
        tmp1.tv_usec = event2.time.tv_usec - event1.time.tv_usec;
        time_t = (tmp1.tv_sec * 1000000 + tmp1.tv_usec) / 1000000.0;

		/* 按键无效操作 */
        if ((time_t < 3) && (time_t > 0.5)) {
            continue;
        }

		/* 长按：大于3秒，小于5秒 */
        if (( time_t >= 3) && (time_t < 5) ) {
            result.status = KEY_LONG_CLICK; /* 长按 */
            break;
        }

		/* 超长按：大于等于6秒 */
        if (time_t >= 6) {
            result.status = KEY_SUPER_LONG_CLICK; /* 超长按 */
            break;
        }
        /* 非电源键 以及 编辑界面 不做双击判断 zf*/
        if((event1.code != 256) || (1 == ClickFlag)){
            result.status = KEY_CLICK; /* 单击 */
            result.key_number = event1.code - 256;
            break;
        }     
        /* 单击：在同个按键按下并松开之后0.3秒内无任何按键操作 */
		tmp3.tv_sec = 0;
		tmp3.tv_usec = 300000 - (tmp1.tv_sec * 1000000 + tmp1.tv_usec);
        tmp3.tv_usec = (tmp3.tv_usec > 300000 || tmp3.tv_usec < 0) ? 200000 : 
                       tmp3.tv_usec;
        event3 = ReadKeyEvent(tmp3);
        if ((TIMEOUT_KEY_CODE == event3.code )) {
            result.status = KEY_CLICK; /* 单击 */
            break;
        }

		/* 在同个按键按下并松开之后0.5秒内，如果有其他按键操作，则判断是不是操作同个按键，
		 * 并且是不是按下操作? 这一步有以下作用:
		 * 1. 解决多个按键乱按导致程序卡死。
		 * 2. 用于判断是不是同个按键执行双击操作
		 */
		if ((event3.type != EV_KEY) || (event3.code != event1.code) || (event3.value != KEY_PRESS)) {
			continue;
		}

		tmp3.tv_sec = TIMEOUT_10_S;
		tmp3.tv_usec = 0;
        event4 = ReadKeyEvent(tmp3);

		/* 判断同个按键第2次按下后是否松开 */
        if ((event4.type != EV_KEY) || (event4.code != event1.code) || (event4.value != KEY_BOUNCE)) {
            continue;
        }

		/* 计算同个按键第2次松开后与第1次按下之间的时间戳，用于判断是不是双击操作 */
        tmp2.tv_sec  = event4.time.tv_sec  - event1.time.tv_sec;
        tmp2.tv_usec = event4.time.tv_usec - event1.time.tv_usec;
        time_t = (tmp2.tv_sec * 1000000  + tmp2.tv_usec) / 1000000.0;

		/* 双击：1秒内同个按键两次按下和松开 */
        if (time_t <= 1) {
            result.status = KEY_DOUBLE_CLICK; /* 双击 */
            break;
        }
    }//end of while;

    result.key_number = event1.code - 256;

    return result;
}

