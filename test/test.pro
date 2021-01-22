QT += testlib
QT += core widgets sql webenginewidgets printsupport multimedia
CONFIG += qt warn_on depend_includepath testcase
DEFINES += QT_NO_WAENING_OUTPUT
TEMPLATE = app

# 使用多字节字符集
#DEFINES  -= UNICODE
#DEFINES  += UMBCS
QMAKE_CXXFLAGS += /utf-8

# 主模块
INCLUDEPATH += $$PWD/../src/Check
include($$PWD/../src/Check/Check.pri)

# 查询模块
INCLUDEPATH += $$PWD/../src/QueryStatistics
include($$PWD/../src/QueryStatistics/QueryStatistics.pri)



# 报告模块
INCLUDEPATH += $$PWD/../src/Report
include($$PWD/../src/Report/Report.pri)


# 系统设置模块
INCLUDEPATH += $$PWD/../src/SysSetting
include($$PWD/../src/SysSetting/SysSetting.pri)

# 系统设置模块2
INCLUDEPATH += $$PWD/../src/MedTool
include($$PWD/../src/MedTool/MedTool.pri)

# 统计模块
INCLUDEPATH += $$PWD/../src/Statistical
include($$PWD/../src/Statistical/Statistical.pri)

# 光盘刻录模块
INCLUDEPATH += $$PWD/../src/DiscBurner
include($$PWD/../src/DiscBurner/DiscBurner.pri)

# 公共模块
INCLUDEPATH += $$PWD/../src/utility
include($$PWD/../src/utility/utility.pri)

# 第三方库
INCLUDEPATH += $$PWD/../src/3rdparty
include($$PWD/../src/3rdparty/3rdparty.pri)

# 配置OpenCV 3.4.5
win32{
    INCLUDEPATH += $$PWD/../src/3rdparty/opencv345/include
    DEPENDPATH += $$PWD/../src/3rdparty/opencv345/include

    CONFIG(release, debug|release){ LIBS += -L$$PWD/../src/3rdparty/opencv345/lib/ -lopencv_world345}
    else{LIBS += -L$$PWD/../src/3rdparty/opencv345/lib/ -lopencv_world345d}
}


# 配置Dcmtk 3.6.5
win32{
    INCLUDEPATH += $$PWD/../src/3rdparty/dcmtk/include
    DEPENDPATH += $$PWD/../src/3rdparty/dcmtk/include
    CONFIG(release, debug|release){LIBS += -L$$PWD/../src/3rdparty/dcmtk/lib/ -ldcmtk}
    else{LIBS += -L$$PWD/../src/3rdparty/dcmtk/lib/ -ldcmtkd}
}



HEADERS += \
    check_test.h \
    discburner_test.h \
    report_test.h \
    system_setting_test.h

SOURCES +=  \
    check_test.cpp \
    discburner_test.cpp \
    main.cpp \
    report_test.cpp \
    system_setting_test.cpp
