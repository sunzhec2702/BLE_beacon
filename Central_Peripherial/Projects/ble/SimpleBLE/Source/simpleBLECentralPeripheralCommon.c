#include "simpleBLECentralPeripheralCommon.h"

extern SYS_CONFIG sys_config;

void set_target_status_to_off()
{
    sys_config.status = BLE_STATUS_OFF;
    simpleBLE_WriteAllDataToFlash();
    return;
}