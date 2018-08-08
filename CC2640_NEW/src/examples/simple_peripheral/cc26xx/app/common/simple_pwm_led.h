#ifndef __SIMPLE_PWM_LED_H
#define __SIMPLE_PWM_LED_H
#include <stdint.h>

typedef struct
{
    uint8_t ledBlinkStatus;
    uint16_t ledBlinkTimes;
    uint16_t ledBlinkOnPeriod;
    uint16_t ledBlinkOffPeriod;
} LedBlinkStruct;

void pwmLedInit(void);
void pwmLedOn(void);
void pwmLedOff(void);
void pwmLedOnPercent(uint8_t percent);
uint32_t calDutyValue(uint8_t percent);
void pwmLedReset(void);
void pwmLedBlinkWithParameters(uint16_t ledOnPeriod, uint16_t ledOffPeriod, uint16_t ledBlinkTime);
#endif
