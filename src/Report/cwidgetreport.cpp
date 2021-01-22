#include "cwidgetreport.h"
#include "ui_cwidgetreport.h"

CWidgetReport::CWidgetReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetReport)
{
    ui->setupUi(this);

    /******** 初始化Tabwidget ********/
    ui->m_tbwReportPage->setCurrentIndex(0);
    m_nPrePageId=0;

    /******** 左下角子页面 ********/
    m_wgtimageviewer = new ImageViewer();

    /******** 构造子界面 ********/
    m_wgtPatientInfo=new CWidgetPatientInfo();
    m_wgtAngiography=new CWidgetAngiography();
    m_wgtPathologyInfo=new CWidgetPathologyInfo();
    m_wgtPCI=new CWidgetPCI();
    m_wgtPatientState=new CWidgetPatientState();
    m_wgtReportPic=new CWidgetReportPic();
    m_wgtAdditionalInfo=new CWidgetAdditionalInfo();
    m_wgtLabExamination=new CWidgetLabExamination();

    /******** 添加子界面 ********/
    ui->scrollArea->setWidget(m_wgtPatientInfo);
    ui->tab_2->layout()->addWidget(m_wgtAngiography);
    ui->tab_3->layout()->addWidget(m_wgtPathologyInfo);
    ui->tab_4->layout()->addWidget(m_wgtPCI);
    ui->tab_5->layout()->addWidget(m_wgtPatientState);
    ui->tab_6->layout()->addWidget(m_wgtReportPic);
    ui->tab_7->layout()->addWidget(m_wgtAdditionalInfo);
    ui->tab_8->layout()->addWidget(m_wgtLabExamination);

    ui->m_layoutShow->addWidget(m_wgtimageviewer);

    /******** 初始化基本信息 ********/
    ui->m_linePatientId->setReadOnly(1);
    ui->m_lineCaseId->setReadOnly(1);
    ui->m_linePatientType->setReadOnly(1);
    ui->m_lineSurgeryType->setReadOnly(1);
    ui->m_lineDoctor->setReadOnly(1);
    ui->m_lineNurse->setReadOnly(1);
    ui->m_lineAssistant->setReadOnly(1);
    ui->m_lineTechnician->setReadOnly(1);
    ui->m_dtSurgery->setReadOnly(1);
    ui->m_tmStart->setReadOnly(1);

    /******** 部件间信息传递 ********/
    SetViewerToReportPic();


    m_sSysCaseId="";

}

CWidgetReport::~CWidgetReport()
{
    delete ui;
    if(m_wgtPatientInfo!=NULL)
    {
        delete m_wgtPatientInfo;
    }

    if(m_wgtAngiography!=NULL)
    {
        delete m_wgtAngiography;
    }

    if(m_wgtPathologyInfo!=NULL)
    {
        delete m_wgtPathologyInfo;
    }

    if(m_wgtPCI!=NULL)
    {
        delete m_wgtPCI;
    }

    if(m_wgtPatientState!=NULL)
    {
        delete m_wgtPatientState;
    }

    if(m_wgtReportPic!=NULL)
    {
        delete m_wgtReportPic;
    }

    if(m_wgtAdditionalInfo!=NULL)
    {
        delete m_wgtAdditionalInfo;
    }

    if(m_wgtLabExamination!=NULL)
    {
        delete m_wgtLabExamination;
    }

    if(m_wgtimageviewer!=NULL)
    {
        delete m_wgtimageviewer;
    }
}

/**
 * @brief 这里首先检索Patiinfo，如果没有syscaseid,则从dicom库从中获取信息
 * @param pPatientId
 */
void CWidgetReport::SetIdPatient(const QString pPatientId)
{
    // 判断当前报告系统中是否有此信息
    this->IsHavePatient(pPatientId);

    /******** 初始化患者基本信息 ********/
    // 通过caseId检索系统syscaseId
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    QString sSqlPatiInfo="select SysCaseID from PatiInfo_T where CaseID='"+pPatientId+"'";
    sqlReport->exec(sSqlPatiInfo);
    while (sqlReport->next())
    {
        m_sSysCaseId=sqlReport->value(0).toString();
    }
    delete sqlReport;
    sqlReport=NULL;


    if(m_sSysCaseId!="")
    {
        // 初始化左侧子页面
        this->UpdateSubPage();
        // 初始化病例报告
        this->UpdateReport();

        m_wgtPatientInfo->SetSysCaseId(m_sSysCaseId);
        m_wgtAngiography->SetSysCaseId(m_sSysCaseId);
        m_wgtPathologyInfo->SetSysCaseId(m_sSysCaseId);
        m_wgtPCI->SetSysCaseId(m_sSysCaseId);
        m_wgtPatientState->SetSysCaseId(m_sSysCaseId);
        m_wgtReportPic->SetSysCaseId(pPatientId);
        m_wgtAdditionalInfo->SetSysCaseId(m_sSysCaseId);
    }
}

void CWidgetReport::AddVideo(std::vector<std::vector<QPixmap> > videos)
{
    m_wgtimageviewer->AddVideo(videos);
}

void CWidgetReport::SetViewerToReportPic()
{
    m_wgtReportPic->SetImageViewer(m_wgtimageviewer);
}

/**
 * @brief CWidgetReport::resizeEvent
 * @param event
 */
void CWidgetReport::resizeEvent(QResizeEvent *event)
{
}

/**
 * @brief 查看是否存在Id
 * @param pPatientId
 */
void CWidgetReport::IsHavePatient(const QString pPatientId)
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QSqlQuery *sqlDicom=new QSqlQuery(SQLDB::GetEvertopDB());

    QString sSysCaseId="";
    QString sSqlSysCaseId="select SysCaseID from PatiInfo_T where CaseID='"+pPatientId+"'";
    sqlReport->exec(sSqlSysCaseId);
    while (sqlReport->next())
    {
        sSysCaseId=sqlReport->value(0).toString();
    }

    if(sSysCaseId=="")
    {
        QString sStudyDate,sStudyTime,sPatiAge,sPatiName,sPatiBir,sPatiSex,sRoom;
        QString sSqlDicom="select StudyDate,StudyTime,PatientsAg,PatientNam,PatientBir,PatientSex,qSpare from DICOMStudies where PatientID='"+pPatientId+"'";
        sqlDicom->exec(sSqlDicom);
        while (sqlDicom->next())
        {
            sStudyDate=sqlDicom->value(0).toString();
            sStudyTime=sqlDicom->value(1).toString().left(10);
            sPatiAge=sqlDicom->value(2).toString();
            sPatiName=sqlDicom->value(3).toString();
            sPatiBir=sqlDicom->value(4).toString();
            sPatiSex=sqlDicom->value(5).toString();
            sRoom=sqlDicom->value(6).toString();
        }

        sPatiAge=this->DeleteRearLetter(sPatiAge);
        // 计算时间
        QDate dtStudy=QDate::fromString(sStudyDate,"yyyyMMdd");
        QTime tmStudy=QTime::fromString(sStudyTime,"hhmmss.zzz");
        QDateTime dtmStudy(dtStudy,tmStudy);
        QString sStudyDateTime=dtmStudy.toString("yyyy-MM-dd hh:mm:ss");

        QDate dtBir=QDate::fromString(sPatiBir,"yyyyMMdd");
        sStudyDate=dtStudy.toString("yyyy-MM-dd");
        sStudyTime=tmStudy.toString("hh:mm:ss.zzz");
        sPatiBir=dtBir.toString("yyyy-MM-dd");

        // 在报告系统中采用男/女
        if(sPatiSex=="F")
        {
            sPatiSex="女";
        }
        else
        {
            sPatiSex="男";
        }

        int nMaxId=0;
        QString sSqlPatiSum="select max(SysCaseID) from PatiInfo_T where PatiDate=('"+sStudyDate+"')";
        sqlReport->exec(sSqlSysCaseId);
        while (sqlReport->next())
        {
            nMaxId=sqlReport->value(0).toString().right(4).toInt();
        }
        QString sHour=QString("%1").arg(tmStudy.hour(),2,10,QChar('0'));
        QString sNextId = QString("%1").arg(nMaxId+1,4,10,QChar('0'));
        QString sSysCaseDate=dtStudy.toString("yyyyMMdd");
        sSysCaseId="DG"+sSysCaseDate+sHour+sNextId;

        QString sSqlPatiInfo="insert into PatiInfo_T(SysCaseID,PatiChName,CaseID,PatiDate,PatiSex,PatiDOB,PatiAge,"
                             "Room) values('"+sSysCaseId+"','"+sPatiName+"','"+pPatientId+"','"+sStudyDateTime+"','"+sPatiSex+"','"+sPatiBir+"','"+sPatiAge+"','"+sRoom+"')";
        sqlReport->exec(sSqlPatiInfo);
        qDebug()<<sSqlPatiInfo;
    }

    delete sqlDicom;
    sqlDicom=NULL;
    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新报告左侧子页面
 */
void CWidgetReport::UpdateSubPage()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sPatientId="";
    QString sName="";
    QString sCaseId="";
    QString sdtSurgery="";
    QString sSex="";
    QString sAge="";
    QString sDoctor="";
    QString sAssistant1="";
    QString sAssistant2="";
    QString sTechnician="";
    QString sNurse1="";
    QString sNurse2="";
    QString sSurgeryType="";
    QString stmBegin="";
    QString stmEnd="";
    QString sPatientType="";

    QString sSqlPatiInfo="select SysCaseID,PatiChName,CaseID,PatiDate,PatiSex,PatiAge,SurName,Assis1,Assis2,Techno,"
                         "Nursury1,Nursury2,SurType,BeginTime,EndTime,PatiStatus from PatiInfo_T where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlPatiInfo);
    while (sqlReport->next())
    {
        sPatientId=sqlReport->value(0).toString();
        sName=sqlReport->value(1).toString();
        sCaseId=sqlReport->value(2).toString();
        sdtSurgery=sqlReport->value(3).toDate().toString(sDateStyle);
        sSex=sqlReport->value(4).toString();
        sAge=sqlReport->value(5).toString()+"岁";
        sDoctor=sqlReport->value(6).toString();
        sAssistant1=sqlReport->value(7).toString();
        sAssistant2=sqlReport->value(8).toString();
        sTechnician=sqlReport->value(9).toString();
        sNurse1=sqlReport->value(10).toString();
        sNurse2=sqlReport->value(11).toString();
        sSurgeryType=sqlReport->value(12).toString();
        stmBegin=sqlReport->value(13).toTime().toString(sTimeStyle);
        stmEnd=sqlReport->value(14).toTime().toString(sTimeStyle);
        sPatientType=sqlReport->value(15).toString();
    }
    delete sqlReport;
    sqlReport=NULL;

    QString sAssistant="";
    if(sNurse1!="")
    {
        sAssistant+=sAssistant1+";";
    }
    sAssistant+=sAssistant2;
    QString sNurse="";
    if(sNurse1!="")
    {
        sNurse+=sNurse1+";";
    }
    sNurse+=sNurse2;
    ui->m_lineNurse->setText(sNurse);

    // 手术类型
    QStringList slstSurgery=sSurgeryType.split('#');
    QString sSurgery="";
    for(int i=0;i<slstSurgery.size()-1;i++)
    {
        if(slstSurgery[i]!="")
        {
            sSurgery+=slstSurgery[i]+";";
        }
    }
    sSurgery+=slstSurgery[slstSurgery.size()-1];


    ui->m_linePatientId->setText(sPatientId);
    ui->m_lblName->setText(sName);
    ui->m_lineCaseId->setText(sCaseId);
    ui->m_dtSurgery->setDate(QDate::fromString(sdtSurgery,sDateStyle));
    ui->m_lblSex->setText(sSex);
    ui->m_lblAge->setText(sAge);
    ui->m_lineDoctor->setText(sDoctor);
    ui->m_lineAssistant->setText(sAssistant);
    ui->m_lineTechnician->setText(sTechnician);
    ui->m_lineSurgeryType->setText(sSurgery);
    ui->m_tmStart->setTime(QTime::fromString(stmBegin,sTimeStyle));
    ui->m_tmEnd->setTime(QTime::fromString(stmEnd,sTimeStyle));
    ui->m_linePatientType->setText(sPatientType);
}

/**
 * @brief CWidgetReport::UpdateUIFromDB
 * @param pPageId
 */
void CWidgetReport::UpdateUIFromDB(int pPageId)
{
    switch (pPageId)
    {
    case PatiInfoPage:
        //m_wgtPatientInfo->UpdateUIFromDatabase();
        break;
    case AngiographyPage:
        //m_wgtAngiography->UpdateUIFromDatabase();
        break;
    case PathologyInfoPage:
        m_wgtPathologyInfo->UpdateUIFromDatabase();
        break;
    case PCIPage:
        m_wgtPCI->UpdateUIFromDatabase();
        break;
    case PatiStatePage:
        //m_wgtPatientState->UpdateUIFromDatabase();
        break;
    case ReportPicPage:
        break;
    case AddInfoPage:
        //m_wgtAdditionalInfo->UpdateUIFromDatabase();
        break;
    case LabExamPage:
        break;
    default:
        break;
    }
}

/**
 * @brief CWidgetReport::UpdateDBFromUI
 * @param pPageId
 */
void CWidgetReport::UpdateDBFromUI(int pPageId)
{
    switch (pPageId)
    {
    case PatiInfoPage:
        m_wgtPatientInfo->UpdateDatabaseFromUI();
        break;
    case AngiographyPage:
        m_wgtAngiography->UpdateDatabaseFromUI();
        break;
    case PathologyInfoPage:
        m_wgtPathologyInfo->UpdateDatabaseFromUI();
        break;
    case PCIPage:
        m_wgtPCI->UpdateDatabaseFromUI();
        break;
    case PatiStatePage:
        m_wgtPatientState->UpdateDatabaseFromUI();
        break;
    case ReportPicPage:
        break;
    case AddInfoPage:
        m_wgtAdditionalInfo->UpdateDatabaseFromUI();
        break;
    case LabExamPage:
        break;
    default:
        break;
    }
}

/**
 * @brief CWidgetReport::UpdateReport
 */
void CWidgetReport::UpdateReport()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    QString sSysCaseID="";
    QString sPatiChName="";
    QString sCaseID="";
    QString sPatiDate="";
    QString sPatiSex="";
    QString sPatiAge="";
    QString sPatiStatus="";

    QString sSqlPatiInfo="select SysCaseID,PatiChName,CaseID,PatiDate,PatiSex,PatiAge,PatiStatus from PatiInfo_T where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlPatiInfo);
    while (sqlReport->next())
    {
        sSysCaseID=sqlReport->value(0).toString();
        sPatiChName=sqlReport->value(1).toString();
        sCaseID=sqlReport->value(2).toString();
        sPatiDate=sqlReport->value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        sPatiSex=sqlReport->value(4).toString();
        sPatiAge=sqlReport->value(5).toString();
        sPatiStatus=sqlReport->value(6).toString();
    }

    QString sSqlReportInfo="select count(*) from operateitem where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReportInfo);
    int nCountItem=0;
    while (sqlReport->next())
    {
        nCountItem=sqlReport->value(0).toInt();
    }

    // 如果没有报告表则插入
    if(nCountItem==0)
    {
        QString sSqlReport="insert into operateitem(name,sex,age,caseid,date,SysCaseID"
                 ") values('"+sPatiChName+"','"+sPatiSex+"','"+sPatiAge+"','"+sCaseID+"','"+sPatiDate+"','"+m_sSysCaseId+"')";
        sqlReport->exec(sSqlReport);
    }
    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief CWidgetReport::DeleteRearLetter
 * @param pStr
 * @return
 */
QString CWidgetReport::DeleteRearLetter(QString pStr)
{
    QString sAge="";
    // 先过略字母
    int nRear=pStr.length()-1;
    for (int i=nRear;i>=0;i--)
    {
        if(pStr[i]>='0'&&pStr[i]<='9')
        {
            nRear=i;
            break;
        }
    }

    for (int i=0;i<=nRear;i++)
    {
        if(pStr[i]>='0'&&pStr[i]<='9')
        {
            sAge+=pStr[i];
        }
    }
    return sAge;
}

/**
 * @brief 启动报告打印页面
 */
void CWidgetReport::on_m_btnWriteReport_clicked()
{
    m_wgtReportPrint=new PrintPreviewDialog();
    m_wgtReportPrint->setModal(1);
    m_wgtReportPrint->SetSysCaseId(m_sSysCaseId);
    m_wgtReportPrint->show();
}

/**
 * @brief CWidgetReport::on_m_tbwReportPage_tabBarClicked
 * @param index
 */
void CWidgetReport::on_m_tbwReportPage_tabBarClicked(int index)
{
    // 这里分为两步1、从数据库到UI 2、从UI到数据库
    if(index!=m_nPrePageId)
    {
        this->UpdateDBFromUI(m_nPrePageId);
        this->UpdateUIFromDB(index);

        if(m_nPrePageId==0)
        {
            this->UpdateSubPage();
        }

        // 上次打开的页面和当前页面
        //qDebug()<<m_nPrePageId<<" "<<index;
        m_nPrePageId=index;
    }
}

/**
 * @brief CWidgetReport::closeEvent
 * @param event
 */
void CWidgetReport::closeEvent(QCloseEvent *event)
{
    this->close();
    emit(ExitReportWindow());
}

