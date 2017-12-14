#ifndef _LIBNFC_MIRROR_SUBR_H_
#define _LIBNFC_MIRROR_SUBR_H_
#include "nfc-types.h"


uint8  mirror(uint8 bt);
uint32 mirror32(uint32 ui32Bits);
uint64 mirror64(uint64 ui64Bits);
void    mirror_uint8s(uint8 *pbts, size_t szLen);

#endif // _LIBNFC_MIRROR_SUBR_H_
