QT += core gui qml quick quickcontrols2

TEMPLATE = lib
CONFIG += staticlib
TARGET = qt_quick_gallery

QT_SOURCE_DIR = $$clean_path($$PWD/../../../..)
GALLERY = $$QT_SOURCE_DIR/qtquickcontrols2/examples/quickcontrols2/gallery
QTBASE = $$QT_SOURCE_DIR/qtbase

SOURCES += quick_gallery.cpp

# Static plugins are registered once by the RT-Thread package integration.
DEFINES += QT_RTTHREAD_PACKAGE_MANAGED_PLUGINS

gallery_resources.prefix = /
gallery_resources.base = $$GALLERY
gallery_resources.files = \
    $$GALLERY/gallery.qml \
    $$files($$GALLERY/pages/*.qml) \
    $$GALLERY/qtquickcontrols2.conf \
    $$files($$GALLERY/icons/gallery/20x20/*.png) \
    $$files($$GALLERY/icons/gallery/20x20@2/*.png) \
    $$files($$GALLERY/icons/gallery/20x20@3/*.png) \
    $$files($$GALLERY/icons/gallery/20x20@4/*.png) \
    $$GALLERY/icons/gallery/index.theme \
    $$files($$GALLERY/images/*.png)
RESOURCES += gallery_resources

font_resources.prefix = /fonts
font_resources.base = $$QTBASE/src/3rdparty/wasm
font_resources.files = $$QTBASE/src/3rdparty/wasm/DejaVuSans.ttf
RESOURCES += font_resources
