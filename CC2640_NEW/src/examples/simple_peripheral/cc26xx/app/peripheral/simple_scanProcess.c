#include "simple_scanProcess.h"
#include "util.h"
#include "simple_advControl.h"

#define COMMS_RSSI_THRES    (-35)

void scanDevInfoCB(gapDeviceInfoEvent_t* devInfo)
{
    DEBUG_STRING("DEVINFO_CB\r\n");
    if (devInfo->dataLen != 30)
        return;
    DEBUG_STRING(Util_convertBdAddr2Str(devInfo->addr));
    DEBUG_STRING("\r\n");
    DEBUG_NUMBER(devInfo->rssi);
    DEBUG_STRING("\r\n");
    if (filterCommFlag(devInfo->pEvtData))
    {
        DEBUG_STRING("COMMSFLAG\r\n");
        if (devInfo->rssi > COMMS_RSSI_THRES)
        {
            DEBUG_STRING("Got a pair\r\n");
        }
    }
}

bool filterCommFlag(uint8_t *data)
{
    if ((data[ADV_FLAG_BYTE] & (0x1 << ADV_FLAG_COMMS_BIT)) == 0x1)
        return true;
    else
        return false;
}