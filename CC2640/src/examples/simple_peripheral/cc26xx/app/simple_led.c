#include "simple_led.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include <Board.h>

#define BOARD_LED_NUM 2

static PIN_Handle ledPinHandle;
static PIN_State ledPinStatus;

// Key debounce clock
// static Clock_Struct ledBlinkClock;

#define LED_BLINK_ON_PERIOD     50  //ms
#define LED_BLINK_OFF_PERIOD    150 //ms

typedef struct
{
    uint8_t ledBlinkStatus;
    uint16_t ledBlinkTimes;
    uint16_t ledBlinkOnPeriod;
    uint16_t ledBlinkOffPeriod;
} LedBlinkStruct;

static LedBlinkStruct ledBlinkStruct[BOARD_LED_NUM];

const PIN_Config ledPinList[BOARD_LED_NUM+1] = {
    Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
    };

void ledInit()
{
    ledPinHandle = PIN_open(&ledPinStatus, ledPinList);
}

void ledOn(uint8_t ledPin)
{
    PIN_setOutputValue(&ledPinStatus, ledPin, 1);
}

void ledOff(uint8_t ledPin)
{
    PIN_setOutputValue(&ledPinStatus, ledPin, 0);
}

void ledToggle(uint8_t ledPin)
{
    PIN_setOutputValue(&ledPinStatus, ledPin, !PIN_getOutputValue(ledPin));
}

void ledBlinkWithParameters(uint8_t ledPin, uint16_t ledOnPeriod, uint16_t ledOffPeriod, uint16_t ledBlinkTime)
{


}