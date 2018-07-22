#include "simple_powerControl.h"
#include "simple_stateControl.h"

static uint32_t wakeUpSecLeft = DEFAULT_WAKE_TIME_SECOND;

void powerControlInit()
{
    // TODO: maybe need to restore from SNV.
}

void resetWakeUpSecLeft()
{
    wakeUpSecLeft = DEFAULT_WAKE_TIME_SECOND;
    bleSysConfig.wakeUpSecLeft = wakeUpSecLeft;
}

void updateWakeUpSecLeft()
{
    wakeUpSecLeft--;
    bleSysConfig.wakeUpSecLeft = wakeUpSecLeft;

    if (wakeUpSecLeft <= 0)
    {
        DEBUG_STRING("WakeUpLeft=0, Sleeping\r\n");
        resetWakeUpSecLeft();
        bleChangeBeaconState(BEACON_SLEEP, 0);
    }
}
