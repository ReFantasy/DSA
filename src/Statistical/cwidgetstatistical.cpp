#include "cwidgetstatistical.h"
#include "ui_cwidgetstatistical.h"

/**
 * @brief CWidgetStatistical::CWidgetStatistical
 * @param parent
 */
CWidgetStatistical::CWidgetStatistical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetStatistical)
{
    ui->setupUi(this);
    this->m_nIdCondition=0;
    this->m_bIsAddCondition=false;

    /******** 初始化时间条件 ********/
    // 初始时默认打开本周范围查询
    ui->m_grpSurgDate->setChecked(1);
    ui->m_radFindRange->setChecked(1);
    ui->m_dtStart->setDate(QDate::currentDate());
    ui->m_dtEnd->setDate(QDate::currentDate());
    this->m_sDateCondition=this->GetDateCondition();

    /******** 初始化查询结果表 ********/
    QStringList sHeadPatiInfo = QString("住院号/姓名/性别/年龄/身高/体重/体表面积/手术日期/术者/手术类型/手术编号").split('/');
    m_modelPatiInfo= new QStandardItemModel();
    m_modelPatiInfo->setHorizontalHeaderLabels(sHeadPatiInfo);
    ui->m_tblvQueryAns->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->m_tblvQueryAns->setModel(m_modelPatiInfo);
    ui->m_tblvQueryAns->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblvQueryAns->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblvQueryAns->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblvQueryAns->horizontalHeader()->setStretchLastSection(1);
    ui->m_tblvQueryAns->show();

    /******** 初始化手术信息 ********/
    QStringList sHeaderSurgInfo = QString("手术信息").split('/');
    m_modelSurgInfo= new QStandardItemModel();
    m_modelSurgInfo->setHorizontalHeaderLabels(sHeaderSurgInfo);
    ui->m_treevSurgInfo->setModel(m_modelSurgInfo);
    ui->m_treevSurgInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_treevSurgInfo->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_treevSurgInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_treevSurgInfo->show();
    this->InitTreeView(ui->m_treevSurgInfo);


    // 初始时默认显示一个条件
    CWidgetCondition *wgtCondition=new CWidgetCondition();
    wgtCondition->HideDelete();
    wgtCondition->SetIndex(this->m_nIdCondition++);
    m_lstCondition.push_back(wgtCondition);
    ui->m_layoutCondition->layout()->addWidget(wgtCondition);


    /******** 初始化部分控件 ********/
    ui->m_grpQueryCondition->setChecked(0);
    ui->m_lineSum->setReadOnly(1);


    /******** 信号槽连接 ********/
    connect(ui->m_scrCondition->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),this,SLOT(UserRangeChanged(int,int)));
}

CWidgetStatistical::~CWidgetStatistical()
{
    delete ui;

    for (int i=0;i<m_lstCondition.size();i++)
    {
        delete(m_lstCondition[i]);
        m_lstCondition[i]=NULL;
    }
}


/**
 * @brief CWidgetStatistical::on_m_btnAddCondition_clicked
 */
void CWidgetStatistical::on_m_btnAddCondition_clicked()
{
    if(ui->m_grpQueryCondition->isChecked())
    {
        CWidgetCondition *wgtCondition=new CWidgetCondition(this);
        wgtCondition->SetIndex(this->m_nIdCondition++);
        m_lstCondition.push_back(wgtCondition);
        ui->m_layoutCondition->addWidget(wgtCondition);

        this->m_bIsAddCondition=true;
    }
    else
    {
        QMessageBox::information(NULL,"提示","请勾选检索条件",QMessageBox::Ok);
    }
}

/**
 * @brief CWidgetStatistical::重置条件列表
 */
void CWidgetStatistical::on_m_btnResetCondition_clicked()
{
    if(ui->m_grpQueryCondition->isChecked())
    {
        for (int i=1;i<m_lstCondition.size();i++)
        {
            delete(m_lstCondition[i]);
            m_lstCondition[i]=NULL;
        }
    }
}

/**
 * @brief CWidgetStatistical::on_m_btnQuery_clicked
 */
void CWidgetStatistical::on_m_btnQuery_clicked()
{
    // 先清空model
    for(int i = 0;i<m_modelPatiInfo->rowCount();i++)
    {
        m_modelPatiInfo->removeRow(i);
    }
    m_modelPatiInfo->setRowCount(0);

    // sql语句
    QString sSqlQuery="";

    // 查询条件
    QString sSqlCondition="";

    if(ui->m_grpSurgDate->isChecked())
    {
        // 获取条件值
        sSqlCondition+=m_sDateCondition;
    }

    QString sPrimaryTable="PatiInfo_T";
    QString sPrimaryKey="SysCaseID";
    QString sSqlTable=sPrimaryTable;

    if(ui->m_grpQueryCondition->isChecked())
    {
        // 这里遍历查询页面中的所有条件 并将表进行连接
        for(int i=0;i<m_lstCondition.size();i++)
        {
            QString sTable="",sCondition="",sAndOr="",sJoin="";
            m_lstCondition[i]->GetSqlQuery(sTable,sCondition,sAndOr,sJoin);

            if(sTable==""||sCondition==""||sAndOr==""||sJoin=="")
            {
                continue;
            }

            if(sTable!=sPrimaryTable)
            {
                sSqlTable+=" inner join "+sTable+" on "+sPrimaryTable+"."+sPrimaryKey+"="+sTable+"."+sJoin;
            }

            if(sSqlCondition=="")
            {
                sSqlCondition=sCondition;
            }
            else
            {
                sSqlCondition+=sAndOr+" "+sCondition+" ";
            }
        }
    }

    if(sSqlCondition!="")
    {
        QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

        sSqlQuery="select PatiInfo_T.CaseID,PatiInfo_T.PatiChName,PatiInfo_T.PatiSex,PatiInfo_T.PatiAge,"
                  "PatiInfo_T.PatiHeig,PatiInfo_T.PatiWeig,PatiInfo_T.PatiBSA,PatiInfo_T.PatiDate,"
                  "PatiInfo_T.SurName,PatiInfo_T.SurType,PatiInfo_T.SysCaseID from "+sSqlTable+" where "+sSqlCondition;

        qDebug()<<sSqlQuery;
        sqlReport->exec(sSqlQuery);
        int nRow=0;
        while (sqlReport->next())
        {
            for (int j=0;j<m_modelPatiInfo->columnCount();j++)
            {
                if(j==7)
                    m_modelPatiInfo->setItem(nRow,j,new QStandardItem(sqlReport->value(j).toDate().toString("yyyy-MM-dd")));
                else
                    m_modelPatiInfo->setItem(nRow,j,new QStandardItem(sqlReport->value(j).toString()));
            }
            nRow++;
        }

        sSqlQuery="select count(*) from "+sSqlTable+" where "+sSqlCondition;
        sqlReport->exec(sSqlQuery);
        sqlReport->next();
        QString nCount=sqlReport->value(0).toString();
        ui->m_lineSum->setText(nCount);

        delete sqlReport;
        sqlReport=NULL;
    }
}

/**
 * @brief 删除当前条件
 * @param pIndex 条件索引
 */
void CWidgetStatistical::DeleteCondition(int pIndex)
{
    if(ui->m_grpQueryCondition->isChecked())
    {
        delete (m_lstCondition[pIndex]);
        m_lstCondition[pIndex]=NULL;
    }
}

/**
 * @brief 滚动条范围改变的响应消息
 * @param pValueMin
 * @param pValueMax
 */
void CWidgetStatistical::UserRangeChanged(int pValueMin,int pValueMax)
{
    if(this->m_bIsAddCondition)
    {
        ui->m_scrCondition->verticalScrollBar()->setSliderPosition(pValueMax);
    }
    this->m_bIsAddCondition=false;
}

/**
 * @brief CWidgetStatistical::InitTreeView
 * @param pTreeView
 */
void CWidgetStatistical::InitTreeView(QTreeView *pTreeView)
{
    QString sCategory="手术信息/造影所见/病变信息/介入治疗/术中及手术状态/术后医嘱";
    QStringList slstCategory=sCategory.split('/');

    for(int i=0;i<slstCategory.size();i++)
    {
        QList<QStandardItem*> lstItems;
        QStandardItem* itemNode = new QStandardItem(slstCategory[i]);
        lstItems.append(itemNode);
        m_modelSurgInfo->appendRow(lstItems);
        m_lstSurgInfo.append(lstItems);
    }
}

QString CWidgetStatistical::GetQueryDate()
{
    QString sStart=ui->m_dtStart->date().toString("yyyy-MM-dd");
    QString sEnd=ui->m_dtEnd->date().toString("yyyy-MM-dd");
    return "PatiDate>='"+sStart+"'and PatiDate<='"+sEnd+"'";
}

/**
 * @brief CWidgetStatistical::GetWeekDay
 * @param pDate
 * @return
 */
int CWidgetStatistical::GetWeekDay(QDateTime pDateTime)
{
    QString sDateTime =pDateTime.toString("ddd");
    QString sWeek="周一,周二,周三,周四,周五,周六,周日";
    QStringList slstWeek=sWeek.split(',');

    int nIdWeek=0;
    for(int i=0;i<slstWeek.size();i++)
    {
        if(sDateTime==slstWeek[i])
        {
            nIdWeek=i;
            break;
        }
    }
    return nIdWeek;
}

/**
 * @brief CWidgetStatistical::ClearTreeView
 * @param pModel
 */
void CWidgetStatistical::ClearTreeView(QStandardItemModel *pModel)
{
    // 清空
    for (int i=0;i<pModel->rowCount();i++)
    {
        auto aItem=pModel->item(i);

        for (int j=0;j<aItem->rowCount();j++)
        {
            aItem->removeRow(j);
        }
    }
}

/**
 * @brief CWidgetStatistical::GetDateCondition
 * @return
 */
QString CWidgetStatistical::GetDateCondition()
{
return "";
}


/**
 * @brief 加载统计页面
 */
void CWidgetStatistical::on_m_btnStatistics_clicked()
{
    m_wgtAnalysis=new CWgtAnalysis();
    m_wgtAnalysis->show();
}




/**
 * @brief CWidgetStatistical::on_m_tblvQueryAns_clicked
 * @param index
 */
void CWidgetStatistical::on_m_tblvQueryAns_clicked(const QModelIndex &index)
{
    this->ClearTreeView(m_modelSurgInfo);
}

/**
 * @brief CWidgetStatistical::on_m_tblvQueryAns_doubleClicked
 * @param index
 */
void CWidgetStatistical::on_m_tblvQueryAns_doubleClicked(const QModelIndex &index)
{
    QString sSysCaseId=m_modelPatiInfo->item(index.row(),10)->text();

    QStringList slstSurgInfo;
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    QString sSqlSurgInfo="select operateprogress,contrastresult,bbresult,pci,inoperate,statebefore,advice from "
                         "operateitem where SysCaseID='"+sSysCaseId+"'";

    sqlReport->exec(sSqlSurgInfo);
    while (sqlReport->next())
    {
        slstSurgInfo.append(sqlReport->value(0).toString());
        slstSurgInfo.append(sqlReport->value(1).toString());
        slstSurgInfo.append(sqlReport->value(2).toString());
        slstSurgInfo.append(sqlReport->value(3).toString());
        slstSurgInfo.append(sqlReport->value(4).toString()+sqlReport->value(5).toString());
        slstSurgInfo.append(sqlReport->value(6).toString());
    }
    delete sqlReport;
    sqlReport=NULL;
    this->ClearTreeView(m_modelSurgInfo);
    if(slstSurgInfo.size()!=0)
    {
        for (int i=0;i<m_modelSurgInfo->rowCount();i++)
        {
            QList<QStandardItem*> lstItems;
            QStandardItem* item2 = new QStandardItem(slstSurgInfo[i]);
            lstItems.append(item2);
            m_modelSurgInfo->item(i)->appendRow(lstItems);
        }
        ui->m_treevSurgInfo->expandAll();
    }
}

/**
 * @brief CWidgetStatistical::on_m_radThisWeek_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radThisWeek_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtEnd->setEnabled(1);

        QDateTime dtmCurr =QDateTime::currentDateTime();
        int nDay=this->GetWeekDay(dtmCurr);

        QDateTime dtmThisWeek=dtmCurr.addDays(-1*nDay);

        ui->m_dtStart->setDate(dtmThisWeek.date());
        ui->m_dtEnd->setDate(dtmCurr.date());

        m_sDateCondition=this->GetQueryDate();
    }
}

/**
 * @brief CWidgetStatistical::on_m_radLastWeek_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radLastWeek_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtEnd->setEnabled(1);

        QDateTime dtmCurr =QDateTime::currentDateTime();
        int nDay=this->GetWeekDay(dtmCurr);

        QDateTime dtmLastWeekStart=dtmCurr.addDays(-1*(nDay+7));
        QDateTime dtmLastWeekEnd=dtmCurr.addDays(-1*(nDay+1));

        ui->m_dtStart->setDate(dtmLastWeekStart.date());
        ui->m_dtEnd->setDate(dtmLastWeekEnd.date());

        m_sDateCondition=this->GetQueryDate();

    }
}

/**
 * @brief CWidgetStatistical::on_m_radThisMonth_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radThisMonth_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtEnd->setEnabled(1);

        QDateTime dtmCurr =QDateTime::currentDateTime();
        int nDay=dtmCurr.toString("dd").toInt();

        QDateTime dtmFirstDay=dtmCurr.addDays(-1*nDay+1);

        ui->m_dtStart->setDate(dtmFirstDay.date());
        ui->m_dtEnd->setDate(dtmCurr.date());

        m_sDateCondition=this->GetQueryDate();
    }
}

/**
 * @brief CWidgetStatistical::on_m_radLastMonth_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radLastMonth_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtEnd->setEnabled(1);

        QDateTime dtmCurr =QDateTime::currentDateTime();
        int nDay=dtmCurr.toString("dd").toInt();
        QDateTime dtmFirstDay=dtmCurr.addDays(-1*nDay+1).addMonths(-1);
        QDateTime dtmFinalDay=dtmCurr.addDays(-1*nDay);

        ui->m_dtStart->setDate(dtmFirstDay.date());
        ui->m_dtEnd->setDate(dtmFinalDay.date());

        m_sDateCondition=this->GetQueryDate();
    }
}

/**
 * @brief CWidgetStatistical::on_m_radThisYear_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radThisYear_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtEnd->setEnabled(1);

        QDateTime dtmCurr =QDateTime::currentDateTime();
        QString sThisYear=dtmCurr.toString("yyyy")+"-01-01";
        QDateTime dtmThisYear=QDateTime::fromString(sThisYear,"yyyy-MM-dd");

        ui->m_dtStart->setDate(dtmThisYear.date());
        ui->m_dtEnd->setDate(dtmCurr.date());

        m_sDateCondition=this->GetQueryDate();
    }
}

/**
 * @brief CWidgetStatistical::on_m_radLastYear_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radLastYear_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtEnd->setEnabled(1);

        QDateTime dtmCurr =QDateTime::currentDateTime();
        QString sThisYear=dtmCurr.toString("yyyy")+"-01-01";
        QDateTime dtmThisYear=QDateTime::fromString(sThisYear,"yyyy-MM-dd");
        QDateTime dtmLastYear=dtmThisYear.addYears(-1);
        QDateTime dtmLastEndYear=dtmThisYear.addDays(-1);

        ui->m_dtStart->setDate(dtmLastYear.date());
        ui->m_dtEnd->setDate(dtmLastEndYear.date());

        m_sDateCondition=this->GetQueryDate();
    }
}

/**
 * @brief 设置为精确查找
 * @param checked
 */
void CWidgetStatistical::on_m_radFindExact_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtStart->setDate(QDate::currentDate());
        ui->m_dtEnd->setEnabled(0);
        QString sStart=ui->m_dtStart->date().toString("yyyy-MM-dd");
        m_sDateCondition= "PatiDate='"+sStart+"'";
    }
}

/**
 * @brief CWidgetStatistical::on_m_radFindRange_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_radFindRange_clicked(bool checked)
{
    if(checked)
    {
        ui->m_dtStart->setDate(QDate::currentDate());
        ui->m_dtEnd->setDate(QDate::currentDate());
        ui->m_dtEnd->setEnabled(1);
        m_sDateCondition=this->GetQueryDate();
    }
}

/**
 * @brief CWidgetStatistical::on_m_grpSurgDate_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_grpSurgDate_clicked(bool checked)
{
    if(!checked)
    {
        this->m_sDateCondition="";
    }
}

/**
 * @brief CWidgetStatistical::on_m_dtStart_editingFinished
 */
void CWidgetStatistical::on_m_dtStart_editingFinished()
{
    ui->m_radFindRange->setChecked(1);
    m_sDateCondition=this->GetQueryDate();
}

/**
 * @brief CWidgetStatistical::on_m_dtEnd_editingFinished
 */
void CWidgetStatistical::on_m_dtEnd_editingFinished()
{
    ui->m_radFindRange->setChecked(1);
    m_sDateCondition=this->GetQueryDate();
}

/**
 * @brief CWidgetStatistical::on_m_grpQueryCondition_clicked
 * @param checked
 */
void CWidgetStatistical::on_m_grpQueryCondition_clicked(bool checked)
{
}
