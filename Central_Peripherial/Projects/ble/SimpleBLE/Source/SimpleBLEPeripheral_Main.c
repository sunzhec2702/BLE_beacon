/**************************************************************************************************
 *                                           Includes
 **************************************************************************************************/
/* Hal Drivers */
#include "hal_types.h"
#include "hal_key.h"
#include "hal_timer.h"
#include "hal_drivers.h"
#include "hal_led.h"

/* OSAL */
#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"
#include "OnBoard.h"
#include "simpleble.h"

/**************************************************************************************************
 * FUNCTIONS
 **************************************************************************************************/

/**************************************************************************************************
 * @fn          main
 *
 * @brief       Start of application.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
int main(void)
{
  /* Initialize hardware */
  HAL_BOARD_INIT();

  // Initialize board I/O
  InitBoard(OB_COLD);

  /* Initialze the HAL driver */
  HalDriverInit();

  /* Initialize NV system */
  osal_snv_init();

  // For quick validation, we don't this.
  {
    int8 ret8 = osal_snv_read(0x80, sizeof(SYS_CONFIG), &sys_config);
    if (NV_OPER_FAILED == ret8)
    {
      simpleBLE_SetAllParaDefault(PARA_ALL_FACTORY);
      simpleBLE_WriteAllDataToFlash();
    }
  }

  /* Initialize LL */

  // 根据S1 按键判断启动从设备或者主设备，
  // 如果启动期间 S1 按键按下，P0_1==0, 则启动主机
  if (false == Check_startup_peripheral_or_central())
  {
    sys_config.role = BLE_ROLE_PERIPHERAL;
    simpleBLE_WriteAllDataToFlash();
  }
  else
  {
    sys_config.role = BLE_ROLE_CENTRAL;
    simpleBLE_WriteAllDataToFlash();
  }

  // 启动串口
  simpleBLE_NPI_init();

  /* Initialize the operating system */
  osal_init_system(sys_config.role);

  /* Enable interrupts */
  HAL_ENABLE_INTERRUPTS();

  // Final board initialization
  InitBoard(OB_READY);

#if defined(POWER_SAVING)
  //    osal_pwrmgr_device( PWRMGR_BATTERY );
  osal_pwrmgr_device(PWRMGR_ALWAYS_ON);
#endif

  /* Start OSAL */
  osal_start_system(); // No Return from here

  return 0;
}

/**************************************************************************************************
                                           CALL-BACKS
**************************************************************************************************/

/*************************************************************************************************
**************************************************************************************************/
