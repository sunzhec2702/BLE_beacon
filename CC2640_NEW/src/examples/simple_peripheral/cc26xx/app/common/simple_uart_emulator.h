#ifndef __SIMPLE_UART_EMULATOR_H
#define __SIMPLE_UART_EMULATOR_H
#include "simpleble.h"

void simpleUartEmulatorCreateTask(void);
void uartEmulatorWriteByte(uint8_t *buf, uint16_t len);
void uartEmulatorWriteString(char *str);
void uartEmulatorWriteNumber(uint16_t val);

#define DEBUG_EMULATOR_ENABLE  1
#define DEBUG_NFC_ENABLE       0

#if ((ENABLE_UART_EMULATOR == 1) && (DEBUG_EMULATOR_ENABLE == 1))
#define DEBUG_BYTE(x, y)    uartEmulatorWriteByte(x, y)
#define DEBUG_STRING(x)    uartEmulatorWriteString(x)
#define DEBUG_NUMBER(x)    uartEmulatorWriteNumber(x)
#else
//#define DEBUG_BYTE(x, y)   {}
//#define DEBUG_STRING(x)    {}
//#define DEBUG_NUMBER(x)    {}
#endif

#if (ENABLE_UART_EMULATOR == 1 && DEBUG_NFC_ENABLE == 1)
#define DEBUG_NFC_BYTE(x, y)    uartEmulatorWriteByte(x, y)
#define DEBUG_NFC_NUMBER(x)    uartEmulatorWriteNumber(x)
#else
#define DEBUG_NFC_BYTE(x, y)   {}
#define DEBUG_NFC_NUMBER(x)    {}
#endif

#endif
