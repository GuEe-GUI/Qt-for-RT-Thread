QT += core
QT -= gui

TEMPLATE = lib
CONFIG += staticlib c++11
TARGET = qt_core_customtype

# Use the unmodified Qt 5.12 custom-type example from the sibling source tree.
# This repository is normally checked out beside qtbase; SDK assembly copies
# the resulting archive into its examples/ directory when needed.
UPSTREAM_EXAMPLE = $$clean_path($$PWD/../../../../qtbase/examples/corelib/tools/customtype)

INCLUDEPATH += $$UPSTREAM_EXAMPLE
SOURCES += \
    core_customtype.cpp \
    $$UPSTREAM_EXAMPLE/main.cpp \
    $$UPSTREAM_EXAMPLE/message.cpp
HEADERS += $$UPSTREAM_EXAMPLE/message.h

# The upstream source keeps its normal main(); the RT-Thread wrapper provides
# qt_main(), which is invoked by the package's qt_run command.
DEFINES += main=qt_core_customtype_upstream_main
