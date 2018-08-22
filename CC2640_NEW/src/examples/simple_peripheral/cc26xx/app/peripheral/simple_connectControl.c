#include "simple_connectControl.h"
#include "simple_gatt_profile.h"

// TODO: add a disconnect clock.
bool beaconConnected = false;

void connectControlInit()
{
    beaconConnected = false;
}

void updateConnectedStatus(bool connected)
{
    beaconConnected = connected;
    //TODO: start clock periold.
}

void profileCharValueChangeCB(uint8_t value)
{
    DEBUG_STRING("Char ");
    DEBUG_NUMBER(value);
    DEBUG_STRING(" : changed\r\n");
    uint8_t newValue;
    switch (value)
    {
    case SIMPLEPROFILE_CHAR1:
        SimpleProfile_GetParameter(SIMPLEPROFILE_CHAR1, &newValue);
        break;

    case SIMPLEPROFILE_CHAR3:
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
}