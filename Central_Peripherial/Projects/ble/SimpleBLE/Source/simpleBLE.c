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
bool g_sleepFlag = TRUE;    //˯�߱�־
uint8 uart_sleep_count = 0; // ˯�߼�����
bool g_rssi_flag = false; //�Ƿ�����
extern gaprole_States_t gapProfileState; // �ӻ�����״̬
// Connection handle
extern uint16 gapConnHandle;
BLE_CENTRAL_CONNECT_CMD g_Central_connect_cmd = BLE_CENTRAL_CONNECT_CMD_NULL;
static void simpleBLE_NpiSerialCallback(uint8 port, uint8 events);


// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ ������ ������С  --amomcu.com
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
          ����£��˴�δ����飬����Ҫ���
          numStr[i] - '0'�Ƿ���[0, 9]���������
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

// ��ȡ�Զ���� nv flash ����  -------δʹ�õ�
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
    //sys_config.baudrate = HAL_UART_BR_9600;
    sys_config.baudrate = HAL_UART_BR_115200;
    sys_config.parity = 0;
    sys_config.stopbit = 0;

    sprintf((char *)sys_config.name, DEV_NAME_DEFAULT); //�豸����

    sys_config.role = BLE_ROLE_PERIPHERAL; //����ģʽ, Ĭ�ϴӻ�
    //sys_config.role = BLE_ROLE_CENTRAL;

    osal_memset(sys_config.mac_addr, 0, sizeof(sys_config.mac_addr));

    sys_config.rssi = 0; //  RSSI �ź�ֵ
    sys_config.rxGain = HCI_EXT_RX_GAIN_STD; //  ��������ǿ��
    sys_config.txPower = DEFAULT_TX_POWER;                  //  �����ź�ǿ��
  }
  GAPBondMgr_SetParameter(GAPBOND_ERASE_ALLBONDS, 0, NULL); //�������Ϣ
  simpleBLE_WriteAllDataToFlash();
}

// ��ӡ���д洢��nv flash�����ݣ� ������Դ���
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
  /*
    P0SEL &= ~0x02;     //����P0.1Ϊ��ͨIO��  
    P0DIR &= ~0x02;     //��������P0.1���ϣ���P0.1Ϊ����ģʽ 
    P0INP &= ~0x02;     //��P0.1��������

    if(0 == P0_1)// �а�������
    {
        // 10ms ȥ���� 
        simpleBLE_Delay_1ms(10);
        if(0 == P0_1)// �а�������
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

// ���п� uart ��ʼ��
void simpleBLE_NPI_init(void)
{
  NPI_InitTransport(simpleBLE_NpiSerialCallback);
  // ������ӡ�������Ǵӻ�
  if (GetBleRole() == BLE_ROLE_CENTRAL)
  {
    NPI_WriteTransport("Central\r\n", 21);
  }
  else
  {
    NPI_WriteTransport("Peripheral\r\n", 24);
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
  HCI_EXT_SetTxPowerCmd(sys_config.txPower);
}

// ����led�Ƶ�״̬
void simpleBle_LedSetState(uint8 onoff)
{
  HalLedSet(HAL_LED_1, onoff); //led����
  P0DIR |= 0x60; // P0.6����Ϊ���
  P0_6 = onoff;
}

// ��ȡ�豸����
uint8 *simpleBle_GetAttDeviceName()
{
  return sys_config.name;
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
    (void)port;
    /*uint8*/ uint16 numBytes = 0;
    uart_sleep_count = 0;
    numBytes = NPI_RxBufLen();
    if (numBytes > 0)
    {
      uint8 *buffer = osal_mem_alloc(numBytes);
      NPI_ReadTransport(buffer, numBytes); //�ͷŴ�������
      if (FALSE == g_sleepFlag) //discard the data directly.
      {
        NPI_WriteTransport(buffer, numBytes); //�ͷŴ�������
      }
      osal_mem_free(buffer);
    }
    return;
  }
}