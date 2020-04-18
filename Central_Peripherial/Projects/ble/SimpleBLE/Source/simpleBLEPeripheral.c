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
#include "hal_vibra_sensor.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// General discoverable mode advertises indefinitely
#define DEFAULT_DISCOVERABLE_MODE GAP_ADTYPE_FLAGS_GENERAL

// Minimum connection interval (units of 1.25ms, 80=100ms) if automatic parameter update request is enabled
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL 6 //80   ���Ӽ�������ݷ������йأ�?? ���Ӽ��Խ�̣�?? ��λʱ���ھ��ܷ���Խ�������??

// Maximum connection interval (units of 1.25ms, 800=1000ms) if automatic parameter update request is enabled
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL 6 //800   ���Ӽ�������ݷ������йأ�?? ���Ӽ��Խ�̣�?? ��λʱ���ھ��ܷ���Խ�������??

// Slave latency to use if automatic parameter update request is enabled
#define DEFAULT_DESIRED_SLAVE_LATENCY 0

// Supervision timeout value (units of 10ms, 1000=10s) if automatic parameter update request is enabled
#define DEFAULT_DESIRED_CONN_TIMEOUT 100 //1000  -����ԭ��Ͽ����Ӻ�??��ʱ�����¹㲥��ʱ��:  100 = 1s

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

// GAP - Advertisement data (max size = 31 bytes, though this is
// best kept short to conserve power while advertisting)
static uint8 advertData_iBeacon[] =
{
  // Flags; this sets the device to use limited discoverable
  // mode (advertises for 30 seconds at a time) instead of general
  // discoverable mode (advertises indefinitely)
  0x02, // length of this data, 0
  GAP_ADTYPE_FLAGS, // 1
  DEFAULT_DISCOVERABLE_MODE | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED, // 2
  // in this peripheral
  0x1A, // length of this data 26byte, 3
  GAP_ADTYPE_MANUFACTURER_SPECIFIC, // 4
  /*Apple Pre-Amble*/
  0x4C, // 5
  0x00, // 6
  0x02, // 7
  0x15, // 8
  /*Device UUID (16 Bytes)*/
  0x49, 0x53, 0x53, 0x4D, 0x41, 0x52, 0x54, 0x00, // ISSMART    8 bytes.
  0x00, 0x00, 0x01, // Device Type     3 bytes.
  MAJOR_HW_VERSION, // 0x00
  MINOR_HW_VERSION, // 0x02
  MAJOR_SW_VERSION, // 0x01
  MIDDLE_SW_VERSION, // 0x00
  MINOR_SW_VERSION, // 0x01
  /*Major Value (2 Bytes)*/
  0x00, 0x00, // 25-26 // 25 for hour index, 26 for index 
  /*Minor Value (2 Bytes)*/
  0x00, 0x00, // 27-28
  /*Measured Power*/
  0xCD //29
};

// LED related.
//static uint8 key_led_count = BUTTON_LED_TOGGLE_COUNT; //Blink for 3 times.

static uint8 led_toggle_count = 0;
static uint8 led_toggle_cnt_target = PERIPHERAL_START_LED_TOGGLE_CNT;
static uint8 led_toggling = FALSE;
//static uint16 led_toggle_period_on = PERIPHERAL_START_LED_TOGGLE_PERIOD_ON;
//static uint16 led_toggle_period_off = PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF;
// Default WAKEUP period
static uint16 wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
static uint8 battery_voltage = 0;
// Key related
static uint8 key_pressed_count = 0;
static uint8 key_processing = FALSE;
//first boot up
static bool first_boot = FALSE; // Set FALSE, the device will boot up. If True, the device will boot up and enter sleep directly.

#if (USE_VIBRA_SENSOR == TRUE)
static bool vibra_sensor_wake_flag = FALSE;
#endif

// Low power status
static bool low_power_state = FALSE;
static bool key_pressed = FALSE;

#if (POWER_OFF_SUPPORT == TRUE)
static bool g_long_press_flag = FALSE;
static uint8 key_long_press_cnt = 0;
static uint8 sleep_toggle_cnt = 0;
#endif
static bool rapid_processing = FALSE;

#ifdef DEBUG_BOARD
static bool debug_low_power = FALSE;
#endif

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void simpleBLEPeripheral_ProcessOSALMsg(osal_event_hdr_t *pMsg);
static void simpleBLEPeripheral_ProcessGATTMsg(gattMsgEvent_t *pMsg);
static uint8 led_toggle_set_param(uint16 toggle_period_on, uint16 toggle_period_off, uint32 toggle_target_cnt, uint16 delay);
static uint8 led_toggle_clean_param(void);
static bool check_low_battery(void);
static void enter_low_battery_mode(void);
#if (POWER_OFF_SUPPORT == TRUE)
static bool check_keys_pressed(uint8 keys);
#endif

static void update_wake_up_hour_2_adv(void);
static void init_ibeacon_advertise(bool reset_index);
static void advertise_control(bool enable);

//#if defined( BLE_BOND_PAIR )
typedef enum {
  BOND_PAIR_STATUS_PAIRING, //δ���??
  BOND_PAIR_STATUS_PAIRED,  //�����??
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
    // Change the ibeacon adverdata of wake up hours remain. //If no vibar interrupt, will not adv after 1 Hour.
    update_wake_up_hour_2_adv();
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
    uint16 rssi_read_rate_1ms = 500; //һ�����??2��
    GAPRole_SetParameter(GAPROLE_RSSI_READ_RATE, sizeof(uint16), &rssi_read_rate_1ms);
  }

  // Set advertising interval
  {
    advInt = SLOW_ADVERTISING_INTERVAL;
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
    uint8 ioCap = GAPBOND_IO_CAP_DISPLAY_ONLY; //��ʾ���룬 �Ա�����������Ե�����??

    /*
    bonding���ǰ�������?��¼����, �´ξͲ��������??. ��bonding�´ξͻ������??.    
    �������Ǵӻ������?? bonding = FALSE �ĺ�����ǣ�?? ���豸ÿ�����Ӷ�������������
    ����  bonding = TRUE �� ���豸ֻ���һ������ʱ��������?? ����Ͽ��󶼲����?�ٴ��������뼴������
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
  // ��������رգ�?? ����뽵�͹��ģ�?? ���Ӧ���?����ģ�?? ����ì����
  HCI_EXT_ClkDivOnHaltCmd(HCI_EXT_ENABLE_CLK_DIVIDE_ON_HALT);
  //HCI_EXT_ClkDivOnHaltCmd( HCI_EXT_ENABLE_CLK_DIVIDE_ON_HALT );

  // �źŷ���ǿ��
  HCI_EXT_SetTxPowerCmd(sys_config.txPower);

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
    // Start the Device
    VOID GAPRole_StartDevice(NULL);
    // Start Bond Manager
    osal_start_timerEx(simpleBLETaskId, SBP_WAKE_EVT, 500);
    return (events ^ START_DEVICE_EVT);
  }

  if (events & SBP_WAKE_EVT)
  {
    osal_pwrmgr_device(PWRMGR_BATTERY); //  ��˯�ߣ����ĺܸߵ�
    if (check_low_battery() == TRUE)
    {
      enter_low_battery_mode();
      return (events ^ SBP_WAKE_EVT);
    }
    g_sleepFlag = FALSE; // First Boot means LED blink but enter sleep mode directly.
    if (first_boot == TRUE)
    {
      first_boot = FALSE;
      led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_START_LED_TOGGLE_CNT, BUTTON_LEY_DELAY_IN_SLEEP);
      osal_start_timerEx(simpleBLETaskId, SBP_SLEEP_EVT, (PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF) * (PERIPHERAL_START_LED_TOGGLE_CNT) + BUTTON_LEY_DELAY_IN_SLEEP);
    }
    else // If not first boot, WAKE_EVT means start to advertise.
    {
      init_ibeacon_advertise(TRUE);
      // Start advertising
      advertise_control(TRUE);
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_INDEX_EVT, SBP_PERIODIC_INDEX_EVT_PERIOD);
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_HOUR_EVT, SBP_PERIODIC_PER_HOUR_PERIOD);
      // LED
      #if (USE_VIBRA_SENSOR == TRUE)
      if (vibra_sensor_wake_flag == FALSE)
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LEY_DELAY_IN_SLEEP);
      else
      {
        vibra_sensor_wake_flag = FALSE;
      }
      #else
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LEY_DELAY_IN_SLEEP);
      #endif
    }
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

  if (events & SBP_PERIODIC_PER_HOUR_EVT)
  {
    DEBUG_PRINT("SBP_PERIODIC_PER_HOUR_EVT\r\n");
    // Restart timer
    if (SBP_PERIODIC_PER_HOUR_PERIOD)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_HOUR_EVT, SBP_PERIODIC_PER_HOUR_PERIOD);
    }

    // Perform periodic application task
    PeripherialPerformPeriodicTask(SBP_PERIODIC_PER_HOUR_EVT);

    return (events ^ SBP_PERIODIC_PER_HOUR_EVT);
  }

  if (events & SBP_PERIODIC_BUTTON_LED_EVT)
  {
    /*
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
    */
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
    DEBUG_PRINT("SBP_SLEEP_EVT\r\n");
    #if (USE_VIBRA_SENSOR == TRUE)
    HalVibraSensorInterruptControl(TRUE);
    #endif
    low_power_state = FALSE; // set false to enable key event.
    g_sleepFlag = TRUE;
    osal_pwrmgr_device(PWRMGR_BATTERY); //  �Զ�˯��
    osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_EVT_ALL);
    advertise_control(FALSE);
    DEBUG_PRINT("Enter Sleep Mode\r\n");
    simpleBLE_Delay_1ms(1);
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
    if (++led_toggle_count <= led_toggle_cnt_target)
    {
      osal_pwrmgr_device(PWRMGR_ALWAYS_ON); // Make sure the LED can on correctly.
      HalLedSet(HAL_LED_2, HAL_LED_MODE_ON);
      simpleBLE_Delay_1ms(PERIPHERAL_LED_PREPARE_PERIOD_KEEP);
      HalLedSet(HAL_LED_TARGET, HAL_LED_MODE_TOGGLE);
      simpleBLE_Delay_1ms(PERIPHERAL_LED_TOGGLE_PERIOD_KEEP);
      HalLedSet(HAL_LED_TARGET, HAL_LED_MODE_OFF);
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT, 0);
    }
    else
    {
      HalLedSet(HAL_LED_TARGET, HAL_LED_MODE_OFF);
      osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT);
      led_toggle_clean_param();
      if (low_power_state == TRUE)
      {
        osal_set_event(simpleBLETaskId, SBP_SLEEP_EVT);
        low_power_state = FALSE;
      }
#if (POWER_OFF_SUPPORT == TRUE)
      if (g_long_press_flag == TRUE)
      {
        key_pressed_count = 0;
        osal_start_timerEx(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT, PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_1);
      }
#endif
    }
    return (events ^ SBP_PERIODIC_LED_EVT);
  }

  if (events & SBP_KEY_CNT_EVT)
  {
    if (key_pressed_count == 0)
      return (events ^ SBP_KEY_CNT_EVT);

    if (g_sleepFlag == TRUE)
    {
      // Any key press event in sleep mode, will boot up device.. One press LED, other no LED blink.
      exit_sleep_mode((key_pressed_count == 1));
    }
    else if (g_sleepFlag == FALSE)
    {
      #if 0
      if (key_pressed_count >= 2)
      #else
      // HARDCODE FOR 2020 rebuild. Any key press will reset wake up hours to default.
      if (key_pressed_count > 0)
      #endif
      {
        DEBUG_PRINT("Timer is reset\r\n");
        wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
        // reset wake_up_left
        update_wake_up_hour_2_adv();
        #if 0
        // LED blink twice
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LED_DELAY);
        #else
        // Then we don't need to blink.
        #endif
      }
      if (key_pressed_count == 1)
      {
        // Blink once
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, BUTTON_LED_TOGGLE_COUNT, BUTTON_LED_DELAY);
        #if (POWER_OFF_SUPPORT == TRUE)
        key_pressed_count = 0;
        osal_set_event(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT);
        #endif
      }
      // Change the advertise date anyway.
      change_advertise_data(TRUE);
    }
    // Reset Key event.
    key_pressed_count = 0;
    key_processing = FALSE;
    return (events ^ SBP_KEY_CNT_EVT);
  }

  if (events & SBP_KEY_LONG_PRESSED_EVT)
  {
#if (POWER_OFF_SUPPORT == TRUE)
    static uint8 sleep_button_event_stage = 0;
    if (g_long_press_flag == TRUE)
    {
      if (key_pressed_count == 2)
      {
        g_long_press_flag = FALSE;
        key_pressed_count = 0;
        sleep_button_event_stage = 0;
        DEBUG_PRINT("Powering off\r\n");
        first_boot = TRUE;
        osal_start_timerEx(simpleBLETaskId, SBP_WAKE_EVT, 0);
        return (events ^ SBP_KEY_LONG_PRESSED_EVT);
      }
      if ((key_pressed_count == 0 && sleep_button_event_stage == 0) || (sleep_button_event_stage == 1))
      {
        // Failed
        sleep_button_event_stage = 0;
        key_pressed_count = 0;
        g_long_press_flag = FALSE;
      }
      else if (key_pressed_count > 0 && sleep_button_event_stage == 0)
      {
        sleep_button_event_stage = 1;
        osal_start_timerEx(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT, PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_2);
      }
      return (events ^ SBP_KEY_LONG_PRESSED_EVT);
    }

    if (check_keys_pressed(HAL_KEY_SW_6) == TRUE)
    {
      key_long_press_cnt++;
      if (key_long_press_cnt == PERIPHERAL_KEY_LONG_PRESS_TIME_CNT)
      {
        g_long_press_flag = TRUE;
        sleep_toggle_cnt = 3;
        key_long_press_cnt = 0;
        //led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, sleep_toggle_cnt, 0);
      }
      else
      {
        osal_start_timerEx(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT, PERIPHERAL_KEY_LONG_PRESS_CALC_PERIOD);
      }
    }
    else if (check_keys_pressed(HAL_KEY_SW_6) == FALSE)
    {
      g_long_press_flag = FALSE;
      key_long_press_cnt = 0;
      osal_stop_timerEx(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT);
    }
    // Reset Key event.
    key_pressed_count = 0;
    key_processing = FALSE;
#endif
    return (events ^ SBP_KEY_LONG_PRESSED_EVT);
  }
  // Discard unknown events
  return 0;
}


static uint8 led_toggle_set_param(uint16 toggle_period_on, uint16 toggle_period_off, uint32 toggle_target_cnt, uint16 delay)
{
  if (led_toggling == TRUE)
    return FALSE;
  osal_pwrmgr_device(PWRMGR_ALWAYS_ON);
  led_toggling = TRUE;
  //led_toggle_period_on = toggle_period_on;
  //led_toggle_period_off = toggle_period_off;
  (void)toggle_period_on;
  (void)toggle_period_off;
  led_toggle_count = 0;
  led_toggle_cnt_target = toggle_target_cnt;
  osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT, delay);
  return TRUE;
}
static uint8 led_toggle_clean_param()
{
  if (led_toggling == FALSE)
    return FALSE;
  osal_pwrmgr_device(PWRMGR_BATTERY);
  //led_toggle_period_on = PERIPHERAL_START_LED_TOGGLE_PERIOD_ON;
  //led_toggle_period_off = PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF;
  led_toggle_count = 0;
  led_toggle_cnt_target = PERIPHERAL_START_LED_TOGGLE_CNT;
  led_toggling = FALSE;
  return TRUE;
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
  if (keys & HAL_KEY_SW_6)
  {
    if (low_power_state == TRUE)
    {
      DEBUG_PRINT("Handle Keys, Low Power Mode\r\n");
      return;
    }

    if (key_processing == FALSE)
    {
      if (key_pressed_count == 0)
      {
        if (wake_up_hours_remain <= RESET_WAKE_TIME_HOURS_THRES)
        {
          wake_up_hours_remain = BUTTON_WAKE_TIME_HOURS;
          update_wake_up_hour_2_adv();
        }
#if (POWER_OFF_SUPPPORT == TRUE)
        if (g_long_press_flag == FALSE)
        {
#endif
          osal_start_timerEx(simpleBLETaskId, SBP_KEY_CNT_EVT, PERIPHERAL_KEY_CALCULATE_PERIOD);
#if (POWER_OFF_SUPPPORT == TRUE)
        }
#endif
      }
      key_pressed_count++;
    }
    key_pressed = !key_pressed;
  }

  #ifdef DEBUG_BOARD
  if (keys & HAL_KEY_SW_1)
  {
    debug_low_power = TRUE;
  }
  if (keys & HAL_KEY_SW_3)
  {
    debug_low_power = FALSE;
  }
  #endif
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
  if (low_power_state == TRUE)
  {
    return;
  }

  switch (event_id)
  {
  case SBP_PERIODIC_INDEX_EVT:
    {
      if (rapid_processing == FALSE)
      {
        advertData_iBeacon[ADV_INDEX_BYTE] += 1;
      }
      GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData_iBeacon), advertData_iBeacon);
    }
    break;
  case SBP_PERIODIC_PER_HOUR_EVT:
    if (g_sleepFlag == TRUE)
    {
      DEBUG_PRINT("sleep already, stop the per hour timer\r\n");
      osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_HOUR_EVT);
    }
    else
    {
      DEBUG_PRINT("This is a per hour event\r\n");
      if (check_low_battery() == TRUE)
      {
        enter_low_battery_mode();
      }
      else
      {
        #if (USE_VIBRA_SENSOR == TRUE)
        if (readVibraTriggered() == TRUE)
        {
          clearVibraTriggered();
          //wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
        }
        else
        {
          wake_up_hours_remain--;
        }
        HalVibraSensorInterruptControl(TRUE);
        update_wake_up_hour_2_adv();
        if (wake_up_hours_remain == 0)
        {
          wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
          DEBUG_PRINT("Enter Sleep mode\r\n");
          osal_start_timerEx(simpleBLETaskId, SBP_SLEEP_EVT, SLEEP_MS);
        }
        #else
        //No Vibra Sensor, wake up hours path.
        wake_up_hours_remain--;
        update_wake_up_hour_2_adv();
        if (wake_up_hours_remain == 0)
        {
          wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
          DEBUG_PRINT("Enter Sleep mode\r\n");
          osal_start_timerEx(simpleBLETaskId, SBP_SLEEP_EVT, SLEEP_MS);
        }
        #endif
      }
    }
    break;
  case SBP_PERIODIC_BUTTON_LED_EVT:
    /*
    HalLedSet(HAL_LED_1, HAL_LED_MODE_TOGGLE);
    key_led_count--;
    */
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

static bool check_low_battery()
{
  #ifdef DEBUG_BOARD
  if (debug_low_power == TRUE)
    return TRUE;
  #endif

  uint32 adc_read = 0;
  for (uint8 i = 0; i < 16; i++)
  {
    HalAdcSetReference(HAL_ADC_REF_125V);
    adc_read += HalAdcRead(HAL_ADC_CHANNEL_VDD, HAL_ADC_RESOLUTION_10);
  }
  adc_read = adc_read >> 4;
  battery_voltage = adc_read * 3 * 125 / 511 / 10;
  DEBUG_VALUE("adc value : ", adc_read, 10);
  DEBUG_VALUE("Battery Value : ", battery_voltage * 10, 10);
  // Update the advertise data.
  advertData_iBeacon[ADV_BAT_BYTE] = battery_voltage & 0xFF;
  if (g_sleepFlag == TRUE && battery_voltage < BATTERY_LOW_THRESHOLD_SLEEP)
  {
    return TRUE;
  }
  else if (g_sleepFlag == FALSE && battery_voltage < BATTERY_LOW_THRESHOLD)
  {
    return TRUE;
  }
  return FALSE;
}

static void enter_low_battery_mode()
{
  DEBUG_PRINT("Enter Low Battery Mode\r\n");
  low_power_state = TRUE;
  advertData_iBeacon[ADV_FLAG_BYTE] |= 0x40;
  // Stop advertising.
  advertise_control(FALSE);
  // LED Blinking.
  led_toggle_set_param(PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_ON, PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_LOW_BAT_LED_TOGGLE_CNT, 0);
}

#if (USE_VIBRA_SENSOR == TRUE)
void wake_from_vibra_sensor()
{
  first_boot = FALSE;
  vibra_sensor_wake_flag = TRUE;
  exit_sleep_mode(FALSE);
}
#endif

void exit_sleep_mode(uint8 first_wake)
{
  if (g_sleepFlag == TRUE)
  {
    if (first_wake == TRUE)
    {
      first_boot = TRUE;
    }
    else if (first_wake == FALSE)
    {
      first_boot = FALSE;
    }
    osal_set_event(simpleBLETaskId, SBP_WAKE_EVT);
  }
}

static void update_wake_up_hour_2_adv()
{
  advertData_iBeacon[ADV_HOUR_LEFT_BYTE] = (wake_up_hours_remain >> DEFAULT_RIGHT_MOVE_BIT) & 0xFF;
}
#if (POWER_OFF_SUPPORT == TRUE)
static bool check_keys_pressed(uint8 keys)
{
  switch (keys)
  {
    case HAL_KEY_SW_6:
      if (!(HAL_KEY_SW_6_PORT & HAL_KEY_SW_6_BIT))    /* Key is active low */
      {
        return TRUE;
      }
      break;
    default:
      break;
  }
  return FALSE;
}
#endif

static void init_ibeacon_advertise(bool reset_index)
{
  advertData_iBeacon[ADV_HOUR_LEFT_BYTE] = (wake_up_hours_remain >> DEFAULT_RIGHT_MOVE_BIT) & 0xFF;
  advertData_iBeacon[ADV_BAT_BYTE] = battery_voltage & 0xFF;
  advertData_iBeacon[ADV_FLAG_BYTE] = 0x00;
  if (reset_index == TRUE)
  {
    advertData_iBeacon[ADV_INDEX_BYTE] = 0x00;
  }
}

static void advertise_control(bool enable)
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