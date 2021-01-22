#ifndef DiscBurnerTest_H
#define DiscBurnerTest_H

#include <QtTest>

#include "cwidgetdiscburner.h"
#include "ui_cwidgetdiscburner.h"

class DiscBurnerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(){}
    void cleanupTestCase(){}

    void test();

};

#endif // DiscBurnerTest_H
