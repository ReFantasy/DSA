#include <QApplication>
#include <QTest>
#include "check_test.h"
#include "discburner_test.h"
#include "report_test.h"
#include "system_setting_test.h"
#include "easyloggingpp/easylogging++.h"

INITIALIZE_EASYLOGGINGPP
int main(int argc, char*argv[])
{
    QApplication app(argc, argv);

    // 创建测试对象
    CheckTest *check_test = new CheckTest;
    DiscBurnerTest *discburner_test = new DiscBurnerTest;
    ReportTest *report_test = new ReportTest;
    SysSettingTest *sys_setting_test = new SysSettingTest;




    // 逐一执行ce测试
    int test_re_value = 0;
    if( (test_re_value = QTest::qExec(check_test)) != 0 )
    {
        return test_re_value;
    }
    else if((test_re_value = QTest::qExec(discburner_test)) != 0)
    {
        return test_re_value;
    }
    else if((test_re_value = QTest::qExec(report_test)) != 0)
    {
        return test_re_value;
    }
    else if((test_re_value = QTest::qExec(sys_setting_test)) != 0)
    {
        return test_re_value;
    }








    delete check_test;
    delete discburner_test;
    delete report_test;

    return 0;
}
