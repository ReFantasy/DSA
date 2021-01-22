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
#ifndef CWIDGETSTATISTICAL_H
#define CWIDGETSTATISTICAL_H
//#pragma execution_character_set("utf-8")

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
#include <QStandardItem>

#include "SQLDB.h"
#include "cwidgetcondition.h"
#include "cwgtanalysis.h"

#include <QWidget>

namespace Ui {
class CWidgetStatistical;
}

class CWidgetStatistical : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetStatistical(QWidget *parent = nullptr);
    ~CWidgetStatistical();

private:
    Ui::CWidgetStatistical *ui;

    // 查询结果
    QStandardItemModel* m_modelPatiInfo;
    // 手术信息
    QStandardItemModel* m_modelSurgInfo;
    QList<QStandardItem*>m_lstSurgInfo;

    // 检索条件widget
    QList<CWidgetCondition*>m_lstCondition;

    CWgtAnalysis*m_wgtAnalysis;

public:

private slots:
    /******** 自定义槽 ********/
    // 删除条件widget
    void DeleteCondition(int pIndex);
    // 滚动条槽
    void UserRangeChanged(int pValueMin,int pValueMax);


    // 条件控制
    void on_m_btnAddCondition_clicked();
    void on_m_btnResetCondition_clicked();
    void on_m_btnQuery_clicked();
    // 统计界面
    void on_m_btnStatistics_clicked();


    // 查询结果表点击事件
    void on_m_tblvQueryAns_clicked(const QModelIndex &index);
    void on_m_tblvQueryAns_doubleClicked(const QModelIndex &index);

    // 本周
    void on_m_radThisWeek_clicked(bool checked);
    // 上周
    void on_m_radLastWeek_clicked(bool checked);
    // 本月
    void on_m_radThisMonth_clicked(bool checked);
    // 上月
    void on_m_radLastMonth_clicked(bool checked);
    // 本年
    void on_m_radThisYear_clicked(bool checked);
    // 上年
    void on_m_radLastYear_clicked(bool checked);

    // 范围精确查找
    void on_m_radFindExact_clicked(bool checked);
    void on_m_radFindRange_clicked(bool checked);

    // 事件条件点击
    void on_m_grpSurgDate_clicked(bool checked);


    void on_m_dtStart_editingFinished();
    void on_m_dtEnd_editingFinished();

    // 高级条件点击
    void on_m_grpQueryCondition_clicked(bool checked);

private:
    // 条件编号
    int m_nIdCondition;
    // 添加标记
    bool m_bIsAddCondition;
    // 时间条件
    QString m_sDateCondition;
protected:

    void InitTreeView(QTreeView*pTreeView);

    QString GetQueryDate();
    int GetWeekDay(QDateTime pDateTime);

    // 清空信息树
    void ClearTreeView(QStandardItemModel* pModel);


    // 获取时间条件
    QString GetDateCondition();
};

#endif // CWIDGETSTATISTICAL_H
