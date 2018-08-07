#include "simple_touchRecord.h"
#include "simple_advControl.h"
#include "simple_flashI2C.h"
#include "simple_led.h"

#define RECORD_NUM_INDEX 0x00
#define BASE_SLAVE_ADDR 0x50
#define MAC2REG(x) (x << 2)
#define MACADDRSIZE 4
#define MAX_TOUCH_PEOPLE    10
/*
 * We use 4 bytes to record the Mac Address. (A-B-C-D-E-F)
 * SUM(A+B+C)-D-E-F
 * macData[3] = SUM, macData[2~0] = D-E-F;
 * eeprom 0x00-0x03 is used to record the num.
 * 0x04~0x07,0x08~0x0B, 0x0C~0x0F.
 * the first 8 bits of the 10 bits register address are the page index.
 * the first 2 bits of the 10 bits are embedded in the slave address.
 */

static uint8_t recordNum = 0;
static uint8_t oneTimeNum = 0;
static uint8_t oneTimeRecords[MACADDRSIZE*MAX_TOUCH_PEOPLE];
static uint8_t macUpdateSec = MAC_RECORD_UPDATE_SEC_PERIOD;
static uint8_t curAdvMacIndex = 0;

uint8_t touchRecordGetMacNum()
{
    return recordNum;
}

static void calSlaveAddrRegAddr(uint8_t macIndex, uint8_t *devAddr, uint8_t *regAddr)
{
    *devAddr = BASE_SLAVE_ADDR + ((MAC2REG(macIndex) >> 8) & 0x3);
    *regAddr = MAC2REG(macIndex) & 0xFF;
}

static void macAddr2Data(uint8_t *macAddr, uint8_t *macData)
{
    macData[MACADDRSIZE - 1] = (macAddr[5] + macAddr[4] + macAddr[3]) & 0xFF;
    macData[MACADDRSIZE - 2] = macAddr[2];
    macData[MACADDRSIZE - 3] = macAddr[1];
    macData[MACADDRSIZE - 4] = macAddr[0];
}

static bool writeMac2Flash(uint8_t macIndex, uint8_t *macAddr)
{
#if (BOARD_TYPE == DEVELOP_BOARD)
    return true;
#else
    uint8_t devAddr = 0, regAddr = 0;
    uint8_t macData[MACADDRSIZE];
    bool ret = true;
    calSlaveAddrRegAddr(macIndex, &devAddr, &regAddr);
    macAddr2Data(macAddr, macData);
    ret = i2cFlashOpen(devAddr);
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
#endif
}

static bool readMacFromFlash(uint8_t macIndex, uint8_t *macData)
{
#if (BOARD_TYPE == DEVELOP_BOARD)
    return true;
#else
    uint8_t devAddr = 0, regAddr = 0;
    bool ret = true;
    calSlaveAddrRegAddr(macIndex, &devAddr, &regAddr);
    ret = i2cFlashOpen(devAddr);
    if (ret == false)
    {
        DEBUG_STRING("I2C Open failed\r\n");
        return ret;
    }
    ret = flashI2CReadReg(regAddr, macData, MACADDRSIZE);
    if (ret == false)
    {
        DEBUG_STRING("i2c read reg fail\r\n");
    }
    i2cFlashClose();
    return ret;
#endif
}

static bool writeNum2Flash(uint8_t number)
{
    uint8_t data[B_ADDR_LEN] = {0, 0, 0, 0, 0, number};
    return writeMac2Flash(RECORD_NUM_INDEX, data);
}

static uint8_t readNumFromFlash()
{
    uint8_t data[MACADDRSIZE] = {0};
    readMacFromFlash(RECORD_NUM_INDEX, data);
    return data[MACADDRSIZE-1];
}

bool touchRecordReset()
{
    recordNum = 0;
    return true;
}

void touchRecordInit()
{
    i2cFlashInit();
    recordNum = 0;
    return;
}

bool touchRecordAddMac(uint8_t *macAddr)
{
    bool ret = true;
    recordNum++;
    ret = writeMac2Flash(recordNum, macAddr);
    if (ret == true)
        touchSecEventReset();
    return ret;
}

bool touchRecordOneTimeMacCheck(uint8_t *macAddr)
{
    for (uint8_t i = 0; i < oneTimeNum; i++)
    {
        if (memcmp(&oneTimeRecords[i * MACADDRSIZE], macAddr, MACADDRSIZE) == 0)
            return false;
    }
    return true;
}

void touchSecEventReset()
{
    macUpdateSec = MAC_RECORD_UPDATE_SEC_PERIOD;
    curAdvMacIndex = recordNum;
}

void touchRecordGotAPair(uint8_t *macAddr)
{
    if (touchRecordOneTimeMacCheck(macAddr) == false)
        return;
    updateBeaconTouchMac(devInfo->addr);
    if (touchRecordAddMac(devInfo->addr) == true)
        pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, (2000) / (LED_BLINK_ON_PERIOD + LED_BLINK_OFF_PERIOD));
    else
        pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 2);
    SimpleBLEPeripheral_scanControl(false);
}

void touchRecordSecEvent()
{
    bool ret = true;
    uint8_t readMacData[MACADDRSIZE];
    if (recordNum == 0)
        return;
    macUpdateSec--;
    if (macUpdateSec == 0)
    {
        macUpdateSec = MAC_RECORD_UPDATE_SEC_PERIOD;
        ret = readMacFromFlash(curAdvMacIndex, readMacData);
        if (ret == true)
        {
            updateBeaconTouchData(readMacData);
            if (curAdvMacIndex == recordNum)
                curAdvMacIndex = 1;
            else
                curAdvMacIndex += 1;
        }
    }
}
