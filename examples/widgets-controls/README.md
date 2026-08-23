# Qt Widgets controls

Interactive kernel-mode QWidget demonstration derived from the original
`qt_main/qt_main.cpp` validation program.  It exercises the framebuffer QPA,
font loading, custom checkbox/radio indicators, progress animation, editable
text, and a clickable button without using QML.

Build it as a target static archive next to the prepared SDK:

```text
mkdir build-widgets-controls && cd build-widgets-controls
<target-qmake> ../widgets-controls.pro
make
```

Select `libqt_widgets_controls.a` through
`PKG_QT_RTTHREAD_DEMO_ARCHIVE`, enable `PKG_QT_RTTHREAD_WIDGETS`, rebuild the
BSP, then run `qt_run`.  Fonts are loaded from the package's configured
`PKG_QT_RTTHREAD_FONTDIR`; deploy `wqy-microhei.ttc` there for the Chinese UI.
