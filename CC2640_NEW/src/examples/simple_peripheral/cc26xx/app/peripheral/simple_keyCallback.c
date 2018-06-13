#include "simple_keyCallback.h"
#include "simple_stateControl.h"
#include "simple_beacon_configuration.h"

void peripheralKeyCallback(uint16_t key)
{
    switch (key)
    {
    case KEY_SELECT:
        bleChangeBeaconState(BEACON_RAPID, RAPID_STATE_PERIOD);
        break;
    case KEY_SELECT_LONG:
        bleChangeBeaconState(BEACON_COMMUNICATION, COMMS_STATE_PERIOD);
        break;
    }
}