#ifndef __SIMPLE_BLE_H__
#define __SIMPLE_BLE_H__

/* Board Type 
 * DEVELOP_BOARD
 * PRODUCT_BOARD
 */
#define BOARD_TYPE  DEVELOP_BOARD

// LED Related Macro
#define LED_BLINK_ON_PERIOD         200 //ms
#define LED_BLINK_OFF_PERIOD        200 //ms

// Internal Events for RTOS application
#define SBP_STATE_CHANGE_EVT                  0x0001
#define SBP_CHAR_CHANGE_EVT                   0x0002
#define SBP_PERIODIC_EVT                      0x0004
#define SBP_CONN_EVT_END_EVT                  0x0008


#endif