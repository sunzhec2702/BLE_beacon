#ifndef __SIMPLE_TOUCH_RECORD_H
#define __SIMPLE_TOUCH_RECORD_H
#include "hal_types.h"

uint8_t touchRecordGetMacNum(void);
bool touchRecordAddMac(uint8_t *macAddr);
bool touchRecordReset(void);
void touchRecordInit(void);
void touchRecordScanDoneCallback(void);
bool touchRecordOneTimeMacCheck(uint8_t *macAddr);
void touchSecEventReset(void);
void touchRecordSecEvent(void);
#endif
