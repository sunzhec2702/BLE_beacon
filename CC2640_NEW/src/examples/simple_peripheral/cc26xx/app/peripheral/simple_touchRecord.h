#ifndef __SIMPLE_TOUCH_RECORD_H
#define __SIMPLE_TOUCH_RECORD_H
#include "hal_types.h"

bool readMacFromFlash(uint8_t macIndex, uint8_t *macData);
uint8_t touchRecordGetMacNum(void);
bool touchRecordAddMac(uint8_t *macAddr);
bool touchRecordReset(void);
void touchRecordInit(void);
void touchRecordScanDoneCallback(void);
bool touchRecordOneTimeMacCheck(uint8_t *macAddr);
void touchSecEventToLatest(void);
void touchRecordSecEvent(void);
void touchRecordGotAPair(uint8_t *macAddr);
#endif
