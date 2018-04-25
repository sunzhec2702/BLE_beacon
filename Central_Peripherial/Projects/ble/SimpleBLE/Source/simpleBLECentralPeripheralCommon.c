#include "simpleBLECentralPeripheralCommon.h"
#include "simpleble.h"
#include "npi.h"
#include "hal_key.h"
#include "broadcaster.h"

extern SYS_CONFIG sys_config;

#define XDATA_MAC_ADDR      (0x780E)

void updateSysConfigMac()
{
  for (uint8 i = 0; i < B_ADDR_LEN; i++)
  {
    sys_config.mac_addr[B_ADDR_LEN - 1 - i] = XREG(XDATA_MAC_ADDR+i);
  }
}

#if (PRESET_ROLE == BLE_PRE_ROLE_BEACON)
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
#elif (PRESET_ROLE == BLE_PRE_ROLE_STATION)
// Place holder
#endif
