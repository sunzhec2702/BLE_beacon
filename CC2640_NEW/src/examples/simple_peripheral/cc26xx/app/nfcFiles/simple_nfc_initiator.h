#ifndef __SIMPLE_NFC_INITIATOR_H
#define __SIMPLE_NFC_INITIATOR_H
#include "nfc/nfc.h"

int nfcWorkAsInitiator(uint16_t timeout, nfc_device *curPnd, nfc_context *curContext);

#endif
