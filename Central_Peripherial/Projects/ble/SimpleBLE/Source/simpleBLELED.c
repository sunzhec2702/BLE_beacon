#include "simpleBLELED.h"


extern uint8 simpleBLETaskId;

// LED related.
static uint8 key_led_count = BUTTON_LED_TOGGLE_COUNT; //Blink for 3 times.
static uint8 led_toggle_status = FALSE;
static uint8 led_toggle_count = 0;
static uint8 led_toggle_cnt_target = PERIPHERAL_START_LED_TOGGLE_CNT;
static uint8 led_toggling = FALSE;
static uint16 led_toggle_period_on = PERIPHERAL_START_LED_TOGGLE_PERIOD_ON;
static uint16 led_toggle_period_off = PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF;

void led_event_callback()
{
    if (++led_toggle_count <= led_toggle_cnt_target)
    {
      osal_pwrmgr_device(PWRMGR_ALWAYS_ON); // Make sure the LED can on correctly.
      HalLedSet(HAL_LED_1, HAL_LED_MODE_TOGGLE);
      if (led_toggle_status == FALSE)
      {
        led_toggle_status = TRUE;
        osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT, led_toggle_period_on);
      }
      else if (led_toggle_status == TRUE)
      {
        led_toggle_status = FALSE;
        osal_start_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT, led_toggle_period_off);
      }
    }
    else
    {
      led_toggle_status = FALSE;
      HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
      osal_stop_timerEx(simpleBLETaskId, SBP_PERIODIC_LED_EVT);
      led_toggle_clean_param();
      if (low_power_state == TRUE)
      {
        osal_set_event(simpleBLETaskId, SBP_SLEEP_EVT);
        low_power_state = FALSE;
      }
      if (g_long_press_flag == TRUE)
      {
        key_pressed_count = 0;
        osal_start_timerEx(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT, PERIPHERAL_KEY_SLEEP_CALC_PERIOD_STAGE_1);
      }
    }
}


uint8 led_toggle_set_param(uint16 toggle_period_on, uint16 toggle_period_off, uint32 toggle_target_cnt, uint16 delay)
{
  if (led_toggling == TRUE)
    return FALSE;
  osal_pwrmgr_device(PWRMGR_ALWAYS_ON);
  led_toggle_status = FALSE;
  led_toggling = TRUE;
  led_toggle_period_on = toggle_period_on;
  led_toggle_period_off = toggle_period_off;
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
  led_toggle_period_on = PERIPHERAL_START_LED_TOGGLE_PERIOD_ON;
  led_toggle_period_off = PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF;
  led_toggle_count = 0;
  led_toggle_cnt_target = PERIPHERAL_START_LED_TOGGLE_CNT;
  led_toggling = FALSE;
  return TRUE;
}