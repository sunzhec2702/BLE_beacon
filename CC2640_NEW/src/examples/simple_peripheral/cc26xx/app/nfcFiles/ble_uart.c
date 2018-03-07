#include "ble_uart.h"
#include "simple_uart_callback.h"
#include "nfc/nfc.h"
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/BIOS.h>
#include <stdio.h>

static Semaphore_Handle nfcUartSem;

void bleUartRxCallback()
{
    Semaphore_post(nfcUartSem);
}

void uart_flush_input(bool wait)
{
    VOID(wait);
    return;
}

int uart_receive(uint8_t *pbtRx, const uint16_t szRx, void *abort_p, int timeout)
{
    uint16_t rxBytes = 0;
    do
    {
        if (Semaphore_pend(nfcUartSem, BIOS_WAIT_FOREVER))
        {
            rxBytes  = getRxBufNumber();
        }
        else
        {
            clearRxBufNumber();
            return NFC_ETIMEOUT;
        }
    }
    while(rxBytes < szRx);
    memcpy(pbtRx, getRxBuf(), rxBytes);
    clearRxBufNumber();
    DEBUG_NFC_BYTE(pbtRx, szRx);
    /*
    DEBUG_STRING("Timeout:");
    DEBUG_NUMBER(timeout);
    DEBUG_STRING("\r\n");
    if (uartReadTransportBKMode(pbtRx, szRx, NULL, timeout) < 0)
    {
        DEBUG_STRING("NFC Uart Read Timeout\r\n");
        return NFC_ETIMEOUT;
    }
    DEBUG_NFC_BYTE(pbtRx, szRx);
    */
    return NFC_SUCCESS;
}

int uart_send(const uint8_t *pbtTx, const uint16_t szTx, int timeout)
{
    VOID(timeout);
    DEBUG_NFC_BYTE((uint8_t*)pbtTx, szTx);
    uartWriteTransportCBMode(pbtTx, szTx);
    /*
    DEBUG_NFC_BYTE((uint8_t*)pbtTx, szTx);
    uartWriteTransportCBMode(pbtTx, szTx);
    */
    return NFC_SUCCESS;
}

void ble_uart_init()
{
    uartInitCBMode();
    nfcUartSem = Semaphore_create(0, NULL, NULL);
}