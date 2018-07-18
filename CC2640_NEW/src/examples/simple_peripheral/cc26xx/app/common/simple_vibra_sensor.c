#include "simple_vibra_sensor.h"
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

//static void Board_keyChangeHandler(UArg a0);
static void vibraSensorCallback(PIN_Handle hPin, PIN_Id pinId)

    // Memory for the GPIO module to construct a Hwi
    Hwi_Struct callbackHwiKeys;

// PIN configuration structure to set all KEY pins as inputs with pullups enabled
PIN_Config vibraIOCfg[] =
    {
        Board_Vibra_IO | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN | PIN_PULLDOWN,
        PIN_TERMINATE};

PIN_State vibraSensorIO;
PIN_Handle hVibraSensorIO;
static Clock_Struct vibraCheckClock;
static bool vibraTriggered = false;

void vibraIntControl(bool enable)
{
    if (enable)
    {
        PIN_setConfig(hVibraSensorIO, PIN_BM_IRQ, Board_Vibra_IO | PINCC26XX_IRQ_BOTHEDGES); // Both Edge
        
    }
    else
    {
        PIN_setConfig(hVibraSensorIO, PIN_BM_IRQ, Board_Vibra_IO | PINCC26XX_IRQ_DIS); // Both Edge
    }
}

void vibraSensorInit()
{
    // Initialize vibra snesor pin. Enable int after callback registered
    hVibraSensorIO = PIN_open(&vibraSensorIO, vibraIOCfg);
    PIN_registerIntCb(hVibraSensorIO, vibraSensorCallback);
    PIN_setConfig(hVibraSensorIO, PINCC26XX_BM_WAKEUP, Board_Vibra_IO | PINCC26XX_WAKEUP_POSEDGE);
    vibraIntControl(true);
    // Setup keycallback for keys
    Util_constructClock(&vibraCheckClock, vibraSensorCheckHandler,
                        VIBRA_SENSOR_CHECK_PERIOD, 0, false, 0);
}

static void vibraSensorCallback(PIN_Handle hPin, PIN_Id pinId)
{
    vibraTriggered = true;
    vibraIntControl(false);
    Util_startClock(&vibraCheckClock);
}

static void vibraSensorCheckHandler(UArg a0)
{
    //TODO: reset the wake up time left and start the interrupt again.
    vibraIntControl(true);
}
/*********************************************************************
*********************************************************************/
