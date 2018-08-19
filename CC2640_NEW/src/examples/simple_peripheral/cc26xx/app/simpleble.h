#ifndef __SIMPLE_BLE_H__
#define __SIMPLE_BLE_H__

// Common Include 
#include <stdint.h>
#include <hal_types.h>
#include <comdef.h>
#include <bcomdef.h>
#include "hci.h"
#include "simple_beacon_configuration.h"

#include "ICall.h"

#include <ti/sysbios/knl/Clock.h>
#define MS_2_TICKS(ms) (((ms)*1000) / Clock_tickPeriod)

/* Board Type 
 * DEVELOP_BOARD
 * PRODUCT_BOARD
 */
#define DEVELOP_BOARD 0
#define PRODUCT_BOARD 1

#define BLE_DEV_BEACON          0x01
#define BLE_DEV_STATION_ADV     0x02

#define PLUS_OBSERVER           1
#define BOARD_TYPE DEVELOP_BOARD

// Debug Uart
#define ENABLE_UART_EMULATOR    1
#include "simple_uart_emulator.h"

// LED Related Macro
#define PWM_LED     1

#endif