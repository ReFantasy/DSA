#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <SQLDB.h>
#include <QDialog>
#include <share.h>
#include "acquiredcmfile.h"
#include "cdlglogin.h"

#define ELPP_QT_LOGGING
#include "easyloggingpp/easylogging++.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("导管室影像信息系统");

    // 状态栏
    this->statusBar()->show();
    this->statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    auto rights = QString("Copyright © 2020-%1")
            .arg(QDate::currentDate().year());
    this->statusBar()->showMessage(rights);

    //QLabel* permanent = new QLabel(this);
    //permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    //permanent->setText("CUST");
    //permanent->setText(tr("<a href=\"http://www.danhongtec.com\">状态栏信息</a>"));
    //permanent->setOpenExternalLinks(true);//设置可以打开网站链接
    //this->statusBar()->addPermanentWidget(permanent);//显示永久信息

    // 将检索模块设置为中心部件
    _check_widget = new Check(this);
    setCentralWidget(_check_widget);


    // 子模块向父模块发送
    connect(_check_widget, &Check::ShowReportUI, this, &MainWindow::ShowReportWidget);

}

MainWindow::~MainWindow()
{
    delete ui;

    if(_report_widget)
    {
        delete _report_widget;
    }

    LOG(INFO)<<QString("DSA Stop ...");
}

void MainWindow::ShowReportWidget(QString patient_id)
{
    LOG(INFO)<<"Open Report module";

    // 创建一个新的报告模块并将病人ID传递进去
    // 报告模块为模态部件，不能同时编辑两个不同病例的报告，保证数据一致性
    if(_report_widget == nullptr)
    {
        _report_widget = new CWidgetReport;
    }
    else
    {
        delete _report_widget;
        _report_widget = new CWidgetReport;
    }

    // 传递病人ID
    _report_widget->SetIdPatient(patient_id);
    // 传递视频
    QStringList filenames;
    auto video = AcquireDcmFile(patient_id.toStdString(), filenames);//_check_widget->SelectedPatientID()
    _report_widget->AddVideo(video);

    _report_widget->setAttribute(Qt::WA_ShowModal, true);  // 模态窗口，阻塞父窗口
    _report_widget->setWindowState(Qt::WindowMaximized);
    _report_widget->show();

    this->hide();

    connect(_report_widget,SIGNAL(ExitReportWindow()),this,SLOT(ShowMainWindow()));
}

/**
 * @brief MainWindow::SetUserAuthority
 * @param auth
 */
void MainWindow::SetUserAuthority(int auth)
{
    _check_widget->SetUserAuthority(auth);
}

/**
 * @brief MainWindow::ShowMainWindow
 */
void MainWindow::ShowMainWindow()
{
    this->setAttribute(Qt::WA_ShowModal, true);
    this->show();
}

