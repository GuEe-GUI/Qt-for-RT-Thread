# QtCore customtype

Kernel-mode wrapper for Qt's built-in
`qtbase/examples/corelib/tools/customtype` example. It uses only QtCore:
`QCoreApplication`, `QString`, `QVariant`, a declared custom metatype, and
`QDebug`. It has no QPA, framebuffer, QML, or font dependency.

Build it as a static archive with the same target qmake used for the Qt SDK:

```text
mkdir build-gcc7 && cd build-gcc7
<target-qmake> ../core-customtype.pro
make
```

Select the resulting `libqt_core_customtype.a` through
`PKG_QT_RTTHREAD_DEMO_ARCHIVE`, rebuild the BSP, and run `qt_run` from msh.
Expected output ends with:

```text
QTCORE_CUSTOMTYPE_STAGE done result=0
```
