# RT-Thread kernel package integration

This directory contains the package-side `Kconfig`, `package.json`, static
plugin registrar, and `SConscript` integration.

## Build boundary

The normal BSP `scons` invocation does not configure or compile Qt. Qt and
tslib are too large for that workflow and require host tools (`qmake`, `moc`,
and `rcc`) in addition to target libraries. The package preparation stage
fetches the pinned sources, applies the selected kernel patch series, and
assembles a relocatable target SDK:

```text
sdk/kernel/
├── include/
├── lib/
├── plugins/
└── qml/
```

`PKG_QT_RTTHREAD_SDK_PATH` selects that SDK. It may be an absolute path during
port development or a path relative to the installed package for a released
preassembled SDK.

## SCons responsibilities

The package `SConscript`:

- exports public Qt include paths;
- selects module, QML plugin, style, image, evdev, and tslib archives from
  Kconfig;
- compiles one static plugin registrar;
- links all Qt, C++, C library and compiler-runtime archives inside a GNU ld
  `--start-group`/`--end-group`, allowing circular static dependencies to be
  resolved without BSP-specific library ordering;
- optionally links a selected external demo archive that exports `qt_main()`.

`PKG_QT_RTTHREAD_DEMO` and `PKG_QT_RTTHREAD_DEMO_ARCHIVE` are independent of
QML: they can select a QtCore, QWidget, QML, or Qt Quick static demo archive.
The linker retains its `qt_main()` symbol explicitly.  The separate
`PKG_QT_RTTHREAD_GALLERY_DEMO` option is only for Qt Quick Controls 2 Gallery,
which additionally needs every bundled Controls style and Qt.labs.settings.

When `PKG_QT_RTTHREAD_DEFAULT_ENTRY` is enabled, the package also supplies the
`qt_run` msh command and creates the configured Qt thread. Applications expose:

```cpp
extern "C" void qt_main(void *parameter);
```

The launcher owns common framebuffer, input, QML interpreter, software scene
graph, and render-loop environment variables. Thread stack, priority, time
slice, pointer, keyboard device, and Qt font directory are Kconfig values.
QtGui, QWidget, and QML applications that display text need TTF or OTF fonts
at `PKG_QT_RTTHREAD_FONTDIR` before `qt_run`; QtCore-only applications do not.
An application may instead embed a font in its resources and register it with
`QFontDatabase::addApplicationFont()`. The `rtthreadfb` platform selects the
primary framebuffer; the unsupported Linux-style `:fb=/dev/fb0` suffix is
intentionally not generated.

This replaces BSP-specific absolute `LINKFLAGS` lists. A normal application
`SConscript` only builds its application sources:

```python
from building import *

cwd = GetCurrentDir()
src = Glob('*.c') + Glob('*.cpp')
group = DefineGroup('Applications', src, depend=[''], CPPPATH=[cwd])
Return('group')
```

## Package-index connection

For local development, place or link this package at
`packages/qt-rtthread`, source its `Kconfig` from the local package menu, and
set `PKG_QT_RTTHREAD_SDK_PATH` to the assembled GCC7 SDK. For publication,
copy `Kconfig` and `package.json` into the RT-Thread packages index under the
`multimedia/qt-rtthread` entry; the downloaded repository supplies this
`SConscript` and `src/qt_rtthread_plugins.cpp`.

The current kernel profile requires C++, DFS/devfs, POSIX device I/O and poll,
the graphics/input framework, and a framebuffer device. Board-specific device
names, Qt thread stack size, touchscreen calibration, and `qt_main` remain BSP
or application policy rather than package-global constants.

QtCore and modest QWidget programs can use the BSP's usual heap. QML/Qt Quick
needs a heap that can allocate full-frame software-rendering buffers: select
`RT_USING_MEMHEAP_AS_HEAP` (and normally `RT_USING_MEMHEAP_AUTO_BINDING`). The
SLAB heap rejects allocations above 16 KiB, which causes Qt Quick's hundreds of
KiB image buffers to fail and can lead to a later null-pointer crash.
