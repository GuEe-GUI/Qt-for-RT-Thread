# Downstream integrations

This directory contains the thin, target-specific layer consumed by downstream
RT-Thread repositories. Runtime porting changes remain in `patches/`; do not
copy them into these directories.

- `kernel/` is copied or referenced by the RT-Thread package index.
- `smart/` is consumed by the RT-Smart userapps package.

Both downstreams must pin the same repository tag and source checksum, while
selecting their own patch series and integration directory.
