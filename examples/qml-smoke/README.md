# QML smoke test

The kernel test deliberately excludes QtGui and Qt Quick. It forces the QV4
interpreter and verifies QML component creation, JavaScript evaluation,
property keys, repeated managed-object allocation, and garbage collection.

The test passes only when the target console prints `QML_SMOKE_PASS`.

The RT-Thread kernel build currently runs the QML type loader synchronously.
This avoids entering RT-Smart's LWP syscall return path from a kernel-created
Qt thread. The RT-Smart user package should keep the normal asynchronous type
loader when the kernel and user package build profiles are split.

QV4 page reservations use RT-Thread aligned heap allocations in this build;
guard pages and executable/JIT mappings are intentionally disabled. Managed
pointers use bit 48 to distinguish compressed kernel addresses from valid low
addresses, so both RT-Thread kernel pointers and RT-Smart mappings round-trip.
