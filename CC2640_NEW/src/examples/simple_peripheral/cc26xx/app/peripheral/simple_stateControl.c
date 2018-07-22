#include "simple_stateControl.h"
#include "simple_peripheral.h"
#include "peripheral_observer.h"
#include "simple_advControl.h"
#include "simple_scanProcess.h"
#include "simple_vibra_sensor.h"
#include <ti/sysbios/knl/Clock.h>
#include <Board.h>
#include "simple_led.h"
#include "util.h"
#include "hci.h"
#include "gap.h"

static Clock_Struct bleStateResetClock;
static BEACON_STATUS curState = BEACON_INVALID;
static uint8_t advEnable = false;
static uint16_t targetKeepTime = 0;
static void bleStateResetClockCallback(UArg arg);

BEACON_STATUS getCurState()
{
    return curState;
}

void bleStateInit()
{
    Util_constructClock(&bleStateResetClock, bleStateResetClockCallback, 0, 0, false, 0);
}

void bleChangeBeaconState(BEACON_STATUS state, uint16_t keepTime)
{
    DEBUG_STRING("CurStatus: ");DEBUG_NUMBER(curState);DEBUG_STRING("\r\n");
    DEBUG_STRING("TarStatus: ");DEBUG_NUMBER(state);DEBUG_STRING("\r\n");
    if (state == curState)
    {
        switch (state)
        {
        case BEACON_RAPID:
            break;
        default:
            return;
        }
    }
    switch (state)
    {
    case BEACON_RAPID:
        pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 1);
        bleAdvControl(false);
        updateRapidBit(true);
        applyAdvData();
        bleSetTxPower(MAX_TX_POWER);
        updateAdvInterval(RAPID_ADVERTISING_INTERVAL);
        bleAdvControl(true);
        break;
    case BEACON_COMMUNICATION:
        pwmLedBlinkWithParameters(LED_BLINK_COMMUNICATE_ON_PERIOD, LED_BLINK_COMMUNICATE_OFF_PERIOD, COMMS_STATE_PERIOD / (LED_BLINK_COMMUNICATE_ON_PERIOD + LED_BLINK_COMMUNICATE_OFF_PERIOD));
        bleAdvControl(false);
        resetBeaconTouchInfo();
        updateComBit(true);
        applyAdvData();
        bleSetTxPower(MAX_TX_POWER);
        updateAdvInterval(RAPID_ADVERTISING_INTERVAL);
        bleAdvControl(true);
#ifdef PLUS_OBSERVER
        SimpleBLEPeripheral_scanControl(true);
#endif
        break;
    case BEACON_NORMAL:
        vibraIntControl(false);
        SimpleBLEPeripheral_periodTaskControl(true);
        if(Util_isActive(&bleStateResetClock) == true)
        {
            DEBUG_STRING("Enter Normal Direct\r\n");
            Util_stopClock(&bleStateResetClock);
        }
#ifdef PLUS_OBSERVER
        SimpleBLEPeripheral_scanControl(false);
#endif
        bleAdvControl(false);
        updateRapidBit(false);
        updateComBit(false);
        applyAdvData();
        bleSetTxPower(DEF_TX_POWER);
        updateAdvInterval(DEFAULT_ADVERTISING_INTERVAL);
        bleAdvControl(true);
        break;
    case BEACON_SLEEP:
        // Stop advertising.
        bleAdvControl(false);
        updateRapidBit(false);
        updateComBit(false);
        applyAdvData();
        // Stop Period Task Clock.
        SimpleBLEPeripheral_periodTaskControl(false);
        Util_stopClock(&bleStateResetClock);
        // Enable Vibra Sensor
        vibraIntControl(true);
        break;
    default:
        DEBUG_STRING("Wrong State\r\n");
        curState = BEACON_INVALID;
        return;
        break;
    }
    curState = state;
    if (keepTime > 0)
        Util_restartClock(&bleStateResetClock, keepTime);
}

void bleAdvControl(uint8_t enable)
{
    advEnable = enable;
    // Set the GAP Role Parameters
    GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8_t),
                         &advEnable);
}

void bleSetTxPower(uint8_t level)
{
    uint8_t status = advEnable;
    bleAdvControl(false);
    HCI_EXT_SetTxPowerCmd(level);
    bleAdvControl(status);
}

static void bleStateResetClockCallback(UArg arg)
{
    targetKeepTime = 0;
    SimpleBLEPeripheral_enqueueMsg(SBP_BEACON_STATE_CHANGE_EVT, BEACON_NORMAL, (uint8_t*)&targetKeepTime);
}
