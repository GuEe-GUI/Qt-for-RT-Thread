# Architecture

## Kernel target

The kernel target links Qt statically into the RT-Thread image. It uses native
RT-Thread threads and IPC plus the RT-Thread framebuffer QPA plugin. QML runs
through the QV4 interpreter, while Qt Quick and Qt Quick Controls 2 use the
software scene graph and basic render loop. Shader-based effects are outside
this profile. AArch64 uses the AAPCS64 thread-pointer register, and the RV64
kernel target uses the RISC-V psABI `tp` register; both require RT-Thread to
allocate a separate static TLS image for every native thread before Qt can run.

The RV64 configuration targets the MMU-enabled S-mode
`qemu-virt64-riscv` BSP with the `riscv64-unknown-linux-musl-` toolchain's
`lp64` ABI.  Its kernel TLS support is deliberately compiled only for that
MMU/S-mode configuration; non-MMU and M-mode RISC-V libcpu targets retain
their existing `tp` policy unchanged.

The RV64 musl toolchain supplies the standard locale, wide-character, process,
and `sysconf()` interfaces itself. The package links that libc normally and
does not override any of its functions.

The software scene graph allocates full-frame and intermediate image buffers.
Kernel QML/Qt Quick therefore requires `RT_USING_MEMHEAP_AS_HEAP`; RT-Thread's
SLAB heap rejects allocations larger than 16 KiB and is not a suitable Qt Quick
application heap.

## RT-Smart target

The RT-Smart target produces user-space libraries and ELF applications. It
uses libc, POSIX filesystem APIs, pthreads, and user-space memory mappings.
Software Qt Quick is enabled only after the QML interpreter and framebuffer
smoke tests pass.

## Build boundary

Host tools such as qmake, moc, rcc, and QML generators run on the development
host. Target libraries and plugins are cross-compiled. The resulting SDK must
record the Qt version, port revision, toolchain tuple, configuration flags,
and compatible RT-Thread revision.

## Downstream repositories

This repository is the versioned source of truth for patches, mkspecs, build
scripts and target integration files. The RT-Thread package index and the
RT-Smart userapps repository should reference a released tag and checksum;
they should not carry private copies of the Qt patches.

The two downstreams select different layers from the same release:

- kernel: `common` plus `kernel` patches and `integrations/kernel`;
- RT-Smart: `common` plus `smart` patches and `integrations/smart`.
