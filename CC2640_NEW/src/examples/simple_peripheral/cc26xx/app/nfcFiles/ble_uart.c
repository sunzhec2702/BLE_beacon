#include "ble_uart.h"
#include "simple_uart_callback.h"
#include "nfc/nfc.h"
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/BIOS.h>
#include <stdio.h>
#include "bleUartCircleBuffer.h"

static Semaphore_Handle nfcUartSem;

void bleUartRxCallback(uint8_t *buf, uint16_t count)
{
    bleUartCircleBufferPut(buf, count);
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
        if (bleUartCircleBufferGetNumber() > 0)
        {
            rxBytes  += bleUartCircleBufferGet(pbtRx + rxBytes, szRx);
        }
        else if (Semaphore_pend(nfcUartSem, timeout))
        {
            rxBytes  += bleUartCircleBufferGet(pbtRx + rxBytes, szRx);
        }
        else
        {
            return NFC_ETIMEOUT;
        }
    } while(rxBytes < szRx);
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
    bleUartCircleBufferInit();
    nfcUartSem = Semaphore_create(0, NULL, NULL);
}