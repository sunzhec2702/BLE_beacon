#include "simple_beacon.h"
#include "simple_led.h"
#include "simple_key.h"
#include "simple_vibra_sensor.h"
#include "simple_beacon_status.h"
#include "simple_touchRecord.h"
#include "simple_stateControl.h"
#include "simple_powerControl.h"
#include "simple_scanProcess.h"
#include "Board.h"
#include <ti/drivers/power/PowerCC26XX.h>

void simple_beacon_drivers_init()
{
    simpleBleStatusInit();
    bleStateInit();
    scanProcessInit();

    // LED related initial.
    //ledInit();
    pwmLedInit();
    pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 3);
    powerControlInit();
    // Key Setup.
    keyInit();
    // Vibra Sensor
    vibraSensorInit();
    // Touch Record
    touchRecordInit();
    return;
}