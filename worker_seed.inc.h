#ifndef SEED_POOL_COUNT
#define SEED_POOL_COUNT 1024
#endif

static inline void store_le64(u8 out[8],u64 v)
{
	for (int i = 0;i < 8;++i) {
		out[i] = v & 0xFF;
		v >>= 8;
	}
}

void *CRYPTO_NAMESPACE(worker_seed)(void *task)
{
	u8 seed[SEED_LEN];
	u8 sk[SECRET_LEN];
	u8 pk[PUBLIC_LEN + 1];
	u8 wpk[PUBLIC_LEN + 1];
	ge_p3 ALIGN(16) ge_public;
	size_t i;
	// Pool RNG output to reduce randombytes() calls per key.
	u8 seed_pool[SEED_LEN * SEED_POOL_COUNT];
	size_t pool_idx = SEED_POOL_COUNT;
	u8 prng_key[crypto_stream_chacha20_KEYBYTES];
	u8 prng_nonce[crypto_stream_chacha20_NONCEBYTES];
	u64 prng_counter = 0;

#ifdef STATISTICS
	struct statstruct *st = (struct statstruct *)task;
#else
	(void) task;
#endif

	PREFILTER

	randombytes_buf(prng_key,sizeof(prng_key));

	pk[PUBLIC_LEN] = 0;
	wpk[PUBLIC_LEN] = 0;

	while (!endwork) {
#ifdef STATISTICS
		++st->numrestart.v;
#endif
		if (pool_idx >= SEED_POOL_COUNT) {
			store_le64(prng_nonce,prng_counter++);
			crypto_stream_chacha20(seed_pool,
				(unsigned long long)sizeof(seed_pool),
				prng_nonce,prng_key);
			pool_idx = 0;
		}
		memcpy(seed,&seed_pool[pool_idx * SEED_LEN],SEED_LEN);
		++pool_idx;
		ed25519_seckey_expand(sk,seed);
		ge_scalarmult_base(&ge_public,sk);
		ge_p3_tobytes(pk,&ge_public);

#ifdef STATISTICS
		++st->numcalc.v;
#endif

		DOFILTER(i,pk,{
			if (numwords > 1) {
				shiftpk(wpk,pk,filter_len(i));
				size_t j;
				for (int w = 1;;) {
					DOFILTER(j,wpk,goto secondfind);
					goto next;
				secondfind:
					if (++w >= numwords)
						break;
					shiftpk(wpk,wpk,filter_len(j));
				}
			}
			ADDNUMSUCCESS;
			irohready(seed,pk,0);
		});
	next:
		;
	}

	POSTFILTER

	sodium_memzero(sk,sizeof(sk));
	sodium_memzero(seed,sizeof(seed));

	return 0;
}
