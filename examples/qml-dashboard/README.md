# QML dashboard

Interactive Qt Quick Controls 2 Material dashboard for the RT-Thread kernel
port.  It demonstrates static QML resources, the software Qt Quick backend,
the framebuffer platform plugin, periodic updates, progress bars, and button
input.

Build it with the target qmake used for the assembled SDK:

```text
mkdir build && cd build
<target-qmake> ../qml-dashboard.pro
make
```

Select the resulting `libqml_dashboard.a` using
`PKG_QT_RTTHREAD_DEMO_ARCHIVE`, rebuild the BSP, then run `qt_run` in msh.
Enable QML, Qt Quick Controls 2, and the Material style in the package
configuration.  A TTF or TTC font under `/fonts/` is required for text.
