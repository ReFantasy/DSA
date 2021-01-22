#include <QApplication>
#include "mainwindow.h"
#include "dsaconfig.h"
#include "cdlglogin.h"
#include <QObject>

// 初始化 LOG
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 初始化配置
    DsaConfig::Init();
    DsaConfig::LogConfig();

    LOG(INFO)<<QString("DSA Start ...");

    SQLDB::InitDB();

    CDlgLogin dlgLogin;
    dlgLogin.setModal(1);
    dlgLogin.show();

    if(dlgLogin.exec()==QDialog::Accepted)
    {
        auto user_type =dlgLogin.GetUserType();

        MainWindow main_window;
        main_window.SetUserAuthority(0);
        main_window.setWindowState(Qt::WindowMaximized);
        main_window.show();
        return a.exec();
    }
    else
    {
        LOG(INFO)<<QString("DSA Stop Without Login ...");
        return 0;
    }
}
