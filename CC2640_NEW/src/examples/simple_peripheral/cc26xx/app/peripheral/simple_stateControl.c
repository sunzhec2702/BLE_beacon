#include "simple_stateControl.h"
#include "peripheral_observer.h"
#include "hci.h"
#include "gap.h"

static uint8_t advEnable = false;

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
