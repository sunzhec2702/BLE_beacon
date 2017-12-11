#include "simpleBLENFCInterface.h"
#include "simpleNFCDevice.h"
#include "pn532_uart.h"
#include "nfc-types.h"

// PN532 Applicaiton
static uint8 receiveByte[MAX_PN532_BUF];
static uin16 receiveByteNum = 0;
static uint8 simpleBLENFC_Id;
static bool waitingRespond = false;


static PN532_TASK transceive_callback_event = TASK_NONE;

static struct nfc_device* cur_nfc_dev;

void SimpleBLENFC_Init(uint8 task_id)
{
    // Init the CC2541 application task.
    simpleBLENFC_Id = task_id;
    memset(receiveByte, 0, MAX_PN532_BUF);
    receiveByteNum = 0;

    // Init PN532 device
    cur_nfc_dev = nfc_init();
}

uint8 getSimpleBLENFC_Id()
{
    return simpleBLENFC_Id;
}

uint8* getReceiveByte()
{
    return receiveByte;
}

uint16 getReceiveByteNum()
{
    return receiveByteNum;
}

// We don't check the result.
void sendUartToPN532(uint8 *sendByteBuf, uint16 numByte)
{
    NPI_WriteTransport(sendByteBuf, numByte);
}

static uint16 SimpleBLENFC_ProcessCallBack(PN532_TASK callback_event)
{
    switch (callback_event)
    {
        case TASK_POWER_ON:
        pn532_uart_wakeup(cur_nfc_dev, TASK_NONE);
        break;
        case TASK_POWER_DOWN:
        break;
        default:
        break;
    }
    return 0;
}


uint16 SimpleBLENFC_ProcessEvent(uint8 task_id, uint16 events)
{
    VOID task_id;
    if (events & UART_RECEIVE_TIMEOUT_EVT)
    {
        // printf("Timeout event\n");
        // after this, the receive the data will be discard.
        transceive_callback_event = TASK_NONE;
        return (events ^ UART_RECEIVE_TIMEOUT_EVT);
    }

    if (events & UART_RECEIVE_TRANS_CB_EVT)
    {
        
        return (events ^ UART_RECEIVE_TRANS_CB_EVT);
    }

}

// Copy the received bytes to this instance.
void receiveUartFromPN532(uint8 *receiveByteBuf, uint16 numByte)
{
    osal_stop_timerEx(simpleBLENFC_Id, UART_RECEIVE_TIMEOUT_EVT);
    if (numByte >= MAX_PN532_BUF)
    {
        return;
    }
    receiveByteNum = numByte;
    memcpy(receiveByte, receiveByteBuf, numByte);
    // Let Trans CB event to handle the 
    osal_set_event(simpleBLENFC_Id, UART_RECEIVE_TRANS_CB_EVT);
    return;
}

void PN532Transceive(uint8 *sendByteBuf, uint16 numByte, uint16 timeout, PN532_TASK task_event)
{
    // Send the bytes via UART.
    receiveByteNum = 0;
    memset(receiveByte, 0, MAX_PN532_BUF);
    sendUartToPN532(sendByteBuf, numByte);
    if (timeout > 0 && cb != TASK_NONE)
    {
        transceive_callback_event = task_event;
        osal_start_timerEx(simpleBLENFC_Id, UART_RECEIVE_TIMEOUT_EVT, timeout);
    }
    return;
}

