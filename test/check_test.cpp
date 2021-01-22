#include "check_test.h"

void CheckTest::test()
{
    Check *pCheck = new Check;
    QTest::mouseClick(pCheck->ui->begin_study_date_on, Qt::LeftButton);
    QTest::mouseClick(pCheck->ui->checkButton, Qt::LeftButton);
    delete pCheck;
}
