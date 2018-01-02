#ifndef __BLE_UART_H_
#define __BLE_UART_H_

#include "simpleble.h"

// Define shortcut to types to make code more readable

void ble_uart_open(const char *pcPortName);
void ble_uart_close(void);
void ble_uart_flush_input(bool wait);

int ble_uart_receive(uint8 *pbtRx, const size_t szRx, void *abort_p, int timeout);
int ble_uart_send(const uint8 *pbtTx, const size_t szTx, int timeout);

int ble_uart_interrupt(uint8 *bleRx, uint16 bleRxNum);
void ble_uart_flush_input(bool wait);
static void SleepWaitUart(uint16 duration);


int ble_uart_poll_init(void);
int ble_uart_poll_receive(uint8* uartRxBuf, const size_t uartRxBufLength, void *abort_p, int timeout);
int ble_uart_poll_send(const uint8* uartTxBuf, const size_t uartTxBufLength, int timeout);


#endif
