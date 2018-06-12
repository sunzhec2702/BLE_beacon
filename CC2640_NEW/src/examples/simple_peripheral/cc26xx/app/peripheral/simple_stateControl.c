#include "simple_stateControl.h"
#include "peripheral_observer.h"
#include "simple_advData.h"
#include "hci.h"
#include "gap.h"

static BEACON_STATUS curState = BEACON_NORMAL;
static uint8_t advEnable = false;

void bleChangeBeaconState(BEACON_STATUS state)
{
    DEBUG_STRING("Enter Status: ");
    DEBUG_NUMBER(state);
    DEBUG_STRING("\r\n");
    switch (state)
    {
        case BEACON_NORMAL:
        break;
        case BEACON_RAPID:
        bleAdvControl(false);
        updateRapidBit(true);
        applyAdvData();
        bleAdvControl(true);
        break;
        case BEACON_COMMUNICATION:
        bleAdvControl(false);
        updateComBit(true);
        applyAdvData();
        bleAdvControl(true);
        break;
        case BEACON_SLEEP:
        break;
        default:
        DEBUG_STRING("Wrong State\r\n");
        return;
        break;
    }
    curState = state;
}


void bleAdvControl(uint8_t enable)
{
    advEnable = enable;
    // Set the GAP Role Parameters
    GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8_t),
                         &enable);
}

void bleSetTxPower(uint8_t level)
{
    uint8_t status = advEnable;
    bleAdvControl(false);
    HCI_EXT_SetTxPowerCmd(level);
    bleAdvControl(status);
}

