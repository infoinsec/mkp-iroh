#ifndef AWS_LC_IROH_H
#define AWS_LC_IROH_H

#include "types.h"

#ifdef USE_AWSLC
void aws_lc_ed25519_pubkey_from_seed(u8 pk[32],const u8 seed[32]);
#endif

#endif
