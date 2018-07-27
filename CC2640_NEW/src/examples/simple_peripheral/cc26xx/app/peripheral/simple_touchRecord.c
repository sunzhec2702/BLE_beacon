#include "simple_touchRecord.h"
#include "simple_flashI2C.h"
#include "simple_led.h"

#define RECORD_NUM_INDEX 0x00
#define BASE_SLAVE_ADDR 0x50
#define MAC2REG(x) (x << 2)
#define MACADDRSIZE 4
/*
 * We use 4 bytes to record the Mac Address. (A-B-C-D-E-F)
 * SUM(A+B+C)-D-E-F
 * eeprom 0x00-0x03 is used to record the num.
 * 0x04~0x07,0x08~0x0B, 0x0C~0x0F.
 * the first 8 bits of the 10 bits register address are the page index.
 * the first 2 bits of the 10 bits are embedded in the slave address.
 */

static uint8_t recordNum = 0;

uint8_t touchRecordGetMacNum()
{
    return recordNum;
}

void calSlaveAddrRegAddr(uint8_t macIndex, uint8_t *slaveAddr, uint8_t *regAddr)
{
    *slaveAddr = BASE_SLAVE_ADDR + (MAC2REG(macIndex) >> 8) & 0x3;
    *regAddr = MAC2REG(macIndex) & 0xFF;
}

void macAddr2Data(uint8_t *macAddr, uint8_t *macData)
{
    macData[MACADDRSIZE - 1] = (macAddr[5] + macAddr[4] + macAddr[3]) & 0xFF;
    macData[MACADDRSIZE - 2] = macAddr[2];
    macData[MACADDRSIZE - 3] = macAddr[1];
    macData[MACADDRSIZE - 4] = macAddr[0];
}

bool writeMac2Flash(uint8_t macIndex, uint8_t *macAddr)
{
    uint8_t slaveAddr = 0, regAddr = 0;
    uint8_t macData[MACADDRSIZE];
    bool ret = true;
    calSlaveAddrRegAddr(macIndex, &slaveAddr, &regAddr);
    macAddr2Data(macAddr, macData);
    ret = i2cFlashOpen(slaveAddr);
    if (ret == false)
    {
        DEBUG_STRING("mac open i2c failed\r\n");
        return ret;
    }
    ret = flashI2CWriteReg(regAddr, macData, MACADDRSIZE);
    if (ret == false)
    {
        DEBUG_STRING("mac write failed\r\n");
    }
    i2cFlashClose();
    return ret;
}

bool readMacFromFlash(uint8_t macIndex, uint8_t *macData)
{
    uint8_t slaveAddr = 0, regAddr = 0;
    bool ret = true;
    calSlaveAddrRegAddr(macIndex, &slaveAddr, &regAddr);
    ret = i2cFlashOpen(slaveAddr);
    if (ret == false)
    {
        DEBUG_STRING("I2C Open failed\r\n");
        return ret;
    }
    /*
    if (flashI2CWriteSingle(RECORD_NUM_REG) == false)
    {
        DEBUG_STRING("Write Reg failed\r\n");
        i2cFlashClose();
        return;
    }
    */
    ret = flashI2CReadReg(regAddr, macData, MACADDRSIZE);
    if (ret == false)
    {
        DEBUG_STRING("i2c read reg fail\r\n");
    }
    i2cFlashClose();
    return ret;
}

void touchRecordWriteNumToFlash()
{
    if (i2cFlashOpen() == false)
    {
        DEBUG_STRING("I2C Open failed\r\n");
        return;
    }
    if (flashI2CWriteReg(RECORD_NUM_REG, &recordNum, 1) == true)
    {
        DEBUG_STRING("RecordNum Set\r\n");
    }
    i2cFlashClose();
}

bool touchRecordAddMac(uint8_t macAddr)
{
    recordNum++;
}

bool touchRecordReset()
{
    recordNum = 0;
    return;
}

void touchRecordInit()
{
    i2cFlashInit();
    return;
}