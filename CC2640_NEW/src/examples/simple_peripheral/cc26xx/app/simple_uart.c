#include "simple_uart.h"

#define UART_CALLBACK_MODE
//#define UART_BLOCKING_MODE

#ifdef UART_CALLBACK_MODE
#include "simple_uart_callback.h"
#endif

void uartReadTransport()
{

}

void uartWriteTransport(uint8_t *str, uint16_t len)
{
    #ifdef UART_CALLBACK_MODE
    uartWriteTransportCBMode(str, len);
    #endif
}

void uartInit()
{
    #ifdef UART_CALLBACK_MODE
    uartInitCBMode();
    #endif
}
