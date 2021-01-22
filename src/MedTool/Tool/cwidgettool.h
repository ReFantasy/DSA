/************************************************************************
*
* 文件名：cwidgettool.h
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
#ifndef CWIDGETTOOL_H
#define CWIDGETTOOL_H
//#pragma execution_character_set("utf-8")

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
#include <QDateTime>
#include <QTime>
#include <QFileDialog>
#include <vector>
#include <queue>
#include <QStandardItem>
#include <QTreeView>
#include <QMessageBox>


namespace Ui {
class CWidgetTool;
}

class CWidgetTool : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetTool(QWidget *parent = nullptr);
    ~CWidgetTool();
    bool ExportExecl(QTableWidget *tblwResult, QString sFilePath);
    void InitTreeNode(int pRoot);
    void InitTreeView(QTreeView *pTreeView);

private slots:
    void on_m_btnCX_clicked();

    void on_m_tblwKCLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnTJ_clicked();

    void on_m_btnCK_clicked();

    void on_m_tblwCKLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_tblwRKKCLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnRKTJ_clicked();

    void on_m_btnRKFW_clicked();

    void on_m_btnRKCX_clicked();

    void on_m_tblwRKLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnTJXQX_clicked();

    void on_m_btnRKRK_clicked();

    void on_m_tbwCXTJ_tabBarClicked(int index);

    void on_m_btnCXTJCX_clicked();

    void on_m_btnCXTJJT_clicked();

    void on_m_btnCXTJBY_clicked();

    void on_m_btnCXTJSY_clicked();

    void on_m_btnCXTJBCWJ_clicked();   

    void on_m_treevQPQC_clicked(const QModelIndex &index);

    void on_m_lineRKQCTM_editingFinished();

    void on_m_tblwQPKCLB_itemDoubleClicked(QTableWidgetItem *item);

    void on_m_btnQPFW_clicked();

    void on_m_btnQPGX_clicked();

    void on_m_btnQPTJ_clicked();

    void on_m_lineQPQCTM_textChanged(const QString &arg1);

    void on_m_lineQPQCTM_editingFinished();

private:
    Ui::CWidgetTool *ui;
    QString m_sCurSelectedRecordCK;
    QStringList m_lCXLBCK;
    QString m_sCurSelectedRecordRK;
    QStringList m_lCXLBRK;
    //添加时判断添加的器械是否为新品
    int m_nIsNewQX;
    //器材查询统计的选项卡的当前索引号
    int m_nCurBarQCTJ;
    //判断器材配置时是否发生过器材条码已存在的警告
    int m_nQPQCTMFlag;
    QString m_sDateSelectWay;
    struct STreeNode{
        QString sName;
        int nParent;
    };
    // 手术器材
    std::vector<STreeNode>m_vNameTool;
    // 器材
    QStandardItemModel* m_modelQC;
};

#endif // CWIDGETTOOL_H
