#ifndef __SIMPLE_STATE_CONTROL_H
#define __SIMPLE_STATE_CONTROL_H

#include "hci.h"

typedef enum
{
    BEACON_NORMAL = 0,
    BEACON_RAPID,
    BEACON_COMMUNICATION,
    BEACON_SLEEP,
} BEACON_STATUS;

void bleChangeBeaconState(BEACON_STATUS state);
void bleAdvControl(uint8_t enable);
void bleSetTxPower(uint8_t level);

#endif
