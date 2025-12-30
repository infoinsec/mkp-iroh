#include "aws_lc_iroh.h"

#ifdef USE_AWSLC
#include <openssl/curve25519.h>
#include <sodium/utils.h>

void aws_lc_ed25519_pubkey_from_seed(u8 pk[32],const u8 seed[32])
{
	u8 priv[ED25519_PRIVATE_KEY_LEN];

	ED25519_keypair_from_seed(pk,priv,seed);
	sodium_memzero(priv,sizeof(priv));
}
#endif
