/*********************************************************************
 * INCLUDES
 */

#include "bcomdef.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"

#include "OnBoard.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_lcd.h"
#include "hal_mcu.h"

#include "gatt.h"

#include "hci.h"

#include "gapgattserver.h"
#include "gattservapp.h"
#include "devinfoservice.h"
#include "simpleGATTprofile.h"
#include "simpleBLECentralPeripheralCommon.h"

#if defined(CC2540_MINIDK)
#include "simplekeys.h"
#endif

#if defined(PLUS_BROADCASTER)
#include "peripheralBroadcaster.h"
#else
#include "peripheral.h"
#endif

#include "gapbondmgr.h"

#include "simpleBLEPeripheral.h"

#if defined FEATURE_OAD
#include "oad.h"
#include "oad_target.h"
#endif

#include "simpleble.h"
#include "npi.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "amomcu_buffer.h"

#include "simpleBLELED.h"
#include "simpleBLEKey.h"
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// General discoverable mode advertises indefinitely
#define DEFAULT_DISCOVERABLE_MODE GAP_ADTYPE_FLAGS_GENERAL

// Minimum connection interval (units of 1.25ms, 80=100ms) if automatic parameter update request is enabled
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL 6 //80   ���Ӽ�������ݷ������йأ�????? ���Ӽ��Խ�̣�????? ��λʱ���ھ��ܷ���Խ�������?????

// Maximum connection interval (units of 1.25ms, 800=1000ms) if automatic parameter update request is enabled
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL 6 //800   ���Ӽ�������ݷ������йأ�????? ���Ӽ��Խ�̣�????? ��λʱ���ھ��ܷ���Խ�������?????

// Slave latency to use if automatic parameter update request is enabled
#define DEFAULT_DESIRED_SLAVE_LATENCY 0

// Supervision timeout value (units of 10ms, 1000=10s) if automatic parameter update request is enabled
#define DEFAULT_DESIRED_CONN_TIMEOUT 100 //1000  -����ԭ��Ͽ����Ӻ�?????��ʱ�����¹㲥��ʱ��:  100 = 1s

// Whether to enable automatic parameter update request when a connection is formed
#define DEFAULT_ENABLE_UPDATE_REQUEST TRUE

// Connection Pause Peripheral time value (in seconds)
#define DEFAULT_CONN_PAUSE_PERIPHERAL 3

// Company Identifier: Texas Instruments Inc. (13)
#define TI_COMPANY_ID 0x000D

#define INVALID_CONNHANDLE 0xFFFF

#if defined(PLUS_BROADCASTER)
#define ADV_IN_CONN_WAIT 500 // delay 500 ms
#endif

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
//uint8 simpleBLEPeripheral_TaskID;   // Task ID for internal task/event processing

gaprole_States_t gapProfileState = GAPROLE_INIT;

bool simpleBLEChar6DoWrite2 = TRUE;
bool timerIsOn = FALSE; //

// Connection handle
uint16 gapConnHandle = NULL;

// GAP - SCAN RSP data (max size = 31 bytes)
static uint8 scanRspData[] =
    {
        // complete name
        0x0A, // length of this data
        GAP_ADTYPE_LOCAL_NAME_COMPLETE,
        0x44,
        0x61,
        0x72,
        0x72,
        0x65,
        0x6E,
        0x42,
        0x4C,
        0x45,
        // connection interval range
        0x05, // length of this data
        GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE,
        LO_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL), // 100ms
        HI_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL),
        LO_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL), // 1s
        HI_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL),
        // Tx power level
        0x02, // length of this data
        GAP_ADTYPE_POWER_LEVEL,
        0 // 0dBm
};

extern uint8 advertData_iBeacon[30];

static uint8 key_led_count = BUTTON_LED_TOGGLE_COUNT; //Blink for 3 times.

// Default WAKEUP period
//static uint8 wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
//static uint8 battery_voltage = 0;

//first boot up
static bool first_boot = FALSE;

//static uint8 key_long_press_cnt = 0;
//static uint8 sleep_toggle_cnt = 0;
static bool rapid_processing = FALSE;

#if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
static uint8 minsRunning = 0;
#endif

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void simpleBLEPeripheral_ProcessOSALMsg(osal_event_hdr_t *pMsg);
static void simpleBLEPeripheral_ProcessGATTMsg(gattMsgEvent_t *pMsg);

static void init_ibeacon_advertise(bool reset_index);

//#if defined( BLE_BOND_PAIR )
typedef enum {
  BOND_PAIR_STATUS_PAIRING, //δ���?????
  BOND_PAIR_STATUS_PAIRED,  //�����?????
} BOND_PAIR_STATUS;

void ProcessPasscodeCB(uint8 *deviceAddr, uint16 connectionHandle, uint8 uiInputs, uint8 uiOutputs);

static void simpleBLEPeripheral_HandleKeys(uint8 shift, uint8 keys);

static uint16 advInt;

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      SimpleBLEPeripheral_Init
 *
 * @brief   Initialization function for the Simple BLE Peripheral App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notificaiton ... ).
 *
 * @param   task_id - the ID assigned by OSAL.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void SimpleBLEPeripheral_Init(uint8 task_id)
{
  simpleBLETaskId = task_id;

  // Setup the GAP
  VOID GAP_SetParamValue(TGAP_CONN_PAUSE_PERIPHERAL, DEFAULT_CONN_PAUSE_PERIPHERAL);

  // Setup the GAP Peripheral Role Profile
  {
    // Change the ibeacon adverdata of wake up hours remain.
    // advertData_iBeacon[ADV_MIN_LEFT_BYTE] = sys_config.minLeft;

    // By setting this to zero, the device will go into the waiting state after
    // being discoverable for 30.72 second, and will not being advertising again
    // until the enabler is set back to TRUE
    // uint16 gapRole_AdvertOffTime = 0;

    // Cannot be connected.
    uint8 advType = GAP_ADTYPE_ADV_NONCONN_IND; // use non-connectable advertisements
    GAPRole_SetParameter(GAPROLE_ADV_EVENT_TYPE, sizeof(uint8), &advType);

    uint8 enable_update_request = DEFAULT_ENABLE_UPDATE_REQUEST;
    uint16 desired_min_interval = DEFAULT_DESIRED_MIN_CONN_INTERVAL;
    uint16 desired_max_interval = DEFAULT_DESIRED_MAX_CONN_INTERVAL;
    uint16 desired_slave_latency = DEFAULT_DESIRED_SLAVE_LATENCY;
    uint16 desired_conn_timeout = DEFAULT_DESIRED_CONN_TIMEOUT;

    // Set the GAP Role Parameters
    // GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &initial_advertising_enable);
    advertise_control(FALSE);
    // GAPRole_SetParameter(GAPROLE_ADVERT_OFF_TIME, sizeof(uint16), &gapRole_AdvertOffTime);

    GAPRole_SetParameter(GAPROLE_SCAN_RSP_DATA, sizeof(scanRspData), scanRspData);
    GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData_iBeacon), advertData_iBeacon);
    GAPRole_SetParameter(GAPROLE_PARAM_UPDATE_ENABLE, sizeof(uint8), &enable_update_request);
    GAPRole_SetParameter(GAPROLE_MIN_CONN_INTERVAL, sizeof(uint16), &desired_min_interval);
    GAPRole_SetParameter(GAPROLE_MAX_CONN_INTERVAL, sizeof(uint16), &desired_max_interval);
    GAPRole_SetParameter(GAPROLE_SLAVE_LATENCY, sizeof(uint16), &desired_slave_latency);
    GAPRole_SetParameter(GAPROLE_TIMEOUT_MULTIPLIER, sizeof(uint16), &desired_conn_timeout);
  }

  // Set the GAP Characteristics
  //GGS_SetParameter( GGS_DEVICE_NAME_ATT, GAP_DEVICE_NAME_LEN, attDeviceName );
  GGS_SetParameter(GGS_DEVICE_NAME_ATT, GAP_DEVICE_NAME_LEN, simpleBle_GetAttDeviceName());

  {
    // ����rssi ������������
    uint16 rssi_read_rate_1ms = 500; //һ�����?????2��
    GAPRole_SetParameter(GAPROLE_RSSI_READ_RATE, sizeof(uint16), &rssi_read_rate_1ms);
  }

  // Set advertising interval
  {
    #if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
    advInt = ADV_INTERVAL_x00MS_TO_TICK(sys_config.stationAdvInterval);
    #else
    advInt = SLOW_ADVERTISING_INTERVAL;
    #endif
    GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MIN, advInt);
    GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MAX, advInt);
    GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MIN, advInt);
    GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MAX, advInt);
  }

  //�������������ص�����
  // Setup the GAP Bond Manager
  {
    uint32 passkey = 0; // passkey "000000"
    uint8 pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
    uint8 mitm = TRUE;
    uint8 ioCap = GAPBOND_IO_CAP_DISPLAY_ONLY; //��ʾ���룬 �Ա�����������Ե�����?????

    /*
    bonding���ǰ�������?��¼����, �´ξͲ��������?????. ��bonding�´ξͻ������?????.    
    �������Ǵӻ������????? bonding = FALSE �ĺ�����ǣ�????? ���豸ÿ�����Ӷ�������������
    ����  bonding = TRUE �� ���豸ֻ���һ������ʱ��������????? ����Ͽ��󶼲����?�ٴ��������뼴������
    ---------------amomcu.com-------------------------    
    */
    uint8 bonding = FALSE;
    pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
    GAPBondMgr_SetParameter(GAPBOND_DEFAULT_PASSCODE, sizeof(uint32), &passkey);
    GAPBondMgr_SetParameter(GAPBOND_PAIRING_MODE, sizeof(uint8), &pairMode);
    GAPBondMgr_SetParameter(GAPBOND_MITM_PROTECTION, sizeof(uint8), &mitm);
    GAPBondMgr_SetParameter(GAPBOND_IO_CAPABILITIES, sizeof(uint8), &ioCap);
    GAPBondMgr_SetParameter(GAPBOND_BONDING_ENABLED, sizeof(uint8), &bonding);
  }
  
  // Initialize GATT attributes
  GGS_AddService(GATT_ALL_SERVICES);           // GAP
  GATTServApp_AddService(GATT_ALL_SERVICES);   // GATT attributes
  DevInfo_AddService();                        // Device Information Service
  SimpleProfile_AddService(GATT_ALL_SERVICES); // Simple GATT Profile
#if defined FEATURE_OAD
  VOID OADTarget_AddService(); // OAD Profile
#endif
  // Register for all key events - This app will handle all key events
  RegisterForKeys(simpleBLETaskId);

#if (defined HAL_LCD) && (HAL_LCD == TRUE)

#if defined FEATURE_OAD
#if defined(HAL_IMAGE_A)
  HalLcdWriteStringValue("BLE Peri-A", OAD_VER_NUM(_imgHdr.ver), 16, HAL_LCD_LINE_1);
#else
  HalLcdWriteStringValue("BLE Peri-B", OAD_VER_NUM(_imgHdr.ver), 16, HAL_LCD_LINE_1);
#endif // HAL_IMAGE_A
#else
  HalLcdWriteString("BLE Peripheral", HAL_LCD_LINE_1);
#endif // FEATURE_OAD

#endif // (defined HAL_LCD) && (HAL_LCD == TRUE)

  // Register callback with SimpleGATTprofile
  // VOID SimpleProfile_RegisterAppCBs(&simpleBLEPeripheral_SimpleProfileCBs);

  // ��Ҫ�رյ�CLK�Զ���Ƶ���ڳ�ʼ���м���HCI_EXT_ClkDivOnHaltCmd( HCI_EXT_DISABLE_CLK_DIVIDE_ON_HALT )?  // �������ᵼ��Ƶ���Զ��л���DMA�����ܵ�Ӱ�죬С��Χ������
  // ��������رգ�????? ����뽵�͹��ģ�????? ���Ӧ���?����ģ�????? ����ì����
  HCI_EXT_ClkDivOnHaltCmd(HCI_EXT_ENABLE_CLK_DIVIDE_ON_HALT);
  //HCI_EXT_ClkDivOnHaltCmd( HCI_EXT_ENABLE_CLK_DIVIDE_ON_HALT );

  // �źŷ���ǿ��
  HCI_EXT_SetTxPowerCmd(3 - sys_config.txPower);

  // Init Peripheral Function.
  set_key_press_process_callback(peripheral_key_press_process_callback);
  
  // Setup a delayed profile startup
  osal_set_event(simpleBLETaskId, START_DEVICE_EVT);
}

/*********************************************************************
 * @fn      SimpleBLEPeripheral_ProcessEvent
 *
 * @brief   Simple BLE Peripheral Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The OSAL assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16 SimpleBLEPeripheral_ProcessEvent(uint8 task_id, uint16 events)
{

  VOID task_id; // OSAL required parameter that isn't used in this function

  if (events & SYS_EVENT_MSG)
  {
    uint8 *pMsg;
    if ((pMsg = osal_msg_receive(simpleBLETaskId)) != NULL)
    {
      simpleBLEPeripheral_ProcessOSALMsg((osal_event_hdr_t *)pMsg);
      // Release the OSAL message
      VOID osal_msg_deallocate(pMsg);
    }
    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }

  if (events & START_DEVICE_EVT)
  {
    updateSysConfigMac();

    first_boot = sys_config.bootup_blink;
    // Only BEACON needs the set the target to off.
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    reset_to_no_battery_status();
    #endif
    // Start the Device
    VOID GAPRole_StartDevice(NULL);
    // Start Bond Manager
    osal_start_timerEx(simpleBLETaskId, SBP_WAKE_EVT, 500);
    return (events ^ START_DEVICE_EVT);
  }

  if (events & SBP_WAKE_EVT)
  {
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    osal_pwrmgr_device(PWRMGR_BATTERY);
    #elif (PRESET_ROLE == BLE_PRE_ROLE_STATION)
    osal_pwrmgr_device(PWRMGR_ALWAYS_ON);
    #endif
    
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    if ((check_low_battery(NULL) == TRUE) && (first_boot == TRUE))
    {
      enter_low_battery_mode();
      return (events ^ SBP_WAKE_EVT);
    }
    #endif
    
    g_sleepFlag = FALSE;
    // Update the advertise data.
    init_ibeacon_advertise(TRUE);

    #if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
    if (sys_config.stationAdvInterval == 0xFF)
      advertise_control(FALSE);
    else
      advertise_control(TRUE);
    #elif (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    // Start advertising
    advertise_control(TRUE);
    #endif


    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    // Index event
    osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_INDEX_EVT, SBP_PERIODIC_INDEX_EVT_PERIOD);
    // Per Min Event
    osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_MIN_EVT, SBP_PERIODIC_PER_MIN_PERIOD);
    if (sys_config.key_pressed_in_scan == TRUE)
    {
      sys_config.key_pressed_in_scan = FALSE;
      simpleBLE_WriteAllDataToFlash();
      change_advertise_data(TRUE);
    }
    if (first_boot == TRUE)
    {
      // Blink twice after 650ms
      led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LEY_DELAY_IN_SLEEP);
    }
    #endif

    return (events ^ SBP_WAKE_EVT);
  }

  if (events & SBP_PERIODIC_INDEX_EVT)
  {
    // Restart timer
    if (SBP_PERIODIC_INDEX_EVT_PERIOD)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_INDEX_EVT, SBP_PERIODIC_INDEX_EVT_PERIOD);
    }
    // Perform periodic application task
    PeripherialPerformPeriodicTask(SBP_PERIODIC_INDEX_EVT);
    return (events ^ SBP_PERIODIC_INDEX_EVT);
  }

  if (events & SBP_PERIODIC_PER_MIN_EVT)
  {
    DEBUG_PRINT("SBP_PERIODIC_PER_MIN_EVT\r\n");
    // Restart timer
    if (SBP_PERIODIC_PER_MIN_PERIOD)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_MIN_EVT, SBP_PERIODIC_PER_MIN_PERIOD);
    }
    // Perform periodic application task
    PeripherialPerformPeriodicTask(SBP_PERIODIC_PER_MIN_EVT);
    return (events ^ SBP_PERIODIC_PER_MIN_EVT);
  }

  if (events & SBP_PERIODIC_BUTTON_LED_EVT)
  {
    // Restart timer
    if (key_led_count > 0)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_BUTTON_LED_EVT, SBP_PERIODIC_BUTTON_LED_PERIOD);
      // Perform periodic application task
      PeripherialPerformPeriodicTask(SBP_PERIODIC_BUTTON_LED_EVT);
    }
    else if (key_led_count == 0)
    {
      key_led_count = BUTTON_LED_TOGGLE_COUNT;
    }
    return (events ^ SBP_PERIODIC_BUTTON_LED_EVT);
  }

  if (events & SBP_PERIODIC_CHN_ADVERT_EVT_PRESS)
  {
    change_advertise_data(TRUE);
    return (events ^ SBP_PERIODIC_CHN_ADVERT_EVT_PRESS);
  }

  if (events & SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE)
  {
    change_advertise_data(FALSE);
    return (events ^ SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE);
  }

  if (events & SBP_DATA_EVT)
  {
    return (events ^ SBP_DATA_EVT);
  }

  if (events & SBP_UART_EVT)
  {
    if (FALSE == timerIsOn)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_DATA_EVT, 6);
    }
    return (events ^ SBP_UART_EVT);
  }
  
  if (events & SBP_SLEEP_EVT)
  {
    /*
    DEBUG_PRINT("SBP_SLEEP_EVT\r\n");
    low_power_state = FALSE; // set false to enable key event.
    g_sleepFlag = TRUE;
    osal_pwrmgr_device(PWRMGR_BATTERY);
    osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_EVT_ALL);
    advertise_control(FALSE);
    DEBUG_PRINT("Enter Sleep Mode\r\n");
    simpleBLE_Delay_1ms(1);
    */
    DEBUG_PRINT("SLEEP EVT, should not be here\r\n");
    return (events ^ SBP_SLEEP_EVT);
  }

  if (events & SBP_PERIODIC_EVT)
  {
    // Restart timer
    if (SBP_PERIODIC_EVT_PERIOD)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_EVT, SBP_PERIODIC_EVT_PERIOD);
    }
    return (events ^ SBP_PERIODIC_EVT);
  }

  if (events & SBP_PERIODIC_LED_EVT)
  {
    led_event_callback();
    return (events ^ SBP_PERIODIC_LED_EVT);
  }

  if (events & SBP_KEY_CNT_EVT)
  {
    key_cnt_evt_callback();
    return (events ^ SBP_KEY_CNT_EVT);
  }

  if (events & SBP_SCAN_ADV_TRANS_EVT)
  {
    scan_adv_event_callback(sys_config.role);
    return (events ^ SBP_SCAN_ADV_TRANS_EVT);
  }
  // Discard unknown events
  return 0;
}

/*********************************************************************
 * @fn      simpleBLEPeripheral_ProcessOSALMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void simpleBLEPeripheral_ProcessOSALMsg(osal_event_hdr_t *pMsg)
{
  switch (pMsg->event)
  {
  case KEY_CHANGE:
    simpleBLEPeripheral_HandleKeys(((keyChange_t *)pMsg)->state, ((keyChange_t *)pMsg)->keys);
    break;

  case GATT_MSG_EVENT:
    // Process GATT message
    simpleBLEPeripheral_ProcessGATTMsg((gattMsgEvent_t *)pMsg);
    break;

  default:
    // do nothing
    break;
  }
}

//#if defined( CC2540_MINIDK )
/*********************************************************************
 * @fn      simpleBLEPeripheral_HandleKeys
 *
 * @brief   Handles all key events for this device.
 *
 * @param   shift - true if in shift/alt.
 * @param   keys - bit field for key events. Valid entries:
 *                 HAL_KEY_SW_2
 *                 HAL_KEY_SW_1
 *
 * @return  none
 */
static void simpleBLEPeripheral_HandleKeys(uint8 shift, uint8 keys)
{
  key_press_handler(keys);
}

//#endif // #if defined( CC2540_MINIDK )

/*********************************************************************
 * @fn      simpleBLEPeripheral_ProcessGATTMsg
 *
 * @brief   Process GATT messages
 *
 * @return  none
 */
static void simpleBLEPeripheral_ProcessGATTMsg(gattMsgEvent_t *pMsg)
{
  GATT_bm_free(&pMsg->msg, pMsg->method);
}

static void PeripherialPerformPeriodicTask(uint16 event_id)
{
  switch (event_id)
  {
  case SBP_PERIODIC_INDEX_EVT:
    {
      #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
      if (rapid_processing == FALSE)
      {
        advertData_iBeacon[ADV_INDEX_BYTE] += 1;
      }
      GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData_iBeacon), advertData_iBeacon);
      #endif
    }
    break;
  case SBP_PERIODIC_PER_MIN_EVT:
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    if (g_sleepFlag == TRUE)
    {
      DEBUG_PRINT("sleep already, stop the per hour timer\r\n");
      osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_MIN_EVT);
    }
    else
    {
      DEBUG_PRINT("This is a per min event\r\n");
      sys_config.minLeft--;
      DEBUG_VALUE("min1Left:", sys_config.minLeft, 10);
      advertData_iBeacon[ADV_MIN_LEFT_BYTE] = sys_config.minLeft;
      if (sys_config.minLeft == 0)
      {
        DEBUG_PRINT("Enter OFF_SCAN Status\r\n");
        set_beacon_status(BLE_STATUS_ON_ADV, BLE_STATUS_OFF, TRUE);
        return;
      }
      minsRunning++;
      DEBUG_VALUE("minsRunning:", minsRunning, 10);
      if (minsRunning == sys_config.powerOnScanInterval)
      {
        if (rapid_processing == TRUE)
        {
          DEBUG_PRINT("minsRunning Event: In rapid processing, change to Central later\r\n");
          osal_start_timerEx(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT, SBP_PERIODIC_ADVERT_CHG_PERIOD);
        }
        else
        {
          DEBUG_PRINT("minsRunning Event: change to Central\r\n");
          osal_set_event(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT);
        }
      }
    }
    #endif
    break;
  case SBP_PERIODIC_BUTTON_LED_EVT:
    HalLedSet(HAL_LED_1, HAL_LED_MODE_TOGGLE);
    key_led_count--;
    break;
  default:
    break;
  }
}

static void change_advertise_data(uint8 key_pressed)
{
  uint8 initial_advertising_enable;
  GAPRole_GetParameter(GAPROLE_ADVERT_ENABLED, &initial_advertising_enable);
  if (key_pressed == TRUE)
  {
    if (initial_advertising_enable == TRUE && rapid_processing == FALSE)
    {
      DEBUG_PRINT("Enter Rapid Mode\r\n");
      rapid_processing = TRUE;
      advertise_control(FALSE);
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_CHN_ADVERT_EVT_PRESS, ENABLE_DISABLE_PERIOD);
    }
    else if (initial_advertising_enable == FALSE && rapid_processing == TRUE)
    {
      advertData_iBeacon[ADV_INDEX_BYTE] += 1;
      advertData_iBeacon[ADV_FLAG_BYTE] |= 0x80;
      // Set advertising interval
      {
        advInt = RAPID_ADVERTISING_INTERVAL;
        GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MIN, advInt);
        GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MAX, advInt);
        GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MIN, advInt);
        GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MAX, advInt);
        advertise_control(TRUE);
      }
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE, SBP_PERIODIC_ADVERT_CHG_PERIOD);
    }
  }
  else
  {
    if (initial_advertising_enable == TRUE && rapid_processing == TRUE)
    {
      advertise_control(FALSE);
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_CHN_ADVERT_EVT_RELEASE, ENABLE_DISABLE_PERIOD);
    }
    else if (initial_advertising_enable == FALSE && rapid_processing == TRUE)
    {
      DEBUG_PRINT("Exit Rapid Mode\r\n");
      advertData_iBeacon[ADV_FLAG_BYTE] &= 0x7F;
      advertData_iBeacon[ADV_INDEX_BYTE] += 1;
      // Set advertising interval
      {
        advInt = SLOW_ADVERTISING_INTERVAL;
        GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MIN, advInt);
        GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MAX, advInt);
        GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MIN, advInt);
        GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MAX, advInt);
        advertise_control(TRUE);
      }
      rapid_processing = FALSE;
    }
  }
}

static void init_ibeacon_advertise(bool reset_index)
{
  #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
  // Update the simpleBLE status. Common Config
  advertData_iBeacon[ADV_STATION_INDEX_1] = (sys_config.stationIndex >> 8) & 0xFF;
  advertData_iBeacon[ADV_STATION_INDEX_2] = (sys_config.stationIndex & 0xFF);
  // Beacon config.
  advertData_iBeacon[ADV_MIN_LEFT_BYTE] = sys_config.minLeft;
  advertData_iBeacon[ADV_BAT_BYTE] = read_battery_value() & 0xFF;
  advertData_iBeacon[ADV_FLAG_BYTE] = 0x00;
  if (reset_index == TRUE)
  {
    advertData_iBeacon[ADV_INDEX_BYTE] = 0x00;
  }
  #endif
  GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData_iBeacon), advertData_iBeacon);
}

void advertise_control(bool enable)
{
  // status check.
  if (enable == TRUE && g_sleepFlag == TRUE)
  {
    DEBUG_PRINT("enable TRUE, g_sleepFlag TRUE");
    return;
  }
  uint8 initial_advertising_enable = enable;
  if (enable == TRUE)
  {
    GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData_iBeacon), advertData_iBeacon);
  }
  GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &initial_advertising_enable);
  return;
}
//#endif

/*********************************************************************
*********************************************************************/


void peripheral_key_press_process_callback(uint8 key_cnt_number)
{
  #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
  if (key_cnt_number == 0)
  {
    return;
  }
  if (g_sleepFlag == TRUE)
  {
    if (key_cnt_number == 1)
    {
      first_boot = TRUE;
    }
    osal_set_event(simpleBLETaskId, SBP_WAKE_EVT);
  }
  else if (g_sleepFlag == FALSE)
  {
    if (key_cnt_number >= 2)
    {
      // LED blink twice
      led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LED_DELAY);
    }
    else if (key_cnt_number == 1)
    {
      // Blink once
      led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, BUTTON_LED_TOGGLE_COUNT, BUTTON_LED_DELAY);
    }
    // Change the advertise date anyway.
    change_advertise_data(TRUE);
  }
  #endif
  return;
}