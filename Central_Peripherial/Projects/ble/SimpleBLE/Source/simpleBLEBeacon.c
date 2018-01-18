#include "simpleBLEBeacon.h"
#include "simpleBLECentral.h"
#include "npi.h"
#include "simpleBLELED.h"

#define MAC_SUM_BYTE    0xBF

#if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
uint8 advertData_iBeacon[ADVERTISE_SIZE] =
{
  0x02, // length of this data, 0
  GAP_ADTYPE_FLAGS, // 1
  GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED, // 2
  0x1A, // length of this data 26byte, 3
  GAP_ADTYPE_MANUFACTURER_SPECIFIC, // 4
  /*Apple Pre-Amble*/
  0x4C, // 5
  0x00, // 6
  0x02, // 7
  0x15, // 8
  /*Device UUID (16 Bytes)*/
  0x53, 0x4D, 0x54, // SMT 3 Bytes.
  0x00, // 12 reserved
  0x00, // 13 reserved.
  MAJOR_HW_VERSION, MAJOR_SW_VERSION, MINOR_SW_VERSION, // 14, 15, 16, HW/SW version
  BLE_BEACON, // 17 Device Type 3 bytes.

  BLE_CMD_POWER_ON, //18

  SCAN_ADV_TRANS_MIN_PERIOD, //19 How often the beacon will scan for the station in power on mode.
  DEFAULT_WAKE_TIME_MINS, //20 The period which the device keeps poweron even without scanning any data.
  SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_1, //21 How often the beacon will scan for the station in power off mode.
  SBP_PERIODIC_OFF_SCAN_PERIOD_SEC_2, //22 The Data will be ((SEC_1 << 8) + SEC_2)

  /*Specific Data*/
  0x00, // 23
  0x00, // 24, Station Index
  /*Major Value (2 Bytes)*/
  0x00, // 25 for min left
  0x00, // 26 for index 
  /*Minor Value (2 Bytes)*/
  0x00, // 27 FlagByte. bit7 rapid bit6 low_bat
  0x00, // 28 Battery Value

  0xCD //29  /*Measured Power*/
};

extern SYS_CONFIG sys_config;
extern uint8 simpleBLETaskId;

// Only be used in OFF STATUS
void scan_adv_event_callback(uint8 role)
{
    if (role == BLE_ROLE_CENTRAL)
    {
        if (getCurrentBLEStatus() == BLE_STATUS_ON_SCAN)
        {
            if (get_led_toggle_status() == TRUE)
            {
                osal_start_timerEx(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT, PERIPHERAL_START_LED_TOGGLE_PERIOD_ON + PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF);
            }
            else
            {
                set_beacon_status(BLE_STATUS_ON_SCAN, BLE_STATUS_ON_ADV, TRUE);
            }
        }
    }
    else if (role == BLE_ROLE_PERIPHERAL)
    {
        set_beacon_status(BLE_STATUS_ON_ADV, BLE_STATUS_ON_SCAN, TRUE);
    }
}

static void retrive_info_from_station_adv(uint8 *pEvtData, bool use_hardcode_value)
{
    /*
    sys_config.stationIndex = (pEvtData[ADV_STATION_INDEX_1] << 8) + pEvtData[ADV_STATION_INDEX_2];
    sys_config.powerOnPeriod = pEvtData[ADV_STATION_POWER_ON_PERIOD_INDEX];
    sys_config.powerOnScanInterval = pEvtData[ADV_STATION_ON_SCAN_INTERVAL_INDEX];
    sys_config.powerOffScanInterval = (pEvtData[ADV_STATION_OFF_SCAN_INTERVAL_INDEX_1] << 8) + pEvtData[ADV_STATION_OFF_SCAN_INTERVAL_INDEX_2];
    */
    sys_config.stationIndex = (pEvtData[ADV_STATION_INDEX_1] << 8) + pEvtData[ADV_STATION_INDEX_2];
    if (use_hardcode_value == TRUE)
    {
        sys_config.powerOnPeriod = DEFAULT_WAKE_TIME_MINS;
        sys_config.powerOnScanInterval = SCAN_ADV_TRANS_MIN_PERIOD;
        sys_config.powerOffScanInterval = SBP_PERIODIC_FAST_OFF_SCAN_PERIOD_MS;
    }
    else
    {
        sys_config.powerOnPeriod = pEvtData[ADV_STATION_POWER_ON_PERIOD_INDEX];
        sys_config.powerOnScanInterval = pEvtData[ADV_STATION_ON_SCAN_INTERVAL_INDEX];
        sys_config.powerOffScanInterval = (pEvtData[ADV_STATION_OFF_SCAN_INTERVAL_INDEX_1] << 8) + pEvtData[ADV_STATION_OFF_SCAN_INTERVAL_INDEX_2];
    }
}

// Check if the adv is only to specific beacon.
static bool simpleBLEStationMacFilter(uint8 *pEvtData)
{
    #ifdef DEBUG_MAC_FILTER
    return TRUE;
    #endif
    if (pEvtData[ADV_SPECIFIC_MAC_LAST_4] == 0x00 &&
        pEvtData[ADV_SPECIFIC_MAC_LAST_3] == 0x00 &&
        pEvtData[ADV_SPECIFIC_MAC_LAST_2] == 0x00 &&
        pEvtData[ADV_SPECIFIC_MAC_LAST_1] == 0x00 &&)
    {
        return TRUE;
    }
    updateSysConfigMac();
    if (pEvtData[ADV_SPECIFIC_MAC_LAST_4] == sys_config.mac_addr[2] && 
        pEvtData[ADV_SPECIFIC_MAC_LAST_3] == sys_config.mac_addr[3] &&
        pEvtData[ADV_SPECIFIC_MAC_LAST_2] == sys_config.mac_addr[4] &&
        pEvtData[ADV_SPECIFIC_MAC_LAST_1] == sys_config.mac_addr[5])
    {
        return TRUE;
    }
    return FALSE;
}

// Filter the MAC Check
static bool simpleBLEStationMacCRCCheck(uint8 *pEvtData, uint8 *addr)
{
    #ifdef DEBUG_MAC_CRC
    return TRUE;
    #endif
    // This addr is reversed.
    uint8 sum = 0;
    for (uint8 i = 0; i < B_ADDR_LEN; i++)
    {
        sum += addr[i];
    }
    sum += MAC_SUM_BYTE;
    sum = sum % 0xFF;
    if (pEvtData[ADV_STATION_MAC_CRC_BYTE] == sum)
        return TRUE;
    return FALSE;
}

void scan_device_info_callback(gapCentralRoleEvent_t *pEvent)
{
    if (simpleBLEFilterSelfBeacon(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == FALSE || 
        simpleBLEFilterIsSmart(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == FALSE)
    {
        return;
    }
    {
        DEBUG_PRINT("Found Smart Device\r\n");
        // Our adv content. do further process.
        if (getCurrentBLEStatus() == BLE_STATUS_ON_SCAN)
        {
            if (simpleBLEFilterDeviceType(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == BLE_STATION_ADV &&
                simpleBLEStationMacCRCCheck(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.addr) == TRUE &&
                simpleBLEStationMacFilter(pEvent->deviceInfo.pEvtData) == TRUE)
            {
                DEBUG_PRINT("Station ADV\r\n");
                DEBUG_VALUE("CMD: ", pEvent->deviceInfo.pEvtData[ADV_STATION_CMD_INDEX], 10);
                DEBUG_VALUE("StationIndex will update to ", advStationIndex, 10);
                DEBUG_VALUE("MinLeft : ", sys_config.minLeft, 10);
                DEBUG_VALUE("PowerOnPeriod", sys_config.powerOnPeriod, 10);
                DEBUG_VALUE("powerOnScanInterval", sys_config.powerOnScanInterval, 10);
                DEBUG_VALUE("powerOffScanInterval", sys_config.powerOffScanInterval, 10);
                uint8 cmd = pEvent->deviceInfo.pEvtData[ADV_STATION_CMD_INDEX];
                switch (cmd)
                {
                    case BLE_CMD_POWER_OFF:
                    // Do nothing.
                    /*
                    retrive_info_from_station_adv(pEvent->deviceInfo.pEvtData);
                    sys_config.stationIndex = 0;
                    sys_config.status = BLE_STATUS_OFF;
                    simpleBLE_SaveAndReset();
                    */
                    break;
                    case BLE_CMD_POWER_ON:
                    DEBUG_VALUE("current stationIndex: ", sys_config.stationIndex, 10);
                    retrive_info_from_station_adv(pEvent->deviceInfo.pEvtData, TRUE);
                    // Reset the wake time left mins.
                    sys_config.minLeft = sys_config.powerOnPeriod;
                    break;
                    default:
                    break;
                }
            }
            else if (simpleBLEFilterDeviceType(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == BLE_BEACON)
            {
                DEBUG_PRINT("Beacon ADV\r\n");
                uint16 advStationIndex = (pEvent->deviceInfo.pEvtData[ADV_STATION_INDEX_1] << 8) + pEvent->deviceInfo.pEvtData[ADV_STATION_INDEX_2];
                if (sys_config.stationIndex < advStationIndex)
                {
                    DEBUG_PRINT("StationIndex Update\r\n");
                    sys_config.stationIndex = advStationIndex;
                    // Reset the wake time left mins.
                    sys_config.minLeft = sys_config.powerOnPeriod;
                }
            }
        }
        else if (getCurrentBLEStatus() == BLE_STATUS_OFF)
        {
            if (simpleBLEFilterDeviceType(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == BLE_STATION_ADV &&
                simpleBLEStationMacCRCCheck(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.addr) == TRUE &&
                simpleBLEStationMacFilter(pEvent->deviceInfo.pEvtData) == TRUE)
            {
                DEBUG_PRINT("OFF: Station ADV\r\n");
                DEBUG_VALUE("CMD: ", cmd, 10);
                DEBUG_VALUE("StationIndex = ", advStationIndex, 10);
                DEBUG_VALUE("PowerOnPeriod", sys_config.powerOnPeriod, 10);
                DEBUG_VALUE("powerOnScanInterval", sys_config.powerOnScanInterval, 10);
                DEBUG_VALUE("powerOffScanInterval", sys_config.powerOffScanInterval, 10);
                DEBUG_VALUE("MinLeft : ", sys_config.minLeft, 10);
                BLE_STATION_CMD cmd = pEvent->deviceInfo.pEvtData[ADV_STATION_CMD_INDEX];
                switch (cmd)
                {
                    case BLE_CMD_POWER_OFF:
                    // Do nothing.
                    /*
                    retrive_info_from_station_adv(pEvent->deviceInfo.pEvtData);
                    sys_config.stationIndex = 0;
                    sys_config.status = BLE_STATUS_OFF;
                    simpleBLE_SaveAndReset();
                    */
                    break;
                    case BLE_CMD_POWER_ON:
                    DEBUG_VALUE("current stationIndex: ", sys_config.stationIndex, 10);
                    retrive_info_from_station_adv(pEvent->deviceInfo.pEvtData, TRUE);
                    // Reset the wake time left mins.
                    sys_config.minLeft = sys_config.powerOnPeriod;
                    set_beacon_status(BLE_STATUS_OFF, BLE_STATUS_ON_ADV, TRUE);
                    break;
                    case BLE_CMD_LED_BLINK:
                    led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, BUTTON_LED_TOGGLE_COUNT, 0);       
                    case BLE_CMD_CHECK_BATTERY:
                    uint8 battery_threshold = pEvent->deviceInfo.pEvtData[ADV_STATION_BATTERY_THRESHOLD];
                    if (check_low_battery(battery_threshold) == TRUE)
                    {
                        enter_low_battery_mode();
                    }
                    break;
                    case BLE_CMD_UPDATE_CONFIG:
                    retrive_info_from_station_adv(pEvent->deviceInfo.pEvtData, FALSE);
                    break;
                    default:
                    break;
                }
            }
            else if (simpleBLEFilterDeviceType(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == BLE_BEACON)
            {
                DEBUG_PRINT("Beacon ADV\r\n");
                uint16 advStationIndex = (pEvent->deviceInfo.pEvtData[ADV_STATION_INDEX_1] << 8) + pEvent->deviceInfo.pEvtData[ADV_STATION_INDEX_2];
                if (sys_config.stationIndex < advStationIndex)
                {
                    DEBUG_PRINT("StationIndex Update\r\n");
                    sys_config.stationIndex = advStationIndex;
                    // Reset the wake time left mins.
                    sys_config.minLeft = sys_config.powerOnPeriod;
                    set_beacon_status(BLE_STATUS_OFF, BLE_STATUS_ON_ADV, TRUE);
                }
            }
        }
    }
}

bool scan_discovery_callback(void)
{
    if (getCurrentBLEStatus() == BLE_STATUS_ON_SCAN && getScanTimeLeft() == 0)
    {
      DEBUG_PRINT("ON_SCAN, TimeLeft 0\r\n");
      osal_set_event(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT);
    }
    else if (getCurrentBLEStatus() == BLE_STATUS_OFF && getScanTimeLeft() == 0)
    {
      DEBUG_PRINT("OFF, TimeLeft 0\r\n");
      resetScanTimeLeft();
      osal_start_timerEx(simpleBLETaskId, SBP_WAKE_EVT, (sys_config.powerOffScanInterval * 1000));
    }
    else
    {
      simpleBLEStartScan();
    }
    return TRUE;
}

void key_press_callback_central(uint8 key_cnt_number)
{
    if (getCurrentBLEStatus() == BLE_STATUS_OFF)
    {
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LED_DELAY);
        return;
    }

    if (key_cnt_number == 0)
    {
        return;
    }

    DEBUG_PRINT("ON_SCAN, KEY CALLBACK\r\n");
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
    sys_config.key_pressed_in_scan = TRUE;
    // After scan finish, the beacon will trigger SCAN_ADV_TRANS automatically.
    //osal_set_event(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT);
    return;
}

void set_beacon_status(BLE_STATUS current_status, BLE_STATUS target_status, bool reset)
{
    switch (target_status)
    {
      case BLE_STATUS_OFF:
      case BLE_STATUS_ON_SCAN:
      if (current_status == BLE_STATUS_ON_ADV)
      {
        sys_config.stationIndex = (advertData_iBeacon[ADV_STATION_INDEX_1] << 8) + advertData_iBeacon[ADV_STATION_INDEX_2];
        sys_config.minLeft = advertData_iBeacon[ADV_MIN_LEFT_BYTE];
        sys_config.bootup_blink = FALSE;
      }
      break;
      case BLE_STATUS_ON_ADV:
      break;
      default:
      break;
    }
    sys_config.status = target_status;
    if (reset == TRUE)
    {
        simpleBLE_SaveAndReset();
    }
    else
    {
        simpleBLE_WriteAllDataToFlash();
    }
    return;
}

// For beacon, the features are LED blink 2 times and ON_ADV
void reset_to_no_battery_status()
{
    sys_config.status = BLE_STATUS_ON_SCAN;
    sys_config.bootup_blink = TRUE;
    simpleBLE_WriteAllDataToFlash();
    return;
}

uint8 read_battery_value()
{
  uint32 adc_read = 0;
  uint8 battery_voltage = 0;
  for (uint8 i = 0; i < 16; i++)
  {
    HalAdcSetReference(HAL_ADC_REF_125V);
    adc_read += HalAdcRead(HAL_ADC_CHANNEL_VDD, HAL_ADC_RESOLUTION_10);
  }
  adc_read = adc_read >> 4;
  battery_voltage = adc_read * 3 * 125 / 511 / 10;
  DEBUG_VALUE("adc value : ", adc_read, 10);
  DEBUG_VALUE("Battery Value : ", battery_voltage * 10, 10);
  return battery_voltage;
}

bool check_low_battery(uint8 threshold)
{
  uint8 battery_voltage = read_battery_value();
  uint8 battery_threshold = (threshold == 0) ? BATTERY_LOW_THRESHOLD:threshold;

  if (g_sleepFlag == FALSE && battery_voltage < battery_threshold)
  {
    return TRUE;
  }
  return FALSE;
}

void enter_low_battery_mode()
{
  // Low Battery Mode. Enter OFF mode.
  /*
  sys_config.status = BLE_STATUS_OFF;
  simpleBLE_SaveAndReset();
  */
  DEBUG_PRINT("Enter Low Battery Mode\r\n");
  low_power_state = TRUE;
  if (sys_config.role = BLE_ROLE_PERIPHERAL)
  {
    advertData_iBeacon[ADV_FLAG_BYTE] |= 0x40;
    // Stop advertising.
    advertise_control(FALSE);
  }
  else if (sys_config.role == BLE_ROLE_CENTRAL)
  {
      return;
  }
  // LED Blinking.
  led_toggle_set_param(PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_ON, PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_LOW_BAT_LED_TOGGLE_CNT, 0);
}
#endif