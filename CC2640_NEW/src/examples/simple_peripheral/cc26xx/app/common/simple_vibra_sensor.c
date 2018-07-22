#include "simple_vibra_sensor.h"
#include "simple_stateControl.h"
#include "simple_peripheral.h"

#include <stdbool.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/drivers/pin/PINCC26XX.h>
#ifdef USE_ICALL
#include <icall.h>
#endif
#include <inc/hw_ints.h>

#define VIBRA_TRIGGER_THRESHOLD     5

//static void Board_keyChangeHandler(UArg a0);
static void vibraSensorCallback(PIN_Handle hPin, PIN_Id pinId);
static void vibraSensorCheckHandler(UArg a0);
static uint8_t vibraTimes = 0;
// Memory for the GPIO module to construct a Hwi
// Hwi_Struct callbackHwiKeys;

// PIN configuration structure to set all KEY pins as inputs with pullups enabled
PIN_Config vibraIOCfg[] =
{
    Board_Vibra_IO | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN | PIN_NOPULL,
    PIN_TERMINATE
};

PIN_State vibraSensorIO;
PIN_Handle hVibraSensorIO;
static Clock_Struct vibraCheckClock;
static bool vibraTriggered = false;

bool getVibraStatus()
{
    return vibraTriggered;
}

void vibraIntControl(bool enable)
{
    if (enable)
    {
        vibraTriggered = false;
        PIN_setConfig(hVibraSensorIO, PIN_BM_IRQ, Board_Vibra_IO | PINCC26XX_IRQ_BOTHEDGES); // Both Edge
    }
    else
    {
        PIN_setConfig(hVibraSensorIO, PIN_BM_IRQ, Board_Vibra_IO | PINCC26XX_IRQ_DIS);
        Util_stopClock(&vibraCheckClock);
    }
}

void vibraSensorInit()
{
    vibraTriggered = false;
    // Initialize vibra snesor pin. Enable int after callback registered
    hVibraSensorIO = PIN_open(&vibraSensorIO, vibraIOCfg);
    PIN_registerIntCb(hVibraSensorIO, vibraSensorCallback);
    PIN_setConfig(hVibraSensorIO, PINCC26XX_BM_WAKEUP, Board_Vibra_IO | PINCC26XX_WAKEUP_POSEDGE);
    vibraIntControl(false);
    // Setup keycallback for keys
    Util_constructClock(&vibraCheckClock, vibraSensorCheckHandler,
                        VIBRA_SENSOR_CHECK_PERIOD, 0, false, 0);
}

static void vibraSensorCallback(PIN_Handle hPin, PIN_Id pinId)
{
    if (vibraTimes < VIBRA_TRIGGER_THRESHOLD)
    {
        vibraTimes++;
        return;
    }
    else
    {
        vibraTimes = 0;
        vibraTriggered = true;
        vibraIntControl(false);
        Util_startClock(&vibraCheckClock);
        if (getCurState() == BEACON_SLEEP)
        {
            SimpleBLEPeripheral_enqueueMsg(SBP_BEACON_STATE_CHANGE_EVT, BEACON_NORMAL, NULL);
        }
            
    }
}

static void vibraSensorCheckHandler(UArg a0)
{
    //TODO: reset the wake up time left and start the interrupt again.
    //TODO: Sleep mode need to check the timer. or increase the timer period.
    vibraIntControl(true);
}
/*********************************************************************
*********************************************************************/
