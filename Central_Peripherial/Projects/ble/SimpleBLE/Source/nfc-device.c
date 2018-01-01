/**
 * @file nfc-device.c
 * @brief Provide internal function to manipulate nfc_device type
 */

#include <stdlib.h>
#include <string.h>

#include "nfc-internal.h"
#include "OSAL.h"

nfc_device * nfc_device_new(const nfc_context *context, const nfc_connstring connstring)
{
  nfc_device *res = osal_mem_alloc(sizeof(*res));

  if (!res) {
    return NULL;
  }

  // Store associated context
  res->context = context;

  // Variables initiatialization
  // Note: Actually, these initialization will be overwritten while the device
  // will be setup. Putting them to _false_ while the default is _true_ ensure we
  // send the command to the chip
  res->bCrc = false;
  res->bPar = false;
  res->bEasyFraming    = false;
  res->bInfiniteSelect = false;
  res->bAutoIso14443_4 = false;
  res->last_error  = 0;
  res->driver_data = NULL;
  res->chip_data   = NULL;

  return res;
}

void
nfc_device_free(nfc_device *dev)
{
  if (dev) {
    //osal_mem_free(dev->driver_data);
    osal_mem_free(dev);
  }
}
