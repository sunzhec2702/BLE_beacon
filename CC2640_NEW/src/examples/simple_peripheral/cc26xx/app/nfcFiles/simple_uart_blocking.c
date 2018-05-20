#include "simple_uart_blocking.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include <ti/sysbios/knl/Clock.h>
#include <inc/hw_ints.h>
#include "Board.h"


static UART_Handle uartHandle;
static Clock_Struct rxTimeoutClock;


//static uint8_t tRxBuf[256];
//static uint8_t tTxBuf[256];

static bool uartInitFlag = false;
static bool uartRxTimeout = false;

static void rxTimeoutCallback(UArg arg)
{
    UART_readCancel(uartHandle);
    uartRxTimeout = true;
}

int uartReadTransportBKMode(uint8_t *buf, uint16_t exceptLen, void *abort_p, int timeout)
{
    uartRxTimeout = false;
    uint16_t readByte = 0;
    do
    {
        readByte += UART_read(uartHandle, buf+readByte, exceptLen);
        if (timeout > 0)
        {
            Util_restartClock(&rxTimeoutClock, timeout);
        }
    } while ((readByte < exceptLen) && (uartRxTimeout == false));
    //DEBUG_STRING("read bytes: ");
    //DEBUG_NUMBER(readByte);
    Util_stopClock(&rxTimeoutClock);
    if (uartRxTimeout == true)
    {
        return -1;
    }
    return 0;
}

int uartWriteTransportBKMode(const uint8_t *str, uint16_t len)
{
    if (uartInitFlag == true)
    {
        //memset(tTxBuf, 0, sizeof(tTxBuf));
        //memcpy(tTxBuf, str, len);
        UART_write(uartHandle, str, len);
    }
    return 0;
}

void uartInitBKMode()
{
    if (!uartInitFlag)
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
        UART_control(uartHandle, UARTCC26XX_CMD_RETURN_PARTIAL_ENABLE, NULL);
        if (!uartHandle)
        {
            DEBUG_STRING("uart block mode error\r\n");
            return;
        }
        Util_constructClock(&rxTimeoutClock, rxTimeoutCallback, 0, 0, false, 0);
        uartInitFlag = true;
        DEBUG_STRING("Uart Block Mode Init Success\r\n");
    }
}