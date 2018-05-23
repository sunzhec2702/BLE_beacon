// Create own task function for NFC.
/* Should add functions:
 * Reset NFC by GPIO and init NFC.
 * provide target mode and inititor mode and card sim mode APIs.
 */
#include "simple_nfc.h"
#include "simple_uart.h"
#include "simple_led.h"
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
#include "hal_trng_wrapper.h"

// Task configuration
#define NFC_TASK_PRIORITY 1

#ifndef NFC_TASK_STACK_SIZE
#define NFC_TASK_STACK_SIZE (3720)
#endif

#define DEFAULT_TARGET_TIMEOUT    10000 //ms
#define DEFAULT_INITIATOR_TIMEOUT 500 //ms

nfc_device *pnd;
nfc_context *context;

Task_Struct nfcTask;
Char nfcTaskStack[NFC_TASK_STACK_SIZE];

//static ICall_EntityID selfEntity;
//static ICall_Semaphore sem;

static PIN_State nfcPinStatus;
static Clock_Struct nfcTasksClock;
static bool enableNFC = true;
static Semaphore_Handle nfcSem;

const PIN_Config nfcPinList[] = {
    Board_NFC_ENABLE | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX, // High Active
    PIN_TERMINATE
    };

bool scheduleNfcTask()
{
    uint32_t randomNumber = HalTRNG_GetTRNG();
    //if ((randomNumber % 2) == 0)
    if (0)
    {
        DEBUG_STRING("Start Target\r\n");
        if (nfcWorkAsTarget(DEFAULT_TARGET_TIMEOUT, pnd, context) == NFC_ERROR)
        {
            DEBUG_STRING("Target Error\r\n");
            return false;
        }
    }
    else
    {
        DEBUG_STRING("Start Initiator\r\n");
        if (nfcWorkAsInitiator(DEFAULT_INITIATOR_TIMEOUT, pnd, context) == NFC_ERROR)
        {
            DEBUG_STRING("Initiator Error\r\n");
            return false;
        }
    }
    return true;
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

void nfcKeyCallback(uint8_t keyStatus)
{
    #if (ENABLE_NFC == 1)
        controlNfcTasks(true);
    #endif
}

void controlNfcTasks(bool enable)
{
    enableNFC = enable;
    if (Util_isActive(&nfcTasksClock) == false)
    {
        Util_restartClock(&nfcTasksClock, 500);
    }
}

bool nfcChipInit(bool lastRes)
{
    if (lastRes == true)
    {
        DEBUG_STRING("LastRes is True\r\n");
        return true;
    }
    if (pnd != NULL)
    {
        DEBUG_STRING("pnd not NULL\r\n");
        nfc_close(pnd);
    }
    if (context != NULL)
    {
        DEBUG_STRING("context not NULL\r\n");
        nfc_exit(context);
    }
    nfc_init(&context);
    if (context == NULL)
    {
        DEBUG_STRING("Unable to init libnfc");
        return false;
    }
    pnd = nfc_open(context, NULL);
    if (pnd == NULL)
    {
        DEBUG_STRING("Cannot open NFC device\r\n");
        return false;
    }
    if (pnd != NULL && context != NULL)
    {
        DEBUG_STRING("ChipInitSuccess\r\n");
    }
    return true;
}

static void simpleNFCInit(void)
{
    //ICall_registerApp(&selfEntity, &sem);
    PIN_open(&nfcPinStatus, nfcPinList);
#ifdef USE_RCOSC
    RCOSC_enableCalibration();
#endif // USE_RCOSC
    ble_uart_init();
    DEBUG_NFC_BYTE("AAAAAA", 6);
    nfcSem = Semaphore_create(0, NULL, NULL);
    Util_constructClock(&nfcTasksClock, nfcTasksTimerCallback, 0, 0, false, 0);
}

static void simpleNFCTaskFxn(UArg a0, UArg a1)
{
    bool lastRes = false;
    uint32_t restartTime = 0;
    // Initialize application
    simpleNFCInit();
    controlNFC(true);
    // Application main loop
    for (;;)
    {
        Semaphore_pend(nfcSem, BIOS_WAIT_FOREVER);
        DEBUG_STRING("Got a semaphore\r\n");
        //controlNFC(true);
        restartTime = (HalTRNG_GetTRNG() % 2000);
        if (nfcChipInit(lastRes) == false)
        {
            //Util_restartClock(&nfcTasksClock, 100);
          continue;
        }
        ledBlinkWithParameters(LED_INDEX_0, 100, 250 + 1000 , 1);
        lastRes = scheduleNfcTask();
        if (lastRes == true)
        {
            ledBlinkWithParameters(LED_INDEX_0, 100, 250 + 1000 , 2);
            //Util_restartClock(&nfcTasksClock, restartTime);
        }
        else
        {
            //ledBlinkWithParameters(LED_INDEX_0, 100, 250 + 1000 , 5);
            //controlNFC(false);
            //Util_restartClock(&nfcTasksClock, restartTime);
        }
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
