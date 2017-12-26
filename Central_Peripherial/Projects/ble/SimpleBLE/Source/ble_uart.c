#include "ble_uart.h"
#include "simpleble.h"
#include "stdio.h"
#include "npi.h"
#include "_hal_uart_dma_common.h"

static uint8 rxBuffer[64];
static uint16 rxNum = 0;
static bool waitingRx = FALSE;

static uint8 SBYTE[2] = {0xDE, 0xAD};
static uint8 RBYTE[2] = {0xBE, 0xAF};

// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ �������? ������С  --amomcu.com
static int ble_uart_waiting_receive_timeout(int times)
{
    int time_left = times;
    
    #if (DEBUG_NFC_UART_MAX_TIMEOUT_ENABLE == 1)
        static uint16 maxWaittime = DEBUG_NFC_UART_MAX_TIMEOUT;
        if (time_left == 0)
        {
            time_left = maxWaittime;
            times = maxWaittime;
        }
    #endif

    while (time_left >= 0)
    {
        if (waitingRx == FALSE)
        {
            return 0;
        }
        int i = 0;
        for (i = 1500; i > 0; i--)
        {
            asm("nop");
        }
        // times == 0 means wait forever.
        if (times == 0)
        {
            continue;
        }
        time_left--;
    }
    #if (DEBUG_NFC_UART_FAKE_RESPOND == 1 || DEBUG_NFC_UART_MAX_TIMEOUT_ENABLE == 1)
    {
        return 0;
    }
    #endif
    return -1;
}

int ble_uart_receive(uint8 *pbtRx, const size_t szRx, void *abort_p, int timeout)
{
    (void)abort_p;
    int retry = 1;
    #if (DEBUG_WAIT_FOR_RX_NUM == 1)
        while(rxNum < szRx)
        {
            waitingRx = TRUE;
            int ret = ble_uart_waiting_receive_timeout(timeout);
            if (ret != 0)
                return -1;
        }
        memcpy(pbtRx, rxBuffer, rxNum);
        return 0;
    #else
        while (retry > 0)
        {
            int ret = ble_uart_waiting_receive_timeout(timeout);
            if (ret == 0)
            {
                memcpy(pbtRx, rxBuffer, rxNum);
                return 0;
            }
            else
            {
                return -1;
            }
            retry--;
        }
        return 0;
    #endif
}

int ble_uart_send(const uint8 *pbtTx, const size_t szTx, int timeout)
{
    memset(rxBuffer, 0, sizeof(rxBuffer));
    rxNum = 0;
    (void)timeout;
    waitingRx = TRUE;
    //HACK send to UART0
    //NPI_WriteTransport(SBYTE, 2);
    NFC_UART_DEBUG( (uint8*) pbtTx, (uint16) szTx);
    NPI_WriteTransportPort(HAL_UART_PORT_1, (uint8*) pbtTx, (uint16) szTx);
    return 0;
}

int ble_uart_interrupt(uint8 *bleRx, uint16 bleRxNum)
{
    NFC_UART_DEBUG((uint8*) bleRx, bleRxNum);
    if (waitingRx == FALSE)
    {
        return -1;
    }
    memcpy(&rxBuffer[rxNum], bleRx, bleRxNum);
    rxNum += bleRxNum;
    waitingRx = FALSE;
    return 0;
}

void ble_uart_flush_input(bool wait)
{
    (void)wait;
    //U0UCR = 0x80;
}