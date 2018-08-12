#ifndef __SIMPLE_SCAN_PROCESS_H
#define __SIMPLE_SCAN_PROCESS_H
#include "gap.h"


#ifdef PLUS_OBSERVER

#define DEFAULT_SCAN_PERIOD (60000) // 1 min
#define DEFAULT_SCAN_TIME   (DEFAULT_SCAN_PERIOD / DEFAULT_SCAN_DURATION)

// Maximum number of scan responses
#define DEFAULT_MAX_SCAN_RES                  50 //8
// Scan duration in ms
#define DEFAULT_SCAN_DURATION                 400
// Scan interval in ms
#define DEFAULT_SCAN_INTERVAL                 400
// Scan interval in ms
#define DEFAULT_SCAN_WINDOW                   400
// Discovey mode (limited, general, all)
#define DEFAULT_DISCOVERY_MODE                DEVDISC_MODE_ALL
// TRUE to use active scan
#define DEFAULT_DISCOVERY_ACTIVE_SCAN         TRUE
// TRUE to use white list during discovery
#define DEFAULT_DISCOVERY_WHITE_LIST          FALSE

void scanDevInfoCB(gapDeviceInfoEvent_t* devInfo);
bool filterStationCRC(uint8_t *data);
uint8_t filterCMD(uint8_t *data);
uint8_t checkSendSource(uint8_t *data);
bool filterBeacon(uint8_t *data);
bool filterCommFlag(uint8_t *data);
bool filterMacCRC(uint8_t *data, uint8_t *macAddr);
void scanDoneCB(gapDevDiscEvent_t *data);
void scanProcessInit(void);
void scanProcessControl(uint8_t enable);
void updateScanInterval(uint16_t scanDuration, uint16_t scanInterval, uint16_t scanWindow);
#endif //#ifdef PLUS_OBSERVER

#endif
