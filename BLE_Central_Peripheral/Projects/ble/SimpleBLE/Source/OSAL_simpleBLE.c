/**************************************************************************************************
 *                                            INCLUDES
 **************************************************************************************************/
 
 /* Application */
#include "OSAL_simpleBLECentral.h"
#include "OSAL_simpleBLEPeripheral.h"
#include "simpleBLEUart.h"
 /*********************************************************************
  * GLOBAL VARIABLES
  */

 uint8 tasksCnt;
 uint16 *tasksEvents;
 pTaskEventHandlerFn tasksArr[MAX_TASKS];

 /*********************************************************************
  * FUNCTIONS
  *********************************************************************/
 
 void osalInitTasks(void)
 {
    ble_uart_init();
    if (1) {
        peripheral_osalInitTasks();
    } else {
        central_osalInitTasks();
    }
 }
 
 /*********************************************************************
 *********************************************************************/
 