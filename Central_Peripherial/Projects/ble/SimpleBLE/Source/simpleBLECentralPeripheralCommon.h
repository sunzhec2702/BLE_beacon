#ifndef __SIMPLE_BLE_CENTRAL_PERIPHERAL_COMMON_H_
#define __SIMPLE_BLE_CENTRAL_PERIPHERAL_COMMON_H_

#include "simpleble.h"

void set_beacon_status(BLE_STATUS current_status, BLE_STATUS target_status, bool reset);
void set_target_status_to_off(void);


#endif