#include "simpleBLEUart.h"
#include "npi.h"
#include "hal_uart.h"
#include "hal_led.h"

#define BLE_UART_BR HAL_UART_BR_115200

void ble_uart_init()
{
    NPI_InitTransport(NpiSerialCallback);
    NPI_WriteTransport("SimpleBLETest_Init\r\n", 20);
    NPI_PrintString("UART Init Done");
}

// 串口回调函数， 下面把该回调函数里实现的功能讲解一下
/*
1, 思路:  当串口收到数据后，就会马上调用以下回调函数，在实际测试中发现，此回调
函数调用频繁， 如果你不执行NPI_ReadTransport函数进行读取， 那么这个回调函数就会
频繁地被执行，但是，你通过串口发送一段数据， 你本意是想处理这一完整一段的数据，所以，
我们在下面引入了时间的处理方法， 也即接收的数据够多或者超时，就读取一次数据， 
然后根据当前的状态决定执行，如果没有连接上，就把所有数据当做AT命令处理， 如果连接
上了，就把数据送到对端。  ---------------amomcu   2014.08.17
*/
static void NpiSerialCallback(uint8 port, uint8 events)
{
    (void)port;                                            //加个 (void)，是未了避免编译告警，明确告诉缓冲区不用理会这个变量
    if (events & (HAL_UART_RX_TIMEOUT | HAL_UART_RX_FULL)) //串口有数据
    {
        uint8 numBytes = 0;

        numBytes = NPI_RxBufLen(); //读出串口缓冲区有多少字节

        if (numBytes == 0)
        {
            return;
        }
        else
        {
            //申请缓冲区buffer
            uint8 *buffer = osal_mem_alloc(numBytes);
            if (buffer)
            {
                //读取读取串口缓冲区数据，释放串口数据
                NPI_ReadTransport(buffer, numBytes);

                //把收到的数据发送到串口-实现回环
                NPI_WriteTransport(buffer, numBytes);
                
                // Process the command.
                ble_command_parse(buffer, numBytes);
                
                //释放申请的缓冲区
                osal_mem_free(buffer);
            }
        }
    }
}

/*
  0xDE
  0xAD // Start flag.
  0x01 // TYPE: LED
  0x31 // LED1/LED2/LED3 HAL_LED_MODE_ON
  */  // Total 4 bytes. StartFlag, TYPE, VALUE
static uint8 command[2];
static uint8 command_len;
static void ble_command_parse(uint8 *buffer, uint8 numBytes)
{
    uint8 i;
    for (i = 0; i < numBytes; i++)
    {
        if (command_len < 2)
        {
            switch(buffer[i])
            {
                case 0xDE:
                if (command_len == 0)
                    command_len++;
                else
                    command_len = 0;
                break;
                case 0xAD:
                if (command_len == 1)
                    command_len++;
                else
                    command_len = 0;
                break;
                default:
                break;
            }
            continue;
        }
        else
        {
            command[command_len-2] = buffer[i];
            command_len++;
        }
    }
    if (command_len == 4) {
        ble_process_command(command);
        osal_memset(command, 0, 2);
    }
}

static void ble_process_command(uint8 *buffer)
{
    switch (buffer[0])
    {
        case 0x01:
        //LED CASE
        HalLedSet(buffer[1] >> 4, buffer[1]&0xF);
        break;
        default:
        break;
    }
}
