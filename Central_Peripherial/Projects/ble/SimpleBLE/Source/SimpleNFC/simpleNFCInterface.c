#include "simpleNFCInterface.h"
#include "nfc-internal.h"

void nfc_init()
{
  nfc_context *res = malloc(sizeof(*res));

  if (!res) {
    return NULL;
  }

  // Set default context values
  res->allow_autoscan = true;
  res->allow_intrusive_scan = false;
#ifdef DEBUG
  res->log_level = 3;
#else
  res->log_level = 1;
#endif

  printf("Darren:DEBUG: MAX_USER_DEFINED_DEGVICES %d\n", MAX_USER_DEFINED_DEVICES);
  // Clear user defined devices array
  for (int i = 0; i < MAX_USER_DEFINED_DEVICES; i++) {
    strcpy(res->user_defined_devices[i].name, "");
    strcpy(res->user_defined_devices[i].connstring, "");
    res->user_defined_devices[i].optional = false;
  }
  res->user_defined_device_count = 0;

#ifdef ENVVARS
  // Load user defined device from environment variable at first
  char *envvar = getenv("LIBNFC_DEFAULT_DEVICE");
  printf("Darren:DEBUG: LIBNFC_DEFAULT_DEVICE %s\n", envvar);
  if (envvar) {
    strcpy(res->user_defined_devices[0].name, "user defined default device");
    strncpy(res->user_defined_devices[0].connstring, envvar, NFC_BUFSIZE_CONNSTRING);
    res->user_defined_devices[0].connstring[NFC_BUFSIZE_CONNSTRING - 1] = '\0';
    res->user_defined_device_count++;
  }

#endif // ENVVARS

#ifdef CONFFILES
  // Load options from configuration file (ie. /etc/nfc/libnfc.conf)
  conf_load(res);
#endif // CONFFILES

#ifdef ENVVARS
  // Environment variables

  // Load user defined device from environment variable as the only reader
  envvar = getenv("LIBNFC_DEVICE");
  if (envvar) {
    strcpy(res->user_defined_devices[0].name, "user defined device");
    strncpy(res->user_defined_devices[0].connstring, envvar, NFC_BUFSIZE_CONNSTRING);
    res->user_defined_devices[0].connstring[NFC_BUFSIZE_CONNSTRING - 1] = '\0';
    res->user_defined_device_count = 1;
  }

  // Load "auto scan" option
  envvar = getenv("LIBNFC_AUTO_SCAN");
  string_as_boolean(envvar, &(res->allow_autoscan));

  // Load "intrusive scan" option
  envvar = getenv("LIBNFC_INTRUSIVE_SCAN");
  string_as_boolean(envvar, &(res->allow_intrusive_scan));

  // log level
  envvar = getenv("LIBNFC_LOG_LEVEL");
  if (envvar) {
    res->log_level = atoi(envvar);
  }
#endif // ENVVARS

  // Initialize log before use it...
  log_init(res);

  // Debug context state
#if defined DEBUG
  log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_NONE,  "log_level is set to %"PRIu32, res->log_level);
#else
  log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG,  "log_level is set to %"PRIu32, res->log_level);
#endif
  log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG, "allow_autoscan is set to %s", (res->allow_autoscan) ? "true" : "false");
  log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG, "allow_intrusive_scan is set to %s", (res->allow_intrusive_scan) ? "true" : "false");

  log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG, "%d device(s) defined by user", res->user_defined_device_count);
  for (uint32_t i = 0; i < res->user_defined_device_count; i++) {
    log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG, "  #%d name: \"%s\", connstring: \"%s\"", i, res->user_defined_devices[i].name, res->user_defined_devices[i].connstring);
  }
  return res;    
}