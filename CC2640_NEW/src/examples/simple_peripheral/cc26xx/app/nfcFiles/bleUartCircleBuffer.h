#ifndef __BLE_UART_CIRCLE_BUFFER_H
#define __BLE_UART_CIRCLE_BUFFER_H

void bleUartCircleBufferInit(void);
void bleUartCircleBufferPut(uint8_t buf, uint16_t number);
uint16_t bleUartCircleBufferGet(uint8_t buf, uint16_t number);
uint16_t bleUartCircleBufferGetNumber(void);
uint16_t bleUartCircleBufferGetEmptyNumber(void);

#endif

