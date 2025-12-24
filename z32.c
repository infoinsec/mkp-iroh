#include <stddef.h>
#include <stdint.h>
#include "types.h"
#include "z32.h"

static const char z32t[32] = {
	'y', 'b', 'n', 'd', // 0
	'r', 'f', 'g', '8', // 1
	'e', 'j', 'k', 'm', // 2
	'c', 'p', 'q', 'x', // 3
	'o', 't', '1', 'u', // 4
	'w', 'i', 's', 'z', // 5
	'a', '3', '4', '5', // 6
	'h', '7', '6', '9', // 7
};

static inline int z32_index(int c)
{
	switch (c) {
	case 'y': return 0;
	case 'b': return 1;
	case 'n': return 2;
	case 'd': return 3;
	case 'r': return 4;
	case 'f': return 5;
	case 'g': return 6;
	case '8': return 7;
	case 'e': return 8;
	case 'j': return 9;
	case 'k': return 10;
	case 'm': return 11;
	case 'c': return 12;
	case 'p': return 13;
	case 'q': return 14;
	case 'x': return 15;
	case 'o': return 16;
	case 't': return 17;
	case '1': return 18;
	case 'u': return 19;
	case 'w': return 20;
	case 'i': return 21;
	case 's': return 22;
	case 'z': return 23;
	case 'a': return 24;
	case '3': return 25;
	case '4': return 26;
	case '5': return 27;
	case 'h': return 28;
	case '7': return 29;
	case '6': return 30;
	case '9': return 31;
	default:
		return -1;
	}
}

char *z32_to(char *dst,const u8 *src,size_t slen)
{
	size_t i;
	for (i = 0; i + 4 < slen; i += 5) {
		*dst++ = z32t[src[i+0] >> 3];
		*dst++ = z32t[((src[i+0] & 7) << 2) | (src[i+1] >> 6)];
		*dst++ = z32t[(src[i+1] >> 1) & 31];
		*dst++ = z32t[((src[i+1] & 1) << 4) | (src[i+2] >> 4)];
		*dst++ = z32t[((src[i+2] & 15) << 1) | (src[i+3] >> 7)];
		*dst++ = z32t[((src[i+3]) >> 2) & 31];
		*dst++ = z32t[((src[i+3] & 3) << 3) | (src[i+4] >> 5)];
		*dst++ = z32t[src[i+4] & 31];
	}
	if (i < slen) {
		*dst++ = z32t[src[i+0] >> 3];
		if (i + 1 < slen) {
			*dst++ = z32t[((src[i+0] & 7) << 2) | (src[i+1] >> 6)];
			*dst++ = z32t[(src[i+1] >> 1) & 31];
			if (i + 2 < slen) {
				*dst++ = z32t[((src[i+1] & 1) << 4) | (src[i+2] >> 4)];
				if (i + 3 < slen) {
					*dst++ = z32t[((src[i+2] & 15) << 1) | (src[i+3] >> 7)];
					*dst++ = z32t[(src[i+3] >> 2) & 31];
					*dst++ = z32t[(src[i+3] & 3) << 3];
				}
				else {
					*dst++ = z32t[(src[i+2] & 15) << 1];
				}
			}
			else
				*dst++ = z32t[(src[i+1] & 1) << 4];
		}
		else
			*dst++ = z32t[(src[i+0] & 7) << 2];
	}
	*dst = 0;
	return dst;
}

size_t z32_from(u8 *dst,u8 *dmask,const char *src)
{
	size_t i, j, k = (size_t)-1, l, sk = 0;
	u8 mask = 0, cmask = 0;
	for (i = 0;;i += 5) {
		j = i/5;
		if (!src[j]) {
			if (k != (size_t)-1)
				dst[k] &= cmask;
			if (dmask)
				*dmask = cmask;
			return k + 1;
		}
		l = i%8;
		k = i/8;
		if (k != sk)
			cmask = 0;
		sk = k;
		mask = (0x1F << 3) >> l;
		cmask |= mask;
		dst[k] &= ~mask;
		int v = z32_index((u8)src[j]);
		if (v < 0)
			v = 0;
		dst[k] |= (v << 3) >> l;
		if (((0x1F << 8) >> (l+5-8)) & 0xFF) {
			++k;
			sk = k;
			mask = ((0x1F << 8) >> (l+5-8)) & 0xFF;
			cmask = mask;
			dst[k] &= ~mask;
			dst[k] |= ((v << 8) >> (l+5-8)) & 0xFF;
		}
	}
}

int z32_valid(const char *src,size_t *count)
{
	const char *p;
	for (p = src;*p;++p) {
		if (z32_index((u8)*p) < 0)
			break;
	}
	if (count)
		*count = (size_t) (p - src);
	return !*p;
}
