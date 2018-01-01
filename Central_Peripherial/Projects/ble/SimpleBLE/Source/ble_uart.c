#include "ble_uart.h"
#include "simpleble.h"
#include "stdio.h"
#include "npi.h"
#include "_hal_uart_dma_common.h"

static uint8 rxBuffer[64];
static uint16 rxNum = 0;
static bool waitingRx = FALSE;

#define MAX_TIMEOUT 10000


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
#if (chip==2541 || chip==2543 || chip==2545)
    // Configure USART0 for Alternative 1 => Port P0 (PERCFG.U0CFG = 0).
    PERCFG = (PERCFG & ~PERCFG_U0CFG) | PERCFG_U0CFG_ALT1;    
#endif
        
#if (chip==2541)
    // Give priority to USART 0 over Timer 1 for port 0 pins.
    P2DIR &= P2DIR_PRIP0_USART0;
#elif (chip==2543 || chip==2545)
    // Give priority to USART 0 over Timer 1 for port 0 pins.
    PPRI &= ~PPRI_PRI0P0;
#endif

#if (chip==2541 || chip==2543 || chip==2545)
    // Set pins 2, 3 and 5 as peripheral I/O and pin 4 as GPIO output.
    P0SEL |= BIT5 | BIT4 | BIT3 | BIT2;
#elif (chip==2544)
    // Set pins 1, 2 and 3 as peripheral I/O and pin 0 as GPIO output.
    P0SEL0 = 0x11;        // Map P0_0 and P0_1 as UASRT0. 
    P0SEL1 = 0x11;        // Map P0_3 and P0_2 as UASRT0. 
#endif
     
#if (chip==2541 || chip==2543 || chip==2545)
    // Initialize P0_1 for SRF05EB S1 button.
    P0SEL &= ~BIT1;           // Function as General Purpose I/O.
    P0DIR &= ~BIT1;           // Input.
#elif (chip==2544)
    // Initialize P0_1 for SRF05EB S1 button.
    P0SEL0 &= ~P0SEL0_SELP0_1;// Function as General Purpose I/O.
    PDIR &= ~PDIR_DIRP0_1;    // Input.
#endif
  
    /***************************************************************************
    * Configure UART
    *
    */
  
    // Initialise bitrate = 57.6 kbps.
    U0BAUD = UART_BAUD_M;
    U0GCR = (U0GCR & ~U0GCR_BAUD_E) | UART_BAUD_E;

    // Initialise UART protocol (start/stop bit, data bits, parity, etc.):
    // USART mode = UART (U0CSR.MODE = 1)
    U0CSR |= U0CSR_MODE;

    // Start bit level = low => Idle level = high  (U0UCR.START = 0).
    U0UCR &= ~U0UCR_START;

    // Stop bit level = high (U0UCR.STOP = 1).
    U0UCR |= U0UCR_STOP;

    // Number of stop bits = 1 (U0UCR.SPB = 0).
    U0UCR &= ~U0UCR_SPB;

    // Parity = disabled (U0UCR.PARITY = 0).
    U0UCR &= ~U0UCR_PARITY;

    // 9-bit data enable = 8 bits transfer (U0UCR.BIT9 = 0).
    U0UCR &= ~U0UCR_BIT9;

    // Level of bit 9 = 0 (U0UCR.D9 = 0), used when U0UCR.BIT9 = 1.
    // Level of bit 9 = 1 (U0UCR.D9 = 1), used when U0UCR.BIT9 = 1.
    // Parity = Even (U0UCR.D9 = 0), used when U0UCR.PARITY = 1.
    // Parity = Odd (U0UCR.D9 = 1), used when U0UCR.PARITY = 1.
    U0UCR &= ~U0UCR_D9;

    // Flow control = disabled (U0UCR.FLOW = 0).
    U0UCR &= ~U0UCR_FLOW;

    // Bit order = LSB first (U0GCR.ORDER = 0).
    U0GCR &= ~U0GCR_ORDER;

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