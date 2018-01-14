#ifndef __SIMPLE_BLE_STATION_H_
#define __SIMPLE_BLE_STATION_H_
#include "simpleble.h"
#include "central.h"

#if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
typedef enum
{
    BLE_STATUS_STATION_SCAN = 0,
    BLE_STATUS_STATION_ADV,
    BLE_STATUS_STATION_STATUS_NUM,
} BLE_STATUS;

typedef enum
{
    BLE_SERIAL_CONFIG_CMD_ROLE_CHANGE = 0, // STATION_SCAN <--> STATION_ADV
    BLE_SERIAL_CONFIG_CMD_ADV_DATA, // CHANGE ADV DATA.
    BLE_SERIAL_CONFIG_CMD_ADV_INTERVAL, // CHANGE ADV INTERVAL.
    BLE_SERIAL_CONFIG_CMD_GET_STATUS, // GET CURRENT CONFIG. INCLUDE ROEL/DATA/INTERVAL
    BLE_SERIAL_CONFIG_CMD_NUM,
} BLE_SERIAL_CONFIG_CMD_TYPE;

typedef enum
{
    BLE_SERIAL_GET_ROLE = 0, // STATION_SCAN <--> STATION_ADV
    BLE_SERIAL_GET_ADV_DATA, // CHANGE ADV DATA.
    BLE_SERIAL_GET_ADV_INTERVAL, // CHANGE ADV INTERVAL.
    BLE_SERIAL_GET_MAC,
    BLE_SERIAL_GET_NUM,
} BLE_SERIAL_GET_INFO_TYPE;

typedef enum
{
    BLE_SERIAL_CONFIG_SUCCESS = 0,
    BLE_SERIAL_CONFIG_CONTINUE,
    BLE_SERIAL_CONFIG_FAILED,
} BLE_SERIAL_CONFIG_STATUS;

BLE_SERIAL_CONFIG_STATUS serialConfigParser(uint8 *data, uint16 dataLen);

bool serialConfigProcess(BLE_SERIAL_CONFIG_CMD_TYPE cmdType, uint8 *config, uint16 configLen);
void scan_adv_event_callback(uint8 role);
void scan_device_info_callback(gapCentralRoleEvent_t *pEvent);
bool scan_discovery_callback(void);
void key_press_callback_central(uint8 key_cnt_number);
void serialConfigSendAck(BLE_SERIAL_CONFIG_STATUS status);

void sendWithFrameBuffer(uint8 *data, uint16 dataLen);

#endif

#endif
