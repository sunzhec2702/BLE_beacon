#include "simple_key.h"
#include "board_key.h"
#include "simple_led.h"
#include <ti/sysbios/knl/Clock.h>
#include "util.h"
#include "simple_peripheral.h"

#define TIMER_BIAS              24  // 24 times for 1 second. When chk period is 50ms.
#define LONG_PRESS_CHK_PERIOD   50
#define LONG_PRESS_POST_PERIOD  800 // LED blink after press.
#define LONG_PRESS_PERIOD       1500 // hold 2s to trigger long press
#define LONG_PRESS_CNT          (((LONG_PRESS_PERIOD - LONG_PRESS_POST_PERIOD) / LONG_PRESS_CHK_PERIOD))

static uint8_t pressRecord = 0;
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
            pressRecord = 0;
            DEBUG_STRING("Hello\r\n");
            Util_restartClock(&keyLongPressClock, LONG_PRESS_POST_PERIOD);
        }
        pressRecord++;
    }
}

void keyInit()
{
    Board_initKeys(processKeyEvent);
    Util_constructClock(&keyLongPressClock, keyLongPressCallback, 0, 0, false, 0);
}

void keyStatusResetAndSendEvent(uint8_t event)
{
    Util_stopClock(&keyLongPressClock);
    pressCnt = 0;
    SimpleBLEPeripheral_enqueueMsg(SBP_KEY_CHANGE_EVT, event, &pressRecord);
}

void keyLongPressCallback(UArg arg)
{
    if (PIN_getInputValue(Board_KEY_SELECT) != KEY_PRESSED)
    {
        if (pressCnt < LONG_PRESS_CNT)
        {
            keyStatusResetAndSendEvent(KEY_SELECT);
        }
        else
        {
            keyStatusResetAndSendEvent(KEY_SELECT_LONG);
        }
    }
    else
    {
        pressCnt++;
        if (pressCnt >= LONG_PRESS_CNT)
        {
            keyStatusResetAndSendEvent(KEY_SELECT_LONG);
        }
        else
        {
            Util_restartClock(&keyLongPressClock, LONG_PRESS_CHK_PERIOD);
        }
    }
    return;
}