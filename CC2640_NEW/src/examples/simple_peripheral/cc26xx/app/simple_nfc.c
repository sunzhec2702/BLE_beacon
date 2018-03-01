// Create own task function for NFC.
/* Should add functions:
 * Reset NFC by GPIO and init NFC.
 * provide target mode and inititor mode and card sim mode APIs.
 */
#include "simple_nfc.h"
#include "simple_uart.h"
#include "icall.h"
#include <ti/drivers/pin/PINCC26XX.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include "util.h"
#include <Board.h>

// Task configuration
#define NFC_TASK_PRIORITY 1

#ifndef NFC_TASK_STACK_SIZE
#define NFC_TASK_STACK_SIZE 1024
#endif

#define DEFAULT_TASK_TIMEOUT    2000 //ms

Task_Struct nfcTask;
Char nfcTaskStack[NFC_TASK_STACK_SIZE];

//static ICall_EntityID selfEntity;
//static ICall_Semaphore sem;

static PIN_State nfcPinStatus;
static Clock_Struct nfcTasksClock;
static bool enableNFC = false;
static Semaphore_Handle nfcSem;

const PIN_Config nfcPinList[] = {
    Board_NFC_ENABLE | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX, // High Active
    PIN_TERMINATE
    };

static void nfcWorkAsInitiator(uint16_t timeout)
{
    return;
}

static void nfcWorkAsTarget(uint16_t timeout)
{
    
    return;
}



static void nfcTasksTimerCallback(UArg arg)
{
    if (enableNFC == true)
    {
        Semaphore_post(nfcSem);
    }
}

static void controlNFC(bool enable)
{
    if (enable)
        PIN_setOutputValue(&nfcPinStatus, Board_NFC_ENABLE, Board_NFC_ON);
    else
        PIN_setOutputValue(&nfcPinStatus, Board_NFC_ENABLE, Board_LED_OFF);
}

void controlNfcTasks(bool enable)
{
    enableNFC = enable;
    if (Util_isActive(&nfcTasksClock) == false)
    {
        Util_restartClock(&nfcTasksClock, 500);
    }
}

static void simpleNFCInit(void)
{
    //ICall_registerApp(&selfEntity, &sem);
    //simple_beacon_drivers_init();
    PIN_open(&nfcPinStatus, nfcPinList);
#ifdef USE_RCOSC
    RCOSC_enableCalibration();
#endif // USE_RCOSC
    uartInitBKMode();
    nfcSem = Semaphore_create(1, NULL, NULL);
    Util_constructClock(&nfcTasksClock, nfcTasksTimerCallback, 0, 0, false, 0);
}

static void simpleNFCTaskFxn(UArg a0, UArg a1)
{
    // Initialize application
    simpleNFCInit();
    // Application main loop
    for (;;)
    {
        Semaphore_pend(nfcSem, BIOS_WAIT_FOREVER);
        uartEmulatorWriteString("Got a semaphore\r\n");
        nfcWorkAsTarget(DEFAULT_TASK_TIMEOUT);
        //Util_restartClock(&nfcTasksClock, )        
    }
}

void simpleNFCcreateTask(void)
{
    Task_Params taskParams;
    // Configure task
    Task_Params_init(&taskParams);
    taskParams.stack = nfcTaskStack;
    taskParams.stackSize = NFC_TASK_STACK_SIZE;
    taskParams.priority = NFC_TASK_PRIORITY;
    Task_construct(&nfcTask, simpleNFCTaskFxn, &taskParams, NULL);
}