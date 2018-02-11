/* 
 * Use this file to use the GPIO hal driver for CC26xx.
 * Basically we use this file for LED1 LED2 and KEY.
 */
#include "simple_gpio.h"
#include <ti/drivers/gpio/GPIOCC26XX.h>


    Board_DK_LED1       | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW   | PIN_PUSHPULL | PIN_DRVSTR_MAX,     /* LED initially off             */
    Board_DK_LED2       | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW   | PIN_PUSHPULL | PIN_DRVSTR_MAX,     /* LED initially off             */
    #if (BOARD_TYPE == PRODUCT_BOARD)
    Board_KEY_SELECT | PIN_INPUT_EN  | PIN_PULLDOWN,                             /* Button is active high          */
    #elif (BOARD_TYPE == DEVELOP_BOARD)
    Board_KEY_SELECT | PIN_INPUT_EN  | PIN_PULLUP | PIN_HYSTERESIS,                             /* Button is active low          */
    #endif
    Board_NFC_ENABLE | PIN_GPIO_OUTPUT_EN  | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,   