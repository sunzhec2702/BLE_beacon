#ifndef __SIMPLE_BLE_H__
#define __SIMPLE_BLE_H__

// Common Include 
#include <stdint.h>
#include <hal_types.h>
#include <comdef.h>
#include <bcomdef.h>
#include "hci.h"
#include "simple_beacon_configuration.h"

// Debug Uart
#include "simple_uart_emulator.h"
#include "ICall.h"

/* Board Type 
 * DEVELOP_BOARD
 * PRODUCT_BOARD
 */
#define DEVELOP_BOARD 0
#define PRODUCT_BOARD 1

#define PLUS_OBSERVER           1
#define BOARD_TYPE PRODUCT_BOARD

#define ENABLE_UART_EMULATOR 1
#define ENABLE_NFC 0

// LED Related Macro
#define LED_BLINK_ON_PERIOD         (100) //ms
#define LED_BLINK_OFF_PERIOD        (200) //ms
#define LED_BLINK_RAPID_OFF_PERIOD  (100) //ms



#define DEF_TX_POWER    HCI_EXT_TX_POWER_MINUS_6_DBM
#define MAX_TX_POWER        HCI_EXT_TX_POWER_2_DBM
#endif