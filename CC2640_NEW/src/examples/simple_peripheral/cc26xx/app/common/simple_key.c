#include "simple_key.h"
#include "board_key.h"
#include "simple_uart.h"
#include "simple_led.h"
#include "simple_nfc.h"
#include <ti/sysbios/knl/Clock.h>
#include "util.h"
#include "simple_peripheral.h"

#define LONG_PRESS_CHK_PERIOD   50
#define LONG_PRESS_POST_PERIOD  200
#define LONG_PRESS_CNT      40
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
        SimpleBLEPeripheral_keyCallback(KEY_SELECT);
    }

    if (pressCnt++ < LONG_PRESS_CNT)
    {
        if (PIN_getInputValue(Board_KEY_SELECT) != KEY_PRESSED)
        {
            pressCnt = 0;
            return;
        }
        Util_restartClock(&keyLongPressClock, LONG_PRESS_CHK_PERIOD);
    }
    else
    {
        pressCnt = 0;
        SimpleBLEPeripheral_keyCallback(KEY_SELECT_LONG);
        DEBUG_STRING("Long pressed\r\n");
    }
}