#ifndef __SIMPLE_UART_CALLBACK_H
#define __SIMPLE_UART_CAKKBACK_H

void clearRxBufNumber(void);
uint16_t getRxBufNumber(void);
uint8_t *getRxBuf(void);
void uartInitCBMode(void);
void uartWriteTransportCBMode(const uint8_t *str, uint16_t len);

#endif
