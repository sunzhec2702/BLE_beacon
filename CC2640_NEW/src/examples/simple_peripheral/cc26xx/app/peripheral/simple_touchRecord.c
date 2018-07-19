#include "simple_touchRecord.h"
#include "simple_flashI2C.h"

static uint32_t recordNum = 0;

uint32_t touchRecordGetMacNum()
{
    return recordNum;
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
    return;
}