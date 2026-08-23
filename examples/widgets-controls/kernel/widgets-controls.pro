QT += core gui widgets

TEMPLATE = lib
CONFIG += staticlib c++11
TARGET = qt_widgets_controls

# Platform, input, and image plugins are registered by the package integration
# source, so this archive only contains the application itself.
SOURCES += widgets_controls.cpp
