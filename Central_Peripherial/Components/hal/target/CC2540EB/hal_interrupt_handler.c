#include "hal_interrupt_handler.h"

/***************************************************************************************************
 *                                    INTERRUPT SERVICE ROUTINE
 ***************************************************************************************************/

/**************************************************************************************************
 * @fn      halPort0Isr
 *
 * @brief   Port0 ISR
 *
 * @param
 *
 * @return
 **************************************************************************************************/
HAL_ISR_FUNCTION( halPort0Isr, P0INT_VECTOR )
{
  HAL_ENTER_ISR();

#if (TARGET_BOARD == DEVELOP_BOARD)
  if( (HAL_KEY_SW_6_PXIFG & HAL_KEY_SW_6_BIT) || (HAL_KEY_SW_7_PXIFG & HAL_KEY_SW_7_BIT) )
  {
    halProcessKeyInterrupt();
    /*
        Clear the CPU interrupt flag for Port_0
        PxIFG has to be cleared before PxIF
    */
    HAL_KEY_SW_6_PXIFG &= ~HAL_KEY_SW_6_BIT;
    HAL_KEY_SW_7_PXIFG &= ~HAL_KEY_SW_7_BIT;
  }
#elif (TARGET_BOARD == PRODUCT_BOARD)
  if( (HAL_KEY_SW_6_PXIFG & HAL_KEY_SW_6_BIT) )
  {
    halProcessKeyInterrupt();
    HAL_KEY_SW_6_PXIFG &= ~HAL_KEY_SW_6_BIT;
  }
  if ( (HAL_VIBRA_PXIFG & HAL_VIBRA_BIT))
  {
    halProcessVibraInterrupt();
    HAL_VIBRA_PXIFG &= ~HAL_VIBRA_BIT;
  }
#endif
  HAL_KEY_CPU_PORT_0_IF = 0;
  CLEAR_SLEEP_MODE();
  HAL_EXIT_ISR();
  return;
}

#if (TARGET_BOARD == DEVELOP_BOARD)
/**************************************************************************************************
 * @fn      halKeyPort2Isr
 *
 * @brief   Port2 ISR
 *
 * @param
 *
 * @return
 **************************************************************************************************/
HAL_ISR_FUNCTION( halKeyPort2Isr, P2INT_VECTOR )
{
  HAL_ENTER_ISR();
  if (HAL_KEY_JOY_MOVE_PXIFG & HAL_KEY_JOY_MOVE_BIT)
  {
    halProcessKeyInterrupt();
  }
  /*
    Clear the CPU interrupt flag for Port_2
    PxIFG has to be cleared before PxIF
    Notes: P2_1 and P2_2 are debug lines.
  */
  HAL_KEY_JOY_MOVE_PXIFG = 0;
  HAL_KEY_CPU_PORT_2_IF = 0;
  CLEAR_SLEEP_MODE();
  HAL_EXIT_ISR();
  return;
}
#endif