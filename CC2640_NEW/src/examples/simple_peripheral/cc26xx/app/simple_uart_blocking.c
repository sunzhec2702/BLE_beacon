#include "simple_uart_blocking.h"

#include "simple_led.h"
#include <string.h>
#include <stdio.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include "Board.h"

static UART_Handle uartHandle;

static uint8_t tRxBuf[256];
static uint8_t tTxBuf[256];

static bool uartInitFlag = false;

void uartWriteTransportBKMode(uint8_t *str, uint16_t len)
{
    if(uartInitFlag == true)
    {
        memset(tTxBuf, 0, sizeof(tTxBuf));
        memcpy(tTxBuf, str, len);
        UART_write(uartHandle, str, len);
    }
}

void uartInitBKMode()
{
    if(!uartInitFlag)
    {
        UART_Params params;
        UART_Params_init(&params);

        params.readMode = UART_MODE_BLOCKING;
        params.writeMode = UART_MODE_BLOCKING;

        params.readCallback = NULL;
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
        UART_control(uartHandle, UARTCC26XX_CMD_RETURN_PARTIAL_ENABLE,  NULL);
        if (!uartHandle)
        {
            ledBlinkWithParameters(LED_INDEX_0, 1000, 200, 10);
        }
        uartInitFlag = true;
        UART_write(uartHandle, "Hello\r\n", 7);
    }
}