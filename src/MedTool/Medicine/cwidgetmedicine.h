/************************************************************************
*
* 文件名：cwidgetmedicine.h
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
#ifndef CWIDGETMEDICINE_H
#define CWIDGETMEDICINE_H

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
#include <vector>
#include <queue>
#include <QStandardItem>
#include <QTreeView>
#include <QMessageBox>

namespace Ui {
class CWidgetMedicine;
}

class CWidgetMedicine : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetMedicine(QWidget *parent = nullptr);
    ~CWidgetMedicine();
    void InitTreeNode(int pRoot);
    void InitTreeView(QTreeView *pTreeView);
    void ShowInfoAtTable(QString sSqlSelect);
private slots:
    void on_m_treevYPYP_clicked(const QModelIndex &index);

    void on_m_btnYPFW_clicked();

    void on_m_btnYPTJ_clicked();

    void on_m_lineYPRK_clicked();

    void on_m_tblwYPKCLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_lineYPYPMCRK_editingFinished();

private:
    Ui::CWidgetMedicine *ui;
    struct STreeNode{
        QString sName;
        int nParent;
    };
    // 药品
    std::vector<STreeNode>m_vNameMedicine;
    // 器材
    QStandardItemModel* m_modelYP;
};

#endif // CWIDGETMEDICINE_H
