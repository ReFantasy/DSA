#include "cwidgetpci.h"
#include "ui_cwidgetpci.h"

/**
 * @brief CWidgetPCI::CWidgetPCI
 * @param parent
 */
CWidgetPCI::CWidgetPCI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetPCI)
{
    ui->setupUi(this);

    /******** 初始化标签页 ********/
    ui->m_tbwSS->setCurrentIndex(0);

    /******** 初始化药物表 ********/
    QStringList sHeaderYW = QString("Id,名称,规格,单位,库存").split(',');
    m_modelYW= new QStandardItemModel();
    m_modelYW->setHorizontalHeaderLabels(sHeaderYW);
    //载入模型
    ui->m_tblvYW->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->m_tblvYW->setModel(m_modelYW);
    ui->m_tblvYW->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblvYW->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblvYW->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblvYW->setColumnWidth(0,30);
    ui->m_tblvYW->horizontalHeader()->setStretchLastSection(1);
    ui->m_tblvYW->show();

    /******** 初始化给药 ********/
    QStringList slstGYFS=QString("IC,IA,IV,IM,Oral").split(',');
    for(int i=0;i<slstGYFS.size();i++)
    {
        ui->m_cmbGYFS->addItem(slstGYFS[i]);
    }
    ui->m_lineGYMC->setReadOnly(1);

    /******** 初始化器材表 ********/
    QStringList sHeaderQC = QString("类别").simplified().split(",");
    m_modelQC= new QStandardItemModel();
    m_modelQC->setHorizontalHeaderLabels(sHeaderQC);
    //载入模型
    ui->m_treevQC->setModel(m_modelQC);
    ui->m_treevQC->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_treevQC->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_treevQC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_treevQC->header()->setStretchLastSection(1);
    ui->m_treevQC->show();


    /******** 初始化手术操作 ********/
    QStringList slstCZJ=QString("鞘,导管,导丝").split(',');
    for(int i=0;i<slstCZJ.size();i++)
    {
        ui->m_cmbCZJ->addItem(slstCZJ[i]);
    }

    QStringList slstCZXG=QString("RCA,RPDA,RPLS,LM,LAD,D1,D2,LCX,LMD,S1,S1,PL,LPDA,LPLS,Ramus").split(',');
    for(int i=0;i<slstCZXG.size();i++)
    {
        ui->m_cmbCZXG->addItem(slstCZXG[i]);
    }

    QStringList slstCZXGWZ=QString("开口,近段,中段,远段,近端,远端,近中段,中远段,全程,病变处,开口病变处,近段病变处,中段病变处,远段病变处,近中段病变处").split(',');
    for(int i=0;i<slstCZXGWZ.size();i++)
    {
        ui->m_cmbCZXGWZ->addItem(slstCZXGWZ[i]);
    }
    const int nCZCS=10;
    for(int i=0;i<nCZCS;i++)
    {
        QString sCZCS=QString::number(i);
        ui->m_cmbCZCS->addItem(sCZCS);
    }

    QStringList slstCZFS=QString("扩张,颈扩张,释放支架,扩支架,后扩张,对吻").split(',');
    for(int i=0;i<slstCZFS.size();i++)
    {
        ui->m_cmbCZFS->addItem(slstCZFS[i]);
    }

    /******** 初始化快捷用语表 ********/
    m_modelKJYY = new QStandardItemModel();
    QStringList sHeaderKJYY = QString("常用快捷用语").simplified().split(",");
    m_modelKJYY->setHorizontalHeaderLabels(sHeaderKJYY);
    ui->m_tblvKJYY->setModel(m_modelKJYY);
    ui->m_tblvKJYY->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblvKJYY->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblvKJYY->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblvKJYY->horizontalHeader()->setStretchLastSection(1);
    ui->m_tblvKJYY->show();

    /******** 初始化手术记录表 ********/
    m_modelSSJL = new QStandardItemModel();
    QStringList sHeaderSSJL = QString("时间,记录内容").simplified().split(",");
    m_modelSSJL->setHorizontalHeaderLabels(sHeaderSSJL);

    ui->m_tblvSSJL->setModel(m_modelSSJL);
    ui->m_tblvSSJL->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->m_tblvSSJL->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblvSSJL->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblvSSJL->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblvSSJL->setColumnWidth(0,180);
    ui->m_tblvSSJL->setColumnWidth(1,300);
    ui->m_tblvSSJL->horizontalHeader()->setStretchLastSection(1);
    ui->m_tblvSSJL->show();



    /******** 初始化病变信息 ********/
    ui->m_radSQXZ50->setChecked(1);
    ui->m_radSQTIMI0->setChecked(1);
    ui->m_radDSTGBBS->setChecked(1);
    ui->m_radCYXZ10->setChecked(1);
    ui->m_radSHTIMI0->setChecked(1);
    ui->m_radSZBFZW->setChecked(1);
    /******** 初始化术中并发症 ********/
    ui->m_radSZBFZW->setChecked(1);
    ui->m_wgtSZBFZ->setEnabled(0);
    /******** 初始化病变特点 ********/
    QStringList slstNameBB=QString("一般病变,分叉病变,钙化病变,血栓病变,桥血管病变,完全闭塞病变,小血管<2.5mm,长病变>20mm,支架内在狭窄").split(',');
    for(int i=0;i<slstNameBB.size();i++)
    {
        ui->m_cmbBBTD->addItem(slstNameBB[i]);
    }
}

CWidgetPCI::~CWidgetPCI()
{
    delete ui;
}

/**
 * @brief CWidgetPCI::SetSysCaseId
 * @param pSysCaseId
 */
void CWidgetPCI::SetSysCaseId(const QString pSysCaseId)
{
    m_sSysCaseId=pSysCaseId;
    this->SetSqDB();
}

/**
 * @brief CWidgetPCI::UpdateUIFromDatabase
 */
void CWidgetPCI::UpdateUIFromDatabase()
{
    this->SetSqDbBB();
}

/**
 * @brief CWidgetPCI::UpdateDatabaseFromUI
 */
void CWidgetPCI::UpdateDatabaseFromUI()
{
    this->UpdateSqDB();
    this->UpdateReportTable();
}

/**
 * @brief CWidgetPCI::UpdateReportTable
 */
void CWidgetPCI::UpdateReportTable()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sPciRec="";
    QString sSqlReport="select Rec from SurgProc_new_T where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReport);
    while(sqlReport->next())
    {
        sPciRec+=sqlReport->value(0).toString();
    }

    sSqlReport="update operateitem set pci='"+sPciRec+"' where SysCaseID ='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReport);

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 数据库读取
 */
void CWidgetPCI::SetSqDB()
{
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetCathLabStock());

    /******** 初始化药物 ********/
    // 这里只显示有库存的药物
    int nNumberHeader=m_modelYW->columnCount();
    QString sSqlPciYw="select ID,LeeName,Style,Unit,Stock_Num from Lee_StockIndex where Stock_Num>0";
    sqlStorge->exec(sSqlPciYw);
    m_lstYW.clear();
    while(sqlStorge->next())
    {
        QList<QString>lstYwRec;
        for (int i=0;i<nNumberHeader;i++)
        {
            QString sAns=sqlStorge->value(i).toString();
            lstYwRec.push_back(sAns);
        }
        m_lstYW.push_back(lstYwRec);
    }


    /******** 初始化器材类别 ********/
    QString sSqlPciQC="select Tv_Name,Tv_Parent from ToolTree_T";
    sqlStorge->exec(sSqlPciQC);
    m_vNameTool.clear();
    while (sqlStorge->next())
    {
        QString sAnsName=sqlStorge->value(0).toString();
        int nAnsParent=sqlStorge->value(1).toInt();
        STreeNode sNode={sAnsName,nAnsParent};
        m_vNameTool.push_back(sNode);
    }

    /******** 初始化器材信息 ********/
    QString sSqlToolInfo="select Full_Name,Std3 from StockIndex_T";
    sqlStorge->exec(sSqlToolInfo);
    m_lstToolInfo.clear();
    while (sqlStorge->next())
    {
        SToolInfo sAnsTool={sqlStorge->value(0).toString(),sqlStorge->value(1).toString().split("->")};
        m_lstToolInfo.append(sAnsTool);
    }


    ////////////////////////////////////////////////////////////////////////////
    /// \brief sqlReport
    ///
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());


    /******** 初始化患者体征 ********/
    QString sSqlHZTZ="select HR,TEMP,NIBP,SPO2,IBP_1,IBP_2,IBP_3,IBP_4 from Patient_sign where SystemCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlHZTZ);
    while (sqlReport->next())
    {
        m_sHR=sqlReport->value(0).toString();
        m_sTEMP=sqlReport->value(1).toString();
        m_slstNIBP=sqlReport->value(2).toString().simplified().split("/");
        m_sSPO2=sqlReport->value(3).toString();
        m_slstIBP1=sqlReport->value(4).toString().simplified().split("/");
        m_slstIBP2=sqlReport->value(5).toString().simplified().split("/");
        m_slstIBP3=sqlReport->value(6).toString().simplified().split("/");
        m_slstIBP4=sqlReport->value(7).toString().simplified().split("/");
    }

    /******** 初始化患者术中状态 ********/
    QString sSqlHZSZZT="select SZZT from CathBook_T where SZZT is not null";
    sqlReport->exec(sSqlHZSZZT);
    m_lstSZZT.clear();
    while (sqlReport->next())
    {
        QString sSZZT=sqlReport->value(0).toString();
        if(sSZZT!="")
        {
            m_lstSZZT.push_back(sSZZT);
        }
    }

    /******** 初始化快捷用语 ********/
    QString sSqlKJYY="select KJYY from CathBook_T where KJYY is not null";
    sqlReport->exec(sSqlKJYY);
    m_lstKJYY.clear();
    while (sqlReport->next())
    {
        QString sKJYY=sqlReport->value(0).toString();
        if(sKJYY!="")
        {
            QList<QString>lstAns;
            lstAns.push_back(sKJYY);
            m_lstKJYY.push_back(lstAns);
        }
    }

    /******** 初始化手术记录 ********/
    QString sSqlSSJL="select PatiDateTime,Rec from SurgProc_new_T where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlSSJL);
    m_lstSSJL.clear();
    while (sqlReport->next())
    {
        QString sDataTime=sqlReport->value(0).toString();
        QString sRec=sqlReport->value(1).toString();
        QList<QString>lstRec;
        lstRec.push_back(sDataTime);
        lstRec.push_back(sRec);
        m_lstSSJL.push_back(lstRec);
    }

    delete sqlStorge;
    sqlStorge=NULL;
    delete sqlReport;
    sqlReport=NULL;

    // 更新UI页面
    this->UpdateShow();

    // 更新病变
    this->SetSqDbBB();
}

/**
 * @brief CWidgetPCI::SetSqBBDB
 */
void CWidgetPCI::SetSqDbBB()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    /******** 记录病变血管 ********/
    QString sSqlBBXG="select bbzywz from BB_BB where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlBBXG);
    m_slstGYXG.clear();
    while (sqlReport->next())
    {
        m_slstGYXG.append(sqlReport->value(0).toString());
    }
    m_slstGYXG.removeDuplicates();

    /******** 记录病变信息 ********/
    QString sSqlBBInfo="select xgmc,bbtd,sqxzcd,timi,dssftgbb,bbcyxz,shtimi,SZBFZ from PCI_ZBB_FB1_T where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlBBInfo);
    m_lstBBInfo.clear();
    while (sqlReport->next())
    {
        SBBInfo sBBInfo;
        sBBInfo.sBBName=sqlReport->value(0).toString();
        sBBInfo.sBBTD=sqlReport->value(1).toString();
        sBBInfo.sSQXZ=sqlReport->value(2).toString();
        sBBInfo.sSQTimi=sqlReport->value(3).toString();
        sBBInfo.sDSTGBB=sqlReport->value(4).toString();
        sBBInfo.sBBCYXZ=sqlReport->value(5).toString();
        sBBInfo.sSHTimi=sqlReport->value(6).toString();
        sBBInfo.sSZBFZ=sqlReport->value(7).toString();
        m_lstBBInfo.push_back(sBBInfo);
    }

    delete sqlReport;
    sqlReport=NULL;

    this->UpdateBBShow();
}

/**
 * @brief CWidgetPCI::UpdateBBShow
 */
void CWidgetPCI::UpdateBBShow()
{
    /******** 初始化靶血管 ********/
    this->InitComboBoxGYXG(ui->m_cmbGYXGMC,m_slstGYXG);

    /******** 初始化病变信息 ********/
    QString sCurrXG=ui->m_cmbGYXGMC->currentText();
    if(sCurrXG!="")
    {
        this->InitBBInfo(sCurrXG);
    }
}

/**
 * @brief CWidgetPCI::UpdateSqDB
 */
void CWidgetPCI::UpdateSqDB()
{
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetCathLabStock());



    ////////////////////////////////////////////////////////////////////////////
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    QString sSqlClearCol="update CathBook_T set SZZT = null";
    sqlReport->exec(sSqlClearCol);
    /******** 更新术中状态 ********/
    for (int i=0;i<ui->m_lstwSZZT->count();i++)
    {
        QString sId=QString::number(i+1);
        QString sValue=ui->m_lstwSZZT->item(i)->text();
        QString sSqlSZZT="update CathBook_T set SZZT ='"+sValue+"' where id ="+sId;
        sqlReport->exec(sSqlSZZT);
    }


    /******** 更新快捷用语 ********/
    sSqlClearCol="update CathBook_T set KJYY = null";
    sqlReport->exec(sSqlClearCol);
    for (int i=0;i<m_modelKJYY->rowCount();i++)
    {
        QString sId=QString::number(i+1);
        QString sValue=m_modelKJYY->item(i)->text();
        QString sSqlKJYY="update CathBook_T set KJYY ='"+sValue+"' where id ="+sId;
        sqlReport->exec(sSqlKJYY);
    }


    /******** 更新手术记录 ********/
    sSqlClearCol="delete from SurgProc_new_T where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlClearCol);
    for (int i=0;i<m_modelSSJL->rowCount();i++)
    {
        QString sId=QString::number(i+1);

        QString sDataTime=m_modelSSJL->item(i,0)->text();
        QDateTime dtmRec=QDateTime::fromString(sDataTime, "yyyy-MM-dd hh:mm:ss");;
        QString sRec=m_modelSSJL->item(i,1)->text();
        QString sSysCaseId=m_sSysCaseId;

        QString sSqlSSJL="insert into SurgProc_new_T(PatiDateTime,Rec,SysCaseID) values('"+sDataTime+"','"+sRec+"','"+sSysCaseId+"')";
        sqlReport->exec(sSqlSSJL);
    }


    /******** 更新患者体征 ********/
    QString sHR=ui->m_lineHR->text();
    QString sTEMP=ui->m_lineTEMP->text();
    QString sNIBP=ui->m_lineNIBP1->text()+"/"+ui->m_lineNIBP2->text()+"/"+ui->m_lineNIBP3->text();
    QString sSPO2=ui->m_lineSPO2->text();
    QString sIBP1=ui->m_lineP11->text()+"/"+ui->m_lineP12->text()+"/"+ui->m_lineP13->text();
    QString sIBP2=ui->m_lineP21->text()+"/"+ui->m_lineP22->text()+"/"+ui->m_lineP23->text();
    QString sIBP3=ui->m_lineP31->text()+"/"+ui->m_lineP32->text()+"/"+ui->m_lineP33->text();
    QString sIBP4=ui->m_lineP41->text()+"/"+ui->m_lineP42->text()+"/"+ui->m_lineP43->text();
    QString sSqlHZTZ="update Patient_sign set HR='"+sHR+"',TEMP='"+sTEMP+"',NIBP='"+sNIBP+"',SPO2='"+sSPO2+"',IBP_1='"+sIBP1+"',IBP_2='"+sIBP2+"',IBP_3='"+sIBP3+"',IBP_4='"+sIBP4+"' where SystemCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlHZTZ);


    delete sqlStorge;
    sqlStorge=NULL;
    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief CWidgetPCI::InitBBInfo
 */
void CWidgetPCI::InitBBInfo(QString pName)
{
    QString sGYXG=pName;

    int nVesselId=-1;
    for (int i=0;i<m_lstBBInfo.size();i++)
    {
        if(m_lstBBInfo[i].sBBName==sGYXG)
        {
            nVesselId=i;
        }
    }

    if(nVesselId<0)
    {
        ui->m_radSQXZ50->setChecked(1);
        ui->m_radSQTIMI0->setChecked(1);
        ui->m_radDSTGBBS->setChecked(1);
        ui->m_radCYXZ10->setChecked(1);
        ui->m_radSHTIMI0->setChecked(1);
        ui->m_radSZBFZW->setChecked(1);
        ui->m_wgtSZBFZ->setEnabled(0);
        return;
    }



    /******** 初始化病变特点 ********/
    this->InitComboBox(ui->m_cmbBBTD,m_lstBBInfo[nVesselId].sBBTD);

    /******** 初始化术前狭窄程度 ********/
    this->InitGroupBox(ui->m_grpSQXZCD,m_lstBBInfo[nVesselId].sSQXZ);

    /******** 初始化术前TIMI ********/
    this->InitGroupBox(ui->m_grpSQTIMI,m_lstBBInfo[nVesselId].sSQTimi);

    /******** 初始化导丝是否通过病变 ********/
    this->InitGroupBox(ui->m_grpDSTGBB,m_lstBBInfo[nVesselId].sDSTGBB);

    /******** 初始化病变残余狭窄 ********/
    this->InitGroupBox(ui->m_grpBBCYXZ,m_lstBBInfo[nVesselId].sBBCYXZ);

    /******** 初始化术后TIMI ********/
    this->InitGroupBox(ui->m_grpSHTIMI,m_lstBBInfo[nVesselId].sSHTimi);

    /******** 初始化术中并发症 ********/
    if(m_lstBBInfo[nVesselId].sSZBFZ=="否")
    {
        this->InitGroupBox(ui->m_grpSZBFZ,"否");
        ui->m_wgtSZBFZ->setEnabled(0);
    }
    else
    {
        this->InitGroupBox(ui->m_grpSZBFZ,"是");
        ui->m_wgtSZBFZ->setEnabled(1);
        QStringList slstBFZ=m_lstBBInfo[nVesselId].sSZBFZ.simplified().split("/");
        for (int i=0;i<slstBFZ.size();i++)
        {
            this->InitGroupCkbBtn(ui->m_wgtSZBFZ,slstBFZ[i]);
        }
    }
}


/**
 * @brief 将数据中的查询结果显示至UI
 */
void CWidgetPCI::UpdateShow()
{
    /******** 初始化药物 ********/
    this->InitItemModel(m_modelYW,m_lstYW);

    /******** 初始化器材 ********/
    this->InitTreeView(ui->m_treevQC);

    /******** 初始化患者体征 ********/
    ui->m_lineHR->setText(m_sHR);
    ui->m_lineTEMP->setText(m_sTEMP);
    this->InitLineEdit(ui->m_lineNIBP1,m_slstNIBP,0);
    this->InitLineEdit(ui->m_lineNIBP2,m_slstNIBP,1);
    this->InitLineEdit(ui->m_lineNIBP3,m_slstNIBP,2);
    ui->m_lineSPO2->setText(m_sSPO2);
    this->InitLineEdit(ui->m_lineP11,m_slstIBP1,0);
    this->InitLineEdit(ui->m_lineP12,m_slstIBP1,1);
    this->InitLineEdit(ui->m_lineP13,m_slstIBP1,2);
    this->InitLineEdit(ui->m_lineP21,m_slstIBP2,0);
    this->InitLineEdit(ui->m_lineP22,m_slstIBP2,1);
    this->InitLineEdit(ui->m_lineP23,m_slstIBP2,2);
    this->InitLineEdit(ui->m_lineP31,m_slstIBP3,0);
    this->InitLineEdit(ui->m_lineP32,m_slstIBP3,1);
    this->InitLineEdit(ui->m_lineP33,m_slstIBP3,2);
    this->InitLineEdit(ui->m_lineP41,m_slstIBP4,0);
    this->InitLineEdit(ui->m_lineP42,m_slstIBP4,1);
    this->InitLineEdit(ui->m_lineP43,m_slstIBP4,2);

    /******** 初始化术中状态 ********/
    this->InitListWidget(ui->m_lstwSZZT,m_lstSZZT);

    /******** 初始化快捷用语 ********/
    this->InitItemModel(m_modelKJYY,m_lstKJYY);

    /******** 初始化手术记录 ********/
    this->InitItemModel(m_modelSSJL,m_lstSSJL);

}

/**
 * @brief 判断pA是不是pB的子串
 * @param pA
 * @param pB
 */
int CWidgetPCI::IsSubsequence(QString pA, QString pB)
{
    int nLengthA=pA.length();
    int nLengthB=pB.length();

    int i=0,j=0;

    while (i<nLengthA&&j<nLengthB)
    {
        if(pA[i]==pB[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j=j-i+1;
            i=0;
        }
    }
    if(i>=nLengthA)
    {
        return j-nLengthA;
    }
    return -1;
}

/**
 * @brief 删除头尾的空格
 * @param pStr
 * @return
 */
QString CWidgetPCI::DelHeadRearSpace(QString pStr)
{
    // 先判断是不是只有空格
    int nCount=0;
    for (int i=0;i<pStr.length();i++)
    {
        if(pStr[i]==32)
        {
            nCount++;
        }
    }
    QString sTemp="";
    if(nCount==pStr.length())
    {
        return sTemp;
    }

    int nStart=0,nEnd=0;
    for (int i=0;i<pStr.length();i++)
    {
        if(pStr[i]!=32)
        {
            nStart=i;
            break;
        }
    }
    for (int i=pStr.length()-1;i>=0;i--)
    {
        if(pStr[i]!=32)
        {
            nEnd=i;
            break;
        }
    }
    for (int i=nStart;i<=nEnd;i++)
    {
        sTemp+=pStr[i];
    }
    return sTemp;
}

/**
 * @brief CWidgetPCI::InitGroupBox
 */
void CWidgetPCI::InitGroupBox(QGroupBox*pGroupBox,QString pAns)
{
    QObjectList alistGroup=pGroupBox->children();
    for(int i=0;i<alistGroup.length();i++)
    {
        if(alistGroup.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(alistGroup.at(i));
            QString sControl=aControl->text();
            QString sAnsTemp=this->DelHeadRearSpace(pAns);
            if(sControl==sAnsTemp)
            {
                aControl->setChecked(1);
                break;
            }
        }
    }
}

/**
 * @brief CWidgetPCI::InitComboBox
 * @param pComboBox
 * @param pAns
 */
void CWidgetPCI::InitComboBox(QComboBox *pComboBox, QString pAns)
{
    for(int i=0;i<pComboBox->count();i++)
    {
        QString sControl=pComboBox->itemText(i);
        QString sAnsTemp=this->DelHeadRearSpace(pAns);
        if(sControl==sAnsTemp)
        {
            pComboBox->setCurrentIndex(i);
            break;
        }
    }
}

/**
 * @brief CWidgetPCI::InitComboBoxGYXG
 * @param pComboBox
 * @param pList
 */
void CWidgetPCI::InitComboBoxGYXG(QComboBox *pComboBox, QStringList pList)
{
    // 先清空combobox
    for(int i=0;i<pComboBox->count();i++)
    {
        pComboBox->removeItem(i);
    }
    pComboBox->clear();

    for(int i=0;i<pList.size();i++)
    {
        pComboBox->addItem(pList[i]);
    }
    pComboBox->setCurrentIndex(-1);
}

/**
 * @brief CWidgetPCI::InitGroupCkbBtn
 * @param pWidget
 * @param pAns
 */
void CWidgetPCI::InitGroupCkbBtn(QWidget *pWidget, QString pAns)
{
    QObjectList alistGroup=pWidget->children();
    for(int i=0;i<alistGroup.length();i++)
    {
        if(alistGroup.at(i)->inherits("QCheckBox"))
        {
            auto aControl=qobject_cast<QCheckBox*>(alistGroup.at(i));
            QString sControl=aControl->text();
            if(sControl==pAns)
            {
                aControl->setChecked(1);
                break;
            }
        }
    }
}

/**
 * @brief CWidgetPCI::InitItemModel
 * @param pItemModel
 * @param plstStr
 */
void CWidgetPCI::InitItemModel(QStandardItemModel*pItemModel,QList<QList<QString>>plstStr)
{
    // 先清空模型
    for(int i = 0;i<pItemModel->rowCount();i++)
    {
        pItemModel->removeRow(i);
    }
    pItemModel->setRowCount(0);

    // 重新设置模型
    for(int i=0;i<plstStr.size();i++)
    {
        for (int j=0;j<plstStr[i].size();j++)
        {
            pItemModel->setItem(i,j,new QStandardItem(plstStr[i][j]));
        }
    }
}

/**
 * @brief CWidgetPCI::InitListWidget
 * @param pListWidget
 * @param plstStr
 */
void CWidgetPCI::InitListWidget(QListWidget *pListWidget, QList<QString> plstStr)
{
    pListWidget->clear();
    for(int i=0;i<plstStr.size();i++)
    {
        pListWidget->addItem(plstStr[i]);
    }
}

/**
 * @brief 层次遍历构造树
 * @param pRoot
 */
void CWidgetPCI::InitTreeNode(int pRoot)
{

    QList<QStandardItem*> lstRootNode1;
    QStandardItem* itemNode1 = new QStandardItem(m_vNameTool[pRoot].sName);
    lstRootNode1.append(itemNode1);
    m_modelQC->appendRow(lstRootNode1);

    queue<int>qLevel1;
    qLevel1.push(pRoot);

    queue<QStandardItem*>qItemNode;
    qItemNode.push(itemNode1);

    while (!qLevel1.empty())
    {
        auto itemTempNode=qItemNode.front();
        qItemNode.pop();
        int nIdTemp=qLevel1.front();
        qLevel1.pop();

        for (int j=0;j<m_vNameTool.size();j++)
        {
            if(m_vNameTool[j].nParent==nIdTemp)
            {
                qLevel1.push(j);

                QList<QStandardItem*> items2;
                QStandardItem* item2 = new QStandardItem(m_vNameTool[j].sName);
                items2.append(item2);
                itemTempNode->appendRow(items2);
                qItemNode.push(item2);
            }
        }
    }
}

/**
 * @brief CWidgetPCI::InitTreeView
 * @param pTreeView
 * @param pTreeNode
 */
void CWidgetPCI::InitTreeView(QTreeView *pTreeView)
{
    //    // 结点深度
    //    int *nNodeLevel=new int[m_vNameTool.size()];
    //    for (int i=0;i<m_vNameTool.size();i++)
    //    {
    //        int nNumberLevel=1;
    //        int nCurr=i;
    //        while (m_vNameTool[nCurr].nParent!=-1)
    //        {
    //            nCurr=m_vNameTool[nCurr].nParent;
    //            ++nNumberLevel;
    //        }
    //        nNodeLevel[i]=nNumberLevel;
    //    }

    //    // 最大层数
    //    int nMaxLevel=-999999;
    //    for (int i=0;i<m_vNameTool.size();i++)
    //    {
    //        if(nNodeLevel[i]>nMaxLevel)
    //        {
    //            nMaxLevel=nNodeLevel[i];
    //        }
    //    }

    // 清空
    for (int i=0;i<m_modelQC->rowCount();i++)
    {
        auto aItem=m_modelQC->item(i);

        for (int j=0;j<aItem->rowCount();j++)
        {
            aItem->removeRow(j);
        }
    }
    // 先构造器材类别数目
    // 遍历时，先找到是哪颗树上的结点

    // 构造森林的根节点
    vector<int>vRootNode;
    for (int i=0;i<m_vNameTool.size();i++)
    {
        if(m_vNameTool[i].nParent==-1)
        {
            vRootNode.push_back(i);
        }
    }
    // 这里采用层次遍历构造森林
    for (int i=0;i<vRootNode.size();i++)
    {
        this->InitTreeNode(vRootNode[i]);
    }


    // 遍历每一条的属性
    for(int i=0;i<m_lstToolInfo.size();i++)
    {
        QString sTypeRoot=m_lstToolInfo[i].sType[0];
        auto aRoot=this->FindToolRoot(sTypeRoot);

        auto aTempNode=aRoot;

        // 遍历其余属性
        for(int j=1;j<m_lstToolInfo[i].sType.size();j++)
        {
            QString sType=m_lstToolInfo[i].sType[j];
            aTempNode=this->FindPriorNode(aTempNode,sType);
        }

        QList<QStandardItem*> lstItems;
        QStandardItem* item2 = new QStandardItem(m_lstToolInfo[i].sName);
        lstItems.append(item2);
        aTempNode->appendRow(lstItems);

    }
}

/**
 * @brief CWidgetPCI::InitLineEdit
 * @param pLineEdit
 * @param pAns
 * @param pId
 */
void CWidgetPCI::InitLineEdit(QLineEdit *pLineEdit, QStringList pAns, int pId)
{
    int nLength=pAns.length();
    if(pId<nLength)
    {
        pLineEdit->setText(pAns[pId]);
    }else
    {
        pLineEdit->setText("");
    }
}

/**
 * @brief CWidgetPCI::GetTextIsPressedGroupRadBtn
 * @param pGroupBox
 * @return
 */
QString CWidgetPCI::GetTextIsPressedGroupRadBtn(QGroupBox *pGroupBox)
{
    QString sTemp="";
    QObjectList alistGroup=pGroupBox->children();
    for(int i=0;i<alistGroup.length();i++)
    {
        if(alistGroup.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(alistGroup.at(i));
            if(aControl->isChecked())
            {
                sTemp=aControl->text();
            }
        }
    }
    return sTemp;
}

/**
 * @brief CWidgetPCI::从组Widget中得到所有checkbox的text
 * @param pWidget
 * @return
 */
QString CWidgetPCI::GetTextIsPressedGroupCkbBtn(QWidget *pWidget)
{
    QString sTemp="";
    QObjectList alistGroup=pWidget->children();
    for(int i=0;i<alistGroup.length();i++)
    {
        if(alistGroup.at(i)->inherits("QCheckBox"))
        {
            auto aControl=qobject_cast<QCheckBox*>(alistGroup.at(i));
            if(aControl->isChecked())
            {
                sTemp+=aControl->text()+"/";
            }
        }
    }
    sTemp=sTemp.left(sTemp.length()-1);
    return sTemp;
}

/**
 * @brief CWidgetPCI::FindToolRoot
 * @param pType
 */
QStandardItem *CWidgetPCI::FindToolRoot(QString pType)
{
    for (int i=0;i<m_modelQC->rowCount();i++)
    {
        QStandardItem*itemRoot=m_modelQC->item(i);
        QString sRoot=itemRoot->text();
        if(pType==sRoot)
        {
            return itemRoot;
        }
    }
    return NULL;
}

/**
 * @brief CWidgetPCI::FindPriorNode
 * @param pType
 * @return
 */
QStandardItem *CWidgetPCI::FindPriorNode(QStandardItem *pCurrNode,QString pType)
{
    // 这里采用层次遍历
    queue<QStandardItem*>qTool;
    qTool.push(pCurrNode);

    while (!qTool.empty())
    {
        auto aFront=qTool.front();
        qTool.pop();

        if(aFront->text()==pType)
        {
            return aFront;
        }

        for (int j=0;j<aFront->rowCount();j++)
        {
            qTool.push(aFront->child(j));
        }
    }
    return NULL;
}

/**
 * @brief CWidgetPCI::on_m_grpGYXG_clicked
 * @param checked
 */
//void CWidgetPCI::on_m_grpGYXG_clicked(bool checked)
//{
//    if (checked)
//    {
//        ui->m_grpGYXG->setFlat(true);
//        //ui->m_grpGYXG->

//        auto alistCon=ui->m_grpGYXG->children();
//        for(int i=0;i<alistCon.length();i++)
//        {
//            if(alistCon.at(i)->inherits("QWidget"))
//            {
//                qobject_cast<QWidget*>(alistCon.at(i))->setVisible(false);
//            }
//        }

//    }
//    else
//    {
//        //隐藏垂直边框
//        ui->m_grpGYXG->setFlat(false);
//        auto alistCon=ui->m_grpGYXG->children();
//        for(int i=0;i<alistCon.length();i++)
//        {
//            if(alistCon.at(i)->inherits("QWidget"))
//            {
//                qobject_cast<QWidget*>(alistCon.at(i))->setVisible(true);
//            }
//        }
//    }
//}

/**
 * @brief CWidgetPCI::on_m_radSZBFZW_clicked
 * @param checked
 */
void CWidgetPCI::on_m_radSZBFZW_clicked(bool checked)
{
    if (checked)
    {
        ui->m_wgtSZBFZ->setEnabled(0);
    }
}

/**
 * @brief CWidgetPCI::on_m_radSZBFZY_clicked
 * @param checked
 */
void CWidgetPCI::on_m_radSZBFZY_clicked(bool checked)
{
    if (checked)
    {
        ui->m_wgtSZBFZ->setEnabled(1);
    }
}

/**
 * @brief CWidgetPCI::on_tableView_doubleClicked
 * @param index
 */
void CWidgetPCI::on_m_tblvYW_doubleClicked(const QModelIndex &index)
{
    //QString("ID,名称,规格,单位,库存")

    ui->m_lineGYMC->setText(m_modelYW->item(index.row(),1)->text());
    ui->m_lineGYDW->setText(m_modelYW->item(index.row(),3)->text());
}

/**
 * @brief CWidgetPCI::干预血管
 */
void CWidgetPCI::on_m_btnGY_clicked()
{
    QString sGYXG=ui->m_cmbGYXGMC->currentText();
    if(sGYXG=="")
    {
        QMessageBox::information(NULL,"提示","没有靶血管",QMessageBox::Ok);
        return;
    }

    int nNumRec=m_modelSSJL->rowCount();

    QDateTime *dtmCurr = new QDateTime(QDateTime::currentDateTime());
    QString sCurrDataTime = dtmCurr->toString("yyyy-MM-dd hh:mm:ss");
    QString sSSJL="对"+sGYXG+"进行干预";
    m_modelSSJL->setItem(nNumRec,0,new QStandardItem(sCurrDataTime));
    m_modelSSJL->setItem(nNumRec,1,new QStandardItem(sSSJL));

}

/**
 * @brief CWidgetPCI::将快捷记录添加至手术记录
 * @param index
 */
void CWidgetPCI::on_m_tblvKJYY_doubleClicked(const QModelIndex &index)
{
    int nNumRec=m_modelSSJL->rowCount();

    QDateTime *dtmCurr = new QDateTime(QDateTime::currentDateTime());
    QString sCurrDataTime = dtmCurr->toString("yyyy-MM-dd hh:mm:ss");

    QString sKJYY=m_modelKJYY->item(index.row(),0)->text();

    m_modelSSJL->setItem(nNumRec,0,new QStandardItem(sCurrDataTime));
    m_modelSSJL->setItem(nNumRec,1,new QStandardItem(sKJYY));
}

/**
 * @brief CWidgetPCI::将手中状态添加至手术记录
 * @param item
 */
void CWidgetPCI::on_m_lstwSZZT_itemDoubleClicked(QListWidgetItem *item)
{
    int nNumRec=m_modelSSJL->rowCount();
    //item->setFlags(Qt::NoItemFlags);
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));

    QDateTime *dtmCurr = new QDateTime(QDateTime::currentDateTime());
    QString sCurrDataTime = dtmCurr->toString("yyyy-MM-dd hh:mm:ss");

    QString sSZZT=item->text();

    m_modelSSJL->setItem(nNumRec,0,new QStandardItem(sCurrDataTime));
    m_modelSSJL->setItem(nNumRec,1,new QStandardItem(sSZZT));
}

/**
 * @brief CWidgetPCI::on_m_btnSZZTZJ_clicked
 */
void CWidgetPCI::on_m_btnSZZTZJ_clicked()
{
    // 计算当前可编辑的行号
    int nCurrId=ui->m_lstwSZZT->count();
    // 获取末尾
    QString sRear=this->DelHeadRearSpace(ui->m_lstwSZZT->item(nCurrId-1)->text());
    if(sRear=="")
    {
        nCurrId--;
    }
    // 如果之前插入了空item 这里进行删除操作
    if(ui->m_lstwSZZT->item(nCurrId)!=NULL)
    {
        ui->m_lstwSZZT->takeItem(nCurrId);
    }

    // 先增加一个新的item
    ui->m_lstwSZZT->addItem(new QListWidgetItem(""));
    ui->m_lstwSZZT->setCurrentRow(nCurrId);

    QListWidgetItem *itemList=ui->m_lstwSZZT->item(nCurrId);
    itemList->setFlags(itemList->flags() | Qt::ItemIsEditable);
    ui->m_lstwSZZT->setFocus();
    ui->m_lstwSZZT->editItem(itemList);


    // 过滤已经添加过的
    //    for(int i=0;i<spfcount; i++)
    //    {
    //        for(int j=0;j<nspfcount;j++)
    //        {
    //            if(spFileNames.value(j)==ui->SPList->item(i)->text())
    //            {
    //                QMessageBox::information(NULL,"样本文件选择",tr("%1此样本文件已添加").arg(spFileNames.value(j)));
    //                return;
    //            }
    //        }
    //    }
}

/**
 * @brief CWidgetPCI::on_m_btnSZZTSC_clicked
 */
void CWidgetPCI::on_m_btnSZZTSC_clicked()
{
    auto nCurrId=ui->m_lstwSZZT->currentIndex().row();
    if(nCurrId>-1)
    {
        ui->m_lstwSZZT->takeItem(nCurrId);
    }
}

/**
 * @brief CWidgetPCI::on_m_btnSZZTXG_clicked
 */
void CWidgetPCI::on_m_btnSZZTXG_clicked()
{
    // 当前可编辑的行号
    int nCurrId=ui->m_lstwSZZT->currentIndex().row();
    if(nCurrId<0)
    {
        return;
    }
    QListWidgetItem *itemList=ui->m_lstwSZZT->item(nCurrId);
    itemList->setFlags(itemList->flags() | Qt::ItemIsEditable);
    ui->m_lstwSZZT->setFocus();
    ui->m_lstwSZZT->editItem(itemList);
}

/**
 * @brief CWidgetPCI::on_m_btnKJYYZJ_clicked
 */
void CWidgetPCI::on_m_btnKJYYZJ_clicked()
{
    // 计算当前行数
    int nCurrId=m_modelKJYY->rowCount();
    // 获取末尾
    QString sRear=this->DelHeadRearSpace(m_modelKJYY->item(nCurrId-1)->text());
    if(sRear=="")
    {
        nCurrId--;
    }
    // 如果之前插入了空item 这里进行删除操作
    if(m_modelKJYY->item(nCurrId)!=NULL)
    {
        m_modelKJYY->takeItem(nCurrId);
    }
    // 先增加一个新的item
    m_modelKJYY->setItem(nCurrId,0,new QStandardItem(""));

    QModelIndex itemId= m_modelKJYY->index(nCurrId,0);
    ui->m_tblvKJYY->setCurrentIndex(itemId);
    ui->m_tblvKJYY->edit(itemId);

    // 过滤已经添加过的
    //    for(int i=0;i<spfcount; i++)
    //    {
    //        for(int j=0;j<nspfcount;j++)
    //        {
    //            if(spFileNames.value(j)==ui->SPList->item(i)->text())
    //            {
    //                QMessageBox::information(NULL,"样本文件选择",tr("%1此样本文件已添加").arg(spFileNames.value(j)));
    //                return;
    //            }
    //        }
    //    }
}

/**
 * @brief CWidgetPCI::on_m_btnKJYYSC_clicked
 */
void CWidgetPCI::on_m_btnKJYYSC_clicked()
{
    auto aCurrId=ui->m_tblvKJYY->currentIndex();
    int nCurrId=aCurrId.row();
    if(nCurrId>-1)
    {
        m_modelKJYY->removeRow(nCurrId);
    }
}

/**
 * @brief CWidgetPCI::on_m_btnKJYYXG_clicked
 */
void CWidgetPCI::on_m_btnKJYYXG_clicked()
{
    int nCurrId=ui->m_tblvKJYY->currentIndex().row();
    if(nCurrId<0)
    {
        return;
    }

    QModelIndex itemId= m_modelKJYY->index(nCurrId,0);
    auto item=m_modelKJYY->item(nCurrId);
    ui->m_tblvKJYY->setCurrentIndex(itemId);
    ui->m_tblvKJYY->edit(itemId);
}

/**
 * @brief 删除选中的手术记录
 */
void CWidgetPCI::on_m_btnSSJLSC_clicked()
{
    int nCurrId=ui->m_tblvSSJL->currentIndex().row();
    if(nCurrId>-1)
    {
        m_modelSSJL->removeRow(nCurrId);
    }
}

/**
 * @brief CWidgetPCI::on_m_btnSSJLXG_clicked
 */
void CWidgetPCI::on_m_btnSSJLXG_clicked()
{
    int nCurrId=ui->m_tblvSSJL->currentIndex().row();
    if(nCurrId<0)
    {
        return;
    }

    QModelIndex itemId= m_modelSSJL->index(nCurrId,1);
    auto item=m_modelSSJL->item(nCurrId);
    ui->m_tblvSSJL->setCurrentIndex(itemId);
    ui->m_tblvSSJL->edit(itemId);
}

/**
 * @brief CWidgetPCI::on_m_btnUpdateDB_clicked
 */
void CWidgetPCI::on_m_btnUpdateDB_clicked()
{
    this->UpdateSqDB();
}

/**
 * @brief CWidgetPCI::器材树双击事件
 * @param index
 */
void CWidgetPCI::on_m_treevQC_doubleClicked(const QModelIndex &index)
{
    QString sQCCurr=m_modelQC->itemData(index).values()[0].toString();
    ui->m_lineCZS->setText(sQCCurr);

    qDebug()<<index.row()<<" "<<index.column();
}

/**
 * @brief CWidgetPCI::on_m_tblvYW_clicked
 * @param index
 */
void CWidgetPCI::on_m_tblvYW_clicked(const QModelIndex &index)
{
    ui->m_lineGYMC->setText("");
    ui->m_lineGYDW->setText("");
    ui->m_dspbGYJL->setValue(0.0);
}

/**
 * @brief CWidgetPCI::on_m_btnSuccess_clicked
 */
void CWidgetPCI::on_m_btnSuccess_clicked()
{
    int nNumRec=m_modelSSJL->rowCount();
    // 将手术操作更新至手术记录
    QDateTime *DateTime = new QDateTime(QDateTime::currentDateTime());
    QString sDateTime = DateTime->toString("yyyy-MM-dd hh:mm:ss");

    QString sCZJ= ui->m_cmbCZJ->currentText();
    QString sCZS= ui->m_lineCZS->text();
    QString sCZXG= ui->m_cmbCZXG->currentText();
    QString sCZXGWZ= ui->m_cmbCZXGWZ->currentText();
    QString sCZAtm= ui->m_spbCZAtm->text();
    QString sCZSpeed= ui->m_spbCZSpeed->text();
    QString sCZFS= ui->m_cmbCZFS->currentText();
    QString sCZCS= ui->m_cmbCZCS->currentText();

    QString sCZRecord="经"+sCZJ+"送"+sCZS+"至"+sCZXG+sCZXGWZ+".以"+sCZAtm+"atm x "+sCZSpeed+"s"+sCZFS+sCZCS+"次.";

    m_modelSSJL->setItem(nNumRec,0,new QStandardItem(sDateTime));
    m_modelSSJL->setItem(nNumRec,1,new QStandardItem(sCZRecord));
}

/**
 * @brief CWidgetPCI::on_m_btnFailure_clicked
 */
void CWidgetPCI::on_m_btnFailure_clicked()
{
    int nNumRec=m_modelSSJL->rowCount();
    // 将手术操作更新至手术记录
    QDateTime *DateTime = new QDateTime(QDateTime::currentDateTime());
    QString sDateTime = DateTime->toString("yyyy-MM-dd hh:mm:ss");

    QString sCZAtm= ui->m_spbCZAtm->text();
    QString sCZSpeed= ui->m_spbCZSpeed->text();
    QString sCZFS= ui->m_cmbCZFS->currentText();
    QString sCZCS= ui->m_cmbCZCS->currentText();

    QString sCZRecord="以"+sCZAtm+"atm x "+sCZSpeed+"s"+sCZFS+sCZCS+"次,未到达指定位置.";

    m_modelSSJL->setItem(nNumRec,0,new QStandardItem(sDateTime));
    m_modelSSJL->setItem(nNumRec,1,new QStandardItem(sCZRecord));
}

/**
 * @brief CWidgetPCI::on_m_btnQDGY_clicked
 */
void CWidgetPCI::on_m_btnQDGY_clicked()
{
    int nNumRec=m_modelSSJL->rowCount();
    QString sGYMC=ui->m_lineGYMC->text();
    if(sGYMC=="")
    {
        QMessageBox::information(NULL,"提示","没有添加药物",QMessageBox::Ok);
        return;
    }

    // 修改库存
    int nCurrRow=ui->m_tblvYW->currentIndex().row();

    QString sCurrId=m_lstYW[nCurrRow][0];

    double dNumUse=ui->m_dspbGYJL->text().toDouble();
    QString sNumUse=ui->m_dspbGYJL->text();

    QString sNumPre=m_modelYW->item(nCurrRow,4)->text();
    double dNumPre=sNumPre.toDouble();
    // 剩余剂量
    double dNumCurr=dNumPre-dNumUse;
    QString sNumCurr=QString::number(dNumCurr);
    m_lstYW[nCurrRow][4]=sNumCurr;
    m_modelYW->item(nCurrRow,4)->setText(sNumCurr);


    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetCathLabStock());
    QString sSqlStorge="update Lee_StockIndex set Stock_Num ='"+sNumCurr+"' where id ='"+sCurrId+"'";
    sqlStorge->exec(sSqlStorge);


    // 将所添加的药物更新至手术记录
    QDateTime *DateTime = new QDateTime(QDateTime::currentDateTime());
    QString sDateTime = DateTime->toString("yyyy-MM-dd hh:mm:ss");

    QString sGYJL=ui->m_dspbGYJL->text();
    QString sGJDW=ui->m_lineGYDW->text();
    QString sGYFS=ui->m_cmbGYFS->currentText();

    QString sGyRecord=QString("给药:%1, %2%3, 方式:%4.").arg(sGYMC).arg(sGYJL).arg(sGJDW).arg(sGYFS);

    m_modelSSJL->setItem(nNumRec,0,new QStandardItem(sDateTime));
    m_modelSSJL->setItem(nNumRec,1,new QStandardItem(sGyRecord));
}

/**
 * @brief 将当前病变保存至数据库
 */
void CWidgetPCI::on_m_btnSave_clicked()
{
    // 首先判断是否被干预过
    QString nCurrVessel=ui->m_cmbGYXGMC->currentText();

    if(nCurrVessel=="")
    {
        QMessageBox::information(NULL,"提示","尚未选择靶血管",QMessageBox::Ok);
        return;
    }

    // 然后判断是否已经被添加至数据库
    // 病变信息
    QString sBBXG=nCurrVessel;
    QString sBBTD=ui->m_cmbBBTD->currentText();;
    QString sSQXZCD=this->GetTextIsPressedGroupRadBtn(ui->m_grpSQXZCD);
    QString sSQTIMI=this->GetTextIsPressedGroupRadBtn(ui->m_grpSQTIMI);
    QString sDSTGBB=this->GetTextIsPressedGroupRadBtn(ui->m_grpDSTGBB);
    QString sBBCYXZ=this->GetTextIsPressedGroupRadBtn(ui->m_grpBBCYXZ);
    QString sSHTIMI=this->GetTextIsPressedGroupRadBtn(ui->m_grpSHTIMI);
    QString sSZBFZ=this->GetTextIsPressedGroupRadBtn(ui->m_grpSZBFZ);
    if(sSZBFZ=="是")
    {
        sSZBFZ=this->GetTextIsPressedGroupCkbBtn(ui->m_wgtSZBFZ);
    }
    QString sXGMC=ui->m_cmbGYXGMC->currentText();
    QString sSSJL="对"+sXGMC+"干预.";

    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    QString sIdCG="";
    QString sSqlFind="select ID from PCI_ZBB_FB1_T where xgmc='"+sXGMC+"' and SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlFind);
    while(sqlReport->next())
    {
        sIdCG=sqlReport->value(0).toString();
    }

    QString sSqlGYXG="";
    if(sIdCG=="")
    {
        sSqlGYXG="insert into PCI_ZBB_FB1_T(SysCaseID,xgmc,bbtd,sqxzcd,timi,dssftgbb,bbcyxz,shtimi,SZBFZ,SurgRecord"
                 ") values('"+m_sSysCaseId+"','"+sBBXG+"','"+sBBTD+"','"+sSQXZCD+"','"+sSQTIMI+"','"+sDSTGBB+"','"+sBBCYXZ+"','"+sSHTIMI+"','"+sSZBFZ+"','"+sSSJL+"')";

    }else
    {
        QMessageBox::information(NULL,"提示","更新当前靶血管信息",QMessageBox::Ok);
        sSqlGYXG="update PCI_ZBB_FB1_T set bbtd='"+sBBTD+"',sqxzcd='"+sSQXZCD+"',timi='"+sSQTIMI+"',dssftgbb='"+sDSTGBB+"',bbcyxz='"+sBBCYXZ+"',shtimi='"+sSHTIMI+"',SZBFZ='"+sSZBFZ+"' where id ="+sIdCG;

    }

    sqlReport->exec(sSqlGYXG);
}

/**
 * @brief CWidgetPCI::on_m_cmbGYXGMC_activated
 * @param index
 */
void CWidgetPCI::on_m_cmbGYXGMC_activated(int index)
{
    QString sCurrXG=ui->m_cmbGYXGMC->currentText();
    if(sCurrXG!="")
    {
        this->InitBBInfo(sCurrXG);
    }
}


