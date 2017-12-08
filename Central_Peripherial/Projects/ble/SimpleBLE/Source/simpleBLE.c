#include "bcomdef.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"
#include "OnBoard.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_lcd.h"
#include "gatt.h"
#include "ll.h"
#include "hci.h"
#include "gapgattserver.h"
#include "gattservapp.h"
#include "central.h"
#include "peripheral.h"
#include "gapbondmgr.h"
#include "simpleGATTprofile.h"
#include "npi.h"
#include "osal_snv.h"
#include "simpleBLE.h"
#include "stdio.h"
#include "string.h"
#include "hal_adc.h"
#include "amomcu_buffer.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

SYS_CONFIG sys_config;
bool g_sleepFlag = FALSE;    //睡眠标志
uint8 uart_sleep_count = 0; // 睡眠计数器
bool g_rssi_flag = false; //是否开启测距
extern gaprole_States_t gapProfileState; // 从机连接状态
// Connection handle
extern uint16 gapConnHandle;
BLE_CENTRAL_CONNECT_CMD g_Central_connect_cmd = BLE_CENTRAL_CONNECT_CMD_NULL;
static void simpleBLE_NpiSerialCallback(uint8 port, uint8 events);


// 该函数延时时间为1ms， 用示波器测量过， 稍有误差， 但误差很小  --amomcu.com
void simpleBLE_Delay_1ms(int times)
{
  while (times--)
  {
    int i = 0;
    for (i = 1500; i > 0; i--)
    {
      asm("nop");
    }
  }
}

// 字符串对比
uint8 str_cmp(uint8 *p1, uint8 *p2, uint8 len)
{
  uint8 i = 0;
  while (i < len)
  {
    if (p1[i] != p2[i])
      return 0;
    i++;
  }
  return 1;
}

// 字符串转数字
uint32 str2Num(uint8 *numStr, uint8 iLength)
{
  uint8 i = 0;
  int32 rtnInt = 0;

  /* 
          为代码简单，在确定输入的字符串都是数字的
          情况下，此处未做检查，否则要检查
          numStr[i] - '0'是否在[0, 9]这个区间内
    */
  for (; i < iLength && numStr[i] != '\0'; ++i)
    rtnInt = rtnInt * 10 + (numStr[i] - '0');

  return rtnInt;
}

/*********************************************************************
 * @fn      bdAddr2Str
 *
 * @brief   Convert Bluetooth address to string
 *
 * @return  none
 */
char *bdAddr2Str(uint8 *pAddr)
{
#define B_ADDR_STR_LEN 15

  uint8 i;
  char hex[] = "0123456789ABCDEF";
  static char str[B_ADDR_STR_LEN];
  char *pStr = str;

  *pStr++ = '0';
  *pStr++ = 'x';

  // Start from end of addr
  pAddr += B_ADDR_LEN;

  for (i = B_ADDR_LEN; i > 0; i--)
  {
    *pStr++ = hex[*--pAddr >> 4];
    *pStr++ = hex[*pAddr & 0x0F];
  }

  *pStr = 0;

  return str;
}

// 保存所有数据到nv flash
void simpleBLE_WriteAllDataToFlash()
{ // 写所有参数
  osal_snv_write(0x80, sizeof(SYS_CONFIG), &sys_config);
}

// 读取自定义的 nv flash 数据  -------未使用到
void simpleBLE_ReadAllDataToFlash()
{
  int8 ret8 = osal_snv_read(0x80, sizeof(SYS_CONFIG), &sys_config);
}

//flag: PARA_ALL_FACTORY:  全部恢复出厂设置
//flag: PARA_PARI_FACTORY: 清除配对信息
void simpleBLE_SetAllParaDefault(PARA_SET_FACTORY flag)
{
  if (flag == PARA_ALL_FACTORY)
  {
    //sys_config.baudrate = HAL_UART_BR_9600;
    sys_config.baudrate = HAL_UART_BR_115200;
    sys_config.parity = 0;
    sys_config.stopbit = 0;

    sprintf((char *)sys_config.name, DEV_NAME_DEFAULT); //设备名称

    sys_config.role = BLE_ROLE_PERIPHERAL; //主从模式, 默认从机
    //sys_config.role = BLE_ROLE_CENTRAL;

    osal_memset(sys_config.mac_addr, 0, sizeof(sys_config.mac_addr));

    sys_config.rssi = 0; //  RSSI 信号值
    sys_config.rxGain = HCI_EXT_RX_GAIN_STD; //  接收增益强度
    sys_config.txPower = 0;                  //  发射信号强度
  }
  GAPBondMgr_SetParameter(GAPBOND_ERASE_ALLBONDS, 0, NULL); //清除绑定信息
  simpleBLE_WriteAllDataToFlash();
}

// 打印所有存储到nv flash的数据， 方便调试代码
void PrintAllPara(void)
{
  char strTemp[32];

  sprintf(strTemp, "sys_config.baudrate = %d\r\n", sys_config.baudrate);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.parity = %d\r\n", sys_config.parity);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.stopbit = %d\r\n", sys_config.stopbit);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.name = %s\r\n", sys_config.name);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.role = %d\r\n", sys_config.role);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.mac_addr = %s\r\n", sys_config.mac_addr);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.rssi = %d\r\n", sys_config.rssi);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

  sprintf(strTemp, "sys_config.txPower = %d\r\n", sys_config.txPower);
  NPI_WriteTransport((uint8 *)strTemp, osal_strlen(strTemp));
  simpleBLE_Delay_1ms(100);

}

// 返回设备角色
//主从模式  0: 从机   1: 主机
BLE_ROLE GetBleRole()
{
  return sys_config.role;
}

// 判断蓝牙是否连接上
// 0: 未连接上
// 1: 已连接上
bool simpleBLE_IfConnected()
{
  if (GetBleRole() == BLE_ROLE_CENTRAL) //主机
  {
    return (simpleBLEState == BLE_STATE_CONNECTED);
  }
  else
  {
    return (gapProfileState == GAPROLE_CONNECTED);
  }
}

// 增加从机地址， 注意， 需要连接成功后， 再增加该地址
void simpleBLE_SetPeripheralMacAddr(uint8 *pAddr)
{
  return;
}

// 有按键按下，则启动为主机， 否则默认启动为从机
// 0 启动peripheral从设备， 1: 启动为 central
bool Check_startup_peripheral_or_central(void)
{
  /*
    P0SEL &= ~0x02;     //设置P0.1为普通IO口  
    P0DIR &= ~0x02;     //按键接在P0.1口上，设P0.1为输入模式 
    P0INP &= ~0x02;     //打开P0.1上拉电阻

    if(0 == P0_1)// 有按键按下
    {
        // 10ms 去抖动 
        simpleBLE_Delay_1ms(10);
        if(0 == P0_1)// 有按键按下
        {
            return true;
        }
    }
    */
  if (PRESET_ROLE == BLE_ROLE_CENTRAL)
    return true;
  else if (PRESET_ROLE == BLE_ROLE_PERIPHERAL)
    return false;
  else
    return false;
}

// 串行口 uart 初始化
void simpleBLE_NPI_init(void)
{
  
  // 开机打印主机还是从机
  if (GetBleRole() == BLE_ROLE_CENTRAL)
  {
    NPI_InitTransport(HAL_UART_PORT_0, simpleBLE_NpiSerialCallback);
    NPI_WriteTransportPort(HAL_UART_PORT_0, "Central\r\n", 21);
    
  }
  else
  {
    NPI_InitTransport(HAL_UART_PORT_0, simpleBLE_NpiSerialCallback);
    NPI_WriteTransport("Peripheral\r\n", 24);
    NPI_InitTransport(HAL_UART_PORT_1, simpleBLE_NpiSerialCallback);
    NPI_WriteTransportPort(HAL_UART_PORT_1, "Peripheral\r\n", 24);
  }
}

// 设置接收增益
void UpdateRxGain(void)
{
  // HCI_EXT_SetRxGainCmd()是用来设置发射功率的.
  // rxGain - HCI_EXT_RX_GAIN_STD, HCI_EXT_RX_GAIN_HIGH
  HCI_EXT_SetRxGainCmd(HCI_EXT_RX_GAIN_STD);
}

// 设置发射功率
void UpdateTxPower(void)
{
  HCI_EXT_SetTxPowerCmd(3 - sys_config.txPower);
}

// 设置led灯的状态
void simpleBle_LedSetState(uint8 onoff)
{
  HalLedSet(HAL_LED_1, onoff); //led常亮
  P0DIR |= 0x60; // P0.6定义为输出
  P0_6 = onoff;
}

// 获取设备名称
uint8 *simpleBle_GetAttDeviceName()
{
  return sys_config.name;
}

// 定时器任务定时执行函数， 用于设置led的状态----也可以增加一个定时器来做
void simpleBLE_performPeriodicTask(void)
{
  return;
}

//uart 回调函数
static void simpleBLE_NpiSerialCallback(uint8 port, uint8 events)
{
  (void)port;
  if (events & (HAL_UART_RX_TIMEOUT | HAL_UART_RX_FULL)) //串口有数据
  {
    (void)port;
    /*uint8*/ uint16 numBytes = 0;
    uart_sleep_count = 0;
    numBytes = NPI_RxBufLen();
    if (numBytes > 0)
    {
      uint8 *buffer = osal_mem_alloc(numBytes);
      NPI_ReadTransport(buffer, numBytes); //释放串口数据
      if (FALSE == g_sleepFlag) //discard the data directly.
      {
        NPI_WriteTransport(buffer, numBytes); //释放串口数据
      }
      osal_mem_free(buffer);
    }
    return;
  }
}

//uart 回调函数
static void simpleBLE_NpiSerialCallbackUART1(uint8 port, uint8 events)
{
  (void)port;
  if (events & (HAL_UART_RX_TIMEOUT | HAL_UART_RX_FULL)) //串口有数据
  {
    (void)port;
    /*uint8*/ uint16 numBytes = 0;
    uart_sleep_count = 0;
    numBytes = NPI_RxBufLenPort(HAL_UART_PORT_1);
    if (numBytes > 0)
    {
      uint8 *buffer = osal_mem_alloc(numBytes);
      NPI_ReadTransportPort(HAL_UART_PORT_1, buffer, numBytes); //释放串口数据
      if (FALSE == g_sleepFlag) //discard the data directly.
      {
        NPI_WriteTransportPort(HAL_UART_PORT_1, buffer, numBytes); //释放串口数据
      }
      osal_mem_free(buffer);
    }
    return;
  }
}