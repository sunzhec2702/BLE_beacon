#include "simple_led.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include <ti/sysbios/knl/Clock.h>
#include <inc/hw_ints.h>
#include <Board.h>

#define LED_INDEX_2_IO(x) Board_LED##x

static PIN_Handle ledPinHandle;
static PIN_State ledPinStatus;
static Clock_Struct ledBlinkClock;
static LedBlinkStruct ledBlinkStruct[BOARD_LED_NUM];

const PIN_Config ledPinList[BOARD_LED_NUM+1] = {
    Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
    };

typedef struct
{
    uint8_t ledBlinkStatus;
    uint16_t ledBlinkTimes;
    uint16_t ledBlinkOnPeriod;
    uint16_t ledBlinkOffPeriod;
} LedBlinkStruct;

static void ledBlinkCallback(UArg ledIndex)
{
    if (ledBlinkStruct[ledIndex].ledBlinkTimes <= 0)
    {
        // make sure the LED is off.
        ledOff(ledIndex);
        return;
    }

    switch (ledBlinkStruct[ledIndex].ledBlinkStatus)
    {
        case Board_LED_OFF:
        ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_ON;
        Util_constructClock(&ledBlinkClock, ledBlinkCallback, ledBlinkStruct[ledIndex].ledBlinkOnPeriod, 0 , true, ledIndex);
        break;
        case Board_LED_ON:
        ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_OFF;
        ledBlinkStruct[ledIndex].ledBlinkTimes--;
        Util_constructClock(&ledBlinkClock, ledBlinkCallback, ledBlinkStruct[ledIndex].ledBlinkOffPeriod, 0 , true, ledIndex);
        break;
        default:
        break;
    }
}


void ledInit()
{
    ledPinHandle = PIN_open(&ledPinStatus, ledPinList);
    for (uint8_t i = 0; i < BOARD_LED_NUM; i++)
    {
        ledBlinkStruct[i].ledBlinkStatus = Board_LED_OFF;
        ledBlinkStruct[i].ledBlinkTimes = 0;
        ledBlinkStruct[i].ledBlinkOnPeriod = 0;
        ledBlinkStruct[i].ledBlinkOffPeriod = 0;
    }
}

void ledOn(Board_LED_Index ledIndex)
{
    PIN_setOutputValue(&ledPinStatus, LED_INDEX_2_IO(Board_LED_Index), Board_LED_ON);
}

void ledOff(Board_LED_Index ledIndex)
{
    PIN_setOutputValue(&ledPinStatus,  LED_INDEX_2_IO(Board_LED_Index), Board_LED_OFF);
}

void ledToggle(Board_LED_Index ledIndex)
{
    PIN_setOutputValue(&ledPinStatus,  LED_INDEX_2_IO(Board_LED_Index), !PIN_getOutputValue(LED_INDEX_2_IO(Board_LED_Index)));
}

void ledBlinkWithParameters(Board_LED_Index ledIndex, uint16_t ledOnPeriod, uint16_t ledOffPeriod, uint16_t ledBlinkTime)
{
    ledBlinkStruct[ledIndex].ledBlinkStatus = Board_LED_OFF;
    ledBlinkStruct[ledIndex].ledBlinkOnPeriod = ledOnPeriod;
    ledBlinkStruct[ledIndex].ledBlinkOffPeriod = ledOffPeriod;
    ledBlinkStruct[ledIndex].ledBlinkTimes = ledBlinkTime;
    ledBlinkCallback(ledIndex);
}
