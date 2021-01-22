void on_m_chkOther_clicked(bool checked);
/************************************************************************
*
* ???????cwidgetpatientstate.h
*
* ?????????
*
* ???????LYH
*
* ?  ??2020-10-
*
* ?��?? 1.0
*
************************************************************************/
#ifndef CWIDGETPATIENTSTATE_H
#define CWIDGETPATIENTSTATE_H


#include <QWidget>
#include <QListWidgetItem>
#include <QTextBrowser>
#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>

#include "isubreport.h"
#include "SQLDB.h"

namespace Ui {
class CWidgetPatientState;
}

class CWidgetPatientState : public QWidget, public ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetPatientState(QWidget *parent = nullptr);
    ~CWidgetPatientState();

private:
    Ui::CWidgetPatientState *ui;

    //单击医学用语列表时，选中的项
    QString m_lstwCYSHYSelected;
    QString m_lstwCYJSYSelected;
    QString m_lstwCYYZSelected;
    //各个控件内容的数据缓存区

    QString m_sSysCaseId;

    QString m_sSZSW;
    QString m_sSHSW;
    QString m_sCZBFZ;
    QStringList m_lCZBFZContent;
    QString m_sIABP;
    QString m_sInOperate;
    QString m_sStateBefore;
    QString m_sAdvice;
    //三个医学用语列表的数据缓存区
    QStringList m_lCYSHY;
    QStringList m_lCYJSY;
    QStringList m_lCYYZ;
private slots:
    void on_m_chkSZSW_clicked(bool checked);

    void on_m_chkSHSW_clicked(bool checked);

    void on_m_chkIABP_clicked(bool checked);

    void on_m_chkCZBFZ_clicked(bool checked);

    void on_m_lstwCYSHY_itemClicked(QListWidgetItem *item);

    void on_m_btnCYSHY_clicked();

    void on_m_lstwCYJSY_itemClicked(QListWidgetItem *item);

    void on_m_btnCYJSY_clicked();

    void on_m_lstwCYYZ_itemClicked(QListWidgetItem *item);

    void on_m_btnCYYZ_clicked();

    void on_m_lstwCYSHY_itemDoubleClicked(QListWidgetItem *item);

    void on_m_lstwCYJSY_itemDoubleClicked(QListWidgetItem *item);

    void on_m_lstwCYYZ_itemDoubleClicked(QListWidgetItem *item);

    void on_m_btnAddCYSHY_clicked();

    void on_m_btnDelCYSHY_clicked();

    void on_m_btnAlterCYSHY_clicked();

    void on_m_btnAddCYJSY_clicked();

    void on_m_btnDelCYJSY_clicked();

    void on_m_btnAlterCYJSY_clicked();

    void on_m_btnAddCYYZ_clicked();

    void on_m_btnDelCYYZ_clicked();

    void on_m_btnAlterCYYZ_clicked();

    void on_groupBox_4_clicked();

    void on_m_btnDelCYSHY_choiced_clicked();

    void on_m_btnDelCYJSY_choiced_clicked();

    void on_m_btnDelCYYZ_choiced_clicked();

    void on_m_chkOther_clicked(bool checked);

public:
    void SetSqDB();
    void UpdateSqDb();
    void UpdateReportTable();
    virtual void SetSysCaseId(const QString pSysCaseId)override;
    virtual void UpdateUIFromDatabase()override;
    virtual void UpdateDatabaseFromUI()override;
    bool CheckDuplicate(QString sItemText, QListWidget *pListWidget);
    void GenerateOutput(QListWidget *pListWidgetChoiced, QTextBrowser *pTextBrowserOutput);
    void GenerateCYYZOutput(QListWidget *pListWidgetChoiced, QTextBrowser *pTextBrowserOutput);
    //void SetSysCaseId(const QString pSysCaseId);

private:

};

#endif // CWIDGETPATIENTSTATE_H
