#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------GPIO控制-------------------------------------*/
#define GPIOPATH "/sys/class/leds"                   //GPIO设备目录
#define PCL_KILL "pcl_kill"                   //系统电源开关
#define PWR_SW "pwr_switch"                   //供电切换开关
#define WIFI_PWR "wifi_pwr"                   //wifi电源开关
#define LCD_PWR "lcd_pwr"                   //LCD电源开关
#define GPRS_PWR "gprs_pwr"                   //3G模块电源
#define GNSS1_PWR "gnss1_pwr"                   //主板1电源
#define GNSS2_PWR "gnss2_pwr"                   //主板2电源
#define PWR_OUT "pwr_out"                   //电源输出开关

#define WIFI_EN "wifi_en"                   //Wifi使能
#define BT_EN "bt_en"                   //蓝牙使能
#define GPRS_EN "gprs_en"                   //3G模块使能

#define LCD_RST "lcd_rst"                   //LCD复位
#define AVR_RST "avr_rst"                   //AVR复位
#define GNSS1_RST "gnss1_rst"                   //主板1复位
#define GNSS2_RST "gnss2_rst"                   //主板2复位

#define LED_LAN_G "led_lan_g"                   //网络灯绿
#define LED_LAN_R "led_lan_r"                   //网络灯红
#define LED_REC_G "led_rec_g"                   //记录灯绿
#define LED_REC_R "led_rec_r"                   //记录灯红
#define LED_GPS_G "led_gps_g"                   //卫星灯绿
#define LED_GPS_R "led_gps_r"                   //卫星灯红
#define LED_PWR_G "led_pwr_g"                   //电源灯绿
#define LED_PWR_R "led_pwr_r"                   //电源灯红

#define TIMEOUT_10_S  10  /* 超时时间：10S */

#define KEY_PRESS  1 /* 按键按下 */
#define KEY_BOUNCE 0 /* 按键弹起 */

#define POWER_KEY_CODE   256 /* 电源键键值 */
#define FN_KEY_CODE      257 /* Fn键键值 */
#define LEFT_KEY_CODE    258 /* left键键值 */
#define RIGHT_KEY_CODE   259 /* right键键值 */
#define TIMEOUT_KEY_CODE 260 /* 按键超时默认键值 */


// LED灯：红灯，黄灯，绿灯
typedef enum {
	LED_RED = 0,
	LED_GREEN = 1,
	LED_YELLOW
} LedColorEnum_t;

// LED灯：卫星灯，记录灯， 网络灯，电源灯
typedef enum {
	LED_GPS = 0,
	LED_REC = 1,
	LED_LAN,
	LED_PWR
} LedTypeEnum_t;

// LED灯：常灭，慢闪，快闪，常亮
typedef enum {
	LED_CLOSE = 0,
	LED_SLOW = 1,
	LED_FAST,
	LED_OPEN
} LedModeEnum_t;




/*
 * 按键操作状态
 */
typedef enum
{
	KEY_CLICK = 0,         /* 单击 */
	KEY_DOUBLE_CLICK,      /* 双击 */
	KEY_LONG_CLICK,        /* 长按 */
	KEY_SUPER_LONG_CLICK,  /* 超长按 */
	KEY_TIMEOUT            /* 10S无按键按下 */
}KeyStatus_t;

/* 
 * 按键类型
 */
#define Power                0 /* 电源键 */
#define Fn                   1 /* 功能键 */
#define Left                 2 /* 左键 */
#define Right                3 /* 右键 */

/*
 * 按键操作
 */
#define CLICK                0 /* 单击 */
#define DBCLICK              1 /* 双击 */
#define LCLICK               2 /* 长按 */
#define SULCLICK             3 /* 超长按 */
#define KEYTIMEOUT           4 /* 10S无按键按下 */

/*
 * key_number : 0 -> Power键
 *              1 -> Fn键
 *              2 -> Left键
 *              3 -> Right键
 *
 * status :     0 -> 单击
 *              1 -> 双击
 *              2 -> 长按
 *              3 -> 超长按
 *              4 -> 10S无按键按下
 */

 /*
 * 按键操作结果
 */
typedef struct KeyResult
{
    unsigned int key_number;  /* 哪个键按下 */
    KeyStatus_t status;       /* 按键状态 */
}KeyResult_t;

/*
 * 返回按键操作结果
 */

void IO_Ctrl(char *ioport, char value);
void Led_Ctrl(char *ledport, int ms);
void Led_Ctrl_All(char enabled);
void Led_Ctrl_Color(LedTypeEnum_t led_type, LedColorEnum_t led_color, LedModeEnum_t led_mode);


KeyResult_t ReturnKeyResult(char ClickFlag);


#ifdef __cplusplus
extern "C" {
#endif
#endif
