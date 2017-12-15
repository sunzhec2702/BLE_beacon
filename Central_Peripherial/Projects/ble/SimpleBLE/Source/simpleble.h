#ifndef SIMPLEBLE_H
#define SIMPLEBLE_H

#ifdef __cplusplus
#include "npi.h"
#include "comdef.h"
extern "C"
{
#endif
#include "hal_types.h"

#define DEVELOP_BOARD 0
#define PRODUCT_BOARD 1

#define NFC_BOARD_VERSION 0x1 //BLE+NFC

#define TARGET_BOARD PRODUCT_BOARD

#define POWER_OFF_SUPPORT TRUE
//#define DEBUG_BOARD 1

#define PRESET_ROLE BLE_ROLE_PERIPHERAL

// 当前单片机运行的角色
typedef enum
{
    BLE_ROLE_PERIPHERAL = 0,        //从机角色
    BLE_ROLE_CENTRAL = 1,           //主机角色    
}BLE_ROLE;

#ifdef DEBUG_BOARD
#define HAL_LCD TRUE
#define HAL_UART TRUE
#define LCD_TO_UART TRUE
#define DEBUG_PRINT(x) NPI_PrintString(x)
#define DEBUG_VALUE(x,y,z) {NPI_PrintValue(x, y, z);NPI_PrintString("\r\n");}
#else // PRODUCT_BOARD
  #if (PRESET_ROLE == BLE_ROLE_CENTRAL)
    #define HAL_LCD FALSE
    #define HAL_UART TRUE
    #define LCD_TO_UART TRUE
  #else // PERIPHERIAL
    #define HAL_LCD FALSE
    #define HAL_UART TRUE
    #define LCD_TO_UART FALSE
  #endif // CENTRAL
#define DEBUG_PRINT(x) {}
#define DEBUG_VALUE(x,y,z) {}
#endif


// 主机从机事件共用定义
#define START_DEVICE_EVT                               0x0001//启动设备
#define SBP_PERIODIC_EVT                               0x0002//系统轮询定时器
#define SBP_DATA_EVT                                   0x8000//数据传输
#define SBP_KEY_CNT_EVT                                0x0008//count the key pressed.
#define SBP_UART_EVT                                   0x0010//串口数据事件
#define SBP_SLEEP_EVT                                  0x0020//睡眠事件
#define SBP_WAKE_EVT                                   0x0040//唤醒事件
#define SBP_PERIODIC_LED_EVT                           0x0080//开机闪灯
#define SBP_CONNECT_EVT                                0x0100//主机连接-确认连接
#define START_DISCOVERY_EVT                            0x0200//发现从设备

#define SBP_PERIODIC_BUTTON_LED_EVT                    0x0400
#define SBP_PERIODIC_PER_HOUR_EVT                      0x0800
#define SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE            0x1000
#define SBP_PERIODIC_CHN_ADVERT_EVT_PRESS              0x2000
#define SBP_PERIODIC_INDEX_EVT                         0x4000//系统轮询定时器

#define SBP_KEY_LONG_PRESSED_EVT                       0x0004

#define SBP_PERIODIC_EVT_ALL (SBP_PERIODIC_EVT|SBP_PERIODIC_LED_EVT|SBP_PERIODIC_BUTTON_LED_EVT|SBP_PERIODIC_PER_HOUR_EVT|SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE|SBP_PERIODIC_CHN_ADVERT_EVT_PRESS|SBP_PERIODIC_INDEX_EVT)

// What is the advertising interval when device is discoverable (units of 625us, 160=100ms)
#define RAPID_ADVERTISING_INTERVAL (160*2) // 200ms
#define SLOW_ADVERTISING_INTERVAL (1600*2) // 2s
#define SBP_PERIODIC_ADVERT_CHG_PERIOD                  2000 // 2s

// How often to perform periodic event
#define SBP_PERIODIC_INDEX_EVT_PERIOD                   1000 // 1s

#ifdef DEBUG_BOARD
#define SBP_PERIODIC_PER_HOUR_PERIOD                    60000    // 1 min
#define DEFAULT_WAKE_TIME_HOURS                         (5) // 5 mins
#define BUTTON_WAKE_TIME_HOURS                          (2) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1) // 1 days
#else
#define SBP_PERIODIC_PER_HOUR_PERIOD                    3600000   // 1 hour
#define DEFAULT_WAKE_TIME_HOURS                         (5 * 24) // 5 days
#define BUTTON_WAKE_TIME_HOURS                          (2 * 24) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1 * 24) // 1 days
#endif

#define SBP_PERIODIC_BUTTON_LED_PERIOD                  100
#define BUTTON_LED_TOGGLE_COUNT                         2

#define SLEEP_MS                                        300  //睡眠时间， 串口激活事件

#define PERIPHERAL_WAKEUP_LED_TOGGLE_CNT                4
#define PERIPHERAL_START_LED_TOGGLE_CNT                 6
#define PERIPHERAL_START_LED_TOGGLE_PERIOD_ON               50
#define PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF              150
#define PERIPHERAL_KEY_CALCULATE_PERIOD                 250 // 250ms

#define PERIPHERAL_KEY_LONG_PRESS_CALC_PERIOD           100 // 100ms
#define PERIPHERAL_KEY_LONG_PRESS_TIME_CNT              (2 * 1000 / PERIPHERAL_KEY_LONG_PRESS_CALC_PERIOD) // 2s
#define PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_1        500 // 500ms
#define PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_2        800 // 800ms

//#define PERIPHERAL_LOW_BAT_LED_TOGGLE_S                 3 // 3s
#define PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_OFF        (150) // 150ms
#define PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_ON         (50) // 50ms
#define PERIPHERAL_LOW_BAT_LED_TOGGLE_CNT               20

#define BUTTON_LED_DELAY  650 // 1s
#define BUTTON_LEY_DELAY_IN_SLEEP  650 //1s

#define BATTERY_LOW_THRESHOLD_SLEEP                           27 //2.7V
#define BATTERY_LOW_THRESHOLD                                 20 //2V
#define ENABLE_DISABLE_PERIOD 500

#define ADV_HOUR_LEFT_BYTE 25
#define ADV_INDEX_BYTE 26
#define ADV_FLAG_BYTE 27
#define ADV_BAT_BYTE 28


//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

//#define RELEASE_VER                      //定义版本发布用
#define     VERSION     "v0.1"  //
#define MAJOR_HW_VERSION   0x00
#define MINOR_HW_VERSION   0x03
#define MAJOR_SW_VERSION   0x01
#if (POWER_OFF_SUPPORT == TRUE)
#define MIDDLE_SW_VERSION  0x01
#elif (POWER_OFF_SUPPORT == FALSE)
#define MIDDLE_SW_VERSION  0x00
#endif
#define MINOR_SW_VERSION   0x03

//设备名称的字符长度 <= 12
#define DEV_NAME_DEFAULT                           "DarrenBLE"


//设备名称的字符长度 <= 12
#define DEV_NAME_LEN                                12
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// 系统定时器间隔时间
#define SBP_PERIODIC_EVT_PERIOD                   100//必须是100ms

//最大记录的从机地址
#define MAX_PERIPHERAL_MAC_ADDR                   10//最大记录的从机地址

//mac地址的字符长度 (一个字节等于两个字符)
#define MAC_ADDR_CHAR_LEN                          12//mac地址的字符长度 (一个字节等于两个字符)

// 出厂设置或清除配对信息与从机信息
typedef enum
{
    PARA_ALL_FACTORY = 0,           //全部恢复出厂设置
    PARA_PARI_FACTORY = 1,          //配对信息恢复出厂设置-相当于清除配对信息与从机信息
}PARA_SET_FACTORY;

// 应用程序状态
enum
{
  BLE_STATE_IDLE,                    //无连接-空闲状态
  BLE_STATE_CONNECTING,             //连接中...
  BLE_STATE_CONNECTED,              //已连接上
  BLE_STATE_DISCONNECTING,          //断开连接中
  BLE_STATE_ADVERTISING             //从机广播中
};

// 连接模式指示
typedef enum
{
  CONNECT_MODE_FIX_ADDR_CONNECTED,     // 指定 mac地址进行连接
  CONNECT_MODE_LAST_ADDR_CONNECTED,    // 连接最后成功连接过的 mac地址
  CONNECT_MODE_MAX,
}CONNECT_MODE;


// 应用程序状态
typedef enum
{
  BLE_CENTRAL_CONNECT_CMD_NULL,              //主机 AT 连接命令  空
  BLE_CENTRAL_CONNECT_CMD_CONNL,             //主机 AT 连接命令  连接最近成功过的地址
  BLE_CENTRAL_CONNECT_CMD_CON,               //主机 AT 连接命令  连接指定地址
  BLE_CENTRAL_CONNECT_CMD_DISC,              //主机 AT 扫描从机命令
  BLE_CENTRAL_CONNECT_CMD_CONN,              //主机 AT 连接命令  连接扫描到的地址的下标号对应的地址
}BLE_CENTRAL_CONNECT_CMD;
extern BLE_CENTRAL_CONNECT_CMD g_Central_connect_cmd ;

// 定于系统结构变量， 该结构会在开机时从nv flash 中读取， 数据有修改时， 需要写入nv flash
// 这样， 就实现了系统重启后数据还是上一次设置的
typedef struct 
{
    /*
    波特率
    0---------9600 
    1---------19200 
    2---------38400 
    3---------57600 
    4---------115200
    */
    uint8 baudrate;                 //波特率 ， 目前支持的列表如上
    uint8 parity;                   //校验位    
    uint8 stopbit;                  //停止位
    // 设备名称，最长 11 位数字或字母，含中划线和下划线，不建议用其它字符    
    uint8 name[12];                 
    BLE_ROLE role;                  //主从模式  0: 从机   1: 主机
    uint8 mac_addr[MAC_ADDR_CHAR_LEN+1];            //本机mac地址 最大12位 字符表示
    int8 rssi;                              //  RSSI 信号值
    uint8 rxGain;                           //  接收增益强度
    uint8 txPower;                          //  发射信号强度
} SYS_CONFIG;
extern SYS_CONFIG sys_config;

extern uint8 simpleBLEState;
extern uint16 simpleBLECharHdl;
extern uint16 simpleBLECharHd6;
extern bool simpleBLEChar6DoWrite;
extern bool simpleBLEChar6DoWrite2;

#if defined (RELEASE_VER)
#define LCD_WRITE_STRING(str, option)                     
#define LCD_WRITE_SCREEN(line1, line2)                    
#define LCD_WRITE_STRING_VALUE(title, value, format, line)

#if defined (HAL_LCD)
#undef HAL_LCD
#define HAL_LCD FALSE 
#endif

#else
// LCD macros
#if HAL_LCD == TRUE
#define LCD_WRITE_STRING(str, option)                       HalLcdWriteString( (str), (option))
#define LCD_WRITE_SCREEN(line1, line2)                      HalLcdWriteScreen( (line1), (line2) )
#define LCD_WRITE_STRING_VALUE(title, value, format, line)  HalLcdWriteStringValue( (title), (value), (format), (line) )
#else
#define LCD_WRITE_STRING(str, option) {}                   
#define LCD_WRITE_SCREEN(line1, line2) {}                  
#define LCD_WRITE_STRING_VALUE(title, value, format, line) {}
#endif
#endif

extern uint8 simpleBLETaskId;               // 主机任务
extern uint8 simpleBLEState;
extern uint16 simpleBLECharHdl;
extern uint16 simpleBLECharHd6;
extern bool simpleBLECentralCanSend;
extern bool simpleBLEChar6DoWrite;

#if 1
// 该函数延时时间为1ms， 用示波器测量过， 稍有误差， 但误差很小  --amomcu.com
void simpleBLE_Delay_1ms(int times);

// 字符串对比
uint8 str_cmp(uint8 *p1,uint8 *p2,uint8 len);

// 字符串转数字
uint32 str2Num(uint8* numStr, uint8 iLength);

char *bdAddr2Str( uint8 *pAddr );

// 保存所有数据到nv flash
void simpleBLE_WriteAllDataToFlash();

// 读取自定义的 nv flash 数据  -------未使用到
void simpleBLE_ReadAllDataToFlash();

//flag: PARA_ALL_FACTORY:  全部恢复出厂设置
//flag: PARA_PARI_FACTORY: 清除配对信息
void simpleBLE_SetAllParaDefault(PARA_SET_FACTORY flag); 

// 打印所有存储到nv flash的数据， 方便调试代码
void PrintAllPara(void);

// 返回设备角色
//主从模式  0: 从机   1: 主机
BLE_ROLE GetBleRole();

// 有按键按下，则启动为主机， 否则默认启动为从机
// 0 启动peripheral从设备， 1: 启动为 central
bool Check_startup_peripheral_or_central(void);

// 串行口 uart 初始化
void simpleBLE_NPI_init(void);

// 设置接收增益
void UpdateRxGain(void);

// 设置发射功率
void UpdateTxPower(void);

// 设置led灯的状态
void simpleBle_LedSetState(uint8 onoff);

// 获取设备名称
uint8* simpleBle_GetAttDeviceName();

// 定时器任务定时执行函数， 用于设置led的状态----也可以增加一个定时器来做
void simpleBLE_performPeriodicTask( void );

//uart 回调函数
static void simpleBLE_NpiSerialCallback( uint8 port, uint8 events );

// AT 命令处理 函数
bool simpleBLE_AT_CMD_Handle(uint8 *pBuffer, uint16 length);
// MT 命令处理 函数
bool simpleBLE_MT_CMD_Handle(uint8 *pBuffer, uint16 length);

#if defined(USE_DISPLAY_KEY_VALUE)  // 测试按键专用，显示5向按键值
void SimpleBLE_DisplayTestKeyValue();
#endif

extern bool g_sleepFlag;    //睡眠标志
extern uint8 uart_sleep_count; // 睡眠计数器
extern bool g_rssi_flag;       //是否开启测距
#endif



/* NFC related macro define */




#ifdef __cplusplus
}
#endif

#endif /* SIMPLEBLE_H */