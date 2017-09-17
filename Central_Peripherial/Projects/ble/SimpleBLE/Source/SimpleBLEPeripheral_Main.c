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
  InitBoard( OB_COLD );

  /* Initialze the HAL driver */
  HalDriverInit();

  /* Initialize NV system */
  osal_snv_init();


// For quick validation, we don't this.
#if 1

    // 从设置中读出以保存的数据， 以便决定现在应该是跑主机还是从机
    // 注意， 这里用到了 osal_snv_xxx ， 数据是存在flash里边的， 大家可以找找相关代码和说明
    // 需要注意的是 osal_snv_read 和 osal_snv_write ， 第一个 参数 osalSnvId_t id
    // 这个id， 我们编程可用的是从 0x80 至 0xff, 其中目前程序中可用的空间是 2048 字节
    // 这个大小定义于 osal_snv.c 中， 即以下宏定义， 跟踪代码进去就能看到
    /*
    // NV page configuration
    #define OSAL_NV_PAGE_SIZE       HAL_FLASH_PAGE_SIZE
    #define OSAL_NV_PAGES_USED      HAL_NV_PAGE_CNT
    #define OSAL_NV_PAGE_BEG        HAL_NV_PAGE_BEG
    #define OSAL_NV_PAGE_END       (OSAL_NV_PAGE_BEG + OSAL_NV_PAGES_USED - 1)
    */
    {
        int8 ret8 = osal_snv_read(0x80, sizeof(SYS_CONFIG), &sys_config);
        // 如果该段内存未曾写入过数据， 直接读，会返回 NV_OPER_FAILED ,
        // 我们利用这个特点作为第一次烧录后的运行， 从而设置参数的出厂设置
        if(NV_OPER_FAILED == ret8)
        {
            simpleBLE_SetAllParaDefault(PARA_ALL_FACTORY);
            simpleBLE_WriteAllDataToFlash();
        } 

        // 执行  串口初始化
//        simpleBLE_NPI_init();     
    }
#endif//这一段代码和说明是 amomcu 增加的  

  /* Initialize LL */

  // 根据S1 按键判断启动从设备或者主设备， 
  // 如果启动期间 S1 按键按下，P0_1==0, 则启动主机
  if(false == Check_startup_peripheral_or_central())
  {   
    sys_config.role = BLE_ROLE_PERIPHERAL;
    sys_config.mode = BLE_MODE_iBeacon;
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
  InitBoard( OB_READY );

  #if defined ( POWER_SAVING )
//    osal_pwrmgr_device( PWRMGR_BATTERY );  
    osal_pwrmgr_device( PWRMGR_ALWAYS_ON );
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
