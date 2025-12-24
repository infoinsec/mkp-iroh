// converts src[0:slen] to z-base-32 string (lowercase, no padding)
char *z32_to(char *dst,const u8 *src,size_t slen);
// calculates length needed to store data converted to z-base-32
#define Z32_TO_LEN(l) (((l) * 8 + 4) / 5)
// converts src string from z-base-32
size_t z32_from(u8 *dst,u8 *dmask,const char *src);
// calculates length needed to store data converted from z-base-32
#define Z32_FROM_LEN(l) (((l) * 5 + 7) / 8)
// validates z-base-32 string and optionally stores length of valid data
// returns 1 if whole string is good, 0 if string contains invalid data
int z32_valid(const char *src,size_t *count);
