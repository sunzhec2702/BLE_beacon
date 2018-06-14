#include "simple_led.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include "util.h"
#include <ti/sysbios/knl/Clock.h>
#include <inc/hw_ints.h>
#include <Board.h>

static PIN_State ledPinStatus;
static Clock_Struct ledBlinkClock[BOARD_LED_NUM];

static LedBlinkStruct ledBlinkStruct[BOARD_LED_NUM] = 
{
    {
        .ledBlinkIO = Board_LED0,
    },
    {
        .ledBlinkIO = Board_LED1,
    }
};

const PIN_Config ledPinList[] = {
    Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
#if (BOARD_TYPE == DEVELOP_BOARD)
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
#elif (BOARD_TYPE == PRODUCT_BOARD)
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX,
#endif
    PIN_TERMINATE
    };

static void ledBlinkCallback(UArg ledIndex)
{
    uint16_t targetPeriod = 0;
#if (BOARD_TYPE == DEVELOP_BOARD)
    if (ledBlinkStruct[ledIndex].ledBlinkTimes <= 0)
    {
        //ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_OFF;
        ledBlinkStruct[ledIndex].ledBlinkTimes = 0;
        ledBlinkStruct[ledIndex].ledBlinkOnPeriod = 0;
        ledBlinkStruct[ledIndex].ledBlinkOffPeriod = 0;
        // make sure the LED is off.
        // ledOff((Board_LED_Index)ledIndex);
        return;
    }

    switch (ledBlinkStruct[ledIndex].ledBlinkStatus)
    {
        case Board_LED_OFF:
        ledOn((Board_LED_Index)ledIndex);
        ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_ON;
        targetPeriod = ledBlinkStruct[ledIndex].ledBlinkOnPeriod;
        break;
        case Board_LED_ON:
        ledOff((Board_LED_Index)ledIndex);
        ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_OFF;
        ledBlinkStruct[ledIndex].ledBlinkTimes--;
        targetPeriod = ledBlinkStruct[ledIndex].ledBlinkOffPeriod;
        break;
        default:
        break;
    }
#elif (BOARD_TYPE == PRODUCT_BOARD)
    if (ledBlinkStruct[ledIndex].ledBlinkTimes <= 0)
    {
        ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_OFF;
        return;
    }
    ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_ON;
    ledToggle(LED_INDEX_0);
    ledToggle(LED_INDEX_1);
    ledBlinkStruct[ledIndex].ledBlinkTimes--;
    targetPeriod = ledBlinkStruct[ledIndex].ledBlinkOffPeriod;
#endif
    Util_restartClock(&ledBlinkClock[ledIndex], targetPeriod);
}

void ledInit()
{
    PIN_open(&ledPinStatus, ledPinList);
    for (uint8_t i = 0; i < BOARD_LED_NUM; i++)
    {
        ledBlinkStruct[i].ledBlinkStatus = Board_LED_OFF;
        ledBlinkStruct[i].ledBlinkTimes = 0;
        ledBlinkStruct[i].ledBlinkOnPeriod = 0;
        ledBlinkStruct[i].ledBlinkOffPeriod = 0;
        Util_constructClock(&ledBlinkClock[i], ledBlinkCallback, 0, 0, false, i);
    }
}

void ledOn(Board_LED_Index ledIndex)
{
    PIN_setOutputValue(&ledPinStatus, ledBlinkStruct[ledIndex].ledBlinkIO, Board_LED_ON);
}

void ledOff(Board_LED_Index ledIndex)
{
    PIN_setOutputValue(&ledPinStatus, ledBlinkStruct[ledIndex].ledBlinkIO, Board_LED_OFF);
}

void ledToggle(Board_LED_Index ledIndex)
{
    PIN_setOutputValue(&ledPinStatus, ledBlinkStruct[ledIndex].ledBlinkIO, !PIN_getOutputValue(ledBlinkStruct[ledIndex].ledBlinkIO));
}

void ledBlinkWithParameters(Board_LED_Index ledIndex, uint16_t ledOnPeriod, uint16_t ledOffPeriod, uint16_t ledBlinkTime)
{
    /*
    if (ledBlinkStruct[ledIndex].ledBlinkTimes > 0)
    {
        DEBUG_STRING("Still Blinking\r\n");
        return;
    }
    */
   
    ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_OFF;
    ledBlinkStruct[ledIndex].ledBlinkOnPeriod = ledOnPeriod;
    ledBlinkStruct[ledIndex].ledBlinkOffPeriod = ledOffPeriod;
    ledBlinkStruct[ledIndex].ledBlinkTimes = ledBlinkTime;
    Util_startClock(&ledBlinkClock[ledIndex]);
    //ledBlinkCallback(ledIndex);
}
