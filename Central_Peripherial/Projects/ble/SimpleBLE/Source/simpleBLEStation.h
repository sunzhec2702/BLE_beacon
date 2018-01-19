#ifndef __SIMPLE_BLE_STATION_H_
#define __SIMPLE_BLE_STATION_H_
#include "central.h"
#include "simpleble.h"

#if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
typedef struct
{
    uint8 stationRole;
    uint8 stationAdvInterval;
    uint8 macAddr[B_ADDR_LEN];
    uint8 stationAdvData[30];
} StationInfo;

typedef struct
{
    uint8 stationAdvInterval;
    uint8 stationAdvData[30];
} StationAdvConfig;

typedef enum
{
    BLE_STATUS_STATION_SCAN = 0,
    BLE_STATUS_STATION_ADV,
    BLE_STATUS_STATION_STATUS_NUM,
} BLE_STATUS;

typedef enum
{
    BLE_SERIAL_CONFIG_CMD_ROLE_CHANGE = 0, // STATION_SCAN <--> STATION_ADV
    BLE_SERIAL_CONFIG_CMD_ADV, // Change the ADV Interval and ADV data
    BLE_SERIAL_CONFIG_CMD_GET_STATUS, // GET CURRENT CONFIG. INCLUDE ROEL/DATA/INTERVAL
    BLE_SERIAL_CONFIG_CMD_NUM,
} BLE_SERIAL_CONFIG_CMD_TYPE;

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
void sendStationInfo(void);

#endif

#endif
