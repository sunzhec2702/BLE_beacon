/******************************************************************************

 @file  dual_image_concept_img_b.c

 @brief This file contains the dual image concept sample application to
        demonstrate a proprietary image on a CC1350.

 Group: WCS, BTS
 Target Device: CC2650, CC2640, CC1350

 ******************************************************************************
 
 Copyright (c) 2014-2016, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble_sdk_2_02_01_18
 Release Date: 2016-10-26 15:20:04
 *****************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include <string.h>
#include <stdlib.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>

#include <driverlib/vims.h>
#include <driverlib/flash.h>

#include "hal_board.h"
#include "hal_mcu.h"
//#include "osal_snv.h"
#include "nvocop.h"

#include "util.h"
#include <ti/mw/display/Display.h>
#include "board_key.h"
#include "board.h"

/*********************************************************************
 * CONSTANTS
 */
// Task configuration
#define DIC_TASK_PRIORITY                     1

#ifndef DIC_TASK_STACK_SIZE
#define DIC_TASK_STACK_SIZE                   644
#endif

// Internal Events for RTOS application
#define DIC_STATE_CHANGE_EVT                  0x0001
#define DIC_KEY_CHANGE_EVT                    0x0002

// Image select symbols
#define LOAD_IMG_A                            0x01
#define LOAD_IMG_B                            0x02

#define NV_ID_SHARED_DATA                     0x80
#define NV_ID_IMAGE_EXECUTE                   0x81

// Key to press to switch images
#if defined (CC2650_LAUNCHXL) || defined (CC1350_LAUNCHXL)
#define DIC_SWITCH_IMAGE_BUTTON               Board_BTN2
#elif defined (CC2650DK_7ID)  || defined (CC1350DK_7XD)
#define DIC_SWITCH_IMAGE_BUTTON               KEY_SELECT
#endif

/*********************************************************************
 * TYPEDEFS
 */

// App event passed from profiles.
typedef struct
{
  appEvtHdr_t hdr; // Event header
  uint8_t *pData;  // Event data
} dicEvt_t;

/*********************************************************************
 * GLOBAL VARIABLES
 */

// Display Interface
Display_Handle dispHandle = NULL;

/*********************************************************************
 * LOCAL VARIABLES
 */

// Semaphore globally used to post events to the application thread
static Semaphore_Handle sem;

// Queue object used for app messages
static Queue_Struct appMsg;
static Queue_Handle appMsgQueue;

// Task configuration
Task_Struct dicTask;
Char dicTaskStack[DIC_TASK_STACK_SIZE];

// Data shared between image A and B.
uint8_t sharedData = 0;

/*********************************************************************
 * LOCAL FUNCTIONS
 */

static void DualImageConcept_init( void );
static void DualImageConcept_taskFxn(UArg a0, UArg a1);

static void DualImageConcept_processAppMsg(dicEvt_t *pMsg);
static void DualImageConcept_enqueueMsg(uint8_t event, uint8_t state,
                                        uint8_t *pData);

static void DualImageConcept_handleKeys(uint8_t shift, uint8_t keys);
void DualImageConcept_keyChangeHandler(uint8 keys);
static void switchImage(void);

/*********************************************************************
 * GLOBAL FUNCTIONS
 */

#ifdef CC1350_LAUNCHXL
PIN_State  radCtrlState;
PIN_Config radCtrlCfg[] = 
{
  Board_DIO1_RFSW   | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, /* RF SW Switch defaults to sub-1GHz path */
  Board_DIO30_SWPWR | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, /* Power to the RF Switch */
  PIN_TERMINATE
};
PIN_Handle radCtrlHandle;
#endif //CC1350_LAUNCHXL

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      DualImageConcept_createTask
 *
 * @brief   Task creation function for the Dual Image Concept.
 *
 * @param   None.
 *
 * @return  None.
 */
void DualImageConcept_createTask(void)
{
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = dicTaskStack;
  taskParams.stackSize = DIC_TASK_STACK_SIZE;
  taskParams.priority = DIC_TASK_PRIORITY;

  Task_construct(&dicTask, DualImageConcept_taskFxn, &taskParams, NULL);
}

/*********************************************************************
 * @fn      DualImageConcept_init
 *
 * @brief   Called during initialization and contains application
 *          specific initialization (ie. hardware initialization/setup,
 *          table initialization, power up notification, etc), and
 *          profile initialization/setup.
 *
 * @param   None.
 *
 * @return  None.
 */
static void DualImageConcept_init(void)
{
  // Checked for shared data
  NVINTF_itemID_t id;

  // Create semaphore
  sem = Semaphore_create(0, NULL, NULL);

  // Create an RTOS queue for message from profile to be sent to app.
  appMsgQueue = Util_constructQueue(&appMsg);

  Board_initKeys(DualImageConcept_keyChangeHandler);

  dispHandle = Display_open(Display_Type_LCD, NULL);

  Display_print0(dispHandle, 0, 0, "CC1350 Image B");

  NVOCOP_initNV(NULL);  

  id.itemID = NV_ID_SHARED_DATA;
  NVOCOP_readItem(id, 0, sizeof(uint8_t), &sharedData);

  // Write the shared data to the LCD.
  Display_print1(dispHandle, 6, 0, "Shared Data: %d", sharedData);
}

/*********************************************************************
 * @fn      DualImageConcept_taskFxn
 *
 * @brief   Application task entry point for the Dual Image Concept.
 *
 * @param   a0, a1 - not used.
 *
 * @return  None.
 */
static void DualImageConcept_taskFxn(UArg a0, UArg a1)
{
  // Initialize application
  DualImageConcept_init();

  // Application main loop
  for (;;)
  {
    // Waits for a signal to the semaphore associated with the calling thread.
    Semaphore_pend(sem, BIOS_WAIT_FOREVER);

    // If RTOS queue is not empty, process app message.
    while (!Queue_empty(appMsgQueue))
    {
      dicEvt_t *pMsg = (dicEvt_t *)Util_dequeueMsg(appMsgQueue);

      if (pMsg)
      {
        // Process message.
        DualImageConcept_processAppMsg(pMsg);

        // Free the space from the message.
        free(pMsg);
      }
    }
  }
}

/*********************************************************************
 * @fn      DualImageConcept_processAppMsg
 *
 * @brief   Process an incoming callback from a profile.
 *
 * @param   pMsg - message to process
 *
 * @return  None.
 */                       
static void DualImageConcept_processAppMsg(dicEvt_t *pMsg)
{
  switch (pMsg->hdr.event)
  {
    case DIC_KEY_CHANGE_EVT:
      DualImageConcept_handleKeys(0, pMsg->hdr.state);
      break;
      
    default:
      // Do nothing.
      break;
  }
}

/*********************************************************************
 * @fn      DualImageConcept_keyChangeHandler
 *
 * @brief   Key event handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
void DualImageConcept_keyChangeHandler(uint8 keys)
{
  DualImageConcept_enqueueMsg(DIC_KEY_CHANGE_EVT, keys, NULL);
}

/*********************************************************************
 * @fn      DualImageConcept_handleKeys
 *
 * @brief   Handles all key events for this device.
 *
 * @param   shift - true if in shift/alt.
 * @param   keys - bit field for key events. Valid entries:
 *                 HAL_KEY_SW_2
 *                 HAL_KEY_SW_1
 *
 * @return  none
 */
static void DualImageConcept_handleKeys(uint8_t shift, uint8_t keys)
{
  (void)shift;  // Intentionally unreferenced parameter

  if (keys & DIC_SWITCH_IMAGE_BUTTON)
  {
    NVINTF_itemID_t id;
    
    // Increment and write shared data
    sharedData++;
    //osal_snv_write(NV_ID_SHARED_DATA, sizeof(uint8_t), &sharedData);
    id.itemID = NV_ID_SHARED_DATA;
    NVOCOP_writeItem(id, sizeof(uint8_t), &sharedData);
    
    // Signal a change in images to run.
    switchImage();
    
    // Reset.
    HAL_SYSTEM_RESET();
    
    // Should never get here.
  }
}

/*********************************************************************
 * @fn      DualImageConcept_enqueueMsg
 *
 * @brief   Creates a message and puts the message in RTOS queue.
 *
 * @param   event  - message event.
 * @param   state  - message state.
 * @param   pData  - message data pointer.
 *
 * @return  None.
 */
static void DualImageConcept_enqueueMsg(uint8_t event, uint8_t state, 
                                        uint8_t *pData)
{
  dicEvt_t *pMsg;
  
  // Create dynamic pointer to message.
  if ((pMsg = malloc(sizeof(dicEvt_t))))
  {
    pMsg->hdr.event = event;
    pMsg->hdr.state = state;
    pMsg->pData = pData;
    
    // Enqueue the message.
    Util_enqueueMsg(appMsgQueue, sem, (uint8*)pMsg);
  }
}

/*********************************************************************
 * @fn      switchImage
 *
 * @brief   Write to BIM's ledger page to signal the other image should be
 *          executed after reset.
 *
 * @param   none
 *
 * @return  VIMS state
 */
static void switchImage(void)
{
  NVINTF_itemID_t id;
  uint8_t data;
   
  // Write Image A's ID so that it will be loaded on reset. 
  data = LOAD_IMG_A;
  id.itemID = NV_ID_IMAGE_EXECUTE;
  
  NVOCOP_writeItem(id, sizeof(uint8_t), &data);
}

/*********************************************************************
*********************************************************************/
