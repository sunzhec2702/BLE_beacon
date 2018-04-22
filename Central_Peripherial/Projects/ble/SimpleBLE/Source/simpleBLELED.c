#include "simpleBLELED.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"
#include "OnBoard.h"
#include "hal_led.h"

extern uint8 simpleBLETaskId;

// LED related.
static uint8 led_toggle_status = FALSE;
static uint8 led_toggle_count = 0;
static uint8 led_toggle_cnt_target = PERIPHERAL_START_LED_TOGGLE_CNT;
static uint8 led_toggling = FALSE;
static uint16 led_toggle_period_on = PERIPHERAL_START_LED_TOGGLE_PERIOD_ON;
static uint16 led_toggle_period_off = PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF;

uint8 get_led_toggle_status()
{
  return led_toggle_status;
}

void led_event_callback()
{
  if (++led_toggle_count <= led_toggle_cnt_target)
  {
    osal_pwrmgr_device(PWRMGR_ALWAYS_ON); // Make sure the LED can on correctly.
    HalLedSet(HAL_LED_2, HAL_LED_MODE_ON);
    simpleBLE_Delay_1ms(PERIPHERAL_LED_PREPARE_PERIOD_KEEP);
    HalLedSet(HAL_LED_TARGET, HAL_LED_MODE_TOGGLE);
    simpleBLE_Delay_1ms(PERIPHERAL_LED_TOGGLE_PERIOD_KEEP);
    HalLedSet(HAL_LED_TARGET, HAL_LED_MODE_OFF);
    osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT, 0);
  }
  else
  {
    //led_toggle_status = FALSE;
    HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
    osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT);
    led_toggle_clean_param();
    /* Previous, we check the low power state
    if (low_power_state == TRUE)
    {
      osal_set_event(simpleBLETaskId, SBP_SLEEP_EVT);
      low_power_state = FALSE;
    }
    */
  }
}


uint8 led_toggle_set_param(uint16 toggle_period_on, uint16 toggle_period_off, uint32 toggle_target_cnt, uint16 delay)
{
  if (led_toggling == TRUE)
    return FALSE;
  osal_pwrmgr_device(PWRMGR_ALWAYS_ON);
  led_toggle_status = FALSE;
  led_toggling = TRUE;
  //led_toggle_period_on = toggle_period_on;
  //led_toggle_period_off = toggle_period_off;
  (void) toggle_period_on;
  (void) toggle_period_off;
  led_toggle_count = 0;
  led_toggle_cnt_target = toggle_target_cnt;
  osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT, delay);
  return TRUE;
}

uint8 led_toggle_clean_param()
{
  if (led_toggling == FALSE)
    return FALSE;
  osal_pwrmgr_device(PWRMGR_BATTERY);
  //led_toggle_period_on = PERIPHERAL_START_LED_TOGGLE_PERIOD_ON;
  //led_toggle_period_off = PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF;
  led_toggle_count = 0;
  led_toggle_cnt_target = PERIPHERAL_START_LED_TOGGLE_CNT;
  led_toggling = FALSE;
  return TRUE;
}