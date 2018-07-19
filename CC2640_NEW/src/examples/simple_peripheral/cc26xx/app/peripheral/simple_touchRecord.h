#ifndef __SIMPLE_TOUCH_RECORD_H
#define __SIMPLE_TOUCH_RECORD_H
#include "hal_types.h"

uint32_t touchRecordGetMacNum(void);
void touchRecordAddMac(uint8_t macAddr);
void touchRecordReset(void);
void touchRecordInit(void);

#endif
