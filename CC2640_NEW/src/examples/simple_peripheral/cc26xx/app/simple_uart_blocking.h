#ifndef __SIMPLE_UART_BLOCKING_H
#define __SIMPLE_UART_BLOCKING_H

void uartInitBKMode();
void uartWriteTransportBKMode(uint8_t *str, uint16_t len);
void uartReadTransportBKMode(uint8_t *buf, uint16_t exceptLen, void *abort_p, int timeout);

#endif

