/**************************************************************************************************
  Filename:       simpleBLECentral.c
  Revised:        $Date: 2011-06-20 11:57:59 -0700 (Mon, 20 Jun 2011) $
  Revision:       $Revision: 28 $

  Description:    This file contains the Simple BLE Central sample application 
                  for use with the CC2540 Bluetooth Low Energy Protocol Stack.

  Copyright 2010 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED ?S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */

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
#include "gapbondmgr.h"
#include "simpleGATTprofile.h"
#include "simpleBLECentral.h"

#include "npi.h"
#include "simpleble.h"
#include "stdio.h"
#include "string.h"
#include "amomcu_buffer.h"

#include "simpleBLEKey.h"
#include "simpleBLELED.h"
#include "simpleBLECentralPeripheralCommon.h"

#if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
#include "simpleBLEStation.h"
#endif

/*********************************************************************
 * MACROS
 */

// Length of bd addr as a string
#define B_ADDR_STR_LEN 15

/*********************************************************************
 * CONSTANTS
 */

// Maximum number of scan responses
#define DEFAULT_MAX_SCAN_RES 40 //8

// Scan duration in ms
#define DEFAULT_SCAN_DURATION 500 //4000  Ĭ��ɨ��ʱ�� ms

// Discovey mode (limited, general, all)
#define DEFAULT_DISCOVERY_MODE DEVDISC_MODE_ALL

// TRUE to use active scan
#define DEFAULT_DISCOVERY_ACTIVE_SCAN TRUE

// TRUE to use white list during discovery
#define DEFAULT_DISCOVERY_WHITE_LIST FALSE

// TRUE to use high scan duty cycle when creating link
#define DEFAULT_LINK_HIGH_DUTY_CYCLE FALSE

// TRUE to use white list when creating link
#define DEFAULT_LINK_WHITE_LIST FALSE

// Default RSSI polling period in ms
#define DEFAULT_RSSI_PERIOD 1000

// Whether to enable automatic parameter update request when a connection is formed
#define DEFAULT_ENABLE_UPDATE_REQUEST TRUE

// Minimum connection interval (units of 1.25ms) if automatic parameter update request is enabled
#define DEFAULT_UPDATE_MIN_CONN_INTERVAL 6 //400  ���Ӽ�������ݷ������йأ�??? ���Ӽ��Խ�̣�??? ��λʱ���ھ��ܷ���Խ�������???

// Maximum connection interval (units of 1.25ms) if automatic parameter update request is enabled
#define DEFAULT_UPDATE_MAX_CONN_INTERVAL 6 //800  ���Ӽ�������ݷ������йأ�??? ���Ӽ��Խ�̣�??? ��λʱ���ھ��ܷ���Խ�������???

// Slave latency to use if automatic parameter update request is enabled
#define DEFAULT_UPDATE_SLAVE_LATENCY 0

// Supervision timeout value (units of 10ms) if automatic parameter update request is enabled
#define DEFAULT_UPDATE_CONN_TIMEOUT 600

// Default passcode
#define DEFAULT_PASSCODE 19655

// Default GAP pairing mode
#define DEFAULT_PAIRING_MODE GAPBOND_PAIRING_MODE_WAIT_FOR_REQ

// Default MITM mode (TRUE to require passcode or OOB when pairing)
#define DEFAULT_MITM_MODE FALSE

// Default bonding mode, TRUE to bond
#define DEFAULT_BONDING_MODE TRUE

// Default GAP bonding I/O capabilities
#define DEFAULT_IO_CAPABILITIES GAPBOND_IO_CAP_DISPLAY_ONLY

// Default service discovery timer delay in ms
#define DEFAULT_SVC_DISCOVERY_DELAY 1000

// TRUE to filter discovery results on desired service UUID
#define DEFAULT_DEV_DISC_BY_SVC_UUID TRUE

// Darren Scan Macros
#define DEFAULT_SCAN_TIME (5000 / DEFAULT_SCAN_DURATION)

// Discovery states
enum
{
  BLE_DISC_STATE_IDLE, // Idle
  BLE_DISC_STATE_SVC,  // Service discovery
  BLE_DISC_STATE_CHAR  // Characteristic discovery
};

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

// Task ID for internal task/event processing
uint8 simpleBLETaskId;

// GAP GATT Attributes
//static const uint8 simpleBLEDeviceName[GAP_DEVICE_NAME_LEN] = "Simple BLE Central";

// Scanning state
static uint8 simpleBLEScanning = FALSE;

// RSSI polling state
static uint8 simpleBLERssi = FALSE;

// Connection handle of current connection
uint16 simpleBLEConnHandle = GAP_CONNHANDLE_INIT;

// Application state
uint8 simpleBLEState = BLE_STATE_IDLE;

// Discovery state
static uint8 simpleBLEDiscState = BLE_DISC_STATE_IDLE;

// Discovered service start and end handle
static uint16 simpleBLESvcStartHdl = 0;
static uint16 simpleBLESvcEndHdl = 0;

// Discovered characteristic handle
uint16 simpleBLECharHdl = 0;
uint16 simpleBLECharHd6 = 0;
bool simpleBLEChar6DoWrite = TRUE;
bool simpleBLECentralCanSend = FALSE; //  �����ɷ�������

extern bool timerIsOn; //

static BLE_STATUS currentBLEStatus;
static uint8 scanTimeLeft = DEFAULT_SCAN_TIME;

static uint8 first_boot = FALSE;

BLE_STATUS getCurrentBLEStatus()
{
  return currentBLEStatus;
}

uint8 getScanTimeLeft()
{
  return scanTimeLeft;
}

void resetScanTimeLeft()
{
  scanTimeLeft = DEFAULT_SCAN_TIME;
}
// Value to write
//static uint8 simpleBLECharVal = 0;

// Value read/write toggle
//static bool simpleBLEDoWrite = FALSE;

// GATT read/write procedure state
//static bool simpleBLEProcedureInProgress = FALSE;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void simpleBLECentralProcessGATTMsg(gattMsgEvent_t *pMsg);
static void simpleBLECentralRssiCB(uint16 connHandle, int8 rssi);
static uint8 simpleBLECentralEventCB(gapCentralRoleEvent_t *pEvent);
static void simpleBLECentralPasscodeCB(uint8 *deviceAddr, uint16 connectionHandle,
                                       uint8 uiInputs, uint8 uiOutputs);
static void simpleBLECentralPairStateCB(uint16 connHandle, uint8 state, uint8 status);
static void simpleBLECentral_HandleKeys(uint8 shift, uint8 keys);
static void simpleBLECentral_ProcessOSALMsg(osal_event_hdr_t *pMsg);
static void simpleBLEGATTDiscoveryEvent(gattMsgEvent_t *pMsg);
static void simpleBLECentralStartDiscovery(void);
//static void simpleBLEAddDeviceInfo(uint8 *pAddr, uint8 addrType);
//static bool simpleBLEFindSvcUuid(uint16 uuid, uint8 *pData, uint8 dataLen);

/*********************************************************************
 * PROFILE CALLBACKS
 */

// GAP Role Callbacks
static const gapCentralRoleCB_t simpleBLERoleCB =
    {
        simpleBLECentralRssiCB, // RSSI callback
        simpleBLECentralEventCB // Event callback
};

// Bond Manager Callbacks
static const gapBondCBs_t simpleBLEBondCB =
    {
        simpleBLECentralPasscodeCB,
        simpleBLECentralPairStateCB};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      SimpleBLECentral_Init
 *
 * @brief   Initialization function for the Simple BLE Central App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notification).
 *
 * @param   task_id - the ID assigned by OSAL.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void SimpleBLECentral_Init(uint8 task_id)
{
  simpleBLETaskId = task_id;

  // Setup Central Profile
  {
    uint8 scanRes = DEFAULT_MAX_SCAN_RES;
    GAPCentralRole_SetParameter(GAPCENTRALROLE_MAX_SCAN_RES, sizeof(uint8), &scanRes);
  }

  // Setup GAP
  GAP_SetParamValue(TGAP_GEN_DISC_SCAN, DEFAULT_SCAN_DURATION);
  GAP_SetParamValue(TGAP_LIM_DISC_SCAN, DEFAULT_SCAN_DURATION);
  GGS_SetParameter(GGS_DEVICE_NAME_ATT, GAP_DEVICE_NAME_LEN, simpleBle_GetAttDeviceName());

  // Setup the GAP Bond Manager
  {
    uint32 passkey = DEFAULT_PASSCODE;
    uint8 pairMode; // = DEFAULT_PAIRING_MODE;
    uint8 mitm = DEFAULT_MITM_MODE;
    uint8 ioCap = DEFAULT_IO_CAPABILITIES;
    //uint8 bonding = DEFAULT_BONDING_MODE;

    /*
    bonding���ǰ�������?��¼����, �´ξͲ��������???. ��bonding�´ξͻ������???.    
    �������Ǵӻ������??? bonding = FALSE �ĺ�����ǣ�??? ���豸ÿ�����Ӷ�������������
    ����  bonding = TRUE �� ���豸ֻ���һ������ʱ��������??? ����Ͽ��󶼲����?�ٴ��������뼴������
    ---------------amomcu.com-------------------------    
    */
    uint8 bonding = FALSE;
    pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
    //#endif
    GAPBondMgr_SetParameter(GAPBOND_DEFAULT_PASSCODE, sizeof(uint32), &passkey);
    GAPBondMgr_SetParameter(GAPBOND_PAIRING_MODE, sizeof(uint8), &pairMode);
    GAPBondMgr_SetParameter(GAPBOND_MITM_PROTECTION, sizeof(uint8), &mitm);
    GAPBondMgr_SetParameter(GAPBOND_IO_CAPABILITIES, sizeof(uint8), &ioCap);
    GAPBondMgr_SetParameter(GAPBOND_BONDING_ENABLED, sizeof(uint8), &bonding);
  }

  // Initialize GATT Client
  VOID GATT_InitClient();

  // Register to receive incoming ATT Indications/Notifications
  GATT_RegisterForInd(simpleBLETaskId);

  // Initialize GATT attributes
  GGS_AddService(GATT_ALL_SERVICES);         // GAP
  GATTServApp_AddService(GATT_ALL_SERVICES); // GATT attributes

  // Register for all key events - This app will handle all key events
  RegisterForKeys(simpleBLETaskId);
  //HalLedSet(HAL_LED_3, HAL_LED_MODE_ON );
  // Setup a delayed profile startup
  set_key_press_process_callback(central_key_press_process_callback);
  osal_set_event(simpleBLETaskId, START_DEVICE_EVT);
}

void simpleBLEStartScan()
{
  simpleBLECentralCanSend = FALSE;

  if (!simpleBLEScanning)
  {
    simpleBLEScanning = TRUE;
    GAPCentralRole_StartDiscovery(DEFAULT_DISCOVERY_MODE,
                                  DEFAULT_DISCOVERY_ACTIVE_SCAN,
                                  DEFAULT_DISCOVERY_WHITE_LIST);
  }
}

/*********************************************************************
 * @fn      SimpleBLECentral_ProcessEvent
 *
 * @brief   Simple BLE Central Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The OSAL assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16 SimpleBLECentral_ProcessEvent(uint8 task_id, uint16 events)
{

  VOID task_id; // OSAL required parameter that isn't used in this function

  if (events & SYS_EVENT_MSG)
  {
    uint8 *pMsg;

    if ((pMsg = osal_msg_receive(simpleBLETaskId)) != NULL)
    {
      simpleBLECentral_ProcessOSALMsg((osal_event_hdr_t *)pMsg);

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
    // record current status;
    currentBLEStatus = sys_config.status;
    // Only Beacon needs this.
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    reset_to_no_battery_status(sys_config.role);
    #endif
    // Start the Device
    VOID GAPCentralRole_StartDevice((gapCentralRoleCB_t *)&simpleBLERoleCB);
    // Register with bond manager after starting device
    GAPBondMgr_Register((gapBondCBs_t *)&simpleBLEBondCB);

    /* TODO: Do we need to check the battery value in OFF_SCAN mode? */
    /*
    if (currentBLEStatus == BLE_STATUS_OFF)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_PER_MIN_EVT, )
    }
    */
    osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_EVT, SBP_PERIODIC_EVT_PERIOD);
    osal_start_timerEx(simpleBLETaskId, SBP_WAKE_EVT, 500);
    return (events ^ START_DEVICE_EVT);
  }

  if (events & SBP_WAKE_EVT)
  {
    g_sleepFlag = FALSE;
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    osal_pwrmgr_device(PWRMGR_BATTERY);
    #elif (PRESET_ROLE == BLE_PRE_ROLE_STATION)
    osal_pwrmgr_device(PWRMGR_ALWAYS_ON); //TODO: Darren: Needs to change this to battery.
    #endif
    
    #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
    if (first_boot == TRUE)
    {
      if (check_low_battery(NULL) == TRUE)
      {
        enter_low_battery_mode();
        return (events ^ SBP_WAKE_EVT);
      }
    }
    if (first_boot == TRUE)
    {
      sys_config.minLeft = DEFAULT_WAKE_TIME_MINS;
      #ifdef DEBUG_BOARD
      PrintAllPara();
      #endif
      // Blink twice after 650ms
      led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, 0);
    }
    #elif (PRESET_ROLE == BLE_PRE_ROLE_STATION)
    sendStationInfo();
    #endif
    DEBUG_PRINT("Central Wake\r\n");
    simpleBLEStartScan();
    return (events ^ SBP_WAKE_EVT);
  }

  if (events & SBP_CONNECT_EVT)
  {
    attWriteReq_t AttReq;
    AttReq.handle = (simpleBLECharHd6 + 1) /*0x0036*/;
    AttReq.len = 2;
    AttReq.sig = 0;
    AttReq.cmd = 0;
    AttReq.pValue = GATT_bm_alloc(simpleBLEConnHandle, ATT_WRITE_REQ, 2, NULL);
    if (AttReq.pValue != NULL)
    {
      AttReq.pValue[0] = 0x01;
      AttReq.pValue[1] = 0x00;
      GATT_WriteCharValue(0, &AttReq, simpleBLETaskId);
      simpleBLECentralCanSend = TRUE;
      LCD_WRITE_STRING("Connected", HAL_LCD_LINE_3);
    }
    else
    {
      LCD_WRITE_STRING_VALUE("err: line=", __LINE__, 10, HAL_LCD_LINE_1);
      while (1)
        ;
    }

    return (events ^ SBP_CONNECT_EVT);
  }

  if (events & SBP_DATA_EVT)
  {
    uint16 totalbytes = qq_total();
    uint8 numBytes;
    // ��  RdLen ���ֽ����ݵ� ������ RdBuf�� ���ض�ȡ������Ч���ݳ���
    if (totalbytes > 0 && simpleBLEChar6DoWrite)
    {
      attWriteReq_t AttReq;
      numBytes = ((totalbytes > SIMPLEPROFILE_CHAR6_LEN) ? SIMPLEPROFILE_CHAR6_LEN : totalbytes);
      AttReq.pValue = GATT_bm_alloc(simpleBLEConnHandle, ATT_WRITE_REQ, numBytes, NULL);
      if (AttReq.pValue != NULL)
      {
        AttReq.handle = simpleBLECharHd6;
        AttReq.len = numBytes;
        AttReq.sig = 0;
        AttReq.cmd = 0;
        //osal_memcpy(AttReq.pValue,buf,AttReq.len);
        qq_read(AttReq.pValue, AttReq.len);
        //GATT_WriteCharValue( simpleBLEConnHandle, &AttReq, simpleBLETaskId );
        GATT_WriteCharValue(0, &AttReq, simpleBLETaskId);
        simpleBLEChar6DoWrite = FALSE;
      }
      else
      {
        //LCD_WRITE_STRING_VALUE( "line=", __LINE__, 10, HAL_LCD_LINE_1 );
      }
    }

    if (qq_total() > 0)
    {
      timerIsOn = TRUE;
      osal_start_timerEx(simpleBLETaskId, SBP_DATA_EVT, 16);
    }
    else
    {
      timerIsOn = FALSE;
    }
    return (events ^ SBP_DATA_EVT);
  }

  if (events & SBP_UART_EVT)
  {
    if (FALSE == timerIsOn)
    {
      //         osal_set_event( simpleBLETaskId, SBP_DATA_EVT );
      osal_start_timerEx(simpleBLETaskId, SBP_DATA_EVT, 8);
    }
    return (events ^ SBP_UART_EVT);
  }

  if (events & SBP_PERIODIC_EVT)
  {
    // Restart timer
    if (SBP_PERIODIC_EVT_PERIOD)
    {
      osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_EVT, SBP_PERIODIC_EVT_PERIOD);
    }
    // Perform periodic application task
    simpleBLE_performPeriodicTask();

    if (simpleBLEState == BLE_STATE_CONNECTED)
    {
      if (!simpleBLERssi)
      {
        simpleBLERssi = TRUE;
        GAPCentralRole_StartRssi(simpleBLEConnHandle, DEFAULT_RSSI_PERIOD);
      }
    }
    else
    {
      if (simpleBLERssi)
      {
        GAPCentralRole_CancelRssi(simpleBLEConnHandle);
      }
    }

    return (events ^ SBP_PERIODIC_EVT);
  }

  if (events & START_DISCOVERY_EVT)
  {
    simpleBLECentralStartDiscovery();
    return (events ^ START_DISCOVERY_EVT);
  }

  if (events & SBP_SCAN_ADV_TRANS_EVT)
  {
    scan_adv_event_callback(sys_config.role);
    return (events ^ SBP_SCAN_ADV_TRANS_EVT);
  }

  if (events & SBP_KEY_CNT_EVT)
  {
    key_cnt_evt_callback();
    return (events ^ SBP_KEY_CNT_EVT);
  }

  if (events & SBP_PERIODIC_LED_EVT)
  {
    led_event_callback();
    return (events ^ SBP_PERIODIC_LED_EVT);
  }
  // Discard unknown events
  return 0;
}

/*********************************************************************
 * @fn      simpleBLECentral_ProcessOSALMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void simpleBLECentral_ProcessOSALMsg(osal_event_hdr_t *pMsg)
{
  switch (pMsg->event)
  {
  case KEY_CHANGE:
    simpleBLECentral_HandleKeys(((keyChange_t *)pMsg)->state, ((keyChange_t *)pMsg)->keys);
    break;

  case GATT_MSG_EVENT:
    simpleBLECentralProcessGATTMsg((gattMsgEvent_t *)pMsg);
    break;
  }
}

/*********************************************************************
 * @fn      simpleBLECentral_HandleKeys
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
static void simpleBLECentral_HandleKeys(uint8 shift, uint8 keys)
{
  key_press_handler(keys);
}

/*********************************************************************
 * @fn      simpleBLECentralProcessGATTMsg
 *
 * @brief   Process GATT messages
 *
 * @return  none
 */
static void simpleBLECentralProcessGATTMsg(gattMsgEvent_t *pMsg)
{
  if (simpleBLEState != BLE_STATE_CONNECTED)
  {
    // In case a GATT message came after a connection has dropped,
    // ignore the message
    goto EXIT;
  }

  if ((pMsg->method == ATT_READ_RSP) ||
      ((pMsg->method == ATT_ERROR_RSP) &&
       (pMsg->msg.errorRsp.reqOpcode == ATT_READ_REQ)))
  {
    if (pMsg->method == ATT_ERROR_RSP)
    {
      //uint8 status = pMsg->msg.errorRsp.errCode;
      //LCD_WRITE_STRING_VALUE( "Read Error", status, 10, HAL_LCD_LINE_1 );
    }
    else
    {
      //After a successful read, display the read value
      //uint8 valueRead = pMsg->msg.readRsp.pValue[0];
      //LCD_WRITE_STRING_VALUE( "Read rsp:", valueRead, 10, HAL_LCD_LINE_1 );
    }
    //simpleBLEProcedureInProgress = FALSE;
  }
  else if ((pMsg->method == ATT_WRITE_RSP) ||
           ((pMsg->method == ATT_ERROR_RSP) &&
            (pMsg->msg.errorRsp.reqOpcode == ATT_WRITE_REQ)))
  {

    if (pMsg->method == ATT_ERROR_RSP == ATT_ERROR_RSP)
    {
      //uint8 status = pMsg->msg.errorRsp.errCode;
      //LCD_WRITE_STRING_VALUE( "Write Error", status, 10, HAL_LCD_LINE_1 );
    }
    else
    {
      // After a succesful write, display the value that was written and increment value
      //LCD_WRITE_STRING_VALUE( "Write sent:", simpleBLECharVal++, 10, HAL_LCD_LINE_1 );
      // ����������ڱ�����һ��д���ݵ��ӻ��Ѿ��ɹ���??? �������ж�д����ʱ���жϣ� ��ȷ�����ݵ�������
      simpleBLEChar6DoWrite = TRUE;
    }

    //simpleBLEProcedureInProgress = FALSE;
  }
  else if (simpleBLEDiscState != BLE_DISC_STATE_IDLE)
  {
    simpleBLEGATTDiscoveryEvent(pMsg);
  }
  else if ((pMsg->method == ATT_HANDLE_VALUE_NOTI)) //֪ͨ
  {
    // Do nothing.
  }

EXIT:
  //  LCD_WRITE_STRING_VALUE( "free line=", __LINE__, 10, HAL_LCD_LINE_1 );
  GATT_bm_free(&pMsg->msg, pMsg->method);
}

/*********************************************************************
 * @fn      simpleBLECentralRssiCB
 *
 * @brief   RSSI callback.
 *
 * @param   connHandle - connection handle
 * @param   rssi - RSSI
 *
 * @return  none
 */
static void simpleBLECentralRssiCB(uint16 connHandle, int8 rssi)
{
  return;
}

// ��ʾ��һ�����豸�ĵ�ַ  nextFalg=true����ʾ��һ����ַ��������ʾ��ǰ��ַ
void simpleBLECentraDisplaNextPeriAddr(bool nextFalg)
{
  return;
}

/*********************************************************************
 * @fn      simpleBLECentralEventCB
 *
 * @brief   Central event callback function.
 *
 * @param   pEvent - pointer to event structure
 *
 * @return  TRUE if safe to deallocate event message, FALSE otherwise.
 */
static uint8 simpleBLECentralEventCB(gapCentralRoleEvent_t *pEvent)
{
  switch (pEvent->gap.opcode)
  {
  case GAP_DEVICE_INIT_DONE_EVENT:
  {
    LCD_WRITE_STRING("BLE Central", HAL_LCD_LINE_1);
    LCD_WRITE_STRING(bdAddr2Str(pEvent->initDone.devAddr), HAL_LCD_LINE_2);
  }
  break;
 
  case GAP_DEVICE_INFO_EVENT:
  {
    scan_device_info_callback(pEvent);
  }
  break;

  case GAP_DEVICE_DISCOVERY_EVENT:
  {
    simpleBLEScanning = FALSE;
    scanTimeLeft--;
    scan_discovery_callback();
  }
  break;

  case GAP_LINK_ESTABLISHED_EVENT:
  {
  }
  break;

  case GAP_LINK_TERMINATED_EVENT:
  {
    simpleBLEState = BLE_STATE_IDLE;
    simpleBLEConnHandle = GAP_CONNHANDLE_INIT;
    simpleBLEDiscState = BLE_DISC_STATE_IDLE;
    simpleBLECharHdl = 0;
    simpleBLECentralCanSend = FALSE;
    LCD_WRITE_STRING("Disconnected", HAL_LCD_LINE_1);
    LCD_WRITE_STRING_VALUE("Reason:", pEvent->linkTerminate.reason, 10, HAL_LCD_LINE_2);
    //��������ʧ�ܺ� ���Գ���ִ��������߼����?��ӻ�???
    simpleBLEScanning = 0;
    simpleBLEStartScan();
  }
  break;

  case GAP_LINK_PARAM_UPDATE_EVENT:
  {
    LCD_WRITE_STRING("Param Update", HAL_LCD_LINE_1);
    osal_start_timerEx(simpleBLETaskId, SBP_CONNECT_EVT, 1000);
    g_sleepFlag = FALSE;
    osal_pwrmgr_device(PWRMGR_BATTERY); //  ��˯�ߣ����ĺܸߵ�
  }
  break;

  default:
    break;
  }
  return (TRUE);
}

bool simpleBLEConnect(uint8 index)
{
  return FALSE;
}

/*********************************************************************
 * @fn      pairStateCB
 *
 * @brief   Pairing state callback.
 *
 * @return  none
 */
static void simpleBLECentralPairStateCB(uint16 connHandle, uint8 state, uint8 status)
{
  if (state == GAPBOND_PAIRING_STATE_STARTED)
  {
    LCD_WRITE_STRING("Pairing started", HAL_LCD_LINE_1);
  }
  else if (state == GAPBOND_PAIRING_STATE_COMPLETE)
  {
    if (status == SUCCESS)
    {
      LCD_WRITE_STRING("Pairing success", HAL_LCD_LINE_1);
    }
    else
    {
      LCD_WRITE_STRING_VALUE("Pairing fail", status, 10, HAL_LCD_LINE_1);
    }
  }
  else if (state == GAPBOND_PAIRING_STATE_BONDED)
  {
    if (status == SUCCESS)
    {
      LCD_WRITE_STRING("Bonding success", HAL_LCD_LINE_1);
    }
  }
}

/*********************************************************************
 * @fn      simpleBLECentralPasscodeCB
 *
 * @brief   Passcode callback.
 *
 * @return  none
 */
static void simpleBLECentralPasscodeCB(uint8 *deviceAddr, uint16 connectionHandle,
                                       uint8 uiInputs, uint8 uiOutputs)
{
  return;
}

/*********************************************************************
 * @fn      simpleBLECentralStartDiscovery
 *
 * @brief   Start service discovery.
 *
 * @return  none
 */
static void simpleBLECentralStartDiscovery(void)
{
  uint8 uuid[ATT_BT_UUID_SIZE] = {LO_UINT16(SIMPLEPROFILE_SERV_UUID),
                                  HI_UINT16(SIMPLEPROFILE_SERV_UUID)};

  // Initialize cached handles
  simpleBLESvcStartHdl = simpleBLESvcEndHdl = simpleBLECharHdl = 0;

  simpleBLEDiscState = BLE_DISC_STATE_SVC;

  // Discovery simple BLE service
  GATT_DiscPrimaryServiceByUUID(simpleBLEConnHandle,
                                uuid,
                                ATT_BT_UUID_SIZE,
                                simpleBLETaskId);
}

/*********************************************************************
 * @fn      simpleBLEGATTDiscoveryEvent
 *
 * @brief   Process GATT discovery event
 *
 * @return  none
 */
static void simpleBLEGATTDiscoveryEvent(gattMsgEvent_t *pMsg)
{
  attReadByTypeReq_t req;
  if (simpleBLEDiscState == BLE_DISC_STATE_SVC)
  {
    // Service found, store handles
    if (pMsg->method == ATT_FIND_BY_TYPE_VALUE_RSP &&
        pMsg->msg.findByTypeValueRsp.numInfo > 0)
    {
      simpleBLESvcStartHdl = ATT_ATTR_HANDLE(pMsg->msg.findByTypeValueRsp.pHandlesInfo, 0);
      simpleBLESvcEndHdl = ATT_GRP_END_HANDLE(pMsg->msg.findByTypeValueRsp.pHandlesInfo, 0);

      //��ÿһ��handle��ֵ����ӡ����
      //LCD_WRITE_STRING_VALUE( "StartHdl=", simpleBLESvcStartHdl, 10, HAL_LCD_LINE_1 );
      //LCD_WRITE_STRING_VALUE( "EndHdl=", simpleBLESvcEndHdl, 10, HAL_LCD_LINE_1 );
      //simpleBLECharHd6 = simpleBLESvcStartHdl;

      for (int i = simpleBLESvcStartHdl; i < simpleBLESvcStartHdl + 10; i++)
      {
        //LCD_WRITE_STRING_VALUE( "handle = ", i, 10, HAL_LCD_LINE_1 );
      }
    }

    // If procedure complete
    if ((pMsg->method == ATT_FIND_BY_TYPE_VALUE_RSP &&
         pMsg->hdr.status == bleProcedureComplete) ||
        (pMsg->method == ATT_ERROR_RSP))
    {
      if (simpleBLESvcStartHdl != 0)
      {
        // Discover characteristic
        simpleBLEDiscState = BLE_DISC_STATE_CHAR;

        req.startHandle = simpleBLESvcStartHdl;
        req.endHandle = simpleBLESvcEndHdl;
        req.type.len = ATT_BT_UUID_SIZE;
        req.type.uuid[0] = LO_UINT16(SIMPLEPROFILE_CHAR6_UUID);
        req.type.uuid[1] = HI_UINT16(SIMPLEPROFILE_CHAR6_UUID);

        GATT_ReadUsingCharUUID(simpleBLEConnHandle, &req, simpleBLETaskId);
      }
    }
  }
  else if (simpleBLEDiscState == BLE_DISC_STATE_CHAR)
  {
    // Characteristic found, store handle
    if (pMsg->method == ATT_READ_BY_TYPE_RSP &&
        pMsg->msg.readByTypeRsp.numPairs > 0)
    {
      simpleBLECharHd6 = BUILD_UINT16(pMsg->msg.readByTypeRsp.pDataList[0],
                                      pMsg->msg.readByTypeRsp.pDataList[1]);

      LCD_WRITE_STRING("Simple Svc Found", HAL_LCD_LINE_1);
      //simpleBLEProcedureInProgress = FALSE;
    }
    else
    {
      LCD_WRITE_STRING_VALUE("pMsg->method=", pMsg->method, 10, HAL_LCD_LINE_1);
      LCD_WRITE_STRING("ERR in Simple Svc Found", HAL_LCD_LINE_1);
    }

    simpleBLEDiscState = BLE_DISC_STATE_IDLE;
  }
}

static uint8 beacon_id[] =
    {
        0x4C, // 5
        0x00, // 6
        0x02, // 7
        0x15  // 8
};

static uint8 isSmart[] =
    {
        0x53,
        0x4D,
        0x54,
};

// Filter if it is a beacon.
bool simpleBLEFilterSelfBeacon(uint8 *data, uint8 dataLen)
{
  if ((osal_memcmp(beacon_id, &data[BEACON_START_INDEX], sizeof(beacon_id)) == TRUE))
  {
    return TRUE;
  }
  return FALSE;
}

// Filter if it is a beacon.
bool simpleBLEFilterIsSmart(uint8 *data, uint8 dataLen)
{
  if ((osal_memcmp(isSmart, &data[BEACON_ISSMART_INDEX], sizeof(isSmart)) == TRUE))
  {
    return TRUE;
  }
  return FALSE;
}

// Filter if it is a beacon.
BLE_DEVICE_TYPE simpleBLEFilterDeviceType(uint8 *data, uint8 dataLen)
{
  VOID dataLen;
  BLE_DEVICE_TYPE deviceType = (BLE_DEVICE_TYPE)data[BEACON_DEVICE_TYPE_INDEX];
  return deviceType;
}

void central_key_press_process_callback(uint8 key_cnt_number)
{
  key_press_callback_central(key_cnt_number);
  return;
}
