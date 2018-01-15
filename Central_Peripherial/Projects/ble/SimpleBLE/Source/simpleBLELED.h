#ifndef __SIMPLE_BLE_LED_H
#define __SIMPLE_BLE_LED_H
#include "simpleble.h"

void led_event_callback(void);
uint8 led_toggle_set_param(uint16 toggle_period_on, uint16 toggle_period_off, uint32 toggle_target_cnt, uint16 delay);
uint8 led_toggle_clean_param(void);
uint8 get_led_toggle_status(void);

#endif
