#ifndef LIB25519_IROH_H
#define LIB25519_IROH_H

#include "types.h"

#ifdef USE_LIB25519_NG
void lib25519_ed25519_pubkey_from_scalar(u8 pk[32],const u8 sk[32]);
#endif

#endif
