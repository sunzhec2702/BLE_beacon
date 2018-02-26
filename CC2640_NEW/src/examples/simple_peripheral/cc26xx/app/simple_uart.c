#include "simple_uart.h"
#include "simple_led.h"
#include <string.h>
#include <stdio.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include "Board.h"

static UART_Handle uartHandle;


static uint8_t tRxBuf[256];
static uint8_t tTxBuf[256];


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

void UartWriteCallBack(UART_Handle handle, void *buf, size_t count)
{
    UART_writeCancel(handle);
}
void UartReadCallBack(UART_Handle handle, void *buf, size_t count)
{
    //memcpy(tTxBuf, buf, count);
    UART_write(handle, buf, count);
    UART_read(uartHandle, tRxBuf, sizeof(tRxBuf));
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
        params.writeCallback = UartWriteCallBack;
        params.readReturnMode = UART_RETURN_FULL;
        params.readDataMode = UART_DATA_BINARY;
        params.writeDataMode = UART_DATA_BINARY;
        params.readEcho = UART_ECHO_OFF;
        params.baudRate = 115200;
        params.dataLength = UART_LEN_8;
        params.stopBits = UART_STOP_ONE;
        params.parityType = UART_PAR_NONE;

        uartHandle = UART_open(Board_UART, &params);
        UART_control(uartHandle, UARTCC26XX_CMD_RETURN_PARTIAL_ENABLE,  NULL);
        if (!uartHandle)
        {
            ledBlinkWithParameters(LED_INDEX_0, 1000, 200, 10);
        }
        uartInitFlag = true;
        UART_write(uartHandle, "HELLO\r\n", 7);
        UART_read(uartHandle, tRxBuf, sizeof(tRxBuf));
    }
}
