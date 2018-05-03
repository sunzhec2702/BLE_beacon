#include "simple_uart.h"
void uartReadTransport()
{
    #if defined UART_BLOCKING_MODE
    //uartReadTransportBKMode();
    #endif
}

void uartWriteTransport(uint8_t *str, uint16_t len)
{
    #if defined UART_CALLBACK_MODE
    uartWriteTransportCBMode(str, len);
    #elif defined UART_BLOCKING_MODE
    uartWriteTransportBKMode(str, len);
    #endif
}

void uartInit()
{
    #if defined UART_CALLBACK_MODE
    uartInitCBMode();
    #elif defined UART_BLOCKING_MODE
    uartInitBKMode();
    #endif
}
