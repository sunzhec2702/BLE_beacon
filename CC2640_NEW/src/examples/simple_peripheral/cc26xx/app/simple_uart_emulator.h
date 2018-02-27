#ifndef __SIMPLE_UART_EMULATOR_H
#define __SIMPLE_UART_EMULATOR_H

void simpleUartEmulatorCreateTask(void);
void uartEmulatorWriteByte(uint8_t *buf, uint16_t len);
#endif
