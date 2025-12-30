# mkp-iroh-z32

This repo contains a modified mkp224o that adds `mkp-iroh-z32`, a vanity
prefix generator for Iroh EndpointIds using z-base-32 (z32) encoding.

## Build dependencies

You need a C compiler, GNU make, autoconf, and libsodium.
For the AWS-LC path, you also need CMake, Go, and Perl (macOS includes /usr/bin/perl).

### macOS (Homebrew)

```bash
xcode-select --install
brew install autoconf make libsodium cmake go
```

Use `gmake` (GNU make) instead of `make`, or add GNU make to your PATH:

```bash
export PATH="/opt/homebrew/opt/make/libexec/gnubin:$PATH"
```

## Happy path (AWS-LC, fastest)

### 1) Build AWS-LC (once)

From the repo root (installs to a local prefix):

```bash
git clone --depth 1 https://github.com/aws/aws-lc.git third_party/aws-lc
cmake -S third_party/aws-lc -B third_party/aws-lc/build -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PWD/aws-lc-install" \
  -DBUILD_TESTING=OFF -DBUILD_TOOL=OFF -DBUILD_LIBSSL=OFF
env GOCACHE="$PWD/.gocache" \
    GOPATH="$PWD/.gopath" \
    GOMODCACHE="$PWD/.gomodcache" \
    cmake --build third_party/aws-lc/build --target install --parallel
```

If you already have an AWS-LC install elsewhere, you can skip this section
and point `--with-aws-lc` to that prefix.

### 2) Build mkp-iroh-z32

From the repo root:

```bash
./autogen.sh
make clean
./configure --enable-intfilter=64 --enable-aws-lc --with-aws-lc=/path/to/aws-lc/install \
  CPPFLAGS="-I/path/to/aws-lc/install/include -I/opt/homebrew/include" \
  LDFLAGS="-L/path/to/aws-lc/install/lib -L/opt/homebrew/lib"
make mkp-iroh-z32
```

Notes:
- `--enable-aws-lc` and `--enable-lib25519` are mutually exclusive.
- If AWS-LC is unavailable, omit `--enable-aws-lc` (or use `--enable-lib25519`).
- `--with-aws-lc` should point to a prefix containing `include/openssl` and
  `lib/libcrypto` (for example, from `cmake --install`).
- Put the AWS-LC include/lib paths before Homebrew in `CPPFLAGS`/`LDFLAGS` to
  avoid accidentally linking against Homebrew OpenSSL.

## Run

```bash
./mkp-iroh-z32 <prefix> [prefix...]
```

- Prefixes use z32 alphabet: `ybndrfg8ejkmcpqxot1uwisza345h769` (lowercase only).
- Multiple prefixes are OR (match any).
- Matches append to `./iroh-keys.txt` and are also printed to stdout by default.
- Use `-x` to suppress stdout output.
- Use `-o` (append) or `-O` (overwrite) to set output file.
- Use `-s` to print statistics.
- For cleaner benchmarking output, use `-x` (no stdout) or a long prefix
  (10+ characters) to reduce matches. Example:

```bash
./mkp-iroh-z32 ybndrfg8ejk -s -x
```

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
