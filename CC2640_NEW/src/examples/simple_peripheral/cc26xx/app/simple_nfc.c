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
#include <ti/sysbios/BIOS.h>
#include "util.h"
#include <Board.h>

#include "simple_nfc_target.h"
#include "simple_nfc_initiator.h"
#include "ble_uart.h"
#include <nfc/nfc.h>
#include "icall_apimsg.h"

// Task configuration
#define NFC_TASK_PRIORITY 1

#ifndef NFC_TASK_STACK_SIZE
#define NFC_TASK_STACK_SIZE 4096
#endif

#define DEFAULT_TASK_TIMEOUT    2000 //ms

nfc_device *pnd;
nfc_context *context;

Task_Struct nfcTask;
Char nfcTaskStack[NFC_TASK_STACK_SIZE];

//static ICall_EntityID selfEntity;
//static ICall_Semaphore sem;

static PIN_State nfcPinStatus;
static Clock_Struct nfcTasksClock;
static bool enableNFC = false;
static Semaphore_Handle nfcSem;

static void scheduleNfcTask(void);

const PIN_Config nfcPinList[] = {
    Board_NFC_ENABLE | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX, // High Active
    PIN_TERMINATE
    };

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

void nfcChipInit()
{
    nfc_init(&context);
    if (context == NULL)
    {
        DEBUG_STRING("Unable to init libnfc");
        return;
    }
    pnd = nfc_open(context, NULL);
    if (pnd == NULL)
    {
        DEBUG_STRING("Cannot open NFC device\r\n");
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
    ble_uart_init();
    nfcChipInit();
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
        DEBUG_STRING("Got a semaphore\r\n");
        scheduleNfcTask();
    }
}

static void scheduleNfcTask()
{
    if (enableNFC == false)
        return;

    uint32_t randomNumber = Util_GetTRNG();
    if ((randomNumber % 2) == 0)
    {
        DEBUG_STRING("Start Target\r\n");
        if (nfcWorkAsTarget(DEFAULT_TASK_TIMEOUT, pnd, context) == NFC_ERROR)
        {
            DEBUG_STRING("Target Error\r\n");
        }
        if (enableNFC == true)
        {
            Util_restartClock(&nfcTasksClock, 500);
        }
    }
    else
    {
        DEBUG_STRING("Start Initiator\r\n");
        if (nfcWorkAsInitiator(DEFAULT_TASK_TIMEOUT, pnd, context) == NFC_ERROR)
        {
            DEBUG_STRING("Initiator Error\r\n");
        }
        if (enableNFC == true)
        {
            Util_restartClock(&nfcTasksClock, 500);
        }
    }
    return;
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