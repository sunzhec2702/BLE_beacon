#include "simple_key.h"
#include "board_key.h"
#include "simple_led.h"
#include <ti/sysbios/knl/Clock.h>
#include "util.h"
#include "simple_peripheral.h"

#define LONG_PRESS_CHK_PERIOD   10
#define LONG_PRESS_POST_PERIOD  800 // LED blink after press.
#define LONG_PRESS_PERIOD       2000 // hold 2s to trigger long press
#define LONG_PRESS_CNT          ((LONG_PRESS_PERIOD - LONG_PRESS_POST_PERIOD) / LONG_PRESS_CHK_PERIOD)

static uint8_t pressCnt = 0;
static Clock_Struct keyLongPressClock;

static void processKeyEvent(uint8_t keyPressed)
{
    if (keyPressed & KEY_SELECT)
    {
        #if (ENABLE_NFC == 1)
        nfcKeyCallback(keyPressed);
        #endif
        if (Util_isActive(&keyLongPressClock) == false)
        {
            DEBUG_STRING("Hello\r\n");
            Util_restartClock(&keyLongPressClock, LONG_PRESS_POST_PERIOD);
        }

    }
}

void keyInit()
{
    Board_initKeys(processKeyEvent);
    Util_constructClock(&keyLongPressClock, keyLongPressCallback, 0, 0, false, 0);
}

void keyLongPressCallback(UArg arg)
{
    if (pressCnt == 0 && PIN_getInputValue(Board_KEY_SELECT) != KEY_PRESSED)
    {
        SimpleBLEPeripheral_enqueueMsg(SBP_KEY_CHANGE_EVT, KEY_SELECT, NULL);
        return;
    }
    if (++pressCnt < LONG_PRESS_CNT)
    {
        if (PIN_getInputValue(Board_KEY_SELECT) != KEY_PRESSED)
        {
            SimpleBLEPeripheral_enqueueMsg(SBP_KEY_CHANGE_EVT, KEY_SELECT, NULL);
            pressCnt = 0;
            return;
        }
        Util_restartClock(&keyLongPressClock, LONG_PRESS_CHK_PERIOD);
    }
    else
    {
        pressCnt = 0;
        SimpleBLEPeripheral_enqueueMsg(SBP_KEY_CHANGE_EVT, KEY_SELECT_LONG, NULL);
        DEBUG_STRING("Long pressed\r\n");
    }
}