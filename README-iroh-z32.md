# mkp-iroh-z32

This repo contains a modified mkp224o that adds `mkp-iroh-z32`, a vanity
prefix generator for Iroh EndpointIds using z-base-32 (z32) encoding.

## Build (recommended)

From the `mkp224o/` directory:

```bash
./autogen.sh
make clean
./configure --enable-intfilter=64 --enable-lib25519 CPPFLAGS="-I/opt/homebrew/include" LDFLAGS="-L/opt/homebrew/lib"
make mkp-iroh-z32
```

Note: `--enable-ref10` was slower on Apple Silicon in our tests, so we avoid it.
If lib25519 is unavailable on your system, omit `--enable-lib25519`.

## Run

```bash
./mkp-iroh-z32 <prefix> [prefix...]
```

- Prefixes use z32 alphabet: `ybndrfg8ejkmcpqxot1uwisza345h769` (lowercase only).
- Multiple prefixes are OR (match any).
- Matches append to `./iroh-keys.txt` by default.
- Use `-o` (append) or `-O` (overwrite) to set output file.
- Use `-s` to print statistics.

## Output

```
Iroh z32: <z32>
EndpointId (hex): <hex>
SecretKey (hex): <hex>
ANNOUNCE_SECRET=<hex>
```

## Notes

- z32 is different from RFC4648 base32 (Tor onion addresses). Prefixes are not
  interchangeable.
- `ANNOUNCE_SECRET` requires the 32-byte seed (this tool outputs it).
