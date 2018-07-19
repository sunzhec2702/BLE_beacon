#include "simple_pwm_led.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include "util.h"
#include <ti/sysbios/knl/Clock.h>
#include <inc/hw_ints.h>
#include <Board.h>
#include <simple_pwm.h>

#if (BOARD_TYPE == PRODUCT_BOARD)
#define DEFAULT_PWM_LED_PERCENT 50
#elif (BOARD_TYPE == DEVELOP_BOARD)
#define DEFAULT_PWM_LED_PERCENT 100
#endif

static PIN_State pwmLedPinStatus;
static Clock_Struct pwmLedBlinkClock;
static LedBlinkStruct pwmLedBlinkStruct;
static PWM_Handle ledPwm;
static void pwmLedBlinkCallback(UArg ledIndex);

const PIN_Config pwmLedPinList[] = {
    Board_PWM_LED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
#if (BOARD_TYPE == PRODUCT_BOARD)
    Board_PWM_LED_IO | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX,
#endif
    PIN_TERMINATE};

void pwmLedInit()
{
    /* Call board init functions. */
    Board_initPWM();
    PWM_Params params;
    PWM_Params_init(&params);
    ledPwm = PWM_open(Board_PWM0, &params);
    //PWM_start(ledPwm);
    //PWM_setDuty(ledPwm, ((uint32_t) ~0)/2);
    PIN_open(&pwmLedPinStatus, pwmLedPinList);
    pwmLedBlinkStruct.ledBlinkStatus = Board_LED_OFF;
    pwmLedBlinkStruct.ledBlinkTimes = 0;
    pwmLedBlinkStruct.ledBlinkOnPeriod = 0;
    pwmLedBlinkStruct.ledBlinkOffPeriod = 0;
    Util_constructClock(&pwmLedBlinkClock, pwmLedBlinkCallback, 0, 0, false, 0);
}

static void pwmLedBlinkCallback(UArg ledIndex)
{
    uint16_t targetPeriod = 0;
    if (pwmLedBlinkStruct.ledBlinkTimes <= 0)
    {
        pwmLedBlinkStruct.ledBlinkStatus = Board_LED_OFF;
        pwmLedBlinkStruct.ledBlinkTimes = 0;
        pwmLedBlinkStruct.ledBlinkOnPeriod = 0;
        pwmLedBlinkStruct.ledBlinkOffPeriod = 0;
        // make sure the LED is off.
        pwmLedOff();
        return;
    }
    switch (pwmLedBlinkStruct.ledBlinkStatus)
    {
        case Board_LED_OFF:
        pwmLedOn();
        pwmLedBlinkStruct.ledBlinkStatus = Board_LED_ON;
        targetPeriod = pwmLedBlinkStruct.ledBlinkOnPeriod;
        break;
        case Board_LED_ON:
        pwmLedOff();
        pwmLedBlinkStruct.ledBlinkStatus = Board_LED_OFF;
        pwmLedBlinkStruct.ledBlinkTimes--;
        targetPeriod = pwmLedBlinkStruct.ledBlinkOffPeriod;
        break;
        default:
        break;
    }
    Util_restartClock(&pwmLedBlinkClock, targetPeriod);
}

void pwmLedOn()
{
    pwmLedOnPercent(DEFAULT_PWM_LED_PERCENT);
}

void pwmLedOff()
{
#if (BOARD_TYPE == PRODUCT_BOARD)
    PIN_setOutputValue(&pwmLedPinStatus, Board_PWM_LED_IO, Board_LED_ON);
#endif
    PWM_setDuty(ledPwm, 0);
    PWM_stop(ledPwm);
}

void pwmLedOnPercent(uint8_t percent)
{
#if (BOARD_TYPE == PRODUCT_BOARD)
    PIN_setOutputValue(&pwmLedPinStatus, Board_PWM_LED_IO, Board_LED_OFF);
#endif
    PWM_start(ledPwm);
    PWM_setDuty(ledPwm, calDutyValue(percent));
}

uint32_t calDutyValue(uint8_t percent)
{
    if (percent > 100 || percent < 0)
    {
        return 0;
    }
    if (percent == 100)
        return (uint32_t) ~0;
    else if (percent == 0)
        return 0;
    else
        return ((uint32_t) ~0) / 100 * percent;
}

void pwmLedBlinkWithParameters(uint16_t ledOnPeriod, uint16_t ledOffPeriod, uint16_t ledBlinkTime)
{
    /*
    if (ledBlinkStruct[ledIndex].ledBlinkTimes > 0)
    {
        DEBUG_STRING("Still Blinking\r\n");
        return;
    }
    */
    pwmLedBlinkStruct.ledBlinkStatus = Board_LED_OFF;
    pwmLedBlinkStruct.ledBlinkOnPeriod = ledOnPeriod;
    pwmLedBlinkStruct.ledBlinkOffPeriod = ledOffPeriod;
    pwmLedBlinkStruct.ledBlinkTimes = ledBlinkTime;
    Util_startClock(&pwmLedBlinkClock);
}