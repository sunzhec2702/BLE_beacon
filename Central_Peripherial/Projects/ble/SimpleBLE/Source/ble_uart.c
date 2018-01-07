#include "ble_uart.h"
#include "simpleble.h"
#include "stdio.h"
#include "npi.h"
#include "_hal_uart_dma_common.h"
#include "nfcApplication.h"
//#include "ble_uart_poll_def.h"

static uint16 rxNum = 0;
static int32 calCnt = 0;

int ble_uart_poll_init()
{
        /***************************************************************************
    * Setup I/O ports
    *
    * Port and pins used by USART0 operating in UART-mode, at the Alternative 1
    * location are:
    * RX     : P0_2
    * TX     : P0_3
    * CT/CTS : P0_4
    * RT/RTS : P0_5
    *
    * These pins must be set to function as peripheral I/O to be used by UART0.
    * The TX pin on the transmitter must be connected to the RX pin on the receiver.
    * If enabling hardware flow control (U0UCR.FLOW = 1) the CT/CTS (Clear-To-Send)
    * on the transmitter must be connected to the RS/RTS (Ready-To-Send) pin on the
    * receiver.
    */
    // Configure USART0 for Alternative 1 => Port P0 (PERCFG.U0CFG = 0).
    PERCFG |= 0x02; //UART1, Alternative 2.
    // Give priority to USART 0 over Timer 1 for port 0 pins.
    P2DIR &= ~0xC0;
    P2DIR |= (0x01 << 6);
    // Set pins 2, 3 and 5 as peripheral I/O and pin 4 as GPIO output.
    P1SEL |= 0xC0;
 
    /***************************************************************************
    * Configure UART
    *
    */
    // Initialise bitrate = 57.6 kbps.
    U1BAUD = 216;
    U1GCR = (U1GCR & ~0x1F) | 11;

    // Initialise UART protocol (start/stop bit, data bits, parity, etc.):
    // USART mode = UART (U0CSR.MODE = 1)
    U1CSR |= 0x80;

    // Start bit level = low => Idle level = high  (U0UCR.START = 0).
    U1UCR &= ~0x01;

    // Stop bit level = high (U0UCR.STOP = 1).
    U1UCR |= 0x02;

    // Number of stop bits = 1 (U0UCR.SPB = 0).
    U1UCR &= ~0x04;

    // Parity = disabled (U0UCR.PARITY = 0).
    U1UCR &= ~0x08;

    // 9-bit data enable = 8 bits transfer (U0UCR.BIT9 = 0).
    U1UCR &= ~0x10;

    // Level of bit 9 = 0 (U0UCR.D9 = 0), used when U0UCR.BIT9 = 1.
    // Level of bit 9 = 1 (U0UCR.D9 = 1), used when U0UCR.BIT9 = 1.
    // Parity = Even (U0UCR.D9 = 0), used when U0UCR.PARITY = 1.
    // Parity = Odd (U0UCR.D9 = 1), used when U0UCR.PARITY = 1.
    U1UCR &= ~0x20;

    // Flow control = disabled (U0UCR.FLOW = 0).
    U1UCR &= ~0x40;

    // Bit order = LSB first (U0GCR.ORDER = 0).
    U1GCR &= ~0x20;

    // Enable receive.
    U1CSR |= 0x40;

    // Clear any pending RX
    U1CSR &= ~0x04;
/*
    uint8 debug_uart[] = {0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0xfd, 0xd4, 0x14, 0x01, 0x17, 0x00};
    ble_uart_poll_send(debug_uart, sizeof(debug_uart), 0);
    ble_uart_poll_receive(uartRxBuf, 15, NULL, 0);
*/
    return 0;
}

int ble_uart_poll_receive(uint8* uartRxBuf, const size_t uartRxBufLength, void *abort_p, int timeout)
{
    (void) abort_p;
    calCnt = 300 * timeout ; // 0x5DC is 1 ms
    uint16 uartRxIndex;
    int32 calCntReal = 0;
    if (timeout < 2000)
    {
        calCnt = 769000 >> 2;
    }
    else if (timeout >= 2000 && timeout <= 5000)
    {
        calCnt = 769000 >> 3;
    }
    if (timeout >= 8000)
    {
        calCnt = 769000 >> 2;
    }
    calCntReal = calCnt;
    //osal_start_timerEx(getNFCAppID(), NFC_UART_RECEIVE_TIMEOUT_EVT, 2000);
    // Enable UART0 RX (U0CSR.RE = 1).
    U1CSR |= 0x40;

    // Clear any pending RX interrupt request (set U0CSR.RX_BYTE = 0).
    // Darren
    // U1CSR &= ~0x04;

    // Loop: receive each UART0 sample from the UART0 RX line.
    for (uartRxIndex = 0; uartRxIndex < uartRxBufLength; uartRxIndex++)
    {
        // Wait until data received (U0CSR.RX_BYTE = 1).
        while( !(U1CSR & 0x04) && (calCntReal > 0 || timeout <= 0) )
        {
            //SleepWaitUart(1);
            calCntReal--;
        }
        // Read UART0 RX buffer.
        uartRxBuf[uartRxIndex] = U1DBUF;
        if (calCntReal <= 0 && timeout > 0)
        {
          //NFC_UART_DEBUG_VALUE("timeout = ", timeout, 10);
          return -6;
        }
        calCntReal = calCnt;
    }
    //uint8 debugReceive[] = {0xBB, 0xAA};
    //NFC_UART_DEBUG(debugReceive, sizeof(debugReceive));
    //NFC_UART_DEBUG(uartRxBuf, (uint16)uartRxBufLength);
    //osal_stop_timerEx(getNFCAppID(), NFC_UART_RECEIVE_TIMEOUT_EVT);
    //NFC_UART_DEBUG(debugReceive, sizeof(debugReceive));
    return 0;
}

int ble_uart_poll_send(const uint8* uartTxBuf, const size_t uartTxBufLength, int timeout)
{
    (void) timeout;
    uint16 uartTxIndex;
    
    // Clear any pending TX interrupt request (set U0CSR.TX_BYTE = 0).
    U1CSR &= ~0x02;

    // Loop: send each UART0 sample on the UART0 TX line.
    for (uartTxIndex = 0; uartTxIndex < uartTxBufLength; uartTxIndex++)
    {
        U1DBUF = uartTxBuf[uartTxIndex];
        while(! (U1CSR & 0x02) );
        U1CSR &= ~0x02;
    }
    uint8 debugSend[] = {0xDD, 0xCC};
    //NFC_UART_DEBUG(debugSend, sizeof(debugSend));
    //NFC_UART_DEBUG((uint8 *)uartTxBuf, (uint16)uartTxBufLength);
    //NFC_UART_DEBUG(debugSend, sizeof(debugSend));
    return 0;
}

int ble_uart_receive(uint8 *pbtRx, const size_t szRx, void *abort_p, int timeout)
{
    (void)abort_p;
    while(rxNum < szRx)
    {
      //SleepWaitUart(1000);
      
    }
    return 0;

/*
    if (timeout == 0)
    {
        timeout = MAX_TIMEOUT;
    }
    while (rxNum < szRx && timeout > 0)
    {
        SleepWaitUart(500);
        timeout -= 500;
    }
    if (timeout <= 0)
    {
        return -6;
    }
    else
    {
        memcpy(pbtRx, rxBuffer, rxNum);
    }
    return 0;
  */
}

/*
int ble_uart_send(const uint8 *pbtTx, const size_t szTx, int timeout)
{
    memset(rxBuffer, 0, sizeof(rxBuffer));
    rxNum = 0;
    (void)timeout;
    waitingRx = TRUE;
    //HACK send to UART0
    //NPI_WriteTransport(SBYTE, 2);
    uint8 debugSend[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    NFC_UART_DEBUG((uint8 *)pbtTx, (uint16)szTx);
    NFC_UART_DEBUG(debugSend, sizeof(debugSend));

    NPI_WriteTransportPort(HAL_UART_PORT_1, (uint8 *)pbtTx, (uint16)szTx);
    return 0;
}

int ble_uart_interrupt(uint8 *bleRx, uint16 bleRxNum)
{
    uint8 debug[] = {0xAB, 0xCD, 0xEF};
    if (waitingRx == FALSE)
    {
        return -1;
    }
    NFC_UART_DEBUG(debug, sizeof(debug));
    NFC_UART_DEBUG((uint8 *)bleRx, bleRxNum);
    memcpy(&rxBuffer[rxNum], bleRx, bleRxNum);
    rxNum += bleRxNum;
    waitingRx = FALSE;
    return 0;
}
*/

void ble_uart_flush_input(bool wait)
{
    (void)wait;
    //U0UCR = 0x80;
}

#pragma optimize = none
static void SleepWaitUart(uint16 duration)
{
    duration >>= 1;

    while (duration-- > 0)
    {
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
        ASM_NOP;
    }
}