#include "simple_touchRecord.h"
#include "simple_flashI2C.h"
#include "simple_led.h"

#define RECORD_NUM_REG      0x00

static uint8_t recordNum = 3;


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
    if (flashI2CWriteReg(0x00, &recordNum, 1) == true)
    {
        DEBUG_STRING("RecordNum Set\r\n");
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
    //
    if (flashI2CWriteSingle(0x00) == false)
        return;
    if (flashI2CReadReg(0x00, &data, 1) == true)
    {
        recordNum = data;
        pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, recordNum);
        //recordNum++;
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
    //touchRecordWriteNumToFlash();
    touchRecordReadNumFromFlash();
    return;
}