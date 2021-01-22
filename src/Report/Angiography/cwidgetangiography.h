/************************************************************************
*
* 文件名：cwidgetangiography.h
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
#ifndef CWIDGETANGIOGRAPHY_H
#define CWIDGETANGIOGRAPHY_H
//#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QCheckBox>
#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <qlistwidget.h>
#include "SQLDB.h"
#include "isubreport.h"
#include<iostream>
using namespace std;

namespace Ui {
class CWidgetAngiography;
}

class CWidgetAngiography : public QWidget, public  ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetAngiography(QWidget *parent = nullptr);
    ~CWidgetAngiography();

private:
    Ui::CWidgetAngiography *ui;

    QString m_sDiagnoseRes;

    QString m_sAngiographyRes;

    // lyh
    QString GetListWidgetText(QListWidget*pListWidget);
public:
    void SetSqDB();
    void UpdateSqDB();
    void UpdateReportTable();
    virtual void SetSysCaseId(const QString pSysCaseId)override;
    virtual void UpdateDatabaseFromUI() override;
    virtual void UpdateUIFromDatabase() override;
    //诊断结果更新函数
    void UpdateZDJG();
private slots:

    void on_m_chkCABG_clicked(bool checked);

    void on_m_chkCZXH_clicked(bool checked);

    void on_m_chkGHY_clicked(bool checked);

    void on_m_chkZXSZY_clicked(bool checked);

    void on_m_chkJWPCI_clicked(bool checked);

    // 用户自定义槽
    void UserStateChangedZYWZ(int state);
    void UserTextChangedZYWZ(const QString &text);
    void UserStateChangedGYXG(int state);
    void UserTextChangedGYXG(const QString &text);



    void on_m_btnCABGChoice_clicked();

    void on_RB_RightGuanAbnormal_clicked();

    void on_RB_RightGuanNormal_clicked();

    void on_RB_LeftZhuGanAbnormal_clicked();

    void on_RB_LeftZhuGanNormal_clicked();

    void on_m_lstwCABGResult_itemDoubleClicked(QListWidgetItem *item);

    void on_m_btnCZXHChoice_clicked();

    void on_m_btnGHXChoice_clicked();

    void on_RB_ShapeNormal_clicked();

    void on_RB_ShapeAbnormal_clicked();

    void on_m_ckbQC_stateChanged(int arg1);

    void on_m_radQC_ZC_clicked();

    void on_m_radQC_JD_clicked();

    void on_m_radQC_WHD_clicked();

    void on_m_radQC_FCYD_clicked();

    void on_m_radQC_SBL_clicked();

    void on_m_radQC_BQD_clicked();

    void on_m_ckbQJD_stateChanged(int arg1);

    void on_m_radQJD_ZC_clicked();

    void on_m_radQJD_JD_clicked();

    void on_m_radQJD_WHD_clicked();

    void on_m_radQJD_FCYD_clicked();

    void on_m_radQJD_SBL_clicked();

    void on_m_radQJD_BQD_clicked();

    void on_m_ckbXJ_stateChanged(int arg1);

    void on_m_radXJ_ZC_clicked();

    void on_m_radXJ_JD_clicked();

    void on_m_radXJ_WHD_clicked();

    void on_m_radXJ_FCYD_clicked();

    void on_m_radXJ_SBL_clicked();

    void on_m_radXJ_BQD_clicked();

    void on_m_ckbGM_stateChanged(int arg1);

    void on_m_radGM_ZC_clicked();

    void on_m_radGM_JD_clicked();

    void on_m_radGM_WHD_clicked();

    void on_m_radGM_FCYD_clicked();

    void on_m_radGM_SBL_clicked();

    void on_m_radGM_BQD_clicked();

    void on_m_ckbHJD_stateChanged(int arg1);

    void on_m_radHJD_ZC_clicked();

    void on_m_radHJD_JD_clicked();

    void on_m_radHJD_WHD_clicked();

    void on_m_radHJD_FCYD_clicked();

    void on_m_radHJD_SBL_clicked();

    void on_m_radHJD_BQD_clicked();

    void on_m_ckbJG_stateChanged(int arg1);

    void on_m_radJG_ZC_clicked();

    void on_m_radJG_JD_clicked();

    void on_m_radJG_WHD_clicked();

    void on_m_radJG_FCYD_clicked();

    void on_m_radJG_SBL_clicked();

    void on_m_radJG_BQD_clicked();

    void on_m_ckbHC_stateChanged(int arg1);

    void on_m_radHC_ZC_clicked();

    void on_m_radHC_JD_clicked();

    void on_m_radHC_WHD_clicked();

    void on_m_radHC_FCYD_clicked();

    void on_m_radHC_SBL_clicked();

    void on_m_radHC_BQD_clicked();

    void on_m_lineYGKK_textChanged(const QString &arg1);

    void on_m_radYYS_clicked();

    void on_m_radZYS_clicked();

    void on_m_radJH_clicked();

    void on_m_lineZZGKK_textChanged(const QString &arg1);

    void on_m_radXQDXNormal_toggled(bool checked);

    void on_m_cmbXYWZ_currentTextChanged(const QString &arg1);

    void on_m_lineSZMQRL_textChanged(const QString &arg1);

    void on_m_lineSSMQRL_textChanged(const QString &arg1);

    void on_m_cmbJYBCL_currentTextChanged(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_m_lstwCZXHResult_itemDoubleClicked(QListWidgetItem *item);

    void on_m_lstwGHXResult_itemDoubleClicked(QListWidgetItem *item);

    void on_m_lstwCABGRight_itemDoubleClicked(QListWidgetItem *item);

    void on_m_lstwCZXHRight_itemDoubleClicked(QListWidgetItem *item);



    void on_m_btnDeleteCABG_clicked();

    void on_m_btnDeleteCZXH_clicked();

    void on_m_btnDeleteGHY_clicked();


    void on_m_ckbZYMJL_DZBB_clicked(bool checked);







    void on_m_radGZ_clicked();

    void on_m_radDPZ_clicked();





    void on_m_ckbZYMJL_SZBB_clicked(bool checked);

    void on_m_ckbZYMJL_LeftDouble_clicked(bool checked);

    void on_m_ckbZYMJL_LeftThree_clicked(bool checked);

    void on_m_radGZ_toggled(bool checked);

private:
    QString m_sSysCaseID;

    QString m_sGMGX;
    QString m_sZZGKK;
    QString m_sYGKK;
    QString m_sCABG;
    QString m_sCZXH;
    QString m_sGHY;
    QString m_sJWPCI;
    QString m_sZXSZY;

    // 显影位置
    vector <QString> m_vPosXY;
    QString m_sPosXY;
    QListWidget *m_lstwPosXY;
//lyh
    //QList<QCheckBox*>m_lstchkPosXY;

    // 干预血管
    vector <QString> m_vGYXG;
    QString m_sGYXG;
    QListWidget *m_lstwGYXG;

    void UpdateGYXG();
    QString m_sZYJL;
    void UpdateZYJL(int arg);


    //数据库BB_BBQT表的字段
    QString m_sGMType;
    QString m_sZzgkk;
    QString m_sYgkk;
    QString m_sJwpciwz;

    void UpdateBB_BBQT();

    //数据库BB_CABG的字段
    QStringList m_sCABGstartblood;
    QStringList m_sCABGendblood;

    //是数据库BB_CZXH的字段

    QStringList m_sCZXHTIMI;
    QStringList m_sCZXHstartblood;
    QStringList m_sCZXHendblood;


    //数据库BB_GHY字段
    QStringList m_sGHYghType;
    QStringList m_sGHYghblood;

    //数据库BB_ZXS字段
    QString m_sZXSFigure;
    QString m_sZXSHeart_Size;
    QString m_sZXSszq;
    QString m_sZXSssq;
    QString m_sZXSsxfs;
    QString m_sZXSQJD;
    QString m_sZXSQC;
    QString m_sZXSXJ;
    QString m_sZXSGM;
    QString m_sZXSHJD;
    QString m_sZXSJG;
    QString m_sZXSHC;
    void UpdateBB_ZXS();

    //存储造影结论
    QList<QCheckBox*> m_ListZYJL;


    //数据库JLYZ字段
    QString m_sJLYZzyjl;
    QString m_sJLYZjyb;
    QString m_sJLYZgyxg;

    //拉取数据后的初始化函数
    void sqlBB_BBQTInit();
    void sqlBB_CABGInit();
    void sqlBB_CZXHInit();
    void sqlBB_GHYInit();
    void sqlBB_ZXSInit();
    void sqlBB_JLYZInit();

    //数据库函数 获取数据
    void getSQLBB_BBQT();
    void getSQLBB_CABG();
    void getSQLBB_CZXH();
    void getSQLBB_GHY();
    void getSQLBB_ZXS();
    void getSQLBB_JLYZ();


    //数据库函数 更新函数
    void updateSQLBB_BBQT();
    void updateSQLBB_CABG();
    void updateSQLBB_CZXH();
    void updateSQLBB_GHY();
    void updateSQLBB_ZXS();
    void updateSQLBB_JLYZ();


    //左心室造影初始化函数
    void ZXSInit();

};

#endif // CWIDGETANGIOGRAPHY_H
