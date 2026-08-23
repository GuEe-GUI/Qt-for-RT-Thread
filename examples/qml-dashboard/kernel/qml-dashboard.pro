QT += qml quick quickcontrols2

TEMPLATE = lib
CONFIG += staticlib c++11
TARGET = qml_dashboard

SOURCES += qml_dashboard.cpp
RESOURCES += qml-dashboard.qrc

# The package integration owns static platform and input plugin registration.
DEFINES += QT_RTTHREAD_PACKAGE_MANAGED_PLUGINS
