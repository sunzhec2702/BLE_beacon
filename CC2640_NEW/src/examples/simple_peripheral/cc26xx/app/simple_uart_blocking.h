#ifndef __SIMPLE_UART_BLOCKING_H
#define __SIMPLE_UART_BLOCKING_H

void uartInitBKMode();
void uartWriteTransportBKMode(uint8_t *str, uint16_t len);

#endif

