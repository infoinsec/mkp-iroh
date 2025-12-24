#!/usr/bin/env python3
import binascii
import sys

PUBKEY_HEX = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
EXPECTED = "yyyoryarywdyqnyjbefoadeqbhebnrounoktcfaadrpbs8y7daxo"
Z32_ALPHABET = "ybndrfg8ejkmcpqxot1uwisza345h769"


def z32_encode(data: bytes) -> str:
    out = []
    buf = 0
    bits = 0
    for b in data:
        buf = (buf << 8) | b
        bits += 8
        while bits >= 5:
            bits -= 5
            out.append(Z32_ALPHABET[(buf >> bits) & 0x1F])
    if bits:
        out.append(Z32_ALPHABET[(buf << (5 - bits)) & 0x1F])
    return "".join(out)


raw = binascii.unhexlify(PUBKEY_HEX)
encoded = z32_encode(raw)
print(encoded)

if encoded != EXPECTED:
    print("unexpected z32 output", file=sys.stderr)
    print("expected:", EXPECTED, file=sys.stderr)
    sys.exit(1)
