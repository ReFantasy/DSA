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
#ifndef CWIDGETCONDITION_H
#define CWIDGETCONDITION_H
//#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QComboBox>
#include <qdebug.h>
#include <QDate>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <QPushButton>
#include <qsql.h>
#include <qsqlquery.h>
#include <SQLDB.h>


namespace Ui {
class CWidgetCondition;
}

class CWidgetCondition : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetCondition(QWidget *parent = nullptr);
    ~CWidgetCondition();
signals:
    void EmitIndex(int pIndex);
private slots:
    void ClickedEmit();
    // 联合条件
    void on_m_cmbAndOr_currentIndexChanged(int index);

    void on_m_cmbCategory_currentIndexChanged(int index);

    void on_m_cmbCategoryValue_activated(int index);

    void on_m_lineValueEdit_editingFinished();

    void on_m_cmbValueSelect_activated(int index);

    void on_m_dtValueStart_userDateChanged(const QDate &date);

    void on_m_dtValueEnd_userDateChanged(const QDate &date);

    void on_m_lineValueRangeL_editingFinished();

    void on_m_lineValueRangeR_editingFinished();

    void on_m_radConditionT_clicked(bool checked);

    void on_m_radConditionF_clicked(bool checked);

    void on_m_cmbJWBS_activated(int index);

    void on_m_cmbStyle_activated(int index);

    void on_m_cmbType_activated(int index);

    void on_m_cmbName_activated(int index);


    void on_m_cmbConditionDGXS_activated(int index);

    void on_m_cmbConditionDGXH_activated(int index);

    void on_m_cmbConditionDGCC_activated(int index);

    void on_m_cmbValueSelectEnd_activated(int index);

    void on_m_cmbValueSelectStart_activated(int index);



    // czxh
    void on_m_cmbCZXHStart_activated(int index);
    void on_m_cmbCZXHEnd_activated(int index);
    void on_m_cmbCZXHTimi_activated(int index);


    void on_m_cmbValueSelectRoot_activated(int index);

    void on_m_radBBRight_clicked(bool checked);

    void on_m_radBBLeft_clicked(bool checked);

private:
    Ui::CWidgetCondition *ui;
private:
    int m_nIndex;

    int m_nCurrType;

    // 通用子项
    QStringList m_slstIsTrue;
    QStringList m_slstIsNormal;
    QStringList m_slstIsHave;
    QStringList m_slstTimi;


    // 各个类别中的子项
    QStringList m_slstPatiInfo;
    QStringList m_slstSurgInfo;
    QStringList m_slstAngiography;
    QStringList m_slstPathology;
    QStringList m_slstMRIType;
    QStringList m_slstPCI;
    QStringList m_slstPatiState;
    QStringList m_slstPCIInfo;
    QStringList m_slstPathologyTrait;

    // 基本资料中的子项
    QStringList m_slstRoom;
    QStringList m_slstSex;
    QStringList m_slstInsur;
    QStringList m_slstInstructor;
    QStringList m_slstSurName;
    QStringList m_slstAssisName;
    QStringList m_slstNurse;
    QStringList m_slstTechnician;
    QStringList m_slstSurgType;
    QStringList m_slstShadow;
    QStringList m_slstClinical;
    QStringList m_slstPatiType;


    // 手术信息中的子项
    QStringList m_slstMzj;
    QStringList m_slstZybw;
    QStringList m_slstCglj;
    QStringList m_slstQgxh;
    QStringList m_slstMed;
    QStringList m_slstDGCC;
    QStringList m_slstDGXS;
    QStringList m_slstDGXH1;
    QStringList m_slstDGXH2;

    // 造影所见中的子项
    QStringList m_slstGMGX;
    QStringList m_slstCABGStart;
    QStringList m_slstCABGEnd;
    QStringList m_slstCZXHStart;
    QStringList m_slstCZXHEnd;
    QStringList m_slstGHYXt;
    QStringList m_slstGHYWz;
    QStringList m_slstZXSZY;
    QStringList m_slstZXSZYTrait;
    QStringList m_slstZYJL;
    QStringList m_slstJYBCl;
    QStringList m_slstGYXG;

    // 病变性质中的子项
    QStringList m_slstBBXG;
    QStringList m_slstBBXZ;
    QStringList m_slstBBLX;
    QStringList m_slstBBXT;
    QStringList m_slstBBGH;
    QStringList m_slstBBCTO;
    QStringList m_slstFCBB;
    QStringList m_slstZZGBB;

    // PCI信息中的子项
    QStringList m_slstDGName;
    QStringList m_slstDSName;
    QStringList m_slstQNName;
    QStringList m_slstZJName;
    QStringList m_slstQTName;
    QStringList m_slstStyle;
    QStringList m_slstType;

    // PCI信息中的子项
    QStringList m_slstBBXGWZ;
    QStringList m_slstJWBS;


    // 表格
    QString m_sSqlTable;
    // 条件
    QString m_sSqlConditon;
    // 条件2
    QString m_sSqlConditon1;
    // 条件2
    QString m_sSqlConditon2;
    // sql语句
    QString m_sSqlQuery;
    // 与或非条件
    QString m_sSqlAndOr;
    // 连接条件
    QString m_sSqlJoin;
protected:
    void InitCombox(QComboBox* pCmb,QStringList pList);
    void HideAllCondition();

    void PatiInfoActivated(int pIndex);
    void SurgInfoActivated(int pIndex);
    void AngiographyActivated(int pIndex);
    void PathologyActivated(int pIndex);
    void MRIActivated(int pIndex);
    void PCIActivated(int pIndex);
    void PatiStateActivated(int pIndex);
    void PCIInfoActivated(int pIndex);
    void PathologyTraitActivated(int pIndex);

    int DataToInt(QDate pData);
    void GetTypeFromDB();


public:
    enum ECategory{
        PatiInfo=0,SurgInfo,Angiography,Pathology,MRI,
        PCI,PatiState,PCIInfo,PathologyTrait};

    enum EPatiInfo{
        CaseId=0,Room,InsurType,PatiSex,PatiAge,PatiDOB,PatiHeig,
        PatiWeig,InstructorName,SurName,Assis,Nursury,Techno,
        SurType,ShadowType,ShadowNum,XTime,PatiStatus};

    enum ESurgInfo{MZJ=0,MZJL,ZYBW,CGLJ,QGXH,YYJL,ZYDG};

    // 造影所见
    enum EAngiography{GMGX=0,ZZGKK,YGKK,CABG,CZXH,GHY,JWPCI,ZXSZY,ZYJL,JYBJY,GYXG};
    enum EZXSAngiography{WX=0,XQ,SX,QJD,QC,XJ,GM,HJD,JG,HC};

    // 病变性质
    enum EPathology{BBWZ=0,XZ,FW,LX,XZL,XT,GH,XS,TIMI,CTO,FCBB,ZZGBB};
    // 影像学检查
    enum EMRI{IVUS=0,OCT,FFR};

    enum EPCI{DG=0,DS,QN,ZJ,QT};

    enum EPatiState{SSQK=0,JSY,SHYZ};

    enum EPCIInfo{BBXGWZ=0,JWBS};

    enum EPathologyTrait{YBBB=0,FXBB,GHBB,XSBB,CBB,CTOBB,DWCLBB};

    enum EJwbs{GXZ=0,GXY,TNB,JQXYS,GXBJZS,XJGS,XLSJ,SGNSJ,NXGJB,QZXGJB,MXFB,TXZL,BMSSS,PCIS,CABGS};


    // 隐藏第一条件的删除按钮
    void HideDelete();
    void SetIndex(int pIndex);
    // 隐藏弹簧
    void HideVerticalSpacer();

    // 获取当前条件值
    void GetSqlQuery(QString &pTable,QString &pSql,QString &pAndOr,QString &pJoin);
};

#endif // CWIDGETCONDITION_H
