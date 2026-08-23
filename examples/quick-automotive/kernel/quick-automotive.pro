QT += core gui qml quick quickcontrols2

TEMPLATE = lib
CONFIG += staticlib
TARGET = qt_quick_automotive

AUTOMOTIVE = ../../../../qtquickcontrols2/examples/quickcontrols2/imagine/automotive

SOURCES += automotive_rtthread.cpp

RESOURCES += \
    $$AUTOMOTIVE/icons/icons.qrc \
    $$AUTOMOTIVE/imagine-assets/imagine-assets.qrc \
    $$AUTOMOTIVE/qml/qml.qrc \
    $$AUTOMOTIVE/qtquickcontrols2.conf
