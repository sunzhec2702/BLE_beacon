/**
 * @file nfc-emulation.h
 * @brief Provide a small API to ease emulation in libnfc
 */

#ifndef __NFC_EMULATION_H__
#define __NFC_EMULATION_H__

#include <sys/types.h>
#include "nfc.h"

#ifdef __cplusplus
extern  "C" {
#endif /* __cplusplus */

struct nfc_emulator;
struct nfc_emulation_state_machine;

/**
 * @struct nfc_emulator
 * @brief NFC emulator structure
 */
struct nfc_emulator {
  nfc_target *target;
  struct nfc_emulation_state_machine *state_machine;
  void *user_data;
};

/**
 * @struct nfc_emulation_state_machine
 * @brief  NFC emulation state machine structure
 */
struct nfc_emulation_state_machine {
  int (*io)(struct nfc_emulator *emulator, const uint8 *data_in, const size_t data_in_len, uint8 *data_out, const size_t data_out_len);
  void *data;
};

NFC_EXPORT int    nfc_emulate_target(nfc_device *pnd, struct nfc_emulator *emulator, const int timeout);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __NFC_EMULATION_H__ */
