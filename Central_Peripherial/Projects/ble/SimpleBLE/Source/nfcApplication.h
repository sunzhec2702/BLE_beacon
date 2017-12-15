#ifndef __NFC_APPLICATION_H_
#define __NFC_APPLICATION_H_

#include "simpleble.h"
#include "OSAL.h"

#define NFC_START_EVT       0x0001
#define NFC_START_INITIATOR 0x0002
#define NFC_START_TARGET    0x0004
#define NFC_START_CARD      0x0008


void nfcAppInit(uint8 task_id);
uint16 nfcAppProcessEvent(uint8 task_id, uint16 events);


void nfcWorkAsInitiator(uint16 timeout);
void nfcWorkAsTarget(uint16 timeout);
void nfcWorkAsCard(void);

#endif
