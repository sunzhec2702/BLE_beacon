#include "simple_powerControl.h"
#include "simple_stateControl.h"
#include "simple_vibra_sensor.h"

#define HOUR_CHECK_SEC (1 * 60 * 60) // 1 Hour
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

void hourEventCheck()
{
    // Check every one hour
    if (wakeUpSecLeft % (HOUR_CHECK_SEC) == 0)
    {
        if (getVibraStatus() == true)
        {
            DEBUG_STRING("Vibra Triggered\r\n");
            wakeUpSecLeft += HOUR_CHECK_SEC;
            // Re-enable the vibra sensor.
            vibraIntControl(true);
        }
    }
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
    hourEventCheck();
}
