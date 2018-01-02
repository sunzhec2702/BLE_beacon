/**
 * @file pn532_uart.c
 * @brief PN532 driver using UART bus (UART, RS232, etc.)
 */
#include "pn532_uart.h"

#include <stdio.h>
#include <string.h>

#include "nfc.h"

#include "drivers.h"
#include "nfc-internal.h"
#include "pn53x.h"
#include "pn53x-internal.h"
#include "ble_uart.h"
#include "OSAL.h"

#define PN532_UART_DEFAULT_SPEED 115200
#define PN532_UART_DRIVER_NAME "pn532_uart"

// Internal data structs
const struct pn53x_io pn532_uart_io;
struct pn532_uart_data {
  //serial_port port;
  int     iAbortFds[2];
};

// Prototypes
int     pn532_uart_ack(nfc_device *pnd);
int     pn532_uart_wakeup(nfc_device *pnd);

#define DRIVER_DATA(pnd) ((struct pn532_uart_data*)(pnd->driver_data))
  /*
static size_t
pn532_uart_scan(const nfc_context *context, nfc_connstring connstrings[], const size_t connstrings_len)
{

  size_t device_found = 0;
  serial_port sp;
  char **acPorts = uart_list_ports();
  const char *acPort;
  int     iDevice = 0;

  while ((acPort = acPorts[iDevice++])) {
    sp = uart_open(acPort);
    log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG, "Trying to find PN532 device on serial port: %s at %d bauds.", acPort, PN532_UART_DEFAULT_SPEED);

    if ((sp != INVALID_SERIAL_PORT) && (sp != CLAIMED_SERIAL_PORT)) {
      // We need to flush input to be sure first reply does not comes from older byte transceive
      ble_uart_flush_input(sp, true);
      // Serial port claimed but we need to check if a PN532_UART is opened.
      uart_set_speed(sp, PN532_UART_DEFAULT_SPEED);

      nfc_connstring connstring;
      snprintf(connstring, sizeof(nfc_connstring), "%s:%s:%"PRIu32, PN532_UART_DRIVER_NAME, acPort, PN532_UART_DEFAULT_SPEED);
      printf("Darren:DEBUG: in uart scan: connstring is %s\n", connstring);
      nfc_device *pnd = nfc_device_new(context, connstring);
      if (!pnd) {
        perror("osal_mem_alloc");
        uart_close(sp);
        iDevice = 0;
        while ((acPort = acPorts[iDevice++])) {
          osal_mem_free((void *)acPort);
        }
        osal_mem_free(acPorts);
        return 0;
      }
      pnd->driver = &pn532_uart_driver;
      pnd->driver_data = osal_mem_alloc(sizeof(struct pn532_uart_data));
      if (!pnd->driver_data) {
        perror("osal_mem_alloc");
        uart_close(sp);
        nfc_device_free(pnd);
        iDevice = 0;
        while ((acPort = acPorts[iDevice++])) {
          osal_mem_free((void *)acPort);
        }
        osal_mem_free(acPorts);
        return 0;
      }
      DRIVER_DATA(pnd)->port = sp;

      // Alloc and init chip's data
      if (pn53x_data_new(pnd, &pn532_uart_io) == NULL) {
        perror("osal_mem_alloc");
        uart_close(DRIVER_DATA(pnd)->port);
        nfc_device_free(pnd);
        iDevice = 0;
        while ((acPort = acPorts[iDevice++])) {
          osal_mem_free((void *)acPort);
        }
        osal_mem_free(acPorts);
        return 0;
      }
      // SAMConfiguration command if needed to wakeup the chip and pn53x_SAMConfiguration check if the chip is a PN532
      CHIP_DATA(pnd)->type = PN532;
      // This device starts in LowVBat power mode
      CHIP_DATA(pnd)->power_mode = LOWVBAT;

#ifndef WIN32
      // pipe-based abort mecanism
      if (pipe(DRIVER_DATA(pnd)->iAbortFds) < 0) {
        uart_close(DRIVER_DATA(pnd)->port);
        pn53x_data_free(pnd);
        nfc_device_free(pnd);
        iDevice = 0;
        while ((acPort = acPorts[iDevice++])) {
          osal_mem_free((void *)acPort);
        }
        osal_mem_free(acPorts);
        return 0;
      }
#else
      DRIVER_DATA(pnd)->abort_flag = false;
#endif

      // Check communication using "Diagnose" command, with "Communication test" (0x00)
      int res = pn53x_check_communication(pnd);
      uart_close(DRIVER_DATA(pnd)->port);
      pn53x_data_free(pnd);
      nfc_device_free(pnd);
      if (res < 0) {
        continue;
      }

      memcpy(connstrings[device_found], connstring, sizeof(nfc_connstring));
      device_found++;

      // Test if we reach the maximum "wanted" devices
      if (device_found >= connstrings_len)
        break;
    }
  }
  iDevice = 0;
  while ((acPort = acPorts[iDevice++])) {
    osal_mem_free((void *)acPort);
  }
  osal_mem_free(acPorts);
  return device_found;

  return 0;
}
  */

struct pn532_uart_descriptor {
  char *port;
  uint32 speed;
};

static void
pn532_uart_close(nfc_device *pnd)
{
  pn53x_idle(pnd);
/*
  // Release UART port
  uart_close(DRIVER_DATA(pnd)->port);

#ifndef WIN32
  // Release file descriptors used for abort mecanism
  close(DRIVER_DATA(pnd)->iAbortFds[0]);
  close(DRIVER_DATA(pnd)->iAbortFds[1]);
#endif
*/

  pn53x_data_free(pnd);
  nfc_device_free(pnd);
}

static nfc_device *
pn532_uart_open(const nfc_context *context, const nfc_connstring connstring)
{
  nfc_device *pnd = NULL;
  // We have a connection
  pnd = nfc_device_new(context, connstring);
  if (!pnd) {
    return NULL;
  }
  //snprintf(pnd->name, sizeof(pnd->name), "%s:%s", PN532_UART_DRIVER_NAME, "0");
  pnd->driver_data = NULL; //osal_mem_alloc(sizeof(struct pn532_uart_data));
  //DRIVER_DATA(pnd)->port = sp;

  // Alloc and init chip's data
  if (pn53x_data_new(pnd, &pn532_uart_io) == NULL) {
    nfc_device_free(pnd);
    return NULL;
  }
  // SAMConfiguration command if needed to wakeup the chip and pn53x_SAMConfiguration check if the chip is a PN532
  CHIP_DATA(pnd)->type = PN532;
  // This device starts in LowVBat mode
  CHIP_DATA(pnd)->power_mode = LOWVBAT;

  // empirical tuning
  CHIP_DATA(pnd)->timer_correction = 48;
  pnd->driver = &pn532_uart_driver;

/*
#ifndef WIN32
  // pipe-based abort mecanism
  if (pipe(DRIVER_DATA(pnd)->iAbortFds) < 0) {
    uart_close(DRIVER_DATA(pnd)->port);
    pn53x_data_free(pnd);
    nfc_device_free(pnd);
    return NULL;
  }
#else
  DRIVER_DATA(pnd)->abort_flag = false;
#endif
*/
  // Check communication using "Diagnose" command, with "Communication test" (0x00)
  if (pn53x_check_communication(pnd) < 0) {
    pn532_uart_close(pnd);
    return NULL;
  }

  if (pn53x_init(pnd) < 0)
  {
    pn532_uart_close(pnd);
    return NULL;
  }
  return pnd;
}

int
pn532_uart_wakeup(nfc_device *pnd)
{
  /* High Speed Unit (HSU) wake up consist to send 0x55 and wait a "long" delay for PN532 being wakeup. */
  const uint8 pn532_wakeup_preamble[] = { 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  int res = ble_uart_poll_send(pn532_wakeup_preamble, sizeof(pn532_wakeup_preamble), 0);
  CHIP_DATA(pnd)->power_mode = NORMAL; // PN532 should now be awake
  return res;
}

#define PN532_BUFFER_LEN (PN53x_EXTENDED_FRAME__DATA_MAX_LEN + PN53x_EXTENDED_FRAME__OVERHEAD)
static int
pn532_uart_send(nfc_device *pnd, const uint8 *pbtData, const size_t szData, int timeout)
{
  int res = 0;
  // Before sending anything, we need to discard from any junk bytes
  ble_uart_flush_input(false);

  switch (CHIP_DATA(pnd)->power_mode) {
    case LOWVBAT: {
      /** PN532C106 wakeup. */
      if ((res = pn532_uart_wakeup(pnd)) < 0) {
        return res;
      }
      // According to PN532 application note, C106 appendix: to go out Low Vbat mode and enter in normal mode we need to send a SAMConfiguration command
      // Darren : Do we need to wait inifiect?
      if ((res = pn532_SAMConfiguration(pnd, PSM_NORMAL, 0)) < 0) {
        return res;
      }
    }
    break;
    case POWERDOWN: {
      if ((res = pn532_uart_wakeup(pnd)) < 0) {
        return res;
      }
    }
    break;
    case NORMAL:
      // Nothing to do :)
      break;
  };

  uint8  abtFrame[PN532_BUFFER_LEN] = { 0x00, 0x00, 0xff };       // Every packet must start with "00 00 ff"
  size_t szFrame = 0;

  if ((res = pn53x_build_frame(abtFrame, &szFrame, pbtData, szData)) < 0) {
    pnd->last_error = res;
    return pnd->last_error;
  }

  res = ble_uart_poll_send(abtFrame, szFrame, timeout);
  if (res != 0) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Unable to transmit data. (TX)");
    pnd->last_error = res;
    return pnd->last_error;
  }

  uint8 abtRxBuf[PN53x_ACK_FRAME__LEN];
  res = ble_uart_poll_receive(abtRxBuf, sizeof(abtRxBuf), 0, timeout);
  if (res != 0) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_DEBUG, "%s", "Unable to read ACK");
    pnd->last_error = res;
    return pnd->last_error;
  }

  if (pn53x_check_ack_frame(pnd, abtRxBuf, sizeof(abtRxBuf)) == 0) {
    // The PN53x is running the sent command
  } else {
    return pnd->last_error;
  }
  return NFC_SUCCESS;
}

static int
pn532_uart_receive(nfc_device *pnd, uint8 *pbtData, const size_t szDataLen, int timeout)
{
  uint8  abtRxBuf[5];
  size_t len;
  void *abort_p = NULL;

#ifndef WIN32
  abort_p = &(DRIVER_DATA(pnd)->iAbortFds[1]);
#else
  abort_p = (void *) & (DRIVER_DATA(pnd)->abort_flag);
#endif

  pnd->last_error = ble_uart_poll_receive(abtRxBuf, 5, abort_p, timeout);

  if (abort_p && (NFC_EOPABORTED == pnd->last_error)) {
    pn532_uart_ack(pnd);
    return NFC_EOPABORTED;
  }

  if (pnd->last_error < 0) {
    goto error;
  }

  const uint8 pn53x_preamble[3] = { 0x00, 0x00, 0xff };
  if (0 != (memcmp(abtRxBuf, pn53x_preamble, 3))) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Frame preamble+start code mismatch");
    pnd->last_error = NFC_EIO;
    goto error;
  }

  if ((0x01 == abtRxBuf[3]) && (0xff == abtRxBuf[4])) {
    // Error frame
    ble_uart_poll_receive(abtRxBuf, 3, 0, timeout);
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Application level error detected");
    pnd->last_error = NFC_EIO;
    goto error;
  } else if ((0xff == abtRxBuf[3]) && (0xff == abtRxBuf[4])) {
    // Extended frame
    pnd->last_error = ble_uart_poll_receive(abtRxBuf, 3, 0, timeout);
    if (pnd->last_error != 0) {
      //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Unable to receive data. (RX)");
      goto error;
    }
    // (abtRxBuf[0] << 8) + abtRxBuf[1] (LEN) include TFI + (CC+1)
    len = (abtRxBuf[0] << 8) + abtRxBuf[1] - 2;
    if (((abtRxBuf[0] + abtRxBuf[1] + abtRxBuf[2]) % 256) != 0) {
      //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Length checksum mismatch");
      pnd->last_error = NFC_EIO;
      goto error;
    }
  } else {
    // Normal frame
    if (256 != (abtRxBuf[3] + abtRxBuf[4])) {
      // TODO: Retry
      //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Length checksum mismatch");
      pnd->last_error = NFC_EIO;
      goto error;
    }

    // abtRxBuf[3] (LEN) include TFI + (CC+1)
    len = abtRxBuf[3] - 2;
  }

  if (len > szDataLen) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "Unable to receive data: buffer too small. (szDataLen: %" PRIuPTR ", len: %" PRIuPTR ")", szDataLen, len);
    pnd->last_error = NFC_EIO;
    goto error;
  }

  // TFI + PD0 (CC+1)
  pnd->last_error = ble_uart_poll_receive(abtRxBuf, 2, 0, timeout);
  if (pnd->last_error != 0) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Unable to receive data. (RX)");
    goto error;
  }

  if (abtRxBuf[0] != 0xD5) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "TFI Mismatch");
    pnd->last_error = NFC_EIO;
    goto error;
  }

  if (abtRxBuf[1] != CHIP_DATA(pnd)->last_command + 1) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Command Code verification failed");
    pnd->last_error = NFC_EIO;
    goto error;
  }

  if (len) {
    pnd->last_error = ble_uart_poll_receive(pbtData, len, 0, timeout);
    if (pnd->last_error != 0) {
      //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Unable to receive data. (RX)");
      goto error;
    }
  }

  pnd->last_error = ble_uart_poll_receive(abtRxBuf, 2, 0, timeout);
  if (pnd->last_error != 0) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Unable to receive data. (RX)");
    goto error;
  }

  uint8 btDCS = (256 - 0xD5);
  btDCS -= CHIP_DATA(pnd)->last_command + 1;
  for (size_t szPos = 0; szPos < len; szPos++) {
    btDCS -= pbtData[szPos];
  }

  if (btDCS != abtRxBuf[0]) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Data checksum mismatch");
    pnd->last_error = NFC_EIO;
    goto error;
  }

  if (0x00 != abtRxBuf[1]) {
    //log_put(LOG_GROUP, LOG_CATEGORY, NFC_LOG_PRIORITY_ERROR, "%s", "Frame postamble mismatch");
    pnd->last_error = NFC_EIO;
    goto error;
  }
  // The PN53x command is done and we successfully received the reply
  return len;
error:
  ble_uart_flush_input(true);
  return pnd->last_error;
}

int
pn532_uart_ack(nfc_device *pnd)
{
  if (POWERDOWN == CHIP_DATA(pnd)->power_mode) {
    int res = 0;
    if ((res = pn532_uart_wakeup(pnd)) < 0) {
      return res;
    }
  }
  return (ble_uart_poll_send(pn53x_ack_frame, sizeof(pn53x_ack_frame),  0));
}

static int
pn532_uart_abort_command(nfc_device *pnd)
{
  return NFC_SUCCESS;
}

const struct pn53x_io pn532_uart_io = {
  .send       = pn532_uart_send,
  .receive    = pn532_uart_receive,
};

const struct nfc_driver pn532_uart_driver = {
  .name                             = PN532_UART_DRIVER_NAME,
  .scan_type                        = INTRUSIVE,
  .scan                             = NULL,
  .open                             = pn532_uart_open,
  .close                            = pn532_uart_close,
  .strerror                         = NULL,

  .initiator_init                   = pn53x_initiator_init,
  .initiator_init_secure_element    = pn532_initiator_init_secure_element,
  .initiator_select_passive_target  = pn53x_initiator_select_passive_target,
  .initiator_poll_target            = NULL,
  .initiator_select_dep_target      = pn53x_initiator_select_dep_target,
  .initiator_deselect_target        = pn53x_initiator_deselect_target,
  .initiator_transceive_bytes       = pn53x_initiator_transceive_bytes,
  .initiator_transceive_bits        = NULL,
  .initiator_transceive_bytes_timed = NULL,
  .initiator_transceive_bits_timed  = NULL,
  .initiator_target_is_present      = pn53x_initiator_target_is_present,

  .target_init           = pn53x_target_init,
  .target_send_bytes     = pn53x_target_send_bytes,
  .target_receive_bytes  = pn53x_target_receive_bytes,
  .target_send_bits      = pn53x_target_send_bits,
  .target_receive_bits   = pn53x_target_receive_bits,

  .device_set_property_bool     = pn53x_set_property_bool,
  .device_set_property_int      = pn53x_set_property_int,
  .get_supported_modulation     = pn53x_get_supported_modulation,
  .get_supported_baud_rate      = pn53x_get_supported_baud_rate,
  .device_get_information_about = NULL,

  .abort_command  = pn532_uart_abort_command,
  .idle           = pn53x_idle,
  .powerdown      = pn53x_PowerDown,
};

