# Qt Quick TV Tennis demo

This is a kernel-mode launcher for Qt's built-in
`examples/quick/animation/behaviors/tvtennis.qml` example. The QML source is
embedded from the selected Qt source tree and retains Qt's BSD example license.

The launcher forces the software scene graph, the basic render loop, and the
QV4 interpreter. It deliberately avoids images, fonts, particles, shaders, and
network access so that the first run tests only Qt Quick item creation,
animation, scene graph rendering, and the RT-Thread framebuffer platform.

Expected console progress:

```text
QUICK_TVTENNIS_STAGE app
QUICK_TVTENNIS_STAGE view
QUICK_TVTENNIS_STAGE qml_ready
QUICK_TVTENNIS_STAGE visible
```

The target must link QtCore, QtGui, QtQml, QtQuick, the RT-Thread framebuffer
QPA plugin, and this example archive.

For the `qemu-virt64-aarch64` BSP, start QEMU with `qemu.py -graphic`.
The default `-nographic` mode does not instantiate `ramfb`, so `/dev/fb0`
does not exist and the `rtthreadfb` platform plugin cannot create a screen.

Static builds must also link `qml/QtQuick.2/libqtquick2plugin.a`; the launcher
explicitly imports `QtQuick2Plugin`, `QRTThreadFbIntegrationPlugin`, and the
evdev mouse and keyboard plugins.
