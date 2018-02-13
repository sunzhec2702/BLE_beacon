#include "simple_key.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include <ti/sysbios/knl/Clock.h>
#include "simple_led.h"
#include "util.h"
#include <Board.h>

#define KEY_DEBOUNCE_TIMEOUT  20

static PIN_Handle keyPinHandle;
static PIN_State keyPinStatus;
static Clock_Struct keyDebounceClock;

static uint8_t keysPressed;

extern void appKeyPressedCallback(uint8_t keyPressed);

const PIN_Config keyPinList[] = {
#if (BOARD_TYPE == PRODUCT_BOARD)
    Board_KEY_SELECT | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN | PIN_PULLDOWN, /* Button is active high          */
#elif (BOARD_TYPE == DEVELOP_BOARD)
    Board_KEY_SELECT | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN | PIN_PULLUP | PIN_HYSTERESIS, /* Button is active low          */
#endif
    PIN_TERMINATE};

static void keyPressedCB(PIN_Handle hPin, PIN_Id pinIbd)
{
    keysPressed = 0;
    if ( PIN_getInputValue(Board_KEY_SELECT) == KEY_PRESSED )
    {
        keysPressed |= KEY_SELECT;
    }
    Util_startClock(&keyDebounceClock);
}

static void Board_keyChangeHandler(UArg a0)
{
    uint8_t debouncedKeyPressed = 0;
    if ((keysPressed & KEY_SELECT) && (PIN_getInputValue(Board_KEY_SELECT) == KEY_PRESSED))
    {
        debouncedKeyPressed |= KEY_SELECT;
    }
    ledToggle(LED_INDEX_0);
    appKeyPressedCallback(debouncedKeyPressed);
}


void keyInit()
{
    // Initialize KEY pins. Enable int after callback registered
    keyPinHandle = PIN_open(&keyPinStatus, keyPinList);
    PIN_registerIntCb(keyPinHandle, keyPressedCB);
    #if (BOARD_TYPE == PRODUCT_BOARD)
    PIN_setConfig(keyPinHandle, PIN_BM_IRQ, Board_KEY_SELECT | PIN_IRQ_POSEDGE); // Rising Edge
    PIN_setConfig(keyPinHandle, PINCC26XX_BM_WAKEUP, Board_KEY_SELECT | PINCC26XX_WAKEUP_POSEDGE);
    #elif (BOARD_TYPE == DEVELOP_BOARD)
    PIN_setConfig(keyPinHandle, PIN_BM_IRQ, Board_KEY_SELECT | PIN_IRQ_NEGEDGE); // Falling Edge.
    PIN_setConfig(keyPinHandle, PINCC26XX_BM_WAKEUP, Board_KEY_SELECT | PINCC26XX_WAKEUP_NEGEDGE);
    #endif
    // Setup keycallback for keys
    Util_constructClock(&keyDebounceClock, Board_keyChangeHandler, KEY_DEBOUNCE_TIMEOUT, 0, false, 0);

  // Set the application callback
  /*
  appKeyChangeHandler = appKeyCB;
  */
}