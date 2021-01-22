#include "cwidgetcondition.h"
#include "ui_cwidgetcondition.h"

CWidgetCondition::CWidgetCondition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetCondition)
{
    ui->setupUi(this);

    /******** 初始化当前属性 ********/
    ui->m_dtValueStart->setDate(QDate::currentDate());
    ui->m_dtValueEnd->setDate(QDate::currentDate());

    /******** 初始化当前属性 ********/
    this->m_nIndex=-1;
    this->m_nCurrType=-1;
    this->m_sSqlTable="";
    this->m_sSqlConditon="";
    this->m_sSqlAndOr="";
    this->m_sSqlJoin="SysCaseID";


    /******** 初始化通用子项 ********/
    QString sIsTrue="是/否";
    m_slstIsTrue=sIsTrue.split('/');
    QString sIsNormal="正常/异常";
    m_slstIsNormal=sIsNormal.split('/');
    QString sIsHave="有/无";
    m_slstIsHave=sIsHave.split('/');
    QString sTimi="0级/Ⅰ级/Ⅱ级/Ⅲ级";
    m_slstTimi=sTimi.split('/');


    /******** 初始化一级类别 ********/
    QString sCategory={"基本资料/手术信息/造影所见/病变/影像学检查/介入治疗/术中及术后状态/PCI直报表信息/病变特点"};
    QStringList slstCategory=sCategory.split('/');
    for(int i=0;i<slstCategory.size();i++)
    {
        ui->m_cmbCategory->addItem(slstCategory[i]);
    }
    ui->m_cmbCategory->setCurrentIndex(0);


    /******** 初始化起始页面 ********/
    // 初始时隐藏所有条件选择项
    this->HideAllCondition();


    /******** 初始化交并条件 ********/
    QString sAndOr={"与/或"};
    QStringList slstAndOr=sAndOr.simplified().split('/');
    for(int i=0;i<slstAndOr.size();i++)
    {
        ui->m_cmbAndOr->addItem(slstAndOr[i]);
    }
    ui->m_cmbAndOr->setCurrentIndex(0);


    /******** 初始化二级类别 ********/
    /******** 基本资料 ********/
    QString sPatiInfo="住院号/导管室/保险类型/性别/年龄/出生日期/身高/体重/指导者/术者/助手/护士/技师/手术类型/造影剂/造影剂剂量/X光照射时间/病人类型";
    m_slstPatiInfo=sPatiInfo.split('/');
    InitCombox( ui->m_cmbCategoryValue,m_slstPatiInfo);
    ui->m_cmbCategoryValue->setCurrentIndex(-1);

    /******** 手术信息 ********/
    QString sSurgInfo="麻醉剂/麻醉剂量/造影部位/插管路径/鞘管型号/药品/造影导管";
    m_slstSurgInfo=sSurgInfo.split('/');

    /******** 造影所见 ********/
    QString sAngiography="冠脉供血/左主干开口/右冠开口/CABG/侧枝循环/钙化影/既往PCI支架影/左心室造影/造影结论/进一步处理建议/干预血管";
    m_slstAngiography=sAngiography.split('/');

    /******** 病变性质 ********/
    QString sPathology="病变血管位置/病变性质/范围/类型/狭窄率/形态/钙化/血栓/TIMI血流/CTO/分叉病变/左主干病变";
    m_slstPathology=sPathology.split('/');

    /******** 影像学检查 ********/
    QString sMRIType="IVUS/OCT/FFR";
    m_slstMRIType=sMRIType.split('/');

    /******** 介入治疗 ********/
    QString sPCI="导管/导丝/球囊/支架/其他";
    m_slstPCI=sPCI.split('/');

    /******** 术中术后状态 ********/
    QString sPatiState="手术情况/结束语/术后医嘱";
    m_slstPatiState=sPatiState.split('/');

    /******** PCI报表 ********/
    QString sPCIInfo="病变血管位置/既往病史";
    m_slstPCIInfo=sPCIInfo.split('/');

    /******** 病变特点 ********/
    QString sPathologyTrait="一般病变/分叉病变/钙化病变/血栓病变/长病变/CTO病变/对吻处理病变";
    m_slstPathologyTrait=sPathologyTrait.split('/');

    /******** 基本资料下的部分子项 ********/
    QString sRoom="Room1/Room2/Room3/Room4";
    m_slstRoom=sRoom.split('/');
    QString sSex="男/女";
    m_slstSex=sSex.split('/');
    QString sClinical ="无症状心肌缺血/可疑心绞痛/稳定型心绞痛/不稳定型心绞痛/ST抬高心肌梗死/非ST抬高心肌梗死";
    m_slstClinical=sClinical.split('/');
    QString sPatiType ="门诊/住院/急诊/转院";
    m_slstPatiType=sPatiType.split('/');


    /******** 手术信息下的部分子项 ********/
    QString sMzj="利多卡因/塞纳卡因";
    m_slstMzj=sMzj.split('/');
    QString sZybw="左、右冠脉/左心室/肾动脉/主动脉/颅动脉";
    m_slstZybw=sZybw.split('/');
    QString sCglj="右桡动脉/左桡动脉/右股动脉/左股动脉";
    m_slstCglj=sCglj.split('/');
    QString sQgxh="4F/5F/6F/7F/8F";
    m_slstQgxh=sQgxh.split('/');
    QString sMed="肝素/硝酸甘油";
    m_slstMed=sMed.split('/');
    QString sDGCC="4Fr/5Fr/6Fr/7Fr/8Fr";
    m_slstDGCC=sDGCC.split('/');
    QString sDGXS="JL/JR/AL/AR/猪尾/多功能管";
    m_slstDGXS=sDGXS.split('/');
    QString sDGXH1="3.0/3.5/4.0/4.5/5.0/5.5/6.0";
    m_slstDGXH1=sDGXH1.split('/');
    QString sDGXH2="1/2/3/4";
    m_slstDGXH2=sDGXH2.split('/');


    /******** 造影所见中的子项 ********/
    QString sGMGX="左优势型/右优势型/均衡型";
    m_slstGMGX=sGMGX.split('/');
    QString sCABGStart="AO/LIMA";
    m_slstCABGStart=sCABGStart.split('/');
    QString sCABGEnd="LAD/LCX/RCA/LM/LIMA";
    m_slstCABGEnd=sCABGEnd.split('/');
    QString sCZXHStart="LAD/LCX/LIMA/LM/RCA";
    m_slstCZXHStart=sCZXHStart.split('/');
    QString sCZXHEnd="LAD/LCX/RCA/LM/LIMA";
    m_slstCZXHEnd=sCZXHEnd.split('/');
    QString sGHYXt="管状/点状";
    m_slstGHYXt=sGHYXt.split('/');
    QString sGHYWz="RCA/LCA/LAD/LCX";
    m_slstGHYWz=sGHYWz.split('/');
    QString sZXSZY="外形/心腔大小/射血分数/前基底/前侧/心尖/膈面/后基底/间隔/后侧";
    m_slstZXSZY=sZXSZY.split('/');
    QString sZXSZYTrait="正常/减低/无活动/反常活动/室壁瘤/不确定";
    m_slstZXSZYTrait=sZXSZYTrait.split('/');
    QString sZYJL="正常/临界/单支病变/双支病变/三支病变/左主干/左主干+LAD单支病变/左主干+LCX单支病变/左主干+RCA单支病变/左主干+双支病变/左主干+三支病变/冠心病/PCI术后/CABG手术";
    m_slstZYJL=sZYJL.split('/');
    QString sJYBCl="即可PCI/择期PCI/择期CABG/不处理";
    m_slstJYBCl=sJYBCl.split('/');
    QString sGYXG="RCA/LCX/LAD/LM/LCA";
    m_slstGYXG=sGYXG.split('/');


    /******** 病变性质中的子项 ********/
    QString sBBXG="一般病变/瘤样扩张/夹层/管腔不规则";
    m_slstBBXG=sBBXG.split('/');
    QString sBBXZ="局限/节段/弥漫";
    m_slstBBXZ=sBBXZ.split('/');
    QString sBBLX="再狭窄/原支架内再狭窄";
    m_slstBBLX=sBBLX.split('/');
    QString sBBXT="同心/偏心";
    m_slstBBXT=sBBXT.split('/');
    QString sBBGH="钙化/轻度/重度";
    m_slstBBGH=sBBGH.split('/');
    QString sBBCTO=">3个月/<=3个月";
    m_slstBBCTO=sBBCTO.split('/');
    QString sFCBB="类型1/类型2";
    m_slstFCBB=sFCBB.split('/');
    QString sZZGBB="类型3/类型4";;
    m_slstZZGBB=sZZGBB.split('/');


    /******** 部分子项由数据库初始化 ********/
    QString sBBXGWZ="LAD/LCX/RCA/LM";
    m_slstBBXGWZ=sBBXGWZ.split('/');
    QString sJWBS="高血脂/高血压/糖尿病/近期吸烟史(<1年)/冠心病家族史/心肌梗死/心力衰竭/肾功能衰竭/脑血管疾病/外周血管疾病/慢性肺病/透析治疗/瓣膜手术史/PCI史/CABG史";
    m_slstJWBS=sJWBS.split('/');



    /******** 部分类别子项由数据库初始化 ********/
    this->GetTypeFromDB();

    /******** 初始化信号槽 ********/
    connect(ui->m_btnDelCondition, SIGNAL(clicked()), this, SLOT(ClickedEmit()));
    connect(this, SIGNAL(EmitIndex(int)), parent, SLOT(DeleteCondition(int)));
}

/**
 * @brief CWidgetCondition::GetTypeFromDB
 */
void CWidgetCondition::GetTypeFromDB()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    /******** 初始化人员 ********/
    QString sSqlStaff="SELECT StaffName,StaffPosi FROM Staff_T";
    sqlReport->exec(sSqlStaff);
    while(sqlReport->next())
    {
        QString sStaff=sqlReport->value(0).toString();
        QString sPos=sqlReport->value(1).toString();
        if(sPos=="技师")
        {
            m_slstTechnician.append(sStaff);
        }
        else if(sPos=="护士")
        {
            m_slstNurse.append(sStaff);
        }
        else
        {
            m_slstInstructor.append(sStaff);
            m_slstSurName.append(sStaff);
            m_slstAssisName.append(sStaff);
        }
    }
    m_slstTechnician.removeDuplicates();
    m_slstNurse.removeDuplicates();
    m_slstInstructor.removeDuplicates();
    m_slstSurName.removeDuplicates();
    m_slstAssisName.removeDuplicates();


    /******** 初始化保险类型 ********/
    QString sSqlInsur="SELECT InsuType FROM InsuType_T";
    sqlReport->exec(sSqlInsur);
    while(sqlReport->next())
    {
        QString sInsur=sqlReport->value(0).toString();
        if(sInsur!="")
        {
            m_slstInsur.append(sInsur);
        }
    }
    m_slstInsur.removeDuplicates();

    /******** 初始化手术类型 ********/
    QString sSqlSurg="SELECT SurgTypeName FROM SurgType_T";
    sqlReport->exec(sSqlSurg);
    while(sqlReport->next())
    {
        QString sSurg=sqlReport->value(0).toString();
        if(sSurg!="")
        {
            m_slstSurgType.append(sSurg);
        }
    }
    m_slstSurgType.removeDuplicates();

    QSqlQuery *sqlStorage=new QSqlQuery(SQLDB::GetCathLabStock());

    /******** 初始化造影剂 ********/
    QString sSqlMed="SELECT LeeName,LeeType FROM Lee_StockIndex";
    sqlStorage->exec(sSqlMed);
    while(sqlStorage->next())
    {
        QString sName=sqlStorage->value(0).toString();
        QString sType=sqlStorage->value(1).toString();
        if(sType=="造影剂")
        {
            m_slstShadow.append(sName);
        }
    }
    m_slstShadow.removeDuplicates();



    //    QStringList sDGName;
    //    QStringList sDGStyle;
    //    QStringList sDGType;
    //    QStringList sDSName;
    //    QStringList sDSStyle;
    //    QStringList sDSType;
    //    QStringList sQNName;
    //    QStringList sQNStyle;
    //    QStringList sQNType;
    //    QStringList sZJName;
    //    QStringList sZJStyle;
    //    QStringList sZJType;
    //    QString sSqlTool="SELECT Short_Name,Std1,Std2,Std3 FROM StockIndex_T";
    //    sqlStorage->exec(sSqlTool);
    //    while(sqlStorage->next())
    //    {
    //        QString sName=sqlStorage->value(0).toString();
    //        QString sStyle=sqlStorage->value(1).toString();
    //        QString sType=sqlStorage->value(2).toString();
    //        QString sTool=sqlStorage->value(3).toString().left(2);
    //        if(sTool=="导管")
    //        {
    //            m_slstDGName.append(sName);
    //        }
    //        else if(sTool=="导丝")
    //        {
    //            m_slstDSName.append(sName);
    //        }
    //        else if(sTool=="球囊")
    //        {
    //            m_slstQNName.append(sName);
    //        }
    //        else if(sTool=="支架")
    //        {
    //            m_slstZJName.append(sName);
    //        }
    //        else
    //        {
    //            m_slstQTName.append(sName);
    //        }
    //    }
    //    m_slstDGName.removeDuplicates();
    //    m_slstDSName.removeDuplicates();
    //    m_slstQNName.removeDuplicates();
    //    m_slstZJName.removeDuplicates();
    //    m_slstQTName.removeDuplicates();

    delete sqlReport;
    sqlReport=NULL;
    delete sqlStorage;
    sqlStorage=NULL;
}


CWidgetCondition::~CWidgetCondition()
{
    delete ui;
}

/**
 * @brief CWidgetCondition::on_m_cmbAndOr_currentIndexChanged
 * @param index
 */
void CWidgetCondition::on_m_cmbAndOr_currentIndexChanged(int index)
{
    QString sCurrText=ui->m_cmbAndOr->currentText();
    if(sCurrText=="与")
    {
        this->m_sSqlAndOr="and";
    }
    else if(sCurrText=="或")
    {
        this->m_sSqlAndOr="or";
    }
}

/**
 * @brief CWidgetCondition::on_m_cmbCategory_currentIndexChanged
 * @param index
 */
void CWidgetCondition::on_m_cmbCategory_currentIndexChanged(int index)
{
    this->m_nCurrType=index;

    switch (index)
    {
    case PatiInfo:
        InitCombox(ui->m_cmbCategoryValue,m_slstPatiInfo);
        m_sSqlTable="PatiInfo_T";
        break;
    case SurgInfo:
        InitCombox(ui->m_cmbCategoryValue,m_slstSurgInfo);
        m_sSqlTable="BB_ZYSJ";
        break;
    case Angiography:
        InitCombox(ui->m_cmbCategoryValue,m_slstAngiography);
        break;
    case Pathology:
        InitCombox(ui->m_cmbCategoryValue,m_slstPathology);
        m_sSqlTable="BB_BB";
        break;
    case MRI:
        InitCombox(ui->m_cmbCategoryValue,m_slstMRIType);
        m_sSqlTable="";
        break;
    case PCI:
        InitCombox(ui->m_cmbCategoryValue,m_slstPCI);
        m_sSqlTable="BBB_QXSY";
        break;
    case PatiState:
        InitCombox(ui->m_cmbCategoryValue,m_slstPatiState);
        m_sSqlTable="BB_JLYZ";
        break;
    case PCIInfo:
        InitCombox(ui->m_cmbCategoryValue,m_slstPCIInfo);
        m_sSqlTable="PCI_ZBB_T";
        break;
    case PathologyTrait:
        InitCombox(ui->m_cmbCategoryValue,m_slstPathologyTrait);
        m_sSqlTable="PCI_ZBB_FB1_T";
        break;
    default:
        break;
    }
}

/**
 * @brief CWidgetCondition::ClickedEmit
 */
void CWidgetCondition::ClickedEmit()
{
    emit(EmitIndex(this->m_nIndex));
}

/**
 * @brief 初始化combobox
 * @param pCmb
 * @param pList
 */
void CWidgetCondition::InitCombox(QComboBox* pCmb, QStringList pList)
{
    pCmb->clear();
    for (int i=0;i<pList.size();i++)
    {
        pCmb->addItem(pList[i]);
    }
    pCmb->setCurrentIndex(-1);
}

/**
 * @brief CWidgetCondition::隐藏所有条件
 */
void CWidgetCondition::HideAllCondition()
{
    ui->m_wgtConditionSelectRoot->hide();
    ui->m_wgtConditionSelect->hide();
    ui->m_wgtConditionSelect2->hide();
    ui->m_wgtConditionGHY->hide();
    ui->m_wgtConditionValue->hide();
    ui->m_wgtConditionRange->hide();
    ui->m_wgtConditionCmbRange->hide();
    ui->m_wgtConditionDate->hide();
    ui->m_wgtConditionDG->hide();
    ui->m_wgtConditionCZXH->hide();
    ui->m_wgtConditionPCI->hide();
    ui->m_wgtConditionTF->hide();
    ui->m_grpMRIType->hide();
    ui->m_wgConditionVessel->hide();
}

/**
 * @brief CWidgetCondition::PatiInfoActivated
 */
void CWidgetCondition::PatiInfoActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case CaseId:
        this->m_sSqlConditon="CaseID";
        ui->m_wgtConditionValue->show();
        break;
    case Room:
        this->m_sSqlConditon="Room";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstRoom);
        break;
    case InsurType:
        this->m_sSqlConditon="InsurType";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstInsur);
        break;
    case PatiSex:
        this->m_sSqlConditon="PatiSex";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstSex);
        break;
    case PatiAge:
        this->m_sSqlConditon="PatiAge";
        ui->m_wgtConditionRange->show();
        break;
    case PatiDOB:
        this->m_sSqlConditon="PatiDOB";
        ui->m_wgtConditionDate->show();
        break;
    case PatiHeig:
        this->m_sSqlConditon="PatiHeig";
        ui->m_wgtConditionRange->show();
        break;
    case PatiWeig:
        this->m_sSqlConditon="PatiWeig";
        ui->m_wgtConditionRange->show();
        break;
    case InstructorName:
        this->m_sSqlConditon="InsductorName";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstInstructor);
        break;
    case SurName:
        this->m_sSqlConditon="SurName";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstSurName);
        break;
    case Assis:
        this->m_sSqlConditon="Assis";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstAssisName);
        break;
    case Nursury:
        this->m_sSqlConditon="Nursury";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstNurse);
        break;
    case Techno:
        this->m_sSqlConditon="Techno";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstTechnician);
        break;
    case SurType:
        this->m_sSqlConditon="SurType";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstSurgType);
        break;
    case ShadowType:
        this->m_sSqlConditon="ShadowType";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstShadow);
        break;
    case ShadowNum:
        this->m_sSqlConditon="ShadowNum";
        ui->m_wgtConditionRange->show();
        break;
    case XTime:
        this->m_sSqlConditon="XTime";
        ui->m_wgtConditionRange->show();
        break;
    case PatiStatus:
        this->m_sSqlConditon="PatiStatus";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstPatiType);
        break;
    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::SurgInfoActivated
 * @param pIndex
 */
void CWidgetCondition::SurgInfoActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case MZJ:
        this->m_sSqlConditon="MZJ";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstMzj);
        break;
    case MZJL:
        this->m_sSqlConditon="MZJL";
        ui->m_wgtConditionValue->show();
        break;
    case ZYBW:
        this->m_sSqlConditon="ZYBW";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZybw);
        break;
    case CGLJ:
        this->m_sSqlConditon="CGLJ";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstCglj);
        break;
    case QGXH:
        this->m_sSqlConditon="QGXH";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstQgxh);
        break;
    case YYJL:
        this->m_sSqlConditon="YYJL";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;
    case ZYDG:
        this->m_sSqlConditon="ZYDG";
        ui->m_wgtConditionDG->show();
        this->InitCombox(ui->m_cmbConditionDGCC,m_slstDGCC);
        this->InitCombox(ui->m_cmbConditionDGXS,m_slstDGXS);
        break;
    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::AngiographyActivated
 * @param pIndex
 */
void CWidgetCondition::AngiographyActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case GMGX:
        this->m_sSqlTable="BB_BBQT";
        this->m_sSqlConditon="GMType";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstGMGX);
        break;
    case ZZGKK:
        this->m_sSqlTable="BB_BBQT";
        this->m_sSqlConditon="Zzgkk";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstIsNormal);
        break;
    case YGKK:
        this->m_sSqlTable="BB_BBQT";
        this->m_sSqlConditon="Ygkk";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstIsNormal);
        break;
    case CABG:
        this->m_sSqlTable="BB_CABG";
        this->m_sSqlConditon="startblood";
        this->m_sSqlConditon1="endblood";
        ui->m_wgtConditionSelect2->show();
        this->InitCombox(ui->m_cmbValueSelectStart,m_slstCABGStart);
        this->InitCombox(ui->m_cmbValueSelectEnd,m_slstCABGEnd);
        break;
    case CZXH:
        this->m_sSqlTable="BB_CZXH";

        this->m_sSqlConditon="startblood";
        this->m_sSqlConditon1="endblood";
        this->m_sSqlConditon2="TIMI";
        ui->m_wgtConditionCZXH->show();
        this->InitCombox(ui->m_cmbCZXHStart,m_slstCZXHStart);
        this->InitCombox(ui->m_cmbCZXHEnd,m_slstCZXHEnd);
        this->InitCombox(ui->m_cmbCZXHTimi,m_slstTimi);
        break;
    case GHY:
        this->m_sSqlTable="BB_GHY";
        this->m_sSqlConditon="ghType";
        this->m_sSqlConditon1="ghblood";
        ui->m_wgtConditionSelect2->show();
        this->InitCombox(ui->m_cmbValueSelectStart,m_slstGHYXt);
        this->InitCombox(ui->m_cmbValueSelectEnd,m_slstGHYWz);
        break;
    case JWPCI:
        this->m_sSqlTable="BB_BBQT";
        this->m_sSqlConditon="Jwpciwz";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstIsHave);
        break;
    case ZXSZY:
        this->m_sSqlTable="BB_ZXS";
        ui->m_wgtConditionSelectRoot->show();
        this->InitCombox(ui->m_cmbValueSelectRoot,m_slstZXSZY);
        break;
    case ZYJL:
        this->m_sSqlTable="BB_JLYZ";
        this->m_sSqlConditon="zyjl";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZYJL);
        break;
    case JYBJY:
        this->m_sSqlTable="BB_JLYZ";
        this->m_sSqlConditon="jyb";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstJYBCl);
        break;
    case GYXG:
        this->m_sSqlTable="BB_JLYZ";
        this->m_sSqlConditon="gyxg";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstGYXG);
        break;

    default:
        break;
    }
    return;
}

void CWidgetCondition::PathologyActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case BBXGWZ:
        this->m_sSqlConditon="bbgm";
        this->m_sSqlConditon1="bbzywz";
        this->m_sSqlConditon2="bbljwz";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;
    case XZ:
        this->m_sSqlConditon="BBXZ";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;
    case FW:
        this->m_sSqlConditon="FW";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;
    case LX:
        this->m_sSqlConditon="BType";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;
    case XZL:
        this->m_sSqlConditon="YYJL";
        ui->m_wgtConditionRange->show();
        break;
    case XT:
        this->m_sSqlConditon="XT";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstBBXT);
        break;
    case GH:
        this->m_sSqlConditon="GH";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstBBGH);
        break;
    case XS:
        this->m_sSqlConditon="XS";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstIsHave);
        break;
    case TIMI:
        this->m_sSqlConditon="TIMI";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstTimi);
        break;
    case CTO:
        this->m_sSqlConditon="CTO";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstBBCTO);
        break;
    case FCBB:
//        this->m_sSqlConditon="";
//        ui->m_wgtConditionSelect->show();
//        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;
    case ZZGBB:
//        this->m_sSqlConditon="";
//        ui->m_wgtConditionSelect->show();
//        this->InitCombox(ui->m_cmbValueSelect,m_slstMed);
        break;

    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::MRIActivated
 * @param pIndex
 */
void CWidgetCondition::MRIActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case IVUS:
        break;
    case OCT:
        break;
    case FFR:
        break;

    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::PCIActivated
 * @param pIndex
 */
void CWidgetCondition::PCIActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case DG:
        ui->m_wgtConditionPCI->show();
        this->m_sSqlConditon="导管";
        break;
    case DS:
        ui->m_wgtConditionPCI->show();
        this->m_sSqlConditon="导丝";
        break;
    case QN:
        ui->m_wgtConditionPCI->show();
        this->m_sSqlConditon="球囊";
        break;
    case ZJ:
        ui->m_wgtConditionPCI->show();
        this->m_sSqlConditon="支架";
        break;
    case QT:
        ui->m_wgtConditionPCI->show();
        this->m_sSqlConditon="其他";
        break;

    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::PatiStateActivated
 * @param pIndex
 */
void CWidgetCondition::PatiStateActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case SSQK:
        this->m_sSqlConditon="ssqk";
        ui->m_wgtConditionValue->show();
        break;
    case JSY:
        this->m_sSqlConditon="jsy";
        ui->m_wgtConditionValue->show();
        break;
    case SHYZ:
        this->m_sSqlConditon="shyz";
        ui->m_wgtConditionValue->show();
        break;

    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::PCIInfoActivated
 * @param pIndex
 */
void CWidgetCondition::PCIInfoActivated(int pIndex)
{
    this->HideAllCondition();
    switch (pIndex)
    {
    case BBXGWZ:
        this->m_sSqlConditon="bbxgwz";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstBBXGWZ);
        break;
    case JWBS:
        ui->m_wgtConditionTF->show();
        this->InitCombox(ui->m_cmbJWBS,m_slstJWBS);
        break;

    default:
        break;
    }
    return;
}

/**
 * @brief CWidgetCondition::PathologyTraitActivated
 * @param pIndex
 */
void CWidgetCondition::PathologyTraitActivated(int pIndex)
{
    this->HideAllCondition();
    this->m_sSqlConditon="BBTD";
    QString sValue=ui->m_cmbCategoryValue->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sValue+"'";

    return;
}

/**
 * @brief CWidgetCondition::DataToInt
 * @param pData
 * @return
 */
int CWidgetCondition::DataToInt(QDate pData)
{
    int nYear=pData.year();
    int nMonth=pData.month();
    int nDay=pData.day();
    int nTemp=nYear*10000+nMonth*100+nDay;
    return nTemp;
}



/**
 * @brief CWidgetCondition::HideDelete
 */
void CWidgetCondition::HideDelete()
{
    ui->m_btnDelCondition->hide();
}

/**
 * @brief CWidgetCondition::SetIndex
 * @param pIndex
 */
void CWidgetCondition::SetIndex(int pIndex)
{
    this->m_nIndex=pIndex;
}

/**
 * @brief CWidgetCondition::HideVerticalSpacer
 */
void CWidgetCondition::HideVerticalSpacer()
{
    ui->verticalSpacer_2->invalidate();
}

/**
 * @brief CWidgetCondition::GetSqlQuery
 * @param pTable
 * @param pSql
 * @param pAndOr
 * @param pPrimaryId
 */
void CWidgetCondition::GetSqlQuery(QString &pTable,QString &pSql,QString &pAndOr,QString &pJoin)
{
    pTable=this->m_sSqlTable;
    pSql=this->m_sSqlQuery;
    pAndOr=this->m_sSqlAndOr;
    pJoin=this->m_sSqlJoin;
}

/**
 * @brief CWidgetCondition::on_m_cmbCategoryValue_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbCategoryValue_activated(int index)
{
    switch (this->m_nCurrType)
    {
    case PatiInfo:
        this->PatiInfoActivated(index);
        break;
    case SurgInfo:
        this->SurgInfoActivated(index);
        break;
    case Angiography:
        this->AngiographyActivated(index);
        break;
    case Pathology:
        this->PathologyActivated(index);
        break;
    case MRI:
        this->MRIActivated(index);
        break;
    case PCI:
        this->PCIActivated(index);
        break;
    case PatiState:
        this->PatiStateActivated(index);
        break;
    case PCIInfo:
        this->PCIInfoActivated(index);
        break;
    case PathologyTrait:
        this->PathologyTraitActivated(index);
        break;
    default:
        break;
    }
}

/**
 * @brief CWidgetCondition::on_m_lineValueEdit_editingFinished
 */
void CWidgetCondition::on_m_lineValueEdit_editingFinished()
{
    QString sValue=ui->m_lineValueEdit->text();
    m_sSqlQuery=m_sSqlConditon+"='"+sValue+"'";
}

/**
 * @brief CWidgetCondition::on_m_cmbValueSelect_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbValueSelect_activated(int index)
{
    QString sValue=ui->m_cmbValueSelect->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sValue+"'";
}

/**
 * @brief CWidgetCondition::on_m_dtValueStart_userDateChanged
 * @param date
 */
void CWidgetCondition::on_m_dtValueStart_userDateChanged(const QDate &date)
{
    QDate dtStart=ui->m_dtValueStart->date();
    QDate dtEnd=ui->m_dtValueEnd->date();
    int nStart=this->DataToInt(dtStart);
    int nEnd=this->DataToInt(dtEnd);
    //    if(nStart>nEnd)
    //    {
    //        QMessageBox::information(NULL,"提示","起始日期大于终止日期",QMessageBox::Ok);
    //        return;
    //    }

    QString sStart=dtStart.toString("yyyy-MM-dd");
    QString sEnd=dtEnd.toString("yyyy-MM-dd");
    m_sSqlQuery=m_sSqlConditon+">='"+sStart+"'and "+m_sSqlConditon+"<='"+sEnd+"'";
}

/**
 * @brief CWidgetCondition::on_m_dtValueEnd_userDateChanged
 * @param date
 */
void CWidgetCondition::on_m_dtValueEnd_userDateChanged(const QDate &date)
{
    QDate dtStart=ui->m_dtValueStart->date();
    QDate dtEnd=ui->m_dtValueEnd->date();
    int nStart=this->DataToInt(dtStart);
    int nEnd=this->DataToInt(dtEnd);
    //    if(nStart>nEnd)
    //    {
    //        QMessageBox::information(NULL,"提示","起始日期大于终止日期",QMessageBox::Ok);
    //        return;
    //    }

    QString sStart=dtStart.toString("yyyy-MM-dd");
    QString sEnd=dtEnd.toString("yyyy-MM-dd");
    m_sSqlQuery=m_sSqlConditon+">='"+sStart+"'and "+m_sSqlConditon+"<='"+sEnd+"'";
}

/**
 * @brief CWidgetCondition::on_m_lineValueRangeL_editingFinished
 */
void CWidgetCondition::on_m_lineValueRangeL_editingFinished()
{
    QString sLeft=ui->m_lineValueRangeL->text();
    QString sRight=ui->m_lineValueRangeR->text();

    m_sSqlQuery=m_sSqlConditon+">='"+sLeft+"'and "+m_sSqlConditon+"<='"+sRight+"'";
}

/**
 * @brief CWidgetCondition::on_m_lineValueRangeR_editingFinished
 */
void CWidgetCondition::on_m_lineValueRangeR_editingFinished()
{
    QString sLeft=ui->m_lineValueRangeL->text();
    QString sRight=ui->m_lineValueRangeR->text();

    m_sSqlQuery=m_sSqlConditon+">='"+sLeft+"'and "+m_sSqlConditon+"<='"+sRight+"'";
}

/**
 * @brief CWidgetCondition::on_m_radConditionT_clicked
 * @param checked
 */
void CWidgetCondition::on_m_radConditionT_clicked(bool checked)
{
    if(checked)
    {
        m_sSqlQuery=m_sSqlConditon+"='是'";
    }
}

/**
 * @brief CWidgetCondition::on_m_radConditionF_clicked
 * @param checked
 */
void CWidgetCondition::on_m_radConditionF_clicked(bool checked)
{
    if(checked)
    {
        m_sSqlQuery=m_sSqlConditon+"='否'";
    }
}

/**
 * @brief 选择既往病史
 * @param index
 */
void CWidgetCondition::on_m_cmbJWBS_activated(int index)
{
    switch (index)
    {
    case GXZ:
        this->m_sSqlConditon="gxz";
        break;
    case GXY:
        this->m_sSqlConditon="gxy";
        break;
    case TNB:
        this->m_sSqlConditon="tnb";
        break;
    case JQXYS:
        this->m_sSqlConditon="jqxys";
        break;
    case GXBJZS:
        this->m_sSqlConditon="gxbjzs";
        break;
    case XJGS:
        this->m_sSqlConditon="xjgs";
        break;
    case XLSJ:
        this->m_sSqlConditon="xlsj";
        break;
    case SGNSJ:
        this->m_sSqlConditon="sgnsj";
        break;
    case NXGJB:
        this->m_sSqlConditon="nxgjb";
        break;
    case QZXGJB:
        this->m_sSqlConditon="wzxgjb";
        break;
    case MXFB:
        this->m_sSqlConditon="mxfb";
        break;
    case TXZL:
        this->m_sSqlConditon="txzl";
        break;
    case BMSSS:
        this->m_sSqlConditon="bmsss";
        break;
    case PCIS:
        this->m_sSqlConditon="pcis";
        break;
    case CABGS:
        this->m_sSqlConditon="cabgs";
        break;

    default:
        break;
    }


    if(ui->m_radConditionT->isChecked())
    {
        m_sSqlQuery=m_sSqlConditon+"='是'";
    }
    else if(ui->m_radConditionF->isChecked())
    {
        m_sSqlQuery=m_sSqlConditon+"='否'";
    }
}



/**
 * @brief CWidgetCondition::on_m_cmbType_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbType_activated(int index)
{
    QString sType="";
    QString sStyle="";


}

/**
 * @brief CWidgetCondition::on_m_cmbStyle_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbStyle_activated(int index)
{

    QSqlQuery *sqlStorage=new QSqlQuery(SQLDB::GetCathLabStock());

    QString sStyle=ui->m_cmbStyle->currentText();
    QString sSqlType="SELECT Std2 FROM StockIndex_T where Std1='"+sStyle+"'";
    sqlStorage->exec(sSqlType);
    while(sqlStorage->next())
    {
        QString sSType=sqlStorage->value(0).toString();
        m_slstStyle.append(sSType);
    }
    m_slstType.removeDuplicates();



    delete sqlStorage;
    sqlStorage=NULL;
}

/**
 * @brief CWidgetCondition::on_m_cmbName_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbName_activated(int index)
{
    QSqlQuery *sqlStorage=new QSqlQuery(SQLDB::GetCathLabStock());

    QString sName=ui->m_cmbName->currentText();
    QString sSqlStyle="SELECT Std1 FROM StockIndex_T where Short_Name='"+sName+"'";
    sqlStorage->exec(sSqlStyle);
    while(sqlStorage->next())
    {
        QString sStyle=sqlStorage->value(0).toString();
        m_slstStyle.append(sStyle);
    }
    m_slstStyle.removeDuplicates();



    delete sqlStorage;
    sqlStorage=NULL;
}

void CWidgetCondition::on_m_cmbConditionDGXS_activated(int index)
{
    QString sDGXS=ui->m_cmbConditionDGXS->currentText();
    if(sDGXS=="JL"||sDGXS=="JR")
    {
        this->InitCombox(ui->m_cmbConditionDGXH,m_slstDGXH1);
    }
    else if(sDGXS=="AL"||sDGXS=="AR")
    {
        this->InitCombox(ui->m_cmbConditionDGXH,m_slstDGXH2);
    }
    else
    {
        ui->m_cmbConditionDGXH->clear();
    }

    QString sDGCC=ui->m_cmbConditionDGCC->currentText();
    QString sDGXH=ui->m_cmbConditionDGXH->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sDGCC+sDGXS+sDGXH+"'";
}

void CWidgetCondition::on_m_cmbConditionDGXH_activated(int index)
{
    QString sDGCC=ui->m_cmbConditionDGCC->currentText();
    QString sDGXS=ui->m_cmbConditionDGXS->currentText();
    QString sDGXH=ui->m_cmbConditionDGXH->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sDGCC+sDGXS+sDGXH+"'";
}

void CWidgetCondition::on_m_cmbConditionDGCC_activated(int index)
{
    QString sDGCC=ui->m_cmbConditionDGCC->currentText();
    QString sDGXS=ui->m_cmbConditionDGXS->currentText();
    QString sDGXH=ui->m_cmbConditionDGXH->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sDGCC+sDGXS+sDGXH+"'";
}

/**
 * @brief CWidgetCondition::on_m_cmbValueSelectEnd_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbValueSelectEnd_activated(int index)
{
    QString sSelectStart=ui->m_cmbValueSelectStart->currentText();
    QString sSelectEnd=ui->m_cmbValueSelectEnd->currentText();

    m_sSqlQuery=m_sSqlConditon+"='"+sSelectStart+"'and "+m_sSqlConditon1+"='"+sSelectEnd+"'";
}
/**
 * @brief CWidgetCondition::on_m_cmbValueSelectStart_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbValueSelectStart_activated(int index)
{
    QString sSelectStart=ui->m_cmbValueSelectStart->currentText();
    QString sSelectEnd=ui->m_cmbValueSelectEnd->currentText();

    m_sSqlQuery=m_sSqlConditon+"='"+sSelectStart+"'and "+m_sSqlConditon1+"='"+sSelectEnd+"'";
}

/**
 * @brief CWidgetCondition::on_m_cmbCZXHStart_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbCZXHStart_activated(int index)
{
    QString sSelectStart=ui->m_cmbCZXHStart->currentText();
    QString sSelectEnd=ui->m_cmbCZXHEnd->currentText();
    QString sSelectTimi=ui->m_cmbCZXHTimi->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sSelectStart+"'and "+m_sSqlConditon1+"='"+sSelectEnd+"'and "+m_sSqlConditon2+"='"+sSelectTimi+"'";
}
/**
 * @brief CWidgetCondition::on_m_cmbCZXHEnd_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbCZXHEnd_activated(int index)
{
    QString sSelectStart=ui->m_cmbCZXHStart->currentText();
    QString sSelectEnd=ui->m_cmbCZXHEnd->currentText();
    QString sSelectTimi=ui->m_cmbCZXHTimi->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sSelectStart+"'and "+m_sSqlConditon1+"='"+sSelectEnd+"'and "+m_sSqlConditon2+"='"+sSelectTimi+"'";
}
/**
 * @brief CWidgetCondition::on_m_cmbCZXHTimi_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbCZXHTimi_activated(int index)
{
    QString sSelectStart=ui->m_cmbCZXHStart->currentText();
    QString sSelectEnd=ui->m_cmbCZXHEnd->currentText();
    QString sSelectTimi=ui->m_cmbCZXHTimi->currentText();
    m_sSqlQuery=m_sSqlConditon+"='"+sSelectStart+"'and "+m_sSqlConditon1+"='"+sSelectEnd+"'and "+m_sSqlConditon2+"='"+sSelectTimi+"'";
}

/**
 * @brief CWidgetCondition::on_m_cmbValueSelectRoot_activated
 * @param index
 */
void CWidgetCondition::on_m_cmbValueSelectRoot_activated(int index)
{
    this->HideAllCondition();
    switch(index)
    {
    case WX:
        this->m_sSqlConditon="Figure";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstIsNormal);
        break;
    case XQ:
        this->m_sSqlConditon="Heart_Size";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstIsNormal);
        break;
    case SX:
        this->m_sSqlConditon="sxfs";
        ui->m_wgtConditionRange->show();
        break;
    case QJD:
        this->m_sSqlConditon="QJD";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    case QC:
        this->m_sSqlConditon="QC";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    case XJ:
        this->m_sSqlConditon="XJ";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    case GM:
        this->m_sSqlConditon="GM";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    case HJD:
        this->m_sSqlConditon="HJD";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    case JG:
        this->m_sSqlConditon="JG";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    case HC:
        this->m_sSqlConditon="HC";
        ui->m_wgtConditionSelect->show();
        this->InitCombox(ui->m_cmbValueSelect,m_slstZXSZYTrait);
        break;
    default:
        break;

    }
}


void CWidgetCondition::on_m_radBBRight_clicked(bool checked)
{

}

void CWidgetCondition::on_m_radBBLeft_clicked(bool checked)
{

}
