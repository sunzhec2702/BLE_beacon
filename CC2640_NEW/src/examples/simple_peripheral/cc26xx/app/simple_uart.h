#ifndef __SIMPLE_UART_H
#define __SIMPLE_UART_H

void uartInit();

extern void UART_WriteTransport (uint8_t *str, uint16_t len);

#endif
