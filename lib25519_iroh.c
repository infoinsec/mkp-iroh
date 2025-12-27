#include "lib25519_iroh.h"

#ifdef USE_LIB25519_NG
#include "lib25519/arm64-maa4-intmul/fe25519.h"
#include "lib25519/arm64-maa4-intmul/sc25519.h"
#include "lib25519/arm64-maa4-intmul/ge25519.h"

void lib25519_ed25519_pubkey_from_scalar(u8 pk[32],const u8 sk[32])
{
	sc25519 sc;
	ge25519 p;
	fe25519 recip;
	fe25519 x;
	fe25519 y;

	sc25519_from32bytes(&sc,sk);
	ge25519_scalarmult_base(&p,&sc);
	fe25519_invert(&recip,&p.z);
	fe25519_mul(&x,&p.x,&recip);
	fe25519_mul(&y,&p.y,&recip);
	fe25519_pack(pk,&y);
	pk[31] ^= (u8) (fe25519_getparity(&x) << 7);
}
#endif
