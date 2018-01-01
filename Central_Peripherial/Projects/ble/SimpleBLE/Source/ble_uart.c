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
}

int ble_uart_receive(uint8 *pbtRx, const size_t szRx, void *abort_p, int timeout)
{
    (void)abort_p;
    while(rxNum < szRx && timeout > 0)
    {
        SleepWaitUart(500);
        timeout -= 500;
    }
    if (timeout <= 0 )
    memcpy(pbtRx, rxBuffer, rxNum);
    return 0;

}

int ble_uart_send(const uint8 *pbtTx, const size_t szTx, int timeout)
{
    memset(rxBuffer, 0, sizeof(rxBuffer));
    rxNum = 0;
    (void)timeout;
    waitingRx = TRUE;
    //HACK send to UART0
    //NPI_WriteTransport(SBYTE, 2);
    uint8 debugSend[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    NFC_UART_DEBUG( (uint8*) pbtTx, (uint16) szTx);
    NFC_UART_DEBUG( debugSend, sizeof(debugSend) );

    NPI_WriteTransportPort(HAL_UART_PORT_1, (uint8*) pbtTx, (uint16) szTx);
    return 0;
}

int ble_uart_interrupt(uint8 *bleRx, uint16 bleRxNum)
{
    uint8 debug[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    NFC_UART_DEBUG(debug, sizeof(debug));
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

#pragma optimize=none
static void SleepWaitUart(uint16 duration)
{
  duration >>= 1;

  while (duration-- > 0)
  {
    ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP;
    ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP;
    ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP; ASM_NOP;
  }
}