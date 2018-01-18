#include "simpleBLECentralPeripheralCommon.h"

extern SYS_CONFIG sys_config;


#if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
void set_beacon_status(BLE_STATUS current_status, BLE_STATUS target_status, bool reset)
{
    switch (target_status)
    {
      case BLE_STATUS_OFF:
      
      break;
      case BLE_STATUS_ON_ADV:
      break;
      case BLE_STATUS_ON_SCAN:
      break;
      default:
      break;
    }
    sys_config.status = target_status;
    if (reset == TRUE)
    {
        simpleBLE_SaveAndReset();
    }
    else
    {
        simpleBLE_WriteAllDataToFlash();
    }
    return;
}

void set_target_status_to_off()
{
    sys_config.status = BLE_STATUS_OFF;
    simpleBLE_WriteAllDataToFlash();
    return;
}

static bool check_low_battery()
{
  #ifdef DEBUG_BOARD
  if (debug_low_power == TRUE)
    return TRUE;
  #endif
  uint32 adc_read = 0;
  for (uint8 i = 0; i < 16; i++)
  {
    HalAdcSetReference(HAL_ADC_REF_125V);
    adc_read += HalAdcRead(HAL_ADC_CHANNEL_VDD, HAL_ADC_RESOLUTION_10);
  }
  adc_read = adc_read >> 4;
  battery_voltage = adc_read * 3 * 125 / 511 / 10;
  DEBUG_VALUE("adc value : ", adc_read, 10);
  DEBUG_VALUE("Battery Value : ", battery_voltage * 10, 10);
  
  #if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
  // Update the advertise data.
  advertData_iBeacon[ADV_BAT_BYTE] = battery_voltage & 0xFF;
  #endif

  if (g_sleepFlag == TRUE && battery_voltage < BATTERY_LOW_THRESHOLD_SLEEP)
  {
    return TRUE;
  }
  else if (g_sleepFlag == FALSE && battery_voltage < BATTERY_LOW_THRESHOLD)
  {
    return TRUE;
  }
  return FALSE;
}

void enter_low_battery_mode()
{
  // Low Battery Mode. Enter OFF mode.
  /*
  sys_config.status = BLE_STATUS_OFF;
  simpleBLE_SaveAndReset();
  */
  DEBUG_PRINT("Enter Low Battery Mode\r\n");
  if (sys_config.role = BLE_ROLE_PERIPHERAL)
  {

  }

  low_power_state = TRUE;
  advertData_iBeacon[ADV_FLAG_BYTE] |= 0x40;
  // Stop advertising.
  advertise_control(FALSE);
  // LED Blinking.
  led_toggle_set_param(PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_ON, PERIPHERAL_LOW_BAT_LED_TOGGLE_PERIOD_OFF, PERIPHERAL_LOW_BAT_LED_TOGGLE_CNT, 0);
}

bool check_keys_pressed(uint8 keys)
{
  switch (keys)
  {
    case HAL_KEY_SW_6:
      if (!(HAL_KEY_SW_6_PORT & HAL_KEY_SW_6_BIT))    /* Key is active low */
      {
        return TRUE;
      }
      break;
    default:
      break;
  }
  return FALSE;
}

#endif
