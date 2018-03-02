#include "ble_uart.h"
#include "simple_uart_blocking.h"

void uart_flush_input(bool wait)
{
    VOID(wait);
    return;
}

int uart_receive(uint8_t *pbtRx, const uint16_t szRx, void *abort_p, int timeout)
{
    uartReadTransportBKMode(pbtRx, szRx, NULL, timeout);
    return 0;
}

int uart_send(const uint8_t *pbtTx, const uint16_t szTx, int timeout)
{
    VOID(timeout);
    uartWriteTransportBKMode(pbtTx, szTx);
    return 0;
}
