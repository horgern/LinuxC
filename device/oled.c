#include "device.h"
#include "ProcessLog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

/*
 * SPI驱动控制OLED电源
 */
#define SPI_IOC_MAGIC	    'x'
#define OLED_IOC_CMD		_IOW(SPI_IOC_MAGIC, 1, unsigned char)
#define OLED_IOC_POWER_ON	_IO(SPI_IOC_MAGIC, 2)
#define OLED_IOC_POWER_OFF	_IO(SPI_IOC_MAGIC, 3)

/*****************************************************************************
 函 数 名  : OLED_WriteCmd
 功能描述  : OLED写入命令
 输入参数  : unsigned char cmd
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OLED_WriteCmd(int fd, unsigned char cmd)
{
	int err = 0;

	err = ioctl(fd, OLED_IOC_CMD, &cmd);
	if (err < 0) {
		printf("%s, %s : OLED Write Cmd error\r\n", __FILE__, __func__);
	}
}
/*****************************************************************************
 函 数 名  : OLED_SetXY
 功能描述  : 设置OLED显示起始地址
 输入参数  : unsigned int x -> 列地址(0-127)
             unsigned int y -> 行地址(0-7)
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OLED_SetXY(unsigned int x, unsigned int y)
{
	x = x + 4; /* 液晶显示其实地址从4开始 */

	OLED_WriteCmd(OLED_ROW_START_ADD | y);              /* 写行地址 */
	OLED_WriteCmd(OLED_LOW_COL_START_ADD | (x & 0x0F)); /* 写列地址低四位 */
	OLED_WriteCmd(OLED_HIGH_COL_START_ADD | (x >> 4));  /* 写列地址高四位 */
}


/*****************************************************************************
 函 数 名  : OLED_WriteData
 功能描述  : OLED写入数据
 输入参数  : unsigned char data
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OLED_WriteData(int fd, unsigned char data)
{
	int err = 0;
	char buf[128] = {0};

	err = write(fd, &data, 1);	/* D/C 引脚的操作由spi驱动完成 */
	if (err < 0) {
		printf("%s, %s : OLED Write Data error\r\n", __FILE__, __func__);
	}
}

void OLED_PrintChar(int fd, unsigned int x, unsigned int y, unsigned char ch)
{
	unsigned int i = 0, add = 0;

	add = ch - 32;  /* 字符字库表中前32个字符没有 */
	add = add * 16; /* 每个字符占16字节 */

	OLED_SetXY(x, y);
	for (i = 0; i < 8; i++) {
	    OLED_WriteData(gC_tab_ascii[add++]);
	}

	OLED_SetXY(x, y + 1);
	for (i = 0; i < 8; i++) {
	    OLED_WriteData(gC_tab_ascii[add++]);
	}
}

/*****************************************************************************
 函 数 名  : OLED_Init
 功能描述  : OLED初始化
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OLED_OpenDisp(void)
{
	int oled_fd = 0;
	/* 打开OLED设备文件 */
	if ((oled_fd = open(OLED_DEV_PATH, O_RDWR | O_NONBLOCK | O_NDELAY)) < 0) {
		PrintMsg(NOTICE, "Open OLED Spi error\n");
		return;
	}
	fcntl(oled_fd, F_SETFL, 0);

    ioctl(oled_fd, OLED_IOC_POWER_ON);       /* 打开OLED电源 */
	OLED_WriteCmd(oled_fd, OLED_DISPLAY_ON); /* 开液晶显示 */
	close(oled_fd);
}

/*****************************************************************************
 函 数 名  : OLED_CloseDisp
 功能描述  : 关闭液晶显示
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OLED_CloseDisp(void)
{
	int oled_fd = 0;
	/* 打开OLED设备文件 */
	if ((oled_fd = open(OLED_DEV_PATH, O_RDWR | O_NONBLOCK | O_NDELAY)) < 0) {
		PrintMsg(NOTICE, "Open OLED Spi error\n");
		return;
	}
	fcntl(oled_fd, F_SETFL, 0);
	OLED_WriteCmd(oled_fd, OLED_DISPLAY_OFF);           /* 关闭液晶显示 */
	close(oled_fd);
}

