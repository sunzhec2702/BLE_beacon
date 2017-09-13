#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H

#include "hal_types.h"
#include "OSAL.h"
#include "OSAL_Tasks.h"

#define MAX_TASKS 12

typedef enum
{
  ROLE_PERI = 0,
  ROLE_CENT = 1
} BLE_ROLE;

extern BLE_ROLE current_role;

#endif