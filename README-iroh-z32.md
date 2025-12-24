# mkp-iroh-z32

This branch adds `mkp-iroh-z32`, a vanity generator for Iroh EndpointIds using
z-base-32 (z32) encoding. It searches for prefixes in the z32-encoded 32-byte
ed25519 public key and outputs the 32-byte seed required for ANNOUNCE_SECRET.

## Identifier formats
- Iroh EndpointId: 32-byte ed25519 public key.
- Iroh z32: 52 chars, alphabet `ybndrfg8ejkmcpqxot1uwisza345h769` (lowercase).
- Tor v3 onion uses RFC4648 base32 with a different alphabet.

## Usage
`./mkp-iroh-z32 <prefix> [prefix...]`

- Multiple prefixes are OR (match any).
- Invalid characters or uppercase letters are rejected.

## Output
Matches append to `./iroh-keys.txt` by default. Use `-o` or `-O` to change
output path/name. `-x` disables output. `-s` prints stats.

Output lines:

```
Iroh z32: <z32>
EndpointId (hex): <hex>
SecretKey (hex): <hex>
ANNOUNCE_SECRET=<hex>
```

## Test vector
Run `python3 contrib/iroh_z32_vector.py` to verify z32 encoding.
