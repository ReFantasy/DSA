#ifndef SYS_SETTING_TEST_H
#define SYS_SETTING_TEST_H

#include <QtTest>

#include "cwidgetsetting.h"
#include "ui_cwidgetsetting.h"

class SysSettingTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(){}
    void cleanupTestCase(){}

    void test();

};

#endif // SYS_SETTING_TEST_H
