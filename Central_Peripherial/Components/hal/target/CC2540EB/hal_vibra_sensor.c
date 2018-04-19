#include "hal_vibra_sensor.h"
#include "hal_mcu.h"
#include "hal_defs.h"
#include "hal_types.h"
#include "hal_drivers.h"
#include "hal_adc.h"
#include "hal_key.h"
#include "osal.h"

#define VIBRA_INT_THRESHOLD     5
static uint16 vibraIntCount = 0;
static bool vibraEnable = FALSE;
static bool vibraTriggered = FALSE;


void clearVibraTriggered()
{
    vibraTriggered = FALSE;
}
bool readVibraTriggered()
{
    return vibraTriggered;
}
void halProcessVibraInterrupt()
{
    vibraIntCount++;
    if (vibraIntCount >= VIBRA_INT_THRESHOLD)
    {
        vibraIntCount = 0;
        vibraTriggered = TRUE;
        HalVibraSensorInterruptControl(FALSE);
    }
}
bool getVibraEnableStatus()
{
    return vibraEnable;
}
void HalVibraSensorInterruptControl(bool enable)
{
    /* Interrupt configuration:
     * - Enable interrupt generation at the port
     * - Enable CPU interrupt
     * - Clear any pending interrupt
     */
    if (enable)
    {
        HAL_VIBRA_ICTL |= HAL_VIBRA_ICTLBIT;
        HAL_VIBRA_IEN |= HAL_VIBRA_IENBIT;
        HAL_VIBRA_PXIFG &= ~(HAL_VIBRA_BIT);
    }
    else
    {
        HAL_VIBRA_PXIFG &= ~(HAL_VIBRA_BIT);
        HAL_VIBRA_ICTL &= ~(HAL_VIBRA_ICTLBIT); /* don't generate interrupt */
    }
    vibraEnable = enable;
}

void HalVibraSensorConfig(bool interruptEnable)
{
    // GPIO Init
    HAL_VIBRA_SEL &= ~(HAL_VIBRA_BIT);    /* Set pin function to GPIO */
    HAL_VIBRA_DIR &= ~(HAL_VIBRA_BIT);    /* Set pin direction to Input */
    // TODO: check this register.
    P2INP |= PUSH2_BV;  /* Configure GPIO tri-state. */

    // Interrupt Init
    /* Rising/Falling edge configuratinn */
    PICTL &= ~(HAL_VIBRA_EDGEBIT);    /* Clear the edge bit */
    /* For falling edge, the bit must be set. */
  #if (HAL_VIBRA_EDGE == HAL_VIBRA_FALLING_EDGE)
    PICTL |= HAL_VIBRA_EDGEBIT;
  #endif
    HalVibraSensorInterruptControl(TRUE);
}