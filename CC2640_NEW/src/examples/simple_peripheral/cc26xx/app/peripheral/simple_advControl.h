#ifndef __SIMPLE_ADV_CONTROL_H
#define __SIMPLE_ADV_CONTROL_H

// Adv index
#define BEACON_START_INDEX 5
#define BEACON_ISSMART_INDEX 9

#define MAC_CRC_BYTE            12
#define MAX_XOR_BYTE            13
#define MAC_XOR_ADV_BYTE        19
#define BEACON_DEVICE_TYPE_INDEX 13
#define TOUCH_BEACON_MAC        15

/*
#define ADV_STATION_CMD_INDEX 18
#define ADV_STATION_BATTERY_THRESHOLD 19
#define ADV_STATION_ON_SCAN_INTERVAL_INDEX 19
#define ADV_STATION_POWER_ON_PERIOD_INDEX 20
#define ADV_STATION_OFF_SCAN_INTERVAL_INDEX_1 21
#define ADV_STATION_OFF_SCAN_INTERVAL_INDEX_2 22
#define ADV_STATION_INDEX_1 23
#define ADV_STATION_INDEX_2 24
*/
#define ADV_RECORD_NUM_BYTE 25
#define ADV_MIN_LEFT_BYTE 25
#define ADV_INDEX_BYTE 26

#define ADV_FLAG_BYTE 27
#define ADV_FLAG_RAPID_BIT      7
#define ADV_FLAG_LOW_BAT_BIT    6
#define ADV_FLAG_COMMS_BIT      5

#define ADV_BAT_BYTE 28

#define ADV_SPECIFIC_MAC_LAST_4 25
#define ADV_SPECIFIC_MAC_LAST_3 26
#define ADV_SPECIFIC_MAC_LAST_2 27
#define ADV_SPECIFIC_MAC_LAST_1 28


typedef enum
{
    NORMAL_ADV = 0,
    FIXUUID_ADV = 1,
} ADV_TYPE;

void updateFixUUID(uint8_t *macAddr, uint8_t crcByte);
void updateTargetAdv(ADV_TYPE type);
void applyAdvData(ADV_TYPE tarAdvType);
void updateMacCRCByte(uint8_t crcByte);
void updateRapidBit(uint8_t enable);
void updateComBit(uint8_t enable);
void updateCurTimeLeft(void);
void updateAdvInterval(uint16_t advInterval);
void updateBeaconIndex(void);
void updateBeaconTouchData(uint8_t *macData);
void updateBeaconTouchMac(uint8_t *macAddr);
void resetBeaconTouchInfo(void);
void bleAdvControl(uint8_t enable, bool connectable);
void bleSetTxPower(uint8_t level);

uint8_t* getAdvData(void);
uint8_t* getResData(void);

#endif
