#include "simple_key.h"
#include "board_key.h"
#include "simple_uart.h"
#include "simple_led.h"
#include "simple_nfc.h"
#include "simple_peripheral.h"

static void processKeyEvent(uint8_t keyPressed)
{
    if (keyPressed & KEY_SELECT)
    {
        SimpleBLEPeripheral_keyCallback(keyPressed);
        #if (ENABLE_NFC == 1)
        nfcKeyCallback(keyPressed);
        #endif
        ledToggle(LED_INDEX_0);
        DEBUG_STRING("Hello\r\n");
    }
}

void keyInit()
{
    Board_initKeys(processKeyEvent);
}