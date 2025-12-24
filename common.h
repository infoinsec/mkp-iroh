#define SECRET_LEN 64
#define PUBLIC_LEN 32
#define SEED_LEN   32
// with checksum + version num
#define PUBONION_LEN (PUBLIC_LEN + 3)

#define PKPREFIX_SIZE (29 + 3)
#define SKPREFIX_SIZE (29 + 3)

extern const char * const pkprefix;
extern const char * const skprefix;

#define FORMATTED_PUBLIC_LEN (PKPREFIX_SIZE + PUBLIC_LEN)
#define FORMATTED_SECRET_LEN (SKPREFIX_SIZE + SECRET_LEN)

// full onion address, WITHOUT newline or terminating nil char
#define ONION_LEN 62

// RFC4648 base32 length for a 32-byte public key (no padding)
#define IROH_BASE32_LEN 52
#define IROH_SECRET_LEN 32

extern pthread_mutex_t fout_mutex;
extern FILE *fout;

extern size_t onionendpos;   // end of .onion within string
extern size_t direndpos;     // end of dir before .onion within string
extern size_t printstartpos; // where to start printing from
extern size_t printlen;      // precalculated, related to printstartpos

extern int iroh_mode;
