/************************************************************************
*
* 文件名：cwidgetpci.h
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
#ifndef CWIDGETPCI_H
#define CWIDGETPCI_H
//#pragma execution_character_set("utf-8")


#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#include <qobject.h>
#include <QWidget>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QDateTime>
#include <qstring.h>

#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <qsqlquerymodel.h>
#include <control.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <QListWidgetItem>
#include <qlist.h>
#include <qtreeview.h>
#include <QStringList>
#include <qtableview.h>
#include <qstringlist.h>
#include <QScrollBar>

#include "SQLDB.h"
#include "isubreport.h"

struct STreeNode{
    QString sName;
    int nParent;
};

struct SBBInfo{
    QString sBBId;
    QString sBBName;
    QString sBBTD;
    QString sSQXZ;
    QString sSQTimi;
    QString sDSTGBB;
    QString sBBCYXZ;
    QString sSHTimi;
    QString sSZBFZ;
};

struct SToolInfo{
    QString sName;
    QStringList sType;
};

namespace Ui {
class CWidgetPCI;
}

class CWidgetPCI : public QWidget, public ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetPCI(QWidget *parent = nullptr);
    ~CWidgetPCI();

private:
    Ui::CWidgetPCI *ui;

    // 药物
    QStandardItemModel* m_modelYW;
    // 手术记录
    QStandardItemModel* m_modelSSJL;
    // 快捷用语
    QStandardItemModel* m_modelKJYY;
    // 器材
    QStandardItemModel* m_modelQC;

public:
    virtual void SetSysCaseId(const QString)override;
    virtual void UpdateUIFromDatabase()override;
    virtual void UpdateDatabaseFromUI()override;
protected:
    void test();
    // 更新页面信息
    void UpdateShow();
    // 更新数据库
    void UpdateSqDB();
    // 初始化病变信息
    void InitBBInfo(QString pName);
    // 判断子序列
    int IsSubsequence(QString pA,QString pB);
    // 删除字符串头尾空格
    QString DelHeadRearSpace(QString pStr);
    // 初始化groupbox
    void InitGroupBox(QGroupBox*pGroupBox,QString pAns);
    // 初始化Combobox
    void InitComboBox(QComboBox*pComboBox,QString pAns);
    // 初始化干预血管
    void InitComboBoxGYXG(QComboBox *pComboBox, QStringList pList);
    // 初始化组中的并发症
    void InitGroupCkbBtn(QWidget*pWidget,QString pAns);
    // 更新tableView
    void InitItemModel(QStandardItemModel*pItemModel,QList<QList<QString>>plstStr);
    // 更新listWidget
    void InitListWidget(QListWidget*pListWidget,QList<QString>plstStr);
    // 构造树
    void InitTreeNode(int pRoot);
    // 构造TreeView
    void InitTreeView(QTreeView*pTreeView);
    // 构造lineEdit
    void InitLineEdit(QLineEdit*pLineEdit,QStringList pAns,int pId);
    // 获取组中按下的radio的text
    QString GetTextIsPressedGroupRadBtn(QGroupBox*pGroupBox);
    // 获取组中按下的Check的text
    QString GetTextIsPressedGroupCkbBtn(QWidget*pWidget);

    // 查找根结点
    QStandardItem* FindToolRoot(QString pType);
    QStandardItem* FindPriorNode(QStandardItem *pCurrNode,QString pType);

    void SetSqDB();
    // 病变
    void SetSqDbBB();
    void UpdateBBShow();

    void UpdateReportTable();

private slots:
    void on_m_tblvYW_clicked(const QModelIndex &index);
    void on_m_tblvYW_doubleClicked(const QModelIndex &index);
    // 给药
    void on_m_btnQDGY_clicked();

    void on_m_treevQC_doubleClicked(const QModelIndex &index);

    void on_m_lstwSZZT_itemDoubleClicked(QListWidgetItem *item);
    // 术中状态增删改
    void on_m_btnSZZTZJ_clicked();
    void on_m_btnSZZTSC_clicked();
    void on_m_btnSZZTXG_clicked();

    void on_m_cmbGYXGMC_activated(int index);

    void on_m_radSZBFZW_clicked(bool checked);
    void on_m_radSZBFZY_clicked(bool checked);

    // 手术记录的删除修改
    void on_m_btnSSJLSC_clicked();
    void on_m_btnSSJLXG_clicked();

    // 干预
    void on_m_btnGY_clicked();


    void on_m_tblvKJYY_doubleClicked(const QModelIndex &index);
    // 快捷用语增删改
    void on_m_btnKJYYZJ_clicked();
    void on_m_btnKJYYSC_clicked();
    void on_m_btnKJYYXG_clicked();

    // 提交至数据库
    void on_m_btnUpdateDB_clicked();


    // 手术操作
    void on_m_btnSuccess_clicked();
    void on_m_btnFailure_clicked();

    // 保存病变
    void on_m_btnSave_clicked();



private:
    QString m_sSysCaseId;

    // 手术器材
    vector<STreeNode>m_vNameTool;

    // 病人体征
    QString m_sHR;
    QString m_sTEMP;
    QStringList m_slstNIBP;
    QString m_sSPO2;
    QStringList m_slstIBP1;
    QStringList m_slstIBP2;
    QStringList m_slstIBP3;
    QStringList m_slstIBP4;


    // 药物
    QList<QList<QString>>m_lstYW;
    // 术中状态
    QList<QString>m_lstSZZT;
    // 快捷用语
    QList<QList<QString>>m_lstKJYY;
    // 手术记录
    QList<QList<QString>>m_lstSSJL;


    // 靶血管
    QStringList m_slstGYXG;
    // 当前所有病变
    QList<SBBInfo>m_lstBBInfo;

    // 库存的器材
    QList<SToolInfo>m_lstToolInfo;
};

#endif // CWIDGETPCI_H
