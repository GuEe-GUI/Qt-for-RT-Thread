# Qt Port for RT-Thread and RT-Smart

This repository contains the RT-Thread porting layer for Qt 5. It does not
vendor the complete Qt source tree. The build scripts download a pinned Qt
release, verify it, and apply the patches in this repository.

## Targets

| Target | Runtime | Initial support |
| --- | --- | --- |
| `kernel` | RT-Thread kernel address space | QtCore, QtGui, QtWidgets, QtSvg, QML, software Qt Quick and Qt Quick Controls 2 |
| `smart` | RT-Smart user process | QtCore, QtGui, QtWidgets, QtSvg, QML and software Qt Quick |

Qt Quick uses the interpreter and software scene graph on both targets. The
kernel port includes a QV4 value-encoding adaptation for RT-Thread's high
kernel virtual addresses; RT-Smart retains the normal low user-space layout.

## Repository layout

```text
config/                 pinned upstream versions and checksums
patches/5.12.12/
  common/               patches shared by both targets
  kernel/               RT-Thread kernel-mode port
  smart/                RT-Smart user-mode port
mkspecs/                target-specific qmake device specifications
scripts/                fetch, patch, build and SDK assembly scripts
integrations/kernel/    RT-Thread kernel package and SCons integration
integrations/smart/     RT-Smart user-app integration contract
examples/               minimal validation applications
tests/                  smoke and platform tests
docs/                   architecture and porting notes
```

## Design rules

1. Keep upstream Qt sources unmodified in version control.
2. Pin every source archive by URL and SHA-256.
3. Keep kernel and RT-Smart mkspecs separate.
4. Use RT-Thread IPC only in the kernel target; use POSIX/pthread in RT-Smart.
5. Build host tools separately from target libraries.
6. Make each patch small, ordered, documented and independently reviewable.

## Status

Kernel-mode QML, JavaScript/GC, Qt Quick animation, and the Qt Quick Controls 2
Imagine Automotive example have been validated on `qemu-virt64-aarch64`.
`qemu-virt64-riscv` has the matching RV64 musl mkspec and MMU/S-mode kernel
static-TLS support. The QtBase, QML, Qt Quick, and Qt Quick Controls 2 static
SDK layers are cross-build validated with the `lp64` ABI; the Qt Quick TV
Tennis smoke demo reaches its visible first frame at runtime. RV64 QML/Quick
requires the memheap application heap rather than the 16 KiB-limited SLAB heap.
The kernel integration is ready for package-index wiring. RT-Smart keeps a
separate integration boundary and patch series; its user-app build remains the
next target rather than inheriting kernel-only adaptations.
