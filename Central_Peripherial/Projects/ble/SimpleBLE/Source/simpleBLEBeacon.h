#ifndef __SIMPLE_BLE_BEACON_H
#define __SIMPLE_BLE_BEACON_H
#include "simpleble.h"
#include "central.h"

#if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
typedef enum
{
    BLE_STATUS_ON_ADV = 0,
    BLE_STATUS_ON_SCAN,
    BLE_STATUS_OFF,
} BLE_STATUS;

typedef enum
{
  BLE_CMD_POWER_ON = 1,
  BLE_CMD_POWER_OFF,
  BLE_CMD_LED_BLINK,
  BLE_CMD_CHECK_BATTERY,
  BLE_CMD_UPDATE_CONFIG,
  BLE_CMD_NUMBER,
} BLE_STATION_CMD;

void scan_adv_event_callback(uint8 role);
static void retrive_info_from_station_adv(uint8 *pEvtData, bool use_hardcode_value);
void scan_device_info_callback(gapCentralRoleEvent_t *pEvent);
bool scan_discovery_callback(void);
void key_press_callback_central(uint8 key_cnt_number);
bool simpleBLEStationMacCRCCheck(uint8 *pEvtData, uint8 *addr);
void set_beacon_status(BLE_STATUS current_status, BLE_STATUS target_status, bool reset);
void reset_to_no_battery_status(uint8 role);
uint8 read_battery_value(void);
bool check_low_battery(uint8 battery_value);
void enter_low_battery_mode(void);


#endif

#endif
