#ifndef __SIMPLE_NFC_DEVICE_H_
#define __SIMPLE_NFC_DEVICE_H_
#include "nfc-types.h"

struct nfc_device* nfc_context_init(void);
struct nfc_device* nfc_device_init(void);

struct nfc_device* get_nfc_device_ptr(void);

#endif
