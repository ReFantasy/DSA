/************************************************************************
*
* cwidgetadditionalinfo.h
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
#ifndef CWIDGETADDITIONALINFO_H
#define CWIDGETADDITIONALINFO_H
//#pragma execution_character_set("utf-8")
#include <QWidget>

#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <qstring.h>

#include <iostream>
#include <vector>
using namespace std;

#include "SQLDB.h"
#include "isubreport.h"

#include <cwgttargetpathology.h>

#include "cwgttargetvessel.h"
#include "cwgttooluse.h"

struct SJWBS
{
    QString sGXY;
    QString sWZXGJB;
    QString sTXZL;
    QString sJQXYS;
    QString sGXZ;
    QString sMXFB;
    QString sXJGS;
    QString sGXBJZS;
    QString sSGNSJ;
    QString sTNB;
    QString sXLSJ;
    QString sNXGJB;
    QString sBMSSS;
    QString sBMSSRQ;
    QString sPCIS;
    QString sPCIRQ;
    QString sCABGS;
    QString sCABGRQ;
    QString sWriter;
    QString sWriteDate;
};




namespace Ui {
class CWidgetAdditionalInfo;
}

class CWidgetAdditionalInfo : public QWidget, ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetAdditionalInfo(QWidget *parent = nullptr);
    ~CWidgetAdditionalInfo();

private:
    Ui::CWidgetAdditionalInfo *ui;
    CWgtTargetPathology *m_wTargetPathology;
    QString m_CaseID;
    QSqlQuery query;
    QSqlDatabase db;
    void SetSqDB();
    void UpdateSqDB();


    void UpdateShow();

    // 既往病史
    SJWBS m_JWBS;
    // 靶血管
    QList<STargetVessel>m_lstTargetVessel;
    // 器械使用
    QList<SToolUse>m_lstToolUse;


    SJWBS GetJWBS();

    //
    QList<CWgtTargetVessel*>m_lstVessel;
    //
    QList<CWgtTargetPathology*>m_lstPathology;

    // 新建病变
    QList<SJrqInfo>m_lstJrqInfo;
    QList<SJrhInfo>m_lstJrhInfo;
    // 术前
    vector<SOCT>m_vSqOCT;
    vector<SIVUS>m_vSqIVUS;
    vector<SSqQCA>m_vSqQCA;
    // 术后
    vector<SOCT>m_vShOCT;
    vector<SIVUS>m_vShIVUS;
    vector<SShQCA>m_vShQCA;


    // 唯一标识符
    QString m_sSysCaseID;

    // datetime格式
    const QString csDateTimeStyle="yyyy-MM-dd hh:mm:ss.zzz";

    int m_nNumberBBB;
    /////////////////////////////////////////////////////////////////////


    // 初始化groupbox
    void InitWidgetRadBtn(QWidget*pWidget,QString pQuery);
     QString GetWidgetRadBtn(QWidget*pWidget);

    void UpdateDBJrqInfo();
    void UpdateDBJrhInfo();
    void UpdateDBSqOCT ();
    void UpdateDBSqIVUS();
    void UpdateDBSqQCA ();
    void UpdateDBShOCT ();
    void UpdateDBShIVUS();
    void UpdateDBShQCA ();



public:
    void SetSysCaseId(const QString) override;
    void UpdateUIFromDatabase() override;
    void UpdateDatabaseFromUI() override;

private slots:
    void on_m_radBMSST_clicked(bool checked);
    void on_m_radBMSSF_clicked(bool checked);
    void on_m_radPCIT_clicked(bool checked);
    void on_m_radPCIF_clicked(bool checked);
    void on_m_radCABGT_clicked(bool checked);
    void on_m_radCABGF_clicked(bool checked);

    // 新建病变
    void on_m_btnAddBBB_clicked();
    void on_m_btnDelBBB_clicked();
};

#endif // CWIDGETADDITIONALINFO_H
