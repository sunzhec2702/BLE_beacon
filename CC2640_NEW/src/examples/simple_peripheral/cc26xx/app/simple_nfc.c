// Create own task function for NFC.
/* Should add functions:
 * Reset NFC by GPIO and init NFC.
 * provide target mode and inititor mode and card sim mode APIs.
 */
#include "simple_nfc.h"
#include "simple_uart.h"
#include "icall.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include "util.h"
   
// Task configuration
#define NFC_TASK_PRIORITY 1

#ifndef NFC_TASK_STACK_SIZE
#define NFC_TASK_STACK_SIZE 1024
#endif

Task_Struct nfcTask;
Char nfcTaskStack[NFC_TASK_STACK_SIZE];

static ICall_EntityID selfEntity;
static ICall_Semaphore sem;

static void simpleNFCInit(void)
{
    //ICall_registerApp(&selfEntity, &sem);
    //simple_beacon_drivers_init();
#ifdef USE_RCOSC
    RCOSC_enableCalibration();
#endif // USE_RCOSC
    uartInitBKMode();
}

static void simpleNFCTaskFxn(UArg a0, UArg a1)
{
    // Initialize application
    simpleNFCInit();
    uint8_t rxBuf[100];
    // Application main loop
    for (;;)
    {
        //uartReadTransportBKMode(rxBuf, 20, NULL, 60000);
        //uartWriteTransportBKMode(rxBuf, 20);
        //ICall_Errno errno = ICall_wait(ICALL_TIMEOUT_FOREVER);
        /*
        if (errno == ICALL_ERRNO_SUCCESS)
        {
            ICall_EntityID dest;
            ICall_ServiceEnum src;
            ICall_HciExtEvt *pMsg = NULL;

            if (ICall_fetchServiceMsg(&src, &dest,
                                      (void **)&pMsg) == ICALL_ERRNO_SUCCESS)
            {
                uint8 safeToDealloc = TRUE;

                if ((src == ICALL_SERVICE_CLASS_BLE) && (dest == selfEntity))
                {
                    ICall_Stack_Event *pEvt = (ICall_Stack_Event *)pMsg;
                }

                if (pMsg && safeToDealloc)
                {
                    ICall_freeMsg(pMsg);
                }
            }
        }
        */
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