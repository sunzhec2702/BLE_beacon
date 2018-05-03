#ifndef __SIMPLE_LED_H
#define __SIMPLE_LED_H
#include <stdint.h>

typedef struct
{
    uint32_t ledBlinkIO;
    uint8_t ledBlinkStatus;
    uint16_t ledBlinkTimes;
    uint16_t ledBlinkOnPeriod;
    uint16_t ledBlinkOffPeriod;
} LedBlinkStruct;

typedef enum
{
    LED_INDEX_0 = 0,
    LED_INDEX_1,
    BOARD_LED_NUM,
} Board_LED_Index;

void ledInit(void);
void ledOn(Board_LED_Index ledIndex);
void ledOff(Board_LED_Index ledIndex);
void ledToggle(Board_LED_Index ledIndex);
void ledBlinkWithParameters(Board_LED_Index ledIndex, uint16_t ledOnPeriod, uint16_t ledOffPeriod, uint16_t ledBlinkTime);
#endif
