/************************************************************************
*
* 文件名：cwidgetdistributor.h
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
#ifndef CWIDGETDISTRIBUTOR_H
#define CWIDGETDISTRIBUTOR_H

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
class CWidgetDistributor;
}

class CWidgetDistributor : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetDistributor(QWidget *parent = nullptr);
    ~CWidgetDistributor();
    void ShowInfoAtTable(QString sSqlSelect);

private slots:
    void on_m_btnPSSCX_clicked();

    void on_m_btnPSSFW_clicked();

    void on_m_btnPSSTJ_clicked();

    void on_m_tblwPSSLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnPSSGX_clicked();

    void on_m_linePSSMC_editingFinished();

    void on_m_btnPSSSC_clicked();

private:
    Ui::CWidgetDistributor *ui;
    //列表中当前选中项的ID
    int m_nCurRecordID;
};

#endif // CWIDGETDISTRIBUTOR_H
