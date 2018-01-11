#ifndef __SIMPLE_BLE_KEY_H
#define __SIMPLE_BLE_KEY_H

#include "simpleble.h"

typedef void (*key_event_process_callback)(uint8);

void set_key_press_process_callback(key_event_process_callback callback);
void key_cnt_evt_callback(void);
void key_press_handler(uint8 keys);


#endif
