/************************************************************************
*
* cwgttargetpathology.h
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
#ifndef TARGETLESION_H
#define TARGETLESION_H

#include <QWidget>
#include <QSqlDatabase>
#include <qcombobox.h>

#include "isubreport.h"

struct SJrqInfo
{
    QString sName,sBBWZ,sBBFW,sBBXT,sBBCJ,sBBWX,sGH,sTIMI,sWQBS,sBBTD,sBBLX,sJDXGWQ;
    QString sSQMCXGZJ,sSQMCBBBCD,sSQMCZXGQ,sSQMCXZCD;
    QString sSQQCA,sSQIVUS,sSQOCT,sSQFFR,sSZBFZ;
};

struct SJrhInfo
{
    QString sBBWZ;
    QString sSHMCXGZJ,sSHMCXZCD,sSHMCZXGQ;
    QString sSHQCA,sSHIVUS,sSHOCT,sSHFFR;
};

//struct SNewPathology
//{
//    SJrqInfo stSqInfo;
//    SJrhInfo stShInfo;
//};

struct SSqQCA
{
    QString sCZXGZJ;
    QString sBBCD;
    QString sXZCD;
    QString sZXGQZJ;
    QString sQNCLXZCD;
    QString sQNCLZXGQ;
};

struct SShQCA
{
    QString sCZXGZJ;
    QString sZJZXGQ;
    QString sQNCLXZCD;
    QString sZJCYXZ;
    QString sBBZXGQZJ;
    QString sZJZCD;
    QString sBBCYXZ;
    QString sQNZXGQZJ;
    QString sZJCDCD;
};

struct SIVUS
{
    QString sEEM_CSA;
    QString sStent_CSA;
    QString sLumen_CSA;
    QString sEEM_Dmax;
    QString sStent_Dmax;
    QString sLumen_Dmax;
    QString sEEM_Dmin;
    QString sStent_Dmin;
    QString sLumen_Dmin;
};

struct SOCT
{
    QString sEEM_CSA;
    QString sStent_CSA;
    QString sLumen_CSA;
    QString sEEM_Dmax;
    QString sStent_Dmax;
    QString sLumen_Dmax;
    QString sEEM_Dmin;
    QString sStent_Dmin;
    QString sLumen_Dmin;
};

struct SJrqPathology
{

    // PCI器械使用
    QString sPCITool;


};

namespace Ui {
class CWgtTargetPathology;
}

class CWgtTargetPathology : public QWidget
{
    Q_OBJECT

public:
    explicit CWgtTargetPathology(QWidget *parent = nullptr);
    ~CWgtTargetPathology();


    // 新病变信息
    void SetNewPathology(SJrqInfo pJrqInfo,SJrhInfo pJrhInfo);

    void SetSqOCT (SOCT pSqOCT);
    void SetSqIVUS(SIVUS pSqIVUS);
    void SetSqQCA (SSqQCA pSqQCA);
    void SetShOCT (SOCT pShOCT);
    void SetShIVUS(SIVUS pShIVUS);
    void SetShQCA (SShQCA pShQCA);


    SJrqInfo GetJrqInfo();
    SJrhInfo GetJrhInfo();
    SOCT GetSqOCT ();
    SIVUS GetSqIVUS();
    SSqQCA GetSqQCA ();
    SOCT GetShOCT ();
    SIVUS GetShIVUS();
    SShQCA GetShQCA ();

private slots:
    void on_m_ckbSQQCA_clicked(bool checked);

    void on_m_ckbSQIVUS_clicked(bool checked);

    void on_m_ckbSQOCT_clicked(bool checked);

    void on_m_ckbSQFFR_clicked(bool checked);

    void on_m_ckbSZBFZ_clicked(bool checked);

    void on_m_ckbSHOCT_clicked(bool checked);

    void on_m_ckbSHQCA_clicked(bool checked);

    void on_m_ckbSHIVUS_clicked(bool checked);

    void on_m_ckbSHFFR_clicked(bool checked);

    void on_m_radBBCJT_clicked(bool checked);

    void on_m_radBBCJF_clicked(bool checked);

    void on_m_radWQBST_clicked(bool checked);

    void on_m_radWQBSF_clicked(bool checked);

private:
    Ui::CWgtTargetPathology *ui;
    QSqlDatabase db;

    /////////////////////////////////////////////
    void InitComboBox(QComboBox *pComboBox, QString pQuery);

    void InitWidgetRadBtn(QWidget *pWidget, QString pQuery);

    void InitWidgetCkbBtn(QWidget *pWidget, QString pQuery);

    QString GetWidgetCkbBtn(QWidget *pWidget);

};

bool UpdateTableForCase(QSqlDatabase &db,const QString &caseid,const QString &tableName,const QString &key,const QString &val);

#endif // TARGETLESION_H
