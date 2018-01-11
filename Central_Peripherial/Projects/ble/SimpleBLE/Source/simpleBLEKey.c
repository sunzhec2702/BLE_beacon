#include "simpleBLEKey.h"
#include "simpleBLEPeripheral.h"
#include "simpleBLECentral.h"


// Key related
static uint8 key_pressed_count = 0;
static uint8 key_processing = FALSE;

static key_event_process_callback process_callback = NULL;

void set_key_press_process_callback(key_event_process_callback callback)
{
    process_callback = callback;
}

void key_cnt_evt_callback()
{
    if (key_pressed_count == 0)
      return;

    if (process_callback != NULL)
    {
        process_callback(key_pressed_count);
    }
    // Reset Key event.
    key_pressed_count = 0;
    key_processing = FALSE;
}

void key_press_handler(uint8 keys)
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
                if (process_callback != NULL)
                {
                    process_callback(0);
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

