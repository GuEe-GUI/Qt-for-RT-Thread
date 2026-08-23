# QMake device specifications

Two independent device specifications will be maintained:

- `rtthread-kernel-aarch64-g++`
- `rtthread-riscv64-linux-musl-g++` (kernel mode, RV64 `lp64` ABI)
- `rtsmart-aarch64-g++`

They must not select the same thread backend merely because they target the
same RT-Thread BSP or CPU architecture.
