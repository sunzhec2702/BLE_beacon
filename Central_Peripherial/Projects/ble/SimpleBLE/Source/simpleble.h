#ifndef SIMPLEBLE_H
#define SIMPLEBLE_H

#ifdef __cplusplus
#include "npi.h"
#include "comdef.h"
#include "simpleBLECentralPeripheralCommon.h"

extern "C"
{
#endif
#include "hal_types.h"

#define DEVELOP_BOARD 0
#define PRODUCT_BOARD 1

//#define NFC_DEBUG_MODE 1 // UART: CC2541 -> NP532 -> PC

//#define NFC_BOARD_VERSION 0x1 //BLE+NFC


//DEBUG RELATED MACRO.
#define DEBUG_NFC_UART_MAX_TIMEOUT_ENABLE 1
#define DEBUG_NFC_UART_MAX_TIMEOUT        5000     
#define DEBUG_NFC_UART_FAKE_RESPOND    0
#define DEBUG_WAIT_FOR_RX_NUM          0


//DEBUG RELATED MACRO DONE.

#define TARGET_BOARD PRODUCT_BOARD

#define POWER_OFF_SUPPORT FALSE
#define DEBUG_BOARD 1

#define PRESET_ROLE BLE_PRE_ROLE_STATION

#define BLE_PRE_ROLE_STATION 0
#define BLE_PRE_ROLE_BEACON 1

#if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
#include "simpleBLEStation.h"
#elif (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
#include "simpleBLEBeacon.h"
#endif

typedef enum
{
  BLE_ROLE_PERIPHERAL = 0,
  BLE_ROLE_CENTRAL,
  BLE_ROLE_NUMBER,
} BLE_ROLE;

typedef enum
{
  BLE_BEACON = 1,
  BLE_STATION_ADV,
} BLE_DEVICE_TYPE;

#ifdef DEBUG_BOARD
#define HAL_LCD TRUE
#define HAL_UART TRUE
#define LCD_TO_UART TRUE
#define DEBUG_BYTES(x, y) NPI_WriteTransport(x, y)
#define DEBUG_PRINT(x) NPI_PrintString(x)
#define DEBUG_VALUE(x,y,z) {NPI_PrintValue(x, y, z);NPI_PrintString("\r\n");}
#else // PRODUCT_BOARD
  #if (PRESET_ROLE == BLE_PRE_ROLE_CENTRAL)
    #define HAL_LCD FALSE
    #define HAL_UART TRUE
    #define LCD_TO_UART TRUE
  #else // PERIPHERIAL
    #define HAL_LCD FALSE
    #define HAL_UART TRUE
    #define LCD_TO_UART FALSE
  #endif // CENTRAL
#define DEBUG_BYTES(x, y) {}
#define DEBUG_PRINT(x) {}
#define DEBUG_VALUE(x,y,z) {}
#endif

#define ADV_INTERVAL_x00MS_TO_TICK(x) (x * 160)


#define NFC_UART_DEBUG NPI_WriteTransport
#define NFC_UART_DEBUG_STRING NPI_PrintString
#define NFC_UART_DEBUG_VALUE NPI_PrintValue

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
//#define SBP_PERIODIC_PER_HOUR_EVT                      0x0800
#define SBP_PERIODIC_PER_MIN_EVT                       0x0800
#define SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE            0x1000
#define SBP_PERIODIC_CHN_ADVERT_EVT_PRESS              0x2000
#define SBP_PERIODIC_INDEX_EVT                         0x4000//ϵͳ��ѯ��ʱ��

//#define SBP_KEY_LONG_PRESSED_EVT                       0x0004
#define SBP_SCAN_ADV_TRANS_EVT                         0x0004

#define SBP_PERIODIC_EVT_ALL (SBP_PERIODIC_EVT|SBP_PERIODIC_LED_EVT|SBP_PERIODIC_BUTTON_LED_EVT|SBP_PERIODIC_PER_HOUR_EVT|SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE|SBP_PERIODIC_CHN_ADVERT_EVT_PRESS|SBP_PERIODIC_INDEX_EVT)

// What is the advertising interval when device is discoverable (units of 625us, 160=100ms)
#define SBP_STATION_ADV_INTERVAL   (20) // 2s
#define RAPID_ADVERTISING_INTERVAL (160*2) // 200ms
#define SLOW_ADVERTISING_INTERVAL (160*20) // 2s
#define SBP_PERIODIC_ADVERT_CHG_PERIOD                  2000 // 2s

// How often to perform periodic event
#define SBP_PERIODIC_INDEX_EVT_PERIOD                   1000 // 1s

#ifdef DEBUG_BOARD

/*
#define SBP_PERIODIC_PER_MIN_PERIOD                     5000    // 5s
#define DEFAULT_WAKE_TIME_MINS                          10      //
#define SCAN_ADV_TRANS_MIN_PERIOD                       5 // 10mins
#define SBP_PERIODIC_OFF_SCAN_PERIOD_MIN                1
#define SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_1              0  //  
#define SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_2              1E // 30*100 ms = 3s
#define SBP_PERIODIC_OFF_SCAN_PERIOD_x00MS              (SBP_PERIODIC_OFF_SCAN_PERIOD_MIN * 60 * 10) // one hour
#define SBP_PERIODIC_FAST_OFF_SCAN_PERIOD_MS            (5000) // 5s
#define DEFAULT_WAKE_TIME_HOURS                         (5) // 5 mins
#define BUTTON_WAKE_TIME_HOURS                          (2) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1) // 1 days
*/

/*********************** DEBUG_BOARD but normal period ********************************/

#define SBP_PERIODIC_PER_MIN_PERIOD                     5000    // 1 min
#define DEFAULT_WAKE_TIME_MINS                          30        // 30mins
#define SCAN_ADV_TRANS_MIN_PERIOD                       10 // 10mins
#define SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_1              0x0E //
#define SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_2              0x10 // total 3600s, 1 hour
#define SBP_PERIODIC_OFF_SCAN_PERIOD_MIN                60
#define SBP_PERIODIC_OFF_SCAN_PERIOD_x00MS              (SBP_PERIODIC_OFF_SCAN_PERIOD_MIN * 60 * 10) // one hour
#define SBP_PERIODIC_FAST_OFF_SCAN_PERIOD_x00MS         (50) // 5s
#define DEFAULT_WAKE_TIME_HOURS                         (5 * 24) // 5 days
#define BUTTON_WAKE_TIME_HOURS                          (2 * 24) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1 * 24) // 1 days

/*********************** DEBUG_BOARD but normal period ********************************/
#else
#define SBP_PERIODIC_PER_MIN_PERIOD                     60000    // 1 min
#define DEFAULT_WAKE_TIME_MINS                          30        // 30mins

#define SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_1              0x0E //
#define SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_2              0x10 // total 3600s, 1 hour

#define SCAN_ADV_TRANS_MIN_PERIOD                       10 // 10mins
#define SBP_PERIODIC_OFF_SCAN_PERIOD_MIN                60
#define SBP_PERIODIC_OFF_SCAN_PERIOD_MS                 (SBP_PERIODIC_OFF_SCAN_PERIOD_MIN * 60 * 1000) // one hour
#define SBP_PERIODIC_FAST_OFF_SCAN_PERIOD_x00MS         (50) // 5s

#define DEFAULT_WAKE_TIME_HOURS                         (5 * 24) // 5 days
#define BUTTON_WAKE_TIME_HOURS                          (2 * 24) // 2 days
#define RESET_WAKE_TIME_HOURS_THRES                     (1 * 24) // 1 days
#endif

#define SBP_PERIODIC_BUTTON_LED_PERIOD                  100
#define BUTTON_LED_TOGGLE_COUNT                         2

#define SLEEP_MS                                        300  //˯��ʱ�䣬 ���ڼ����¼�

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




// Adv index
#define BEACON_START_INDEX 5
#define BEACON_ISSMART_INDEX 9

#define ADV_STATION_MAC_CRC_BYTE 12

#define BEACON_DEVICE_TYPE_INDEX 17
#define ADV_STATION_CMD_INDEX 18
#define ADV_STATION_BATTERY_THRESHOLD 19
#define ADV_STATION_ON_SCAN_INTERVAL_INDEX 19
#define ADV_STATION_POWER_ON_PERIOD_INDEX 20
#define ADV_STATION_OFF_SCAN_INTERVAL_INDEX_1 21
#define ADV_STATION_OFF_SCAN_INTERVAL_INDEX_2 22

#define ADV_STATION_INDEX_1 23
#define ADV_STATION_INDEX_2 24

#define ADV_MIN_LEFT_BYTE 25
#define ADV_INDEX_BYTE 26
#define ADV_FLAG_BYTE 27
#define ADV_BAT_BYTE 28

#define ADV_SPECIFIC_MAC_LAST_4 25
#define ADV_SPECIFIC_MAC_LAST_3 26
#define ADV_SPECIFIC_MAC_LAST_2 27
#define ADV_SPECIFIC_MAC_LAST_1 28


//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

//#define RELEASE_VER                      //����汾������????
#define     VERSION     "v0.1"  //
#define MAJOR_HW_VERSION   0x00
#define MINOR_HW_VERSION   0x03
#define MAJOR_SW_VERSION   0x02
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

// ϵͳ��ʱ�����ʱ��????
#define SBP_PERIODIC_EVT_PERIOD                   100//������100ms

//����¼�Ĵӻ���ַ
#define MAX_PERIPHERAL_MAC_ADDR                   10//����¼�Ĵӻ���ַ

//mac��ַ���ַ����� (һ���ֽڵ��������ַ�)
#define MAC_ADDR_CHAR_LEN                          12//mac��ַ���ַ����� (һ���ֽڵ��������ַ�)
#define ADVERTISE_SIZE                             30
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
  BLE_CENTRAL_CONNECT_CMD_DISC,              //���� AT ɨ��ӻ�����????
  BLE_CENTRAL_CONNECT_CMD_CONN,              //���� AT ��������  ����ɨ�赽�ĵ�ַ���±�Ŷ�Ӧ�ĵ��?
}BLE_CENTRAL_CONNECT_CMD;
extern BLE_CENTRAL_CONNECT_CMD g_Central_connect_cmd ;

// ����ϵͳ�ṹ������ �ýṹ���ڿ���ʱ��nv flash �ж�ȡ�� �������޸�ʱ�� ��Ҫд��nv flash
// ������ ��ʵ����ϵͳ��������ݻ�����һ�����õ�????
typedef struct 
{
    BLE_STATUS status;
    BLE_ROLE role;                  //����ģʽ  0: �ӻ�   1: ����
    uint8 mac_addr[B_ADDR_LEN];            //����mac��ַ ���????12λ �ַ���ʾ
    int8 rssi;                              //  RSSI �ź�ֵ
    uint8 rxGain;                           //  ��������ǿ��
    uint8 txPower;                          //  �����ź�ǿ��
    uint16 stationIndex;
    uint8 beaconIndex;
    uint8 minLeft;
    
    uint8 key_pressed_in_scan;
    uint8 bootup_blink;

    uint8 stationAdvInterval;

    // Values got from station adv.
    uint8 stationAdvCmd;
    uint8 powerOnScanInterval; // ON_SCAN/ON_ADV trans interval. default 10 mins.
    uint8 powerOnPeriod; // Without new adv data, how long will it last in ON status. default 30 mins.
    uint16 powerOffScanInterval; // The scan interval in OFF mode, default 1 hour
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
// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ �������???? ������С  --amomcu.com
void simpleBLE_Delay_1ms(int times);

// �ַ����Ա�
uint8 str_cmp(uint8 *p1,uint8 *p2,uint8 len);

// �ַ���ת����
uint32 str2Num(uint8* numStr, uint8 iLength);

char *bdAddr2Str( uint8 *pAddr );

void simpleBLE_SaveAndReset(void);

// �����������ݵ�nv flash
void simpleBLE_WriteAllDataToFlash();

// ��ȡ�Զ����???? nv flash ����  -------δʹ�õ�
void simpleBLE_ReadAllDataToFlash();

//flag: PARA_ALL_FACTORY:  ȫ���ָ���������
//flag: PARA_PARI_FACTORY: ��������Ϣ
void simpleBLE_SetAllParaDefault(PARA_SET_FACTORY flag); 

// ��ӡ���д洢��nv flash�����ݣ� ������Դ���????
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
static void simpleBLE_NpiSerialCallback1(uint8 port, uint8 events);


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



/* NFC related macro define */




#ifdef __cplusplus
}
#endif

#endif /* SIMPLEBLE_H */