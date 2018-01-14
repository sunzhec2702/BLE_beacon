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
} BLE_STATION_CMD;

void scan_adv_event_callback(uint8 role);
void scan_device_info_callback(gapCentralRoleEvent_t *pEvent);
bool scan_discovery_callback(void);
void key_press_callback_central(uint8 key_cnt_number);
#endif

#endif
