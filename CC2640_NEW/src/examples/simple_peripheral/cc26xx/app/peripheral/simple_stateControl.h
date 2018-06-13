#ifndef __SIMPLE_STATE_CONTROL_H
#define __SIMPLE_STATE_CONTROL_H

#include "hci.h"

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
