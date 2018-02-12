#include "simple_beacon_common.h"
#include "simple_led.h"
#include "Board.h"

void simple_beacon_drivers_init()
{
    // LED related initial.
    ledInit();
    ledBlinkWithParameters(Board_LED0, LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 5);

    // Key Setup.
    
    return;
}