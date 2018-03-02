#ifndef __SIMPLE_BLE_H__
#define __SIMPLE_BLE_H__

// Common Include 
#include <stdint.h>
#include <hal_types.h>
#include <comdef.h>

// Debug Uart
#include "simple_uart_emulator.h"
#include "ICall.h"
/* Board Type 
 * DEVELOP_BOARD
 * PRODUCT_BOARD
 */
#define DEVELOP_BOARD 0
#define PRODUCT_BOARD 1

#define BOARD_TYPE DEVELOP_BOARD

#define ENABLE_UART_EMULATOR 1
#define ENABLE_NFC 1

// LED Related Macro
#define LED_BLINK_ON_PERIOD         100 //ms
#define LED_BLINK_OFF_PERIOD        250 //ms

// Internal Events for RTOS application
#define SBP_STATE_CHANGE_EVT                  0x0001
#define SBP_CHAR_CHANGE_EVT                   0x0002
#define SBP_PERIODIC_EVT                      0x0004
#define SBP_CONN_EVT_END_EVT                  0x0008


#endif