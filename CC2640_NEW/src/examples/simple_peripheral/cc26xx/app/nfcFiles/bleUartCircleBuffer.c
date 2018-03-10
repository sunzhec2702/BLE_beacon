#include "bleUartCircleBuffer.h"
#define BUFFER_SIZE 64
static uint8_t buffer[BUFFER_SIZE];
static uint16_t tail = 0;
static uint16_t head = 0;
static uint16_t emptySize = BUFFER_SIZE;

void bleUartCircleBufferInit(void)
{
    tail = 0;
    head = 0;
    emptySize = BUFFER_SIZE;
}

void bleUartCircleBufferPut(uint8_t *buf, uint16_t number)
{
    if (number > BUFFER_SIZE)
    {
        DEBUG_STRING("Input number is larger than Circle Buffer\r\n");
        return;
    }
    if (number > emptySize)
    {
        head += (number - emptySize);
        head %= BUFFER_SIZE;
        emptySize = number;
    }
    
    uint16_t bufIndex = 0;
    if ((tail + number) > BUFFER_SIZE)
    {
        memcpy(&buffer[tail], buf, BUFFER_SIZE - tail);
        number -= BUFFER_SIZE - tail;
        bufIndex = BUFFER_SIZE - tail;
        emptySize -= BUFFER_SIZE - tail;
        tail = 0;
    }
    memcpy(&buffer[tail], buf + bufIndex, number);
    tail += number;
    tail %= BUFFER_SIZE;
    emptySize -= number;
}

uint16_t bleUartCircleBufferGet(uint8_t *buf, uint16_t number)
{
    uint16_t readNumber = number;
    if (readNumber > (BUFFER_SIZE - emptySize))
    {
        DEBUG_STRING("Input number is larger than Circle Buffer\r\n");
        readNumber = (BUFFER_SIZE - emptySize);
        number = readNumber;
    }
    uint16_t bufIndex = 0;
    if ((head + readNumber) > BUFFER_SIZE)
    {
        memcpy(buf, &buffer[head], BUFFER_SIZE - head);
        readNumber -= BUFFER_SIZE - head;
        bufIndex = BUFFER_SIZE - head;
        emptySize += BUFFER_SIZE - head;
        head = 0;
    }
    memcpy(buf + bufIndex, &buffer[head], readNumber);
    head += readNumber;
    head %= BUFFER_SIZE;
    emptySize += readNumber;
    return number;
}

uint16_t bleUartCircleBufferGetNumber(void)
{
    return (BUFFER_SIZE - emptySize);
}

uint16_t bleUartCircleBufferGetEmptyNumber(void)
{
    return (emptySize);
}