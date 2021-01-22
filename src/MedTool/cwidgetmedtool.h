/************************************************************************
*
* 文件名：cwidgetmedtool.h
*
* 文件描述：
*
* 创建人：LYH
*
* 时  间：2020-10-
*
* 版本号 1.0
*
************************************************************************/
#ifndef CWIDGETMEDTOOL_H
#define CWIDGETMEDTOOL_H

#include "cwidgettool.h"
#include "cwidgetmedicine.h"
#include "cwidgetdistributor.h"

#include <QWidget>
#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include "SQLDB.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class CWidgetMedTool;
}

class CWidgetMedTool : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetMedTool(QWidget *parent = nullptr);
    ~CWidgetMedTool();
    void ShowInfoAtTable(QString sSqlSelect, QTableWidget* tblwCurLB);

private slots:
    void on_m_btnRYCX_clicked();

    void on_m_btnRYFW_clicked();

    void on_m_btnRYTJ_clicked();

    void on_m_tblwRYLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnRYGX_clicked();

    void on_m_btnRYSC_clicked();

    void on_m_lineBXLXMC_editingFinished();

    void on_m_btnBXLXTJ_clicked();

    void on_m_btnBXLXFW_clicked();

    void on_m_btnBXLXGX_clicked();

    void on_m_tblwBXLXLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnBXLXSC_clicked();

    void on_m_btnSSLXFW_clicked();

    void on_m_btnSSLXTJ_clicked();

    void on_m_tblwSSLXLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnSSLXGX_clicked();

    void on_m_btnSSLXSC_clicked();

private:
    Ui::CWidgetMedTool *ui;
    // 人员管理列表当前选中ID
    int m_nCurRecordIDRY;
    // 保险类型管理列表当前选中ID
    int m_nCurRecordIDBXLX;
    // 保险类型管理列表当前选中ID
    int m_nCurRecordIDSSLX;
    // 各个子界面
    CWidgetTool *m_wgtTool;
    CWidgetMedicine *m_wgtMedicine;
    CWidgetDistributor *m_wgtDistributor;
};

#endif // CWIDGETMEDTOOL_H
