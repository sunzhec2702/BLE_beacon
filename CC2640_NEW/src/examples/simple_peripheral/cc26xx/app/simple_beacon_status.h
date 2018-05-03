#ifndef __SIMPLE_NV_H
#define __SIMPLE_NV_H

typedef enum
{
  BLE_ROLE_PERIPHERAL = 0,
  BLE_ROLE_CENTRAL,
  BLE_ROLE_NUMBER,
} BLE_ROLE;

typedef enum
{
    BLE_STATUS_ON_ADV = 0,
    BLE_STATUS_ON_SCAN,
    BLE_STATUS_OFF,
} BLE_STATUS;

typedef struct 
{
    // Basic Information of Beacon.
    BLE_STATUS status;
    BLE_ROLE role;
    uint8_t macAddr[B_ADDR_LEN];
    int8_t rssi;
    uint8_t rxGain;
    uint8_t txPower;
    // Current Status of Beacon.
    uint8_t bootupBlink;
    uint16_t stationIndex;
    uint8_t beaconIndex;
    uint8_t minLeft;
    bool keyPressedInScan;
    // Configuration From Station ADV
    uint8_t onScanAdvTransPeriod; // ON_SCAN/ON_ADV trans interval. default 10 mins.
    uint8_t onPeriod; // Without new adv data, how long will it last in ON status. default 30 mins.
    uint16_t offScanPeriod; // The scan interval in OFF mode, default 1 hour when power on. Once start adv, change to 5s.
} SYS_CONFIG;

void simpleNVInit(void);
 

#endif
