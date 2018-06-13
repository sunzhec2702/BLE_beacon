#include "simple_scanProcess.h"
#include "util.h"
#include "simple_led.h"
#include "simple_advControl.h"
#include "simple_stateControl.h"
#include "peripheral_observer.h"
#include "simple_peripheral.h"

#define COMMS_RSSI_THRES    (-35)

#ifdef PLUS_OBSERVER
static bool scanningStarted = false;
static uint8_t deviceInfoCnt = 0;

void scanProcessInit()
{
    
}

void updateScanInterval()
{

}

void SimpleBLEPeripheral_scanControl(uint8_t enable)
{
    if (enable)
    {
        uint8 status;
        //Start scanning if not already scanning
        if ((scanningStarted == false))
        {
            status = GAPObserverRole_StartDiscovery(DEFAULT_DISCOVERY_MODE,
                                                    DEFAULT_DISCOVERY_ACTIVE_SCAN,
                                                    DEFAULT_DISCOVERY_WHITE_LIST);
            if (status == SUCCESS)
            {
                scanningStarted = true;
                DEBUG_STRING("Scanning On\r\n");
            }
            else
            {
                DEBUG_STRING("Scanning failed\r\n");
            }
        }
    }
    else
    {
        uint8 status;
        if (scanningStarted == true)
        {
            status = GAPObserverRole_CancelDiscovery();
            if (status == SUCCESS)
            {
                scanningStarted = FALSE;
                DEBUG_STRING("Scanning Off\r\n");
            }
            else
            {
                DEBUG_STRING("Scanning Off Fail\r\n");
            }
        }
    }
    return;
}

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
            static uint16_t targetKeepTime = 0;
            DEBUG_STRING("Got a pair\r\n");
            ledBlinkWithParameters(LED_INDEX_0,LED_BLINK_ON_PERIOD, LED_BLINK_RAPID_OFF_PERIOD, 3);
            SimpleBLEPeripheral_enqueueMsg(SBP_BEACON_STATE_CHANGE_EVT, BEACON_NORMAL, (uint8_t*)&targetKeepTime);
        }
    }
}

void scanDoneCB(gapDevDiscEvent_t *data)
{
    DEBUG_STRING("scanDone\r\n");
    scanningStarted = false;
}

bool filterCommFlag(uint8_t *data)
{
    if ((data[ADV_FLAG_BYTE] & (0x1 << ADV_FLAG_COMMS_BIT)))
        return true;
    else
        return false;
}

#endif