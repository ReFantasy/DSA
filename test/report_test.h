#ifndef REPORT_TEST_H
#define REPORT_TEST_H

#include <QtTest>

#include "cwidgetreport.h"
#include "ui_cwidgetreport.h"

class ReportTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(){}
    void cleanupTestCase(){}

    void test();

};

#endif // REPORT_TEST_H
