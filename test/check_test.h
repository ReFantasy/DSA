#ifndef CHECK_TEST_H
#define CHECK_TEST_H

#include <QtTest>

#include "check.h"
#include "ui_check.h"

class CheckTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(){}
    void cleanupTestCase(){}

    void test();

};

#endif // CHECK_TEST_H
