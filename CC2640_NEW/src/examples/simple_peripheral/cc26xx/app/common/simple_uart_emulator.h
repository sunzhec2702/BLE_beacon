#ifndef __SIMPLE_UART_EMULATOR_H
#define __SIMPLE_UART_EMULATOR_H

// Choose only one from below two.
#define DEBUG_EMULATOR
//#define DEBUG_NFC

#if defined (DEBUG_EMULATOR)
#define DEBUG_BYTE(x, y)    uartEmulatorWriteByte(x, y)
#define DEBUG_STRING(x)    uartEmulatorWriteString(x)
#define DEBUG_NUMBER(x)    uartEmulatorWriteNumber(x)
#else
#define DEBUG_BYTE(x, y)   {}
#define DEBUG_STRING(x)    {}
#define DEBUG_NUMBER(x)    {}
#endif

#if defined (DEBUG_NFC)
#define DEBUG_NFC_BYTE(x, y)    uartEmulatorWriteByte(x, y)
#define DEBUG_NFC_NUMBER(x)    uartEmulatorWriteNumber(x)
#else
#define DEBUG_NFC_BYTE(x, y)   {}
#define DEBUG_NFC_NUMBER(x)    {}
#endif

void simpleUartEmulatorCreateTask(void);
void uartEmulatorWriteByte(uint8_t *buf, uint16_t len);
void uartEmulatorWriteString(char *str);
void uartEmulatorWriteNumber(uint16_t val);
#endif
