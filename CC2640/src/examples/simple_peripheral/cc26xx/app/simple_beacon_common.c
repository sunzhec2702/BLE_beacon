#include "simple_beacon_common.h"
#include "simple_led.h"
#include "Board.h"

void simple_beacon_drivers_init()
{
    // LED related initial.
    ledInit();
    ledBlinkWithParameters(LED_INDEX_0, LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 100);
    //ledOn(LED_INDEX_0);

    // Key Setup.
    // keyInit();
    return;
}