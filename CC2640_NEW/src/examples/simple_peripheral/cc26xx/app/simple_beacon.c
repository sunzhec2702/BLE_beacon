#include "simple_beacon.h"
#include "simple_led.h"
#include "simple_key.h"
#include "simple_beacon_status.h"
#include "Board.h"


void simple_beacon_drivers_init()
{
    simpleNVInit();
    // LED related initial.
    ledInit();
    ledBlinkWithParameters(LED_INDEX_0, LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 3);
    // Key Setup.
    keyInit();
    return;
}