#ifndef __SIMPLE_UART_H
#define __SIMPLE_UART_H

//#define UART_CALLBACK_MODE
#define UART_BLOCKING_MODE

#if defined UART_CALLBACK_MODE
#include "simple_uart_callback.h"
#elif defined UART_BLOCKING_MODE
#include "simple_uart_blocking.h"
#endif

void uartInit();
void uartWriteTransport(uint8_t *str, uint16_t len);
#endif
