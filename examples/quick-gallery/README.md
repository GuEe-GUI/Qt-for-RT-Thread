# Qt Quick Controls 2 Gallery

RT-Thread kernel-mode launcher for Qt's built-in Qt Quick Controls 2 Gallery.
It is the primary visual QML validation demo because it exercises text, images,
layouts, models, navigation, animation, mouse/keyboard input, and the standard
embedded controls without requiring shader effects.

The launcher uses the QV4 interpreter, software scene graph, basic render loop,
Fusion style, RT-Thread framebuffer, and evdev input. Fusion is used because
its software-rendered control backgrounds do not depend on Material elevation
and shadow composition.
DejaVu Sans is embedded and registered at startup so text rendering does not
depend on a `/fonts` directory in the target filesystem.

Expected console progress:

```text
QUICK_GALLERY_STAGE app
QUICK_GALLERY_STAGE engine
QUICK_GALLERY_STAGE visible
```

Run QEMU with `qemu.py -graphic`, then execute `qt_run` in msh.
