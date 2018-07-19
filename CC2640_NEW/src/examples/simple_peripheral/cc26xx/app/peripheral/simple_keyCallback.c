#include "simple_keyCallback.h"
#include "simple_stateControl.h"
#include "simple_beacon_configuration.h"
#include "simple_led.h"

void peripheralKeyCallback(uint16_t keyEvent)
{
    switch (keyEvent)
    {
    case KEY_SELECT:
        bleChangeBeaconState(BEACON_RAPID, RAPID_STATE_PERIOD);
        break;
    case KEY_SELECT_LONG:
        bleChangeBeaconState(BEACON_COMMUNICATION, COMMS_STATE_PERIOD);
        break;
    }
}