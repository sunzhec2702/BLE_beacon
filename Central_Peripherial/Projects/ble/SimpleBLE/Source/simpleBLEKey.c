#include "simpleBLEKey.h"

// Key related
static uint8 key_pressed_count = 0;
static uint8 key_processing = FALSE;

void key_cnt_evt_callback()
{
    if (key_pressed_count == 0)
      return (events ^ SBP_KEY_CNT_EVT);

    if (g_sleepFlag == TRUE)
    {
      if (key_pressed_count == 1)
      {
        first_boot = TRUE;
      }
      osal_set_event(simpleBLETaskId, SBP_WAKE_EVT);        
    }
    else if (g_sleepFlag == FALSE)
    {
      if (key_pressed_count >= 2)
      {
        DEBUG_PRINT("Timer is reset\r\n");
        wake_up_hours_remain = DEFAULT_WAKE_TIME_HOURS;
        // reset wake_up_left
        advertData_iBeacon[ADV_HOUR_LEFT_BYTE] = wake_up_hours_remain;
        // LED blink twice
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_WAKEUP_LED_TOGGLE_CNT, BUTTON_LED_DELAY);
      }
      else if (key_pressed_count == 1)
      {
        // Blink once
        led_toggle_set_param(PERIPHERAL_START_LED_TOGGLE_PERIOD_ON, PERIPHERAL_START_LED_TOGGLE_PERIOD_OFF, BUTTON_LED_TOGGLE_COUNT, BUTTON_LED_DELAY);
        #if (POWER_OFF_SUPPORT == TRUE)
        key_pressed_count = 0;
        osal_set_event(simpleBLETaskId, SBP_KEY_LONG_PRESSED_EVT);
        #endif
      }
      // Change the advertise date anyway.
      change_advertise_data(TRUE);
    }
    // Reset Key event.
    key_pressed_count = 0;
    key_processing = FALSE;
}

void key_cnt_function()
{
    if (keys & HAL_KEY_SW_6)
    {
        if (low_power_state == TRUE)
        {
            DEBUG_PRINT("Handle Keys, Low Power Mode\r\n");
            return;
        }

        if (key_processing == FALSE)
        {
            if (key_pressed_count == 0)
            {
                if (wake_up_hours_remain <= RESET_WAKE_TIME_HOURS_THRES)
                {
                    wake_up_hours_remain = BUTTON_WAKE_TIME_HOURS;
                    advertData_iBeacon[ADV_HOUR_LEFT_BYTE] = wake_up_hours_remain;
                }
                if (g_long_press_flag == FALSE)
                {
                    osal_start_timerEx(simpleBLETaskId, SBP_KEY_CNT_EVT, PERIPHERAL_KEY_CALCULATE_PERIOD);
                }
            }
            key_pressed_count++;
        }
        key_pressed = !key_pressed;
    }

#ifdef DEBUG_BOARD
    if (keys & HAL_KEY_SW_1)
    {
        debug_low_power = TRUE;
    }
    if (keys & HAL_KEY_SW_3)
    {
        debug_low_power = FALSE;
    }
#endif
}

