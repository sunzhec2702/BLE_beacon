/**
 * @file nfc.h
 * @brief libnfc interface
 *
 * Provide all usefull functions (API) to handle NFC devices.
 */

#ifndef _LIBNFC_H_
#  define _LIBNFC_H_

#include "nfc-types.h"

#  ifndef __has_attribute
#    define __has_attribute(x) 0
#  endif

#  if __has_attribute(nonnull) || defined(__GNUC__)
#    define __has_attribute_nonnull 1
#  endif

#  if __has_attribute_nonnull
#    define ATTRIBUTE_NONNULL( param ) __attribute__((nonnull (param)))
#  else
#  define ATTRIBUTE_NONNULL( param )
#  endif

#  ifdef __cplusplus
extern  "C" {
#  endif                        // __cplusplus

/* NFC Device/Hardware manipulation */
nfc_device *nfc_open(nfc_context *context, const nfc_connstring connstring) ATTRIBUTE_NONNULL(1);
void nfc_close(nfc_device *pnd);
int nfc_abort_command(nfc_device *pnd);
size_t nfc_list_devices(nfc_context *context, nfc_connstring connstrings[], size_t connstrings_len) ATTRIBUTE_NONNULL(1);
int nfc_idle(nfc_device *pnd);

/* NFC initiator: act as "reader" */
int nfc_initiator_init(nfc_device *pnd);
int nfc_initiator_init_secure_element(nfc_device *pnd);
int nfc_initiator_select_passive_target(nfc_device *pnd, const nfc_modulation nm, const uint8 *pbtInitData, const size_t szInitData, nfc_target *pnt);
int nfc_initiator_list_passive_targets(nfc_device *pnd, const nfc_modulation nm, nfc_target ant[], const size_t szTargets);
int nfc_initiator_poll_target(nfc_device *pnd, const nfc_modulation *pnmTargetTypes, const size_t szTargetTypes, const uint8 uiPollNr, const uint8 uiPeriod, nfc_target *pnt);
int nfc_initiator_select_dep_target(nfc_device *pnd, const nfc_dep_mode ndm, const nfc_baud_rate nbr, const nfc_dep_info *pndiInitiator, nfc_target *pnt, const int timeout);
int nfc_initiator_poll_dep_target(nfc_device *pnd, const nfc_dep_mode ndm, const nfc_baud_rate nbr, const nfc_dep_info *pndiInitiator, nfc_target *pnt, const int timeout);
int nfc_initiator_deselect_target(nfc_device *pnd);
int nfc_initiator_transceive_bytes(nfc_device *pnd, const uint8 *pbtTx, const size_t szTx, uint8 *pbtRx, const size_t szRx, int timeout);
int nfc_initiator_transceive_bits(nfc_device *pnd, const uint8 *pbtTx, const size_t szTxBits, const uint8 *pbtTxPar, uint8 *pbtRx, const size_t szRx, uint8 *pbtRxPar);
int nfc_initiator_transceive_bytes_timed(nfc_device *pnd, const uint8 *pbtTx, const size_t szTx, uint8 *pbtRx, const size_t szRx, uint32 *cycles);
int nfc_initiator_transceive_bits_timed(nfc_device *pnd, const uint8 *pbtTx, const size_t szTxBits, const uint8 *pbtTxPar, uint8 *pbtRx, const size_t szRx, uint8 *pbtRxPar, uint32 *cycles);
int nfc_initiator_target_is_present(nfc_device *pnd, const nfc_target *pnt);

/* NFC target: act as tag (i.e. MIFARE Classic) or NFC target device. */
int nfc_target_init(nfc_device *pnd, nfc_target *pnt, uint8 *pbtRx, const size_t szRx, int timeout);
int nfc_target_send_bytes(nfc_device *pnd, const uint8 *pbtTx, const size_t szTx, int timeout);
int nfc_target_receive_bytes(nfc_device *pnd, uint8 *pbtRx, const size_t szRx, int timeout);
int nfc_target_send_bits(nfc_device *pnd, const uint8 *pbtTx, const size_t szTxBits, const uint8 *pbtTxPar);
int nfc_target_receive_bits(nfc_device *pnd, uint8 *pbtRx, const size_t szRx, uint8 *pbtRxPar);

/* Error reporting */
const char *nfc_strerror(const nfc_device *pnd);
int nfc_strerror_r(const nfc_device *pnd, char *buf, size_t buflen);
void nfc_perror(const nfc_device *pnd, const char *s);
int nfc_device_get_last_error(const nfc_device *pnd);

/* Special data accessors */
const char *nfc_device_get_name(nfc_device *pnd);
const char *nfc_device_get_connstring(nfc_device *pnd);
int nfc_device_get_supported_modulation(nfc_device *pnd, const nfc_mode mode,  const nfc_modulation_type **const supported_mt);
int nfc_device_get_supported_baud_rate(nfc_device *pnd, const nfc_modulation_type nmt, const nfc_baud_rate **const supported_br);

/* Properties accessors */
int nfc_device_set_property_int(nfc_device *pnd, const nfc_property property, const int value);
int nfc_device_set_property_bool(nfc_device *pnd, const nfc_property property, const bool bEnable);

/* Misc. functions */
void iso14443a_crc(uint8 *pbtData, size_t szLen, uint8 *pbtCrc);
void iso14443a_crc_append(uint8 *pbtData, size_t szLen);
void iso14443b_crc(uint8 *pbtData, size_t szLen, uint8 *pbtCrc);
void iso14443b_crc_append(uint8 *pbtData, size_t szLen);
uint8 *iso14443a_locate_historical_bytes(uint8 *pbtAts, size_t szAts, size_t *pszTk);

void nfc_free(void *p);
const char *nfc_version(void);
int nfc_device_get_information_about(nfc_device *pnd, char **buf);

/* String converter functions */
const char *str_nfc_modulation_type(const nfc_modulation_type nmt);
const char *str_nfc_baud_rate(const nfc_baud_rate nbr);
int str_nfc_target(char **buf, const nfc_target *pnt, bool verbose);

/* Error codes */
/** @ingroup error
 * @hideinitializer
 * Success (no error)
 */
#define NFC_SUCCESS			 0
/** @ingroup error
 * @hideinitializer
 * Input / output error, device may not be usable anymore without re-open it
 */
#define NFC_EIO				-1
/** @ingroup error
 * @hideinitializer
 * Invalid argument(s)
 */
#define NFC_EINVARG			-2
/** @ingroup error
 * @hideinitializer
 *  Operation not supported by device
 */
#define NFC_EDEVNOTSUPP			-3
/** @ingroup error
 * @hideinitializer
 * No such device
 */
#define NFC_ENOTSUCHDEV			-4
/** @ingroup error
 * @hideinitializer
 * Buffer overflow
 */
#define NFC_EOVFLOW			-5
/** @ingroup error
 * @hideinitializer
 * Operation timed out
 */
#define NFC_ETIMEOUT			-6
/** @ingroup error
 * @hideinitializer
 * Operation aborted (by user)
 */
#define NFC_EOPABORTED			-7
/** @ingroup error
 * @hideinitializer
 * Not (yet) implemented
 */
#define NFC_ENOTIMPL			-8
/** @ingroup error
 * @hideinitializer
 * Target released
 */
#define NFC_ETGRELEASED			-10
/** @ingroup error
 * @hideinitializer
 * Error while RF transmission
 */
#define NFC_ERFTRANS			-20
/** @ingroup error
 * @hideinitializer
 * MIFARE Classic: authentication failed
 */
#define NFC_EMFCAUTHFAIL		-30
/** @ingroup error
 * @hideinitializer
 * Software error (allocation, file/pipe creation, etc.)
 */
#define NFC_ESOFT			-80
/** @ingroup error
 * @hideinitializer
 * Device's internal chip error
 */
#define NFC_ECHIP			-90


#  ifdef __cplusplus
}
#  endif                        // __cplusplus
#endif                          // _LIBNFC_H_
