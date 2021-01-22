INCLUDEPATH+=$$PWD/AdditionalInfo
include($$PWD/AdditionalInfo/AdditionalInfo.pri)
INCLUDEPATH+=$$PWD/Angiography
include($$PWD/Angiography/Angiography.pri)
INCLUDEPATH+=$$PWD/LabExamination
include($$PWD/LabExamination/LabExamination.pri)
INCLUDEPATH+=$$PWD/PathologyInfo
include($$PWD/PathologyInfo/PathologyInfo.pri)
INCLUDEPATH+=$$PWD/PatientInfo
include($$PWD/PatientInfo/PatientInfo.pri)
INCLUDEPATH+=$$PWD/PatientState
include($$PWD/PatientState/PatientState.pri)
INCLUDEPATH+=$$PWD/PCI
include($$PWD/PCI/PCI.pri)
INCLUDEPATH+=$$PWD/ReportPic
include($$PWD/ReportPic/ReportPic.pri)
INCLUDEPATH+=$$PWD/ReportPrint
include($$PWD/ReportPrint/ReportPrint.pri)

FORMS += \
    $$PWD/cwidgetreport.ui

HEADERS += \
    $$PWD/cwidgetreport.h \
    $$PWD/isubreport.h

SOURCES += \
    $$PWD/cwidgetreport.cpp \
    $$PWD/isubreport.cpp

RESOURCES += \
    $$PWD/Image.qrc

DISTFILES +=


