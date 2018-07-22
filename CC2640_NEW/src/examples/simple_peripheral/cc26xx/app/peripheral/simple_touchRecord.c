#include "simple_touchRecord.h"
#include "simple_flashI2C.h"

#define RECORD_NUM_REG      0x00

static uint8_t recordNum = 10;


uint32_t touchRecordGetMacNum()
{
    return recordNum;
}

void touchRecordWriteNumToFlash()
{
    if (i2cFlashOpen() == false)
    {
        DEBUG_STRING("I2C Open failed\r\n");
        return;
    }
    if (flashI2CWriteSingle(&recordNum) == true)
    {
        DEBUG_STRING("RecordNum Set\r\n");
        recordNum++;
    }
    i2cFlashClose();
}

void touchRecordReadNumFromFlash()
{
    static uint8_t data;
    if (i2cFlashOpen() == false)
    {
        DEBUG_STRING("I2C Open failed\r\n");
        return;
    }
    if (flashI2CRead(&data) == true)
    {
        DEBUG_STRING("Read data ");
        DEBUG_NUMBER(data);
        DEBUG_STRING("\r\n");
        recordNum++;
    }
    i2cFlashClose();
}

void touchRecordAddMac(uint8_t macAddr)
{
    recordNum++;
}

void touchRecordReset()
{
    recordNum = 0;
    return;
}

void touchRecordInit()
{
    //TODO: read structure from the flash and to know the number.
    i2cFlashInit();
    touchRecordWriteNumToFlash();
    touchRecordReadNumFromFlash();
    return;
}