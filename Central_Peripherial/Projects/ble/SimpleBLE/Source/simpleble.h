#ifndef SIMPLEBLE_H
#define SIMPLEBLE_H

#ifdef __cplusplus
#include "npi.h"
extern "C"
{
#endif
#include "hal_types.h"

#define DEVELOP_BOARD 0
#define PRODUCT_BOARD 1

#define TARGET_BOARD PRODUCT_BOARD

#define POWER_OFF_SUPPORT TRUE
//#define DEBUG_BOARD 1

#define PRESET_ROLE BLE_ROLE_PERIPHERAL

// ��ǰ��Ƭ�����еĽ�ɫ
typedef enum
{
    BLE_ROLE_PERIPHERAL = 0,        //�ӻ���ɫ
    BLE_ROLE_CENTRAL = 1,           //������ɫ    
}BLE_ROLE;

#if (PRESET_ROLE == BLE_ROLE_CENTRAL)
#define HAL_LCD TRUE
#define HAL_UART TRUE
#define LCD_TO_UART TRUE
#endif

#ifdef DEBUG_BOARD
#define HAL_LCD TRUE
#define HAL_UART TRUE
#define LCD_TO_UART TRUE
#define DEBUG_PRINT(x) NPI_PrintString(x)
#define DEBUG_VALUE(x,y,z) {NPI_PrintValue(x, y, z);NPI_PrintString("\r\n");}
#else // PRODUCT_BOARD
  #if (PRESET_ROLE == BLE_ROLE_CENTRAL)
    #define HAL_LCD TRUE
    #define HAL_UART TRUE
    #define LCD_TO_UART TRUE
  #else // PERIPHERIAL
    #define HAL_LCD FALSE
    #define HAL_UART FALSE
    #define LCD_TO_UART FALSE
  #endif // CENTRAL
#define DEBUG_PRINT(x) {}
#define DEBUG_VALUE(x,y,z) {}
#endif


// �����ӻ��¼����ö���
#define START_DEVICE_EVT                               0x0001//���豸
#define SBP_PERIODIC_EVT                               0x0002//ϵͳ��ѯ��ʱ��
#define SBP_DATA_EVT                                   0x8000//���ݴ���
#define SBP_KEY_CNT_EVT                                0x0008//count the key pressed.
#define SBP_UART_EVT                                   0x0010//���������¼�
#define SBP_SLEEP_EVT                                  0x0020//˯���¼�
#define SBP_WAKE_EVT                                   0x0040//�����¼�
#define SBP_PERIODIC_LED_EVT                           0x0080//��������
#define SBP_CONNECT_EVT                                0x0100//��������-ȷ������
#define START_DISCOVERY_EVT                            0x0200//���ִ��豸

#define SBP_PERIODIC_BUTTON_LED_EVT                    0x0400
#define SBP_PERIODIC_PER_HOUR_EVT                      0x0800
#define SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE            0x1000
#define SBP_PERIODIC_CHN_ADVERT_EVT_PRESS              0x2000
#define SBP_PERIODIC_INDEX_EVT                         0x4000//ϵͳ��ѯ��ʱ��

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
#define DEFAULT_RIGHT_MOVE_BIT                          3
#define BUTTON_WAKE_TIME_HOURS                          (2) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1) // 1 days
#else
#define SBP_PERIODIC_PER_HOUR_PERIOD                    3600000 // 1 hour
#define DEFAULT_WAKE_TIME_HOURS                         (24 * 60) // 5 days
#define DEFAULT_RIGHT_MOVE_BIT                          3
#define BUTTON_WAKE_TIME_HOURS                          (2 * 24) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1 * 24) // 1 days
#endif

#define SBP_PERIODIC_BUTTON_LED_PERIOD                  100
#define BUTTON_LED_TOGGLE_COUNT                         1

#define SLEEP_MS                                        300  //˯��ʱ�䣬 ���ڼ����¼�

#define PERIPHERAL_WAKEUP_LED_TOGGLE_CNT                2
#define PERIPHERAL_START_LED_TOGGLE_CNT                 3

#define PERIPHERAL_LED_PREPARE_PERIOD_KEEP                  650
#define PERIPHERAL_LED_TOGGLE_PERIOD_KEEP                   30

#define PERIPHERAL_START_LED_TOGGLE_PERIOD_ON               200
#define PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF              PERIPHERAL_START_LED_TOGGLE_PERIOD_ON
#define PERIPHERAL_KEY_CALCULATE_PERIOD                 250 // 250ms

#define PERIPHERAL_KEY_LONG_PRESS_CALC_PERIOD           100 // 100ms
#define PERIPHERAL_KEY_LONG_PRESS_TIME_CNT              (2 * 1000 / PERIPHERAL_KEY_LONG_PRESS_CALC_PERIOD) // 2s
#define PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_1        500 // 500ms
#define PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_2        800 // 800ms

//#define PERIPHERAL_LOW_BAT_LED_TOGGLE_S                 3 // 3s
#define PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_OFF        (150) // 150ms
#define PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_ON         (50) // 50ms
#define PERIPHERAL_LOW_BAT_LED_TOGGLE_CNT               20

#define BUTTON_LED_DELAY  (650 - PERIPHERAL_LED_PREPARE_PERIOD_KEEP) // 1s
#define BUTTON_LEY_DELAY_IN_SLEEP  BUTTON_LED_DELAY //1s

#define BATTERY_LOW_THRESHOLD_SLEEP                           27 //2.7V
#define BATTERY_LOW_THRESHOLD                                 20 //2V
#define ENABLE_DISABLE_PERIOD 500

#define ADV_HOUR_LEFT_BYTE 25
#define ADV_INDEX_BYTE 26
#define ADV_FLAG_BYTE 27
#define ADV_BAT_BYTE 28


//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

//#define RELEASE_VER                      //����汾������?
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

//�豸���Ƶ��ַ����� <= 12
#define DEV_NAME_DEFAULT                           "DarrenBLE"


//�豸���Ƶ��ַ����� <= 12
#define DEV_NAME_LEN                                12
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// ϵͳ��ʱ�����ʱ��?
#define SBP_PERIODIC_EVT_PERIOD                   100//������100ms

//����¼�Ĵӻ���ַ
#define MAX_PERIPHERAL_MAC_ADDR                   10//����¼�Ĵӻ���ַ

//mac��ַ���ַ����� (һ���ֽڵ��������ַ�)
#define MAC_ADDR_CHAR_LEN                          12//mac��ַ���ַ����� (һ���ֽڵ��������ַ�)

// �������û���������Ϣ��ӻ����?
typedef enum
{
    PARA_ALL_FACTORY = 0,           //ȫ���ָ���������
    PARA_PARI_FACTORY = 1,          //������?�ָ���������-�൱����������Ϣ��ӻ����?
}PARA_SET_FACTORY;

// Ӧ�ó���״̬
enum
{
  BLE_STATE_IDLE,                    //������-����״̬
  BLE_STATE_CONNECTING,             //������...
  BLE_STATE_CONNECTED,              //��������
  BLE_STATE_DISCONNECTING,          //�Ͽ�������
  BLE_STATE_ADVERTISING             //�ӻ��㲥��
};

// ����ģʽָʾ
typedef enum
{
  CONNECT_MODE_FIX_ADDR_CONNECTED,     // ָ�� mac��ַ��������
  CONNECT_MODE_LAST_ADDR_CONNECTED,    // �������ɹ����ӹ��� mac��ַ
  CONNECT_MODE_MAX,
}CONNECT_MODE;


// Ӧ�ó���״̬
typedef enum
{
  BLE_CENTRAL_CONNECT_CMD_NULL,              //���� AT ��������  ��
  BLE_CENTRAL_CONNECT_CMD_CONNL,             //���� AT ��������  ��������ɹ����ĵ��?
  BLE_CENTRAL_CONNECT_CMD_CON,               //���� AT ��������  ����ָ����ַ
  BLE_CENTRAL_CONNECT_CMD_DISC,              //���� AT ɨ��ӻ�����?
  BLE_CENTRAL_CONNECT_CMD_CONN,              //���� AT ��������  ����ɨ�赽�ĵ�ַ���±�Ŷ�Ӧ�ĵ��?
}BLE_CENTRAL_CONNECT_CMD;
extern BLE_CENTRAL_CONNECT_CMD g_Central_connect_cmd ;

// ����ϵͳ�ṹ������ �ýṹ���ڿ���ʱ��nv flash �ж�ȡ�� �������޸�ʱ�� ��Ҫд��nv flash
// ������ ��ʵ����ϵͳ��������ݻ�����һ�����õ�?
typedef struct 
{
    /*
    ������
    0---------9600 
    1---------19200 
    2---------38400 
    3---------57600 
    4---------115200
    */
    uint8 baudrate;                 //������ �� Ŀǰ֧�ֵ��б�����
    uint8 parity;                   //У��λ    
    uint8 stopbit;                  //ֹͣλ
    // �豸���ƣ�� 11 λ���ֻ���ĸ�����л��ߺ��»��ߣ��������������ַ�    
    uint8 name[12];                 
    BLE_ROLE role;                  //����ģʽ  0: �ӻ�   1: ����
    uint8 mac_addr[MAC_ADDR_CHAR_LEN+1];            //����mac��ַ ���?12λ �ַ���ʾ
    int8 rssi;                              //  RSSI �ź�ֵ
    uint8 rxGain;                           //  ��������ǿ��
    uint8 txPower;                          //  �����ź�ǿ��
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

extern uint8 simpleBLETaskId;               // ��������
extern uint8 simpleBLEState;
extern uint16 simpleBLECharHdl;
extern uint16 simpleBLECharHd6;
extern bool simpleBLECentralCanSend;
extern bool simpleBLEChar6DoWrite;

#if 1
// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ �������? ������С  --amomcu.com
void simpleBLE_Delay_1ms(int times);

// �ַ����Ա�
uint8 str_cmp(uint8 *p1,uint8 *p2,uint8 len);

// �ַ���ת����
uint32 str2Num(uint8* numStr, uint8 iLength);

char *bdAddr2Str( uint8 *pAddr );

// �����������ݵ�nv flash
void simpleBLE_WriteAllDataToFlash();

// ��ȡ�Զ����? nv flash ����  -------δʹ�õ�
void simpleBLE_ReadAllDataToFlash();

//flag: PARA_ALL_FACTORY:  ȫ���ָ���������
//flag: PARA_PARI_FACTORY: ��������Ϣ
void simpleBLE_SetAllParaDefault(PARA_SET_FACTORY flag); 

// ��ӡ���д洢��nv flash�����ݣ� ������Դ���?
void PrintAllPara(void);

// �����豸��ɫ
//����ģʽ  0: �ӻ�   1: ����
BLE_ROLE GetBleRole();

// �а������£�����Ϊ������ ����Ĭ����Ϊ�ӻ�
// 0 ��peripheral���豸�� 1: ��Ϊ central
bool Check_startup_peripheral_or_central(void);

// ���п� uart ��ʼ��
void simpleBLE_NPI_init(void);

// ���ý�������
void UpdateRxGain(void);

// ���÷��书��
void UpdateTxPower(void);

// ����led�Ƶ�״̬
void simpleBle_LedSetState(uint8 onoff);

// ��ȡ�豸����
uint8* simpleBle_GetAttDeviceName();

// ��ʱ������ʱִ�к����� ��������led��״̬----Ҳ��������һ����ʱ������
void simpleBLE_performPeriodicTask( void );

//uart �ص�����
static void simpleBLE_NpiSerialCallback( uint8 port, uint8 events );
// AT ����� ����
bool simpleBLE_AT_CMD_Handle(uint8 *pBuffer, uint16 length);
// MT ����� ����
bool simpleBLE_MT_CMD_Handle(uint8 *pBuffer, uint16 length);

#if defined(USE_DISPLAY_KEY_VALUE)  // ���԰���ר�ã���ʾ5�򰴼�ֵ
void SimpleBLE_DisplayTestKeyValue();
#endif

extern bool g_sleepFlag;    //˯�߱�־
extern uint8 uart_sleep_count; // ˯�߼�����
extern bool g_rssi_flag;       //�Ƿ�����
#endif

#ifdef __cplusplus
}
#endif

#endif /* SIMPLEBLE_H */