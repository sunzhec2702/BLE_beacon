#include "simple_powerControl.h"
#include "simple_stateControl.h"
#include "simple_vibra_sensor.h"
#include "simple_led.h"
#include "simple_peripheral.h"
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>

#define HOUR_CHECK_SEC (1 * 60 * 60) // 1 Hour
static uint32_t wakeUpSecLeft = DEFAULT_WAKE_TIME_SECOND;

/*
// Power Notify Object for wake-up callbacks
static Power_NotifyObj powerEventNotifyObj;
uint32_t powerEventCallback(uint32_t eventType, uint32_t clientArg)
{
  tempEvent = eventType;
  if (eventType == PowerCC26XX_ENTERING_STANDBY)
  {
    pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 1);
    return 0;
  }
  else if (eventType == PowerCC26XX_AWAKE_STANDBY_LATE)
  {
    //pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 1);
    return 0;
  }
  else
    return 0;
}
*/
void powerControlInit()
{
    // TODO: maybe need to restore from SNV.
        // Receive callback when device wakes up from Standby Mode.
    //Power_registerNotify(&powerEventNotifyObj, PowerCC26XX_ENTERING_STANDBY|PowerCC26XX_AWAKE_STANDBY_LATE, 
                         //(Power_NotifyFxn)powerEventCallback, 
                         //NULL);
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
        }
        if (getVibraEnableStatus() == false)
            vibraIntControl(true);
    }
}

void updateWakeUpSecLeft()
{
    wakeUpSecLeft--;
    bleSysConfig.wakeUpSecLeft = wakeUpSecLeft;
    hourEventCheck();
    if (wakeUpSecLeft <= 0)
    {
        DEBUG_STRING("WakeUpLeft=0, Sleeping\r\n");
        resetWakeUpSecLeft();
        SimpleBLEPeripheral_enqueueMsg(SBP_BEACON_STATE_CHANGE_EVT, BEACON_SLEEP, NULL);
    }
}
