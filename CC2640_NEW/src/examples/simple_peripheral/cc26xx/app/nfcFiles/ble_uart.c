#include "ble_uart.h"
#include "simple_uart_blocking.h"
#include "nfc/nfc.h"

void uart_flush_input(bool wait)
{
    VOID(wait);
    return;
}

int uart_receive(uint8_t *pbtRx, const uint16_t szRx, void *abort_p, int timeout)
{
    DEBUG_STRING("Timeout:");
    DEBUG_NUMBER(timeout);
    DEBUG_STRING("\r\n");
    if (uartReadTransportBKMode(pbtRx, szRx, NULL, timeout) < 0)
    {
        DEBUG_STRING("NFC Uart Read Timeout\r\n");
        return NFC_ETIMEOUT;
    }
    DEBUG_NFC_BYTE(pbtRx, szRx);
    return NFC_SUCCESS;
}

int uart_send(const uint8_t *pbtTx, const uint16_t szTx, int timeout)
{
    VOID(timeout);
    DEBUG_NFC_BYTE((uint8_t*)pbtTx, szTx);
    uartWriteTransportBKMode(pbtTx, szTx);
    return NFC_SUCCESS;
}
