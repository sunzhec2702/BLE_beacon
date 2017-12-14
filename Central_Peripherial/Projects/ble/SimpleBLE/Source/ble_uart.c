#include "ble_uart.h"
#include "simpleble.h"
#include "stdio.h"
#include "_hal_uart_dma_common.h"

static uint8 rxBuffer[64];
static uint16 rxNum = 0;
static bool waitingRx = FALSE;

// �ú�����ʱʱ��Ϊ1ms�� ��ʾ������������ �������? ������С  --amomcu.com
static int ble_uart_waiting_receive_timeout(int times)
{
    while (times--)
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
    }
    return -1;
}

int ble_uart_receive(uint8 *pbtRx, const size_t szRx, void *abort_p, int timeout)
{
    (void)abort_p;
    int retry = 1;
    while(retry > 0)
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
    }
    return 0;
}

int ble_uart_send(const uint8 *pbtTx, const size_t szTx, int timeout)
{
    memset(rxBuffer, 0, sizeof(rxBuffer));
    rxNum = 0;
    (void)timeout;
    waitingRx = TRUE;
    NPI_WriteTransport(pbtTx, szTx);
}

int ble_uart_interrupt(uint8 *bleRx, uint16 bleRxNum)
{
    memcpy(&rxBuffer[rxNum], bleRx, bleRxNum);
    rxNum += bleRxNum;
    waitingRx = FALSE;
}

void ble_uart_flush_input(bool wait)
{
    (void) wait;
    U0UCR = 0x80;
}