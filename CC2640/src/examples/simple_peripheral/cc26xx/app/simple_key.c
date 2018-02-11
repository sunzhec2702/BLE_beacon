#include "simple_key.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include <Board.h>

static PIN_Handle keyPinHandle;
static PIN_State  keyPinStatus;

const PIN_Config keyPinList[] = {
    #if (BOARD_TYPE == PRODUCT_BOARD)
    Board_KEY_SELECT | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN  | PIN_PULLDOWN,                    /* Button is active high          */
    #elif (BOARD_TYPE == DEVELOP_BOARD)
    Board_KEY_SELECT | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN  | PIN_PULLUP | PIN_HYSTERESIS,     /* Button is active low          */
    #endif
    PIN_TERMINATE
};

void keyInit()
{

}

void keyPressedCB()
{

}