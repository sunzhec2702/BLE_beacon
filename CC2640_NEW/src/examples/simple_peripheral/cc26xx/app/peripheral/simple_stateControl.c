#include "simple_stateControl.h"
#include "simple_peripheral.h"
#include "peripheral_observer.h"
#include "simple_advControl.h"
#include <ti/sysbios/knl/Clock.h>
#include <Board.h>
#include "simple_led.h"
#include "util.h"
#include "hci.h"
#include "gap.h"

#ifdef PLUS_OBSERVER
static bool scanningStarted = false;
static uint8_t deviceInfoCnt = 0;
#endif

static Clock_Struct bleStateClock;
static BEACON_STATUS curState = BEACON_INVALID;
static uint8_t advEnable = false;
static void bleStateClockCallback(UArg arg);

BEACON_STATUS getCurState()
{
    return curState;
}

void bleStateInit()
{
    Util_constructClock(&bleStateClock, bleStateClockCallback, 0, 0, false, 0);
}


void bleChangeBeaconState(BEACON_STATUS state, uint16_t keepTime)
{
    DEBUG_STRING("CurStatus: ");DEBUG_NUMBER(curState);DEBUG_STRING("\r\n");
    DEBUG_STRING("TarStatus: ");DEBUG_NUMBER(state);DEBUG_STRING("\r\n");
    if (state > curState)
    {
        DEBUG_STRING("Priority Error\r\n");
        return;
    }
    switch (state)
    {
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
    case BEACON_NORMAL:
        bleAdvControl(false);
        updateRapidBit(false);
        updateComBit(false);
        applyAdvData();
        bleSetTxPower(DEFAULT_TX_POWER);
        bleAdvControl(true);
        break;
    case BEACON_SLEEP:
        break;
    default:
        DEBUG_STRING("Wrong State\r\n");
        curState = BEACON_INVALID;
        return;
        break;
    }
    curState = state;
    if (keepTime > 0)
        Util_restartClock(&bleStateClock, keepTime);
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

#ifdef PLUS_OBSERVER
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
#endif

static void bleStateClockCallback(UArg arg)
{
    bleChangeBeaconState(BEACON_NORMAL, 0);
}
