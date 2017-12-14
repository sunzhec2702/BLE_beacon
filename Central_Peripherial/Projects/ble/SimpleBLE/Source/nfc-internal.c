/**
* @file nfc-internal.c
* @brief Provide some useful internal functions
*/

#include "nfc.h"
#include "nfc-internal.h"
#include "OSAL.h"

#include <stdlib.h>
#include <string.h>

void
string_as_boolean(const char *s, bool *value)
{
  if (s) {
    if (!(*value)) {
      if ((strcmp(s, "yes") == 0) ||
          (strcmp(s, "true") == 0) ||
          (strcmp(s, "1") == 0)) {
        *value = true;
        return;
      }
    } else {
      if ((strcmp(s, "no") == 0) ||
          (strcmp(s, "false") == 0) ||
          (strcmp(s, "0") == 0)) {
        *value = false;
        return;
      }
    }
  }
}

nfc_context *
nfc_context_new(void)
{
  nfc_context *res = osal_mem_alloc(sizeof(*res));

  if (!res) {
    return NULL;
  }

  // Set default context values
  res->allow_autoscan = true;
  res->allow_intrusive_scan = false;
  res->log_level = 1;

  // Clear user defined devices array
  for (int i = 0; i < MAX_USER_DEFINED_DEVICES; i++) {
    strcpy(res->user_defined_devices[i].name, "");
    strcpy(res->user_defined_devices[i].connstring, "");
    res->user_defined_devices[i].optional = false;
  }
  res->user_defined_device_count = 0;
  return res;
}

void
nfc_context_free(nfc_context *context)
{
  //log_exit();
  osal_mem_free(context);
}

void
prepare_initiator_data(const nfc_modulation nm, uint8 **ppbtInitiatorData, size_t *pszInitiatorData)
{
  switch (nm.nmt) {
    case NMT_ISO14443B: {
      // Application Family Identifier (AFI) must equals 0x00 in order to wakeup all ISO14443-B PICCs (see ISO/IEC 14443-3)
      *ppbtInitiatorData = (uint8 *) "\x00";
      *pszInitiatorData = 1;
    }
    break;
    case NMT_ISO14443BI: {
      // APGEN
      *ppbtInitiatorData = (uint8 *) "\x01\x0b\x3f\x80";
      *pszInitiatorData = 4;
    }
    break;
    case NMT_ISO14443B2SR: {
      // Get_UID
      *ppbtInitiatorData = (uint8 *) "\x0b";
      *pszInitiatorData = 1;
    }
    break;
    case NMT_ISO14443B2CT: {
      // SELECT-ALL
      *ppbtInitiatorData = (uint8 *) "\x9F\xFF\xFF";
      *pszInitiatorData = 3;
    }
    break;
    case NMT_FELICA: {
      // polling payload must be present (see ISO/IEC 18092 11.2.2.5)
      *ppbtInitiatorData = (uint8 *) "\x00\xff\xff\x01\x00";
      *pszInitiatorData = 5;
    }
    break;
    case NMT_ISO14443A:
    case NMT_JEWEL:
    case NMT_DEP:
      *ppbtInitiatorData = NULL;
      *pszInitiatorData = 0;
      break;
  }
}

int
connstring_decode(const nfc_connstring connstring, const char *driver_name, const char *bus_name, char **pparam1, char **pparam2)
{
  if (driver_name == NULL) {
    driver_name = "";
  }
  if (bus_name == NULL) {
    bus_name = "";
  }
  int n = strlen(connstring) + 1;
  char *param0 = osal_mem_alloc(n);
  if (param0 == NULL) {
    perror("osal_mem_alloc");
    return 0;
  }
  char *param1 = osal_mem_alloc(n);
  if (param1 == NULL) {
    perror("osal_mem_alloc");
    osal_mem_free(param0);
    return 0;
  }
  char *param2    = osal_mem_alloc(n);
  if (param2 == NULL) {
    perror("osal_mem_alloc");
    osal_mem_free(param0);
    osal_mem_free(param1);
    return 0;
  }

  char format[32];
  snprintf(format, sizeof(format), "%%%i[^:]:%%%i[^:]:%%%i[^:]", n - 1, n - 1, n - 1);
  int res = sscanf(connstring, format, param0, param1, param2);

  if (res < 1 || ((0 != strcmp(param0, driver_name)) &&
                  (bus_name != NULL) &&
                  (0 != strcmp(param0, bus_name)))) {
    // Driver name does not match.
    res = 0;
  }
  if (pparam1 != NULL) {
    if (res < 2) {
      osal_mem_free(param1);
      *pparam1 = NULL;
    } else {
      *pparam1 = param1;
    }
  } else {
    osal_mem_free(param1);
  }
  if (pparam2 != NULL) {
    if (res < 3) {
      osal_mem_free(param2);
      *pparam2 = NULL;
    } else {
      *pparam2 = param2;
    }
  } else {
    osal_mem_free(param2);
  }
  osal_mem_free(param0);
  return res;
}

