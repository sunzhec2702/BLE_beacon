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
bool g_sleepFlag = FALSE;    //˯�߱�־
uint8 uart_sleep_count = 0; // ˯�߼�����
bool g_rssi_flag = false; //�Ƿ�����
extern gaprole_States_t gapProfileState; // �ӻ�����״̬
// Connection handle
extern uint16 gapConnHandle;
BLE_CENTRAL_CONNECT_CMD g_Central_connect_cmd = BLE_CENTRAL_CONNECT_CMD_NULL;
static void simpleBLE_NpiSerialCallback(uint8 port, uint8 events);


// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ �������? ������С  --amomcu.com
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

// �ַ����Ա�
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

// �ַ���ת����
uint32 str2Num(uint8 *numStr, uint8 iLength)
{
  uint8 i = 0;
  int32 rtnInt = 0;

  /* 
          Ϊ����򵥣���ȷ��������ַ����������ֵ�
          ����£��˴�δ����飬����Ҫ���?
          numStr[i] - '0'�Ƿ���[0, 9]���������?
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

// �����������ݵ�nv flash
void simpleBLE_WriteAllDataToFlash()
{ // д���в���
  osal_snv_write(0x80, sizeof(SYS_CONFIG), &sys_config);
}

// ��ȡ�Զ����? nv flash ����  -------δʹ�õ�
void simpleBLE_ReadAllDataToFlash()
{
  int8 ret8 = osal_snv_read(0x80, sizeof(SYS_CONFIG), &sys_config);
}

//flag: PARA_ALL_FACTORY:  ȫ���ָ���������
//flag: PARA_PARI_FACTORY: ��������Ϣ
void simpleBLE_SetAllParaDefault(PARA_SET_FACTORY flag)
{
  if (flag == PARA_ALL_FACTORY)
  {
    sys_config.status = BLE_STATUS_ON_ADV;
    sys_config.role = BLE_ROLE_CENTRAL; //����ģʽ, Ĭ�ϴӻ�
    sys_config.rssi = 0; //  RSSI �ź�ֵ
    sys_config.rxGain = HCI_EXT_RX_GAIN_STD; //  ��������ǿ��
    sys_config.txPower = 0;                  //  �����ź�ǿ��
    sys_config.stationIndex = 0;
    sys_config.minLeft = 30;
  }
  GAPBondMgr_SetParameter(GAPBOND_ERASE_ALLBONDS, 0, NULL); //��������?
  simpleBLE_WriteAllDataToFlash();
}

// ��ӡ���д洢��nv flash�����ݣ� ������Դ���?
void PrintAllPara(void)
{
  char strTemp[32];
  sprintf(strTemp, "sys_config.status = %d\r\n", sys_config.status);
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

// �����豸��ɫ
//����ģʽ  0: �ӻ�   1: ����
BLE_ROLE GetBleRole()
{
  return sys_config.role;
}

// �ж������Ƿ�������
// 0: δ������
// 1: ��������
bool simpleBLE_IfConnected()
{
  if (GetBleRole() == BLE_ROLE_CENTRAL) //����
  {
    return (simpleBLEState == BLE_STATE_CONNECTED);
  }
  else
  {
    return (gapProfileState == GAPROLE_CONNECTED);
  }
}

// ���Ӵӻ���ַ�� ע�⣬ ��Ҫ���ӳɹ��� �����Ӹõ�ַ
void simpleBLE_SetPeripheralMacAddr(uint8 *pAddr)
{
  return;
}

// �а������£�����Ϊ������ ����Ĭ����Ϊ�ӻ�
// 0 ��peripheral���豸�� 1: ��Ϊ central
bool Check_startup_peripheral_or_central(void)
{
  switch (sys_config.status)
  {
    case BLE_STATUS_OFF:
    return true;
    break;
    case BLE_STATUS_ON_ADV:
    return false;
    break;
    case BLE_STATUS_ON_SCAN:
    return true;
    break;
  }
}

// ���п� uart ��ʼ��
void simpleBLE_NPI_init(void)
{
  
  // ������ӡ�������Ǵӻ�
  if (GetBleRole() == BLE_ROLE_CENTRAL)
  {
    NPI_InitTransport(HAL_UART_PORT_0, simpleBLE_NpiSerialCallback);
    NPI_WriteTransportPort(HAL_UART_PORT_0, "Central\r\n", 21);
    
  }
  else
  {
    NPI_InitTransport(HAL_UART_PORT_0, simpleBLE_NpiSerialCallback);
    //ble_uart_poll_init();
    //NPI_InitTransport(HAL_UART_PORT_1, simpleBLE_NpiSerialCallback1);
    //uint8 WAKE_UP[] = {0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0xfd, 0xd4, 0x14, 0x01, 0x17, 0x00};
    //NPI_WriteTransportPort(HAL_UART_PORT_1, WAKE_UP, sizeof(WAKE_UP));
    //NPI_WriteTransportPort(HAL_UART_PORT_0, WAKE_UP, sizeof(WAKE_UP));
  }
}

// ���ý�������
void UpdateRxGain(void)
{
  // HCI_EXT_SetRxGainCmd()���������÷��书�ʵ�.
  // rxGain - HCI_EXT_RX_GAIN_STD, HCI_EXT_RX_GAIN_HIGH
  HCI_EXT_SetRxGainCmd(HCI_EXT_RX_GAIN_STD);
}

// ���÷��书��
void UpdateTxPower(void)
{
  HCI_EXT_SetTxPowerCmd(3 - sys_config.txPower);
}

// ����led�Ƶ�״̬
void simpleBle_LedSetState(uint8 onoff)
{
  HalLedSet(HAL_LED_1, onoff); //led����
  P0DIR |= 0x60; // P0.6����Ϊ���?
  P0_6 = onoff;
}

// ��ȡ�豸����
uint8 *simpleBle_GetAttDeviceName()
{
  return "DarrenBLE";
}

// ��ʱ������ʱִ�к����� ��������led��״̬----Ҳ��������һ����ʱ������
void simpleBLE_performPeriodicTask(void)
{
  return;
}

//uart �ص�����
static void simpleBLE_NpiSerialCallback(uint8 port, uint8 events)
{
  (void)port;
  if (events & (HAL_UART_RX_TIMEOUT | HAL_UART_RX_FULL)) //����������
  {
    /*uint8*/ uint16 numBytes = 0;
    uart_sleep_count = 0;
    numBytes = NPI_RxBufLen();
    if (numBytes > 0)
    {
      uint8 *buffer = osal_mem_alloc(numBytes);
      NPI_ReadTransport(buffer, numBytes); //�ͷŴ�������
      /* Darren:Handle this sleep issue.
      if (FALSE == g_sleepFlag) //discard the data directly.
      {
      }
      */
      // Directly send to interface 
      // ble_uart_interrupt(buffer, numBytes);
      NPI_WriteTransport(buffer, numBytes); //�ͷŴ�������
      //NPI_WriteTransportPort(HAL_UART_PORT_1, buffer, numBytes);
      osal_mem_free(buffer);
    }
    return;
  }
}