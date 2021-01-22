QT += core widgets sql printsupport multimedia

CONFIG += C++14


# 编译优化
QMAKE_CXXFLAGS_RELEASE += /O2   # 编译优化

# 使用多字节字符集
#DEFINES  -= UNICODE
#DEFINES  += UMBCS
QMAKE_CXXFLAGS += /utf-8

# 主模块
INCLUDEPATH += $$PWD/Check
include($$PWD/Check/Check.pri)

# 查询模块
INCLUDEPATH += $$PWD/QueryStatistics
include($$PWD/QueryStatistics/QueryStatistics.pri)



# 报告模块
INCLUDEPATH += $$PWD/Report
include($$PWD/Report/Report.pri)


# 系统设置模块
INCLUDEPATH += $$PWD/SysSetting
include($$PWD/SysSetting/SysSetting.pri)

# 系统设置模块2
INCLUDEPATH += $$PWD/MedTool
include($$PWD/MedTool/MedTool.pri)

# 统计模块
INCLUDEPATH += $$PWD/Statistical
include($$PWD/Statistical/Statistical.pri)

# 光盘刻录模块
INCLUDEPATH += $$PWD/DiscBurner
include($$PWD/DiscBurner/DiscBurner.pri)

# 公共模块
INCLUDEPATH += $$PWD/utility
include($$PWD/utility/utility.pri)

# 第三方库
INCLUDEPATH += $$PWD/3rdparty
include($$PWD/3rdparty/3rdparty.pri)

# 配置OpenCV 3.4.5
win32{
    INCLUDEPATH += $$PWD/3rdparty/opencv345/include
    DEPENDPATH += $$PWD/3rdparty/opencv345/include

    CONFIG(release, debug|release){ LIBS += -L$$PWD/3rdparty/opencv345/lib/ -lopencv_world345}
    else{LIBS += -L$$PWD/3rdparty/opencv345/lib/ -lopencv_world345d}
}


# 配置Dcmtk 3.6.5
win32{
    INCLUDEPATH += $$PWD/3rdparty/dcmtk/include
    DEPENDPATH += $$PWD/3rdparty/dcmtk/include
    CONFIG(release, debug|release){LIBS += -L$$PWD/3rdparty/dcmtk/lib/ -ldcmtk}
    else{LIBS += -L$$PWD/3rdparty/dcmtk/lib/ -ldcmtkd}
}

# 配置

SOURCES += \
    cdlglogin.cpp \
    main.cpp \
    mainwindow.cpp

FORMS += \
    cdlglogin.ui \
    mainwindow.ui

HEADERS += \
    cdlglogin.h \
    mainwindow.h

RC_ICONS = DSA.ico
