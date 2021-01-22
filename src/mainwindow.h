#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "check.h"
#include "cwidgetreport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief 创建并弹出新的报告界面
     */
    void ShowReportWidget(QString);

    Check *GetCheckModule(){return _check_widget;}

    void SetUserAuthority(int);
private slots:
    void ShowMainWindow();
private:
    Ui::MainWindow *ui;

    // 检索模块
    Check *_check_widget = nullptr;

    // 报告模块
    CWidgetReport *_report_widget = nullptr;

};

#endif // MAINWINDOW_H
