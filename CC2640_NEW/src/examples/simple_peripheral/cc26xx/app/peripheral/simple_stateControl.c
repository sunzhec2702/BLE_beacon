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
        ledBlinkWithParameters(LED_INDEX_0, LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 1);
        bleAdvControl(false);
        updateRapidBit(true);
        applyAdvData();
        bleAdvControl(true);
        break;
        case BEACON_COMMUNICATION:
        ledBlinkWithParameters(LED_INDEX_0, LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 3);
        bleAdvControl(false);
        updateComBit(true);
        applyAdvData();
        bleSetTxPower(MAX_TX_POWER);
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

