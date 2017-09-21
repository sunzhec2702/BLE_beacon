/**************************************************************************************************
 *                                            INCLUDES
 **************************************************************************************************/
#include "hal_types.h"
#include "OSAL.h"
#include "OSAL_Tasks.h"

/* HAL */
#include "hal_drivers.h"

/* LL */
#include "ll.h"

/* HCI */
#include "hci_tl.h"

#if defined ( OSAL_CBTIMER_NUM_TASKS )
  #include "osal_cbtimer.h"
#endif

/* L2CAP */
#include "l2cap.h"

/* gap */
#include "gap.h"
#include "gapgattserver.h"
#include "gapbondmgr.h"

/* GATT */
#include "gatt.h"

#include "gattservapp.h"

/* Profiles */
#include "central.h"

/* Application */
#include "simpleBLECentral.h"

/*********************************************************************
 * GLOBAL VARIABLES
 */

// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr_central[] =
{
  LL_ProcessEvent,
  Hal_ProcessEvent,
  HCI_ProcessEvent,
#if defined ( OSAL_CBTIMER_NUM_TASKS )
  OSAL_CBTIMER_PROCESS_EVENT( osal_CbTimerProcessEvent ),
#endif
  L2CAP_ProcessEvent,
  GAP_ProcessEvent,
  GATT_ProcessEvent,
  SM_ProcessEvent,
  GAPCentralRole_ProcessEvent,
  GAPBondMgr_ProcessEvent,
  GATTServApp_ProcessEvent,
  SimpleBLECentral_ProcessEvent
};

extern uint8 tasksCnt;
extern uint16 *tasksEvents;
extern pTaskEventHandlerFn tasksArr[];

/*********************************************************************
 * FUNCTIONS
 *********************************************************************/

/*********************************************************************
 * @fn      osalInitTasks
 *
 * @brief   This function invokes the initialization function for each task.
 *
 * @param   void
 *
 * @return  none
 */
void osalInitCentralTasks( void )
{
  uint8 taskID = 0;

  tasksCnt = sizeof( tasksArr_central ) / sizeof( tasksArr_central[0] );  
  osal_memcpy(tasksArr, tasksArr_central, sizeof( tasksArr_central));    
    
  tasksEvents = (uint16 *)osal_mem_alloc( sizeof( uint16 ) * tasksCnt);
  osal_memset( tasksEvents, 0, (sizeof( uint16 ) * tasksCnt));

  /* LL Task */
  LL_Init( taskID++ );

  /* Hal Task */
  Hal_Init( taskID++ );

  /* HCI Task */
  HCI_Init( taskID++ );

#if defined ( OSAL_CBTIMER_NUM_TASKS )
  /* Callback Timer Tasks */
  osal_CbTimerInit( taskID );
  taskID += OSAL_CBTIMER_NUM_TASKS;
#endif

  /* L2CAP Task */
  L2CAP_Init( taskID++ );

  /* GAP Task */
  GAP_Init( taskID++ );

  /* GATT Task */
  GATT_Init( taskID++ );

  /* SM Task */
  SM_Init( taskID++ );

  /* Profiles */
  GAPCentralRole_Init( taskID++ );
  GAPBondMgr_Init( taskID++ );

  GATTServApp_Init( taskID++ );

  /* Application */
  SimpleBLECentral_Init( taskID );
}

/*********************************************************************
*********************************************************************/