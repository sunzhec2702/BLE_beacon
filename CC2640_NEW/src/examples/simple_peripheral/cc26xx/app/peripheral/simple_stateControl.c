#include "simple_stateControl.h"
#include "simple_peripheral.h"
#include "peripheral_observer.h"
#include "simple_advControl.h"
#include "simple_scanProcess.h"
#include "simple_vibra_sensor.h"
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <Board.h>
#include "simple_led.h"
#include "util.h"
#include "hci.h"
#include "gap.h"

static Clock_Struct bleStateResetClock;
static BEACON_STATUS curState = BEACON_INVALID;
static BEACON_STATUS restoreState = BEACON_NORMAL;
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

// return TRUE to do further process.
static bool bleStateCheck(BEACON_STATUS targetState)
{
    // Process same state situation.
    if (curState == targetState)
    {
        switch (targetState)
        {
        case BEACON_RAPID:
        case BEACON_COMMUNICATION:
            return true;
        default:
            break;
        }
        return false;
    }
    // Process priority issue.
    switch (targetState)
    {
    case BEACON_RAPID:
        if (curState == BEACON_COMMUNICATION)
            return false;
    case BEACON_SLEEP:
        if (curState == BEACON_COMMUNICATION)
        {
            // Retry after COMMS_STATE_PERIOD.
            restoreState = BEACON_SLEEP;
            Util_restartClock(&bleStateResetClock, COMMS_STATE_PERIOD);
            return false;
        }
        break;
    case BEACON_COMMUNICATION:
    case BEACON_NORMAL:
    default:
        break;
    }
    return true;
}

void bleChangeBeaconState(BEACON_STATUS state, uint16_t keepTime)
{
    DEBUG_STRING("CurStatus: ");
    DEBUG_NUMBER(curState);
    DEBUG_STRING("\r\n");
    DEBUG_STRING("TarStatus: ");
    DEBUG_NUMBER(state);
    DEBUG_STRING("\r\n");
    if (bleStateCheck(state) == false)
        return;
    switch (state)
    {
    case BEACON_RAPID:
        restoreState = BEACON_NORMAL;
        pwmLedReset();
        pwmLedBlinkWithParameters(LED_BLINK_ON_PERIOD, LED_BLINK_OFF_PERIOD, 1);
        bleAdvControl(false);
        updateRapidBit(true);
        applyAdvData();
        bleSetTxPower(MAX_TX_POWER);
        updateAdvInterval(RAPID_ADVERTISING_INTERVAL);
        bleAdvControl(true);
        break;
    case BEACON_COMMUNICATION:
        restoreState = BEACON_NORMAL;
        pwmLedReset();
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
        restoreState = BEACON_NORMAL;
        SimpleBLEPeripheral_periodTaskControl(true);
        if (Util_isActive(&bleStateResetClock) == true)
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
        restoreState = BEACON_NORMAL;
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
        curState = BEACON_INVALID;
        restoreState = BEACON_NORMAL;
        DEBUG_STRING("Wrong State\r\n");
        break;
    }
    curState = state;
    if (keepTime > 0)
        Util_restartClock(&bleStateResetClock, keepTime);
}

static void bleStateResetClockCallback(UArg arg)
{
    targetKeepTime = 0;
    SimpleBLEPeripheral_enqueueMsg(SBP_BEACON_STATE_CHANGE_EVT, restoreState, (uint8_t *)&targetKeepTime);
}
