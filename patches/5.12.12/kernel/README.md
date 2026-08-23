# RT-Thread kernel patches

This series contains the RT-Thread native thread and synchronization backends,
kernel-compatible platform definitions, and kernel-mode QPA integration.

The validated kernel-mode QML/Qt Quick additions are recorded in `series`:

1. `0100-qml-qv4-high-address-support.patch` adapts QV4 pointer/value encoding
   and executable-memory allocation to RT-Thread's high kernel addresses.
2. `0110-qml-synchronous-loader.patch` keeps QQml's loader on the kernel launch
   thread, avoiding an unsupported worker-thread startup path.
3. `0120-qthread-startup-unlock.patch` releases the QThread startup mutex before
   creating its event dispatcher.
4. `0130-event-dispatcher-input-notifiers.patch` combines the RT semaphore
   wakeup path with fd polling, restoring `QSocketNotifier` and evdev input.
5. `0150-riscv64-musl-mkspec.patch` adds the RV64 musl qmake device
   specification used by `qemu-virt64-riscv`.
Apply these patches in the listed order after the base RT-Thread kernel port.
The Qt 5.12 source archive contains CRLF files while the stored patch series is
normalized to LF, so the package script must use whitespace-tolerant matching:

```sh
while IFS= read -r patch_name; do
    git apply --ignore-whitespace "qt-rtthread-port/patches/5.12.12/kernel/$patch_name"
done < qt-rtthread-port/patches/5.12.12/kernel/series
```

They have been validated with the QML smoke test, Qt Quick TV Tennis, and the
interactive Qt Quick Controls 2 Gallery using the interpreter, software scene
graph, Fusion style, framebuffer QPA, embedded font, and evdev mouse/keyboard.
The RV64 musl toolchain provides the standard locale, wide-character, process,
and `sysconf()` APIs directly; the package does not replace libc functions.

The two Automotive glow edits are deliberately excluded: they are example-only
shader fallbacks, not part of QML runtime support.
