#ifndef __SIMPLE_SCAN_PROCESS_H
#define __SIMPLE_SCAN_PROCESS_H
#include "gap.h"


void scanDevInfoCB(gapDeviceInfoEvent_t* devInfo);
bool filterStationCRC(uint8_t *data);
uint8_t filterCMD(uint8_t *data);
uint8_t checkSendSource(uint8_t *data);
bool filterCommFlag(uint8_t *data);

#endif
