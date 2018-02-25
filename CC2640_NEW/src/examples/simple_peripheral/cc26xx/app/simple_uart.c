#include "simple_uart.h"
#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "npi_tl_uart.h"

#ifdef NPI_USE_UART


static char tRxBuf[256];
static char tTxBuf[256];

static bool uartInitFlag = FALSE;

void UART_WriteTransport (uint8_t *str, uint16_t len)
{
    if(uartInitFlag)
    {
        memset(tTxBuf, 0, sizeof(tTxBuf));
        
        memcpy(tTxBuf, str, len);
        NPITLUART_writeTransport(len);
    }
}

void  UartCallBack(uint16_t rxLen, uint16_t txLen)
{
    if(uartInitFlag)
    {
    //   LCD_WRITE_STRING_VALUE("rxLen: ", (uint32_t)rxLen, 10, LCD_PAGE5);
    //   LCD_WRITE_STRING_VALUE("txLen: ", (uint32_t)txLen, 10, LCD_PAGE6);

    //   
       if(rxLen > 0)
       {
    //        sprintf(tTxBuf, "123");
    //        NPITLUART_writeTransport(strlen(tTxBuf));
            sprintf(tTxBuf, tRxBuf, rxLen);
            NPITLUART_writeTransport(rxLen);
       }
    }
}


void Uart_Init()
{
    if(!uartInitFlag)
    {
        NPITLUART_initializeTransport(tRxBuf, tTxBuf, UartCallBack);
        uartInitFlag = TRUE;

        sprintf(tTxBuf, "NPITLUART_initialize");
        NPITLUART_writeTransport(strlen(tTxBuf));
    }
}

#endif


