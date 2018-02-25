#include "simple_key.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include <ti/sysbios/knl/Clock.h>
#include "simple_led.h"
#include "util.h"
#include <Board.h>
#include "board_key.h"

static void processKeyEvent(uint8_t keyPressed)
{
    ledToggle(LED_INDEX_0);
}

void keyInit()
{
    Board_initKeys(processKeyEvent);
}