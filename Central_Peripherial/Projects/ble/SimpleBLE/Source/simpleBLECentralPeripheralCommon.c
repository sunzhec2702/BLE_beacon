#include "simpleBLECentralPeripheralCommon.h"
#include "simpleble.h"
#include "npi.h"

extern SYS_CONFIG sys_config;

void updateSysConfigMac()
{
  uint8 *mac_addr = (uint8*)osal_mem_alloc(B_ADDR_LEN);
  if (mac_addr == NULL)
  {
      return FALSE;
  }
  GAPRole_GetParameter(GAPROLE_BD_ADDR, mac_addr);
  osal_revmemcpy(sys_config.mac_addr, mac_addr, MAC_ADDR_CHAR_LEN);
  osal_mem_free(mac_addr);
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
