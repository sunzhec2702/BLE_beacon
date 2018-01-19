#include "simpleBLECentralPeripheralCommon.h"
#include "simpleble.h"
#include "npi.h"
#include "hal_key.h"
#include "broadcaster.h"

extern SYS_CONFIG sys_config;

#define HAL_KEY_SW_6_PORT   P0
#define HAL_KEY_SW_6_BIT    BV(1)

void updateSysConfigMac()
{
  uint8 mac_addr[B_ADDR_LEN] = {0};
  GAPRole_GetParameter(GAPROLE_BD_ADDR, mac_addr);
  GAPRole_GetParameter(GAPROLE_BD_ADDR, mac_addr);
  osal_revmemcpy(sys_config.mac_addr, mac_addr, B_ADDR_LEN);
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

#endif
