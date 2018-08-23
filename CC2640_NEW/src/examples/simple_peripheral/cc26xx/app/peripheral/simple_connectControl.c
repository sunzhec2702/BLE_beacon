#include "simple_connectControl.h"
#include "simple_gatt_profile.h"
#include "simple_touchRecord.h"
#include <ti/sysbios/knl/Clock.h>
#include "util.h"

#define DISCONNECT_TIME_MS          (1*60*1000)
bool beaconConnected = false;
static Clock_Struct disconnectClock;
static void diconnectCallback(UArg arg);

void connectControlInit()
{
    beaconConnected = false;
    Util_constructClock(&disconnectClock, diconnectCallback, 0, 0, false, 0);
}

static void diconnectCallback(UArg arg)
{
    DEBUG_STRING("WILL DISCONNECT\r\n");
    //TODO: add disconnect function.
}

void updateConnectedStatus(bool connected)
{
    beaconConnected = connected;
    //TODO: start clock periold.
    Util_restartClock(&disconnectClock, DISCONNECT_TIME_MS);
}

void profileCharValueChangeCB(uint8_t value)
{
    DEBUG_STRING("Char ");
    DEBUG_NUMBER(value);
    DEBUG_STRING(" : changed\r\n");
    uint8_t newValue;
    switch (value)
    {
    case PROFILE_QUERY_INDEX_CHAR:
        SimpleProfile_GetParameter(PROFILE_QUERY_INDEX_CHAR, &newValue);
        uint8_t macData[SIMPLEPROFILE_CHAR5_LEN] = {0};
        bool ret = 0;
        ret = readMacFromFlash(newValue, &macData[1]);
        if (ret == false)
        {
            DEBUG_STRING("Read Mac index fail\r\n");
        }
        else
        {
            macData[0] = newValue;
            SimpleProfile_SetParameter(PROFILE_MAC_RECORD_CHAR, SIMPLEPROFILE_CHAR5_LEN, macData);
        }
        break;
    case PROFILE_COMMAND_CHAR:
        SimpleProfile_GetParameter(SIMPLEPROFILE_CHAR3, &newValue);
        break;
    default:
        // should not reach here!
        break;
    }
    DEBUG_STRING("newValue: ");
    DEBUG_NUMBER(newValue);
    DEBUG_STRING("\r\n");
    //TODO: reset the disconnect clock.
    Util_restartClock(&disconnectClock, DISCONNECT_TIME_MS);
}