INCLUDEPATH+=$$PWD/Medicine
include($$PWD/Medicine/Medicine.pri)
INCLUDEPATH+=$$PWD/Tool
include($$PWD/Tool/Tool.pri)
INCLUDEPATH+=$$PWD/Distributor
include($$PWD/Distributor/Distributor.pri)

FORMS += \
    $$PWD/cwidgetmedtool.ui

HEADERS += \
    $$PWD/cwidgetmedtool.h

SOURCES += \
    $$PWD/cwidgetmedtool.cpp
