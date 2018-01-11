#ifndef __SIMPLE_BLE_KEY_H
#define __SIMPLE_BLE_KEY_H

#include "simpleble.h"

typedef void (*key_event_process_callback)(uint8);

void key_cnt_evt_callback(void);
void key_press_handler(void);


#endif
