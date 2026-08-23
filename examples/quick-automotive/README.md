# Qt Quick Controls 2 Automotive demo

RT-Thread kernel-mode launcher for Qt's
`quickcontrols2/imagine/automotive` example. It uses the QV4 interpreter,
software scene graph, Imagine style, RT-Thread framebuffer, and evdev input.

The two optional `QtGraphicalEffects` glow layers are disabled because the
software framebuffer backend has no shader implementation. All other QML,
Controls 2, Imagine assets, images, layout, animation, and input remain active.

Run QEMU with `qemu.py -graphic`, then execute `qt_run` in msh.

Expected console progress:

```text
QUICK_AUTOMOTIVE_STAGE app
QUICK_AUTOMOTIVE_STAGE engine
QUICK_AUTOMOTIVE_STAGE visible
```

The static image must link the QtQuick, Window, Layouts, Templates 2, Controls
2, and Imagine QML plugins together with `Qt5QuickControls2`,
`Qt5QuickTemplates2`, `Qt5Quick`, and `Qt5Qml`. The launcher imports these
plugins explicitly so static registration does not depend on linker discovery.

Use `QT_QPA_PLATFORM=rtthreadfb`. Do not append the Linux-style
`:fb=/dev/fb0` argument: on the kernel-thread launch path that form currently
enters an RT-Smart signal-return path and trips `lwp_thread_signal_catch`.
