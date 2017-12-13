#ifndef __SIMPLE_BLE_NFC_INTERFACE_H_
#define __SIMPLE_BLE_NFC_INTERFACE_H_

#include "../simpleble.h"
#include "simpleBLEPN532StateMachine.h"

#define MAX_PN532_BUF 32

typedef enum
{
    ROLE_CARD = 0,
    ROLE_INITIATOR,
    ROLE_TARGET,
    ROLE_IDLE,
} PN532_ROLE;

typedef enum 
{
    TASK_POWER_ON = 0,
    TASK_POWER_ON_RES,
    TASK_POWER_DOWN,
    TASK_LOW_BATTERY,
    TASK_DIAGNOSE,
    TASK_SAM_CONFIGURATION,
    TASK_GET_FIRMWARE,
    TASK_SET_PARAMETERS,
    TASK_READ_REGISTER,
    TASK_WRITE_REGISTER,
    TASK_RF_CONFIGURATION,
    // High Level
    TASK_CHECK_COMMU,
    TASK_NONE,
} PN532_TASK;

#define UART_RECEIVE_EVT 0x0001
#define UART_RECEIVE_TIMEOUT_EVT 0x0002
#define UART_RECEIVE_TRANS_CB_EVT 0x0004

uint8 getSimpleBLENFC_Id(void);
uint8* getReceiveByte(void);
uint16 getReceiveByteNum(void);

uint16 SimpleBLENFC_ProcessEvent(uint8 task_id, uint16 events);
void receiveUartFromPN532(uint8 *receiveByteBuf, uint16 numByte);
void sendUartToPN532(uint8 *sendByteBuf, uint16 numByte);
int PN532Transceive(uint8 *sendByteBuf, uint16 numByte, uint16 timeout, bool build_frame);
void clear_uart_buffer(void);
void SimpleBLENFC_Init(uint8 task_id);

#endif
