#ifndef __SIMPLE_STATE_CONTROL_H
#define __SIMPLE_STATE_CONTROL_H
#include "hci.h"

#ifdef PLUS_OBSERVER
// Maximum number of scan responses
#define DEFAULT_MAX_SCAN_RES                  50//8
// Scan duration in ms
#define DEFAULT_SCAN_DURATION                 5000
// Scan interval in ms
#define DEFAULT_SCAN_INTERVAL                 10
// Scan interval in ms
#define DEFAULT_SCAN_WINDOW                   5
// Discovey mode (limited, general, all)
#define DEFAULT_DISCOVERY_MODE                DEVDISC_MODE_ALL
// TRUE to use active scan
#define DEFAULT_DISCOVERY_ACTIVE_SCAN         TRUE
// TRUE to use white list during discovery
#define DEFAULT_DISCOVERY_WHITE_LIST          FALSE
#endif //#ifdef PLUS_OBSERVER

typedef enum
{
    BEACON_SLEEP = 0,
    BEACON_NORMAL,
    BEACON_COMMUNICATION,
    BEACON_RAPID,
    BEACON_INVALID,
} BEACON_STATUS;

BEACON_STATUS getCurState(void);
void bleStateInit(void);
void bleChangeBeaconState(BEACON_STATUS state, uint16_t keepTime);
void bleAdvControl(uint8_t enable);
void bleSetTxPower(uint8_t level);
void SimpleBLEPeripheral_scanControl(uint8_t enable);

#endif
