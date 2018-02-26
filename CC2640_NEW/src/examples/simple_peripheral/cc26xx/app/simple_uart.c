#include "simple_uart.h"
#include "simple_led.h"
#include <string.h>
#include <stdio.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include "Board.h"

static UART_Handle uartHandle;

/*
static char tRxBuf[256];
static char tTxBuf[256];
*/

static bool uartInitFlag = false;

void UART_WriteTransport (uint8_t *str, uint16_t len)
{
    /*
    if(uartInitFlag)
    {
        memset(tTxBuf, 0, sizeof(tTxBuf));
        
        memcpy(tTxBuf, str, len);
        NPITLUART_writeTransport(len);
    }
    */
}

void UartReadCallBack(UART_Handle handle, void *buf, size_t count)
{
    /*
    if(uartInitFlag == true)
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
    */
}


void uartInit()
{
    if(!uartInitFlag)
    {
        UART_Params params;
        UART_Params_init(&params);

        params.readMode = UART_MODE_CALLBACK;
        params.writeMode = UART_MODE_CALLBACK;

        params.readCallback = UartReadCallBack;
        params.writeCallback = NULL;
        params.readReturnMode = UART_RETURN_FULL;
        params.readDataMode = UART_DATA_BINARY;
        params.writeDataMode = UART_DATA_BINARY;
        params.readEcho = UART_ECHO_OFF;
        params.baudRate = 115200;
        params.dataLength = UART_LEN_8;
        params.stopBits = UART_STOP_ONE;
        params.parityType = UART_PAR_NONE;

        uartHandle = UART_open(Board_UART, &params);
        if (!uartHandle)
        {
            ledBlinkWithParameters(LED_INDEX_0, 1000, 200, 10);
        }
        uartInitFlag = true;
        UART_write(uartHandle, "HELLO\r\n", 7);
    }
}
