#!/usr/bin/env python3
import base64
import binascii
import sys

PUBKEY_HEX = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
EXPECTED = "aaaqeayeaudaocajbifqydiob4ibceqtcqkrmfyydenbwha5dypq"

raw = binascii.unhexlify(PUBKEY_HEX)
encoded = base64.b32encode(raw).decode("ascii").lower().rstrip("=")
print(encoded)

if encoded != EXPECTED:
    print("unexpected base32 output", file=sys.stderr)
    print("expected:", EXPECTED, file=sys.stderr)
    sys.exit(1)
