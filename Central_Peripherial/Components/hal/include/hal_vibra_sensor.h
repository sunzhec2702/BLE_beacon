#ifndef HAL_VIBRA_SENSOR_H
#define HAL_VIBRA_SENSOR_H

#include "hal_board.h"

/* Vibra Sensor in on P0.6 */

#define HAL_VIBRA_RISING_EDGE   0
#define HAL_VIBRA_FALLING_EDGE  1

/* Vibra Sensor GPIO */
#define HAL_VIBRA_PORT   P0
#define HAL_VIBRA_BIT    BV(6)
#define HAL_VIBRA_SEL    P0SEL
#define HAL_VIBRA_DIR    P0DIR

/* Vibra Sensor Interrupt config */
#define HAL_VIBRA_EDGEBIT  BV(0) //PICTL[0] for all PORT0 GPIOs.
#define HAL_VIBRA_EDGE  HAL_VIBRA_FALLING_EDGE

/* Vibra Sensor Interrupts */
#define HAL_VIBRA_IEN      IEN1  /* CPU interrupt mask register */
#define HAL_VIBRA_IENBIT   BV(5) /* Mask bit for all of Port_0 */
#define HAL_VIBRA_ICTL     P0IEN /* Port Interrupt Control register */
#define HAL_VIBRA_ICTLBIT  BV(6) /* P0IEN - P0.6 enable/disable bit */
#define HAL_VIBRA_PXIFG    P0IFG /* Interrupt flag at source */

typedef void (*halVibraSensorCBack_t)(void);

void halProcessVibraInterrupt(void);
void HalVibraSensorInterruptControl(bool enable);
void HalVibraSensorConfig (bool interruptEnable);

#endif
