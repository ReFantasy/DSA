#include "cwidgetpatientstate.h"
#include "ui_cwidgetpatientstate.h"



CWidgetPatientState::CWidgetPatientState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetPatientState)
{
    ui->setupUi(this);

    ui->m_wgtIABP->hide();

    /******** 默认术中存活 ********/
    ui->m_chkSZSW->setChecked(0);
    ui->m_grpSZSWYY->hide();
    ui->m_grpSHQK->show();

    /******** 默认术后存活 ********/
    ui-> m_chkSHSW->setChecked(0);
    ui->m_grpSHSWYY->hide();

    /******** 默认无并发症 ********/
    ui-> m_chkCZBFZ->setChecked(0);
    ui->m_grpBFZ->hide();

    /******** 默认无并发症 ********/
    ui-> m_chkIABP->setChecked(0);
    ui->m_wgtIABP->hide();
    ui->m_lineBRZTQT->hide();

//    /******** 调节增删改按钮大小 ********/
//    ui->m_btnAddCYSHY->setFixedSize(QSize(24, 24));
//    ui->m_btnAddCYJSY->setFixedSize(QSize(24, 24));
//    ui->m_btnAddCYYZ->setFixedSize(QSize(24, 24));

//    ui->m_btnDelCYSHY->setFixedSize(QSize(24, 24));
//    ui->m_btnDelCYJSY->setFixedSize(QSize(24, 24));
//    ui->m_btnDelCYYZ->setFixedSize(QSize(24, 24));

//    ui->m_btnAlterCYSHY->setFixedSize(QSize(24, 24));
//    ui->m_btnAlterCYJSY->setFixedSize(QSize(24, 24));
//    ui->m_btnAlterCYYZ->setFixedSize(QSize(24, 24));

//    ui->m_btnDelCYSHY_choiced->setFixedSize(QSize(24, 24));
//    ui->m_btnDelCYJSY_choiced->setFixedSize(QSize(24, 24));
//    ui->m_btnDelCYYZ_choiced->setFixedSize(QSize(24, 24));
}

/**
 * @brief CWidgetPatientState::~CWidgetPatientState
 */
CWidgetPatientState::~CWidgetPatientState()
{
    delete ui;
}

/**
 * @brief CWidgetPatientState::on_m_chkSZSW_clicked
 * @param checked
 */
void CWidgetPatientState::on_m_chkSZSW_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSZSWYY->show();
        ui->m_grpSHQK->hide();
    }
    else
    {
        ui->m_grpSZSWYY->hide();
        ui->m_grpSHQK->show();
        ui->m_grpSHSWYY->hide();
        ui->m_grpBFZ->hide();
        ui->m_chkCZBFZ->show();
    }
    ui->m_chkSHSW->setChecked(0);
    ui->m_chkCZBFZ->setChecked(0);
    ui->m_cmbSZXYX->setCurrentIndex(-1);
    ui->m_cmbSZPCICZ->setCurrentIndex(-1);
    ui->m_cmbSHXYX->setCurrentIndex(-1);
    ui->m_cmbSHPCICZ->setCurrentIndex(-1);
    ui->m_chkSHXG->setChecked(0);
    ui->m_chkCQCX->setChecked(0);
    ui->m_chkDBJGM->setChecked(0);
    ui->m_chkJZWKSS->setChecked(0);
    ui->m_chkOther->setChecked(0);
    ui->m_chkSHGR->setChecked(0);
    ui->m_chkSHXG->setChecked(0);
    ui->m_chkXSSS->setChecked(0);
    ui->m_chkXSXC->setChecked(0);
    ui->m_chkYZCX->setChecked(0);
    ui->m_chkZQGNSJ->setChecked(0);
    ui->m_lineBRZTQT->hide();
}
/**
 * @brief CWidgetPatientState::on_m_chkSHSW_clicked
 * @param checked
 */
void CWidgetPatientState::on_m_chkSHSW_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSHSWYY->show();
        ui->m_chkCZBFZ->hide();
        ui->m_grpBFZ->hide();
        ui->m_chkSZSW->setChecked(0);
        ui->m_chkCZBFZ->setChecked(0);
    }
    else
    {
        ui->m_grpSHSWYY->hide();
        ui->m_chkCZBFZ->show();
    }
    ui->m_cmbSHXYX->setCurrentIndex(-1);
    ui->m_cmbSHPCICZ->setCurrentIndex(-1);
    ui->m_chkSHXG->setChecked(0);
    ui->m_chkCQCX->setChecked(0);
    ui->m_chkDBJGM->setChecked(0);
    ui->m_chkJZWKSS->setChecked(0);
    ui->m_chkOther->setChecked(0);
    ui->m_chkSHGR->setChecked(0);
    ui->m_chkSHXG->setChecked(0);
    ui->m_chkXSSS->setChecked(0);
    ui->m_chkXSXC->setChecked(0);
    ui->m_chkYZCX->setChecked(0);
    ui->m_chkZQGNSJ->setChecked(0);
    ui->m_lineBRZTQT->hide();
}
/**
 * @brief CWidgetPatientState::on_m_chkCZBFZ_clicked
 * @param checked
 */
void CWidgetPatientState::on_m_chkCZBFZ_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpBFZ->show();
        ui->m_chkSZSW->setChecked(0);
        ui->m_chkSHSW->setChecked(0);
    }
    else
    {
        ui->m_grpBFZ->hide();
        ui->m_chkSHXG->setChecked(0);
        ui->m_chkCQCX->setChecked(0);
        ui->m_chkDBJGM->setChecked(0);
        ui->m_chkJZWKSS->setChecked(0);
        ui->m_chkOther->setChecked(0);
        ui->m_chkSHGR->setChecked(0);
        ui->m_chkSHXG->setChecked(0);
        ui->m_chkXSSS->setChecked(0);
        ui->m_chkXSXC->setChecked(0);
        ui->m_chkYZCX->setChecked(0);
        ui->m_chkZQGNSJ->setChecked(0);
        ui->m_lineBRZTQT->hide();
    }
}
/**
 * @brief CWidgetPatientState::on_m_chkIABP_clicked
 * @param checked
 */
void CWidgetPatientState::on_m_chkIABP_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtIABP->show();
    }
    else
    {
        ui->m_wgtIABP->hide();
        ui->m_radPCISQ->setCheckable(0);
        ui->m_radPCISZ->setCheckable(0);
        ui->m_radPCISH->setCheckable(0);

        ui->m_radPCISQ->setCheckable(1);
        ui->m_radPCISZ->setCheckable(1);
        ui->m_radPCISH->setCheckable(1);
    }
}


/**
 * @brief 更新数据库
 */
void CWidgetPatientState::UpdateSqDb()
{
    /******** 默认术中存活 ********/

    /******** 获取报告输出内容 ********/
    m_sInOperate = ui->m_txtbCYSHY->toPlainText().replace(";","//");
    m_sStateBefore = ui->m_txtbCYJSY->toPlainText().replace(";","//");;
    m_sAdvice = ui->m_txtbCYYZ->toPlainText();
    qDebug() << m_sAdvice;
    /******** 将报告输出内容更新至数据库 ********/
    QSqlQuery* sqlReport = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlReport->exec("select * from BB_JLYZ where SysCaseID='" + m_sSysCaseId + "'");
    if(sqlReport->last())
    {
        sqlReport->exec("update BB_JLYZ set shyz='" + m_sAdvice + "' where SysCaseID='" + m_sSysCaseId + "'");
        sqlReport->exec("update BB_JLYZ set ssqk='" + m_sInOperate + "' where SysCaseID='" + m_sSysCaseId + "'");
        sqlReport->exec("update BB_JLYZ set jsy='" + m_sStateBefore + "' where SysCaseID='" + m_sSysCaseId + "'");
        qDebug() << "update BB_JLYZ set shyz='" + m_sAdvice + "' where SysCaseID='" + m_sSysCaseId + "'";
    }
    else
    {
        sqlReport->exec("insert into BB_JLYZ(shyz,ssqk,jsy,SysCaseID) values('" + m_sAdvice + "','" + m_sInOperate + "','" + m_sStateBefore + "','" + m_sSysCaseId + "')");
    }

//    //测试修改结果（BB_JLYZ）
//    sqlReport->exec("select ssqk,jsy,shyz from BB_JLYZ where SysCaseID='" + m_sSysCaseId + "'");
//    while(sqlReport->next())
//    {
//        qDebug()<< "数据库中:\n" << sqlReport->value(0).toString() << "\n"
//                 << sqlReport->value(1).toString() << "\n"
//                 << sqlReport->value(2).toString() << "\n";
//    }
//    qDebug()<< "程序中:\n" << m_sInOperate << "\n" << m_sStateBefore << "\n" << m_sAdvice;



    /******** 获取各个控件选中情况 ********/
    QString sJudgeFalse = "0";
    if(ui->m_chkSZSW->isChecked())
    {
        m_sSZSW = ui->m_cmbSZXYX->currentText() + "/" + ui->m_cmbSZPCICZ->currentText();
    }
    else
    {
        m_sSZSW = sJudgeFalse;
    }

    if(ui->m_chkSHSW->isChecked())
    {
        m_sSHSW = ui->m_cmbSHXYX->currentText() + "/" + ui->m_cmbSHPCICZ->currentText();
    }
    else
    {
        m_sSHSW = sJudgeFalse;
    }
    // 清空术后并发症的缓存
    m_sCZBFZ = "";
    m_lCZBFZContent.clear();
    if(ui->m_chkCZBFZ->isChecked())
    {       
        /******** 遍历复选框，获取选中的复选框的文本，并将其整合成字符串 ********/
        auto alistgrpBFZ = ui->m_grpBFZ->children();
        for(int i = 0;i < alistgrpBFZ.length();i++)
        {
            if(alistgrpBFZ.at(i)->inherits("QCheckBox"))
            {
                auto aCurChk = qobject_cast<QCheckBox*>(alistgrpBFZ.at(i));
                QString sCurCheckbox = aCurChk->text();
                if(aCurChk->isChecked())
                {
                    if(sCurCheckbox == "其它")
                        m_lCZBFZContent.append(sCurCheckbox + ';' + ui->m_lineBRZTQT->text());
                    else
                        m_lCZBFZContent.append(sCurCheckbox);
                }
            }
        }
        m_sCZBFZ = "";
        foreach(QString sCurrent, m_lCZBFZContent)
        {
            m_sCZBFZ += sCurrent + "/";
        }
        m_sCZBFZ = m_sCZBFZ.left(m_sCZBFZ.length() - 1);
    }
    else
    {
        m_sCZBFZ = sJudgeFalse;
    }
    if(ui->m_chkIABP->isChecked())
    {
        /******** 遍历m_grpBFZ,初始化复选框 ********/
        auto alistwgtIABP = ui->m_wgtIABP->children();
        for(int i = 0;i < alistwgtIABP.length();i++)
        {
            if(alistwgtIABP.at(i)->inherits("QRadioButton"))
            {
                auto aCurRadbtn = qobject_cast<QRadioButton*>(alistwgtIABP.at(i));
                QString sCurRadbtn = aCurRadbtn->text();
                if(aCurRadbtn->isChecked())
                    m_sIABP = aCurRadbtn->text();
            }
        }
    }
    else
    {
        m_sIABP = sJudgeFalse;
    }
    /******** 将控件的选中情况更新至数据库 ********/
    sqlReport->exec("select * from PCI_ZBB_T where SysCaseID='" + m_sSysCaseId + "'");
    if(sqlReport->last())
    {
        sqlReport->exec("update PCI_ZBB_T set szsw='"+ m_sSZSW + "' where SysCaseID='" + m_sSysCaseId + "'");
        sqlReport->exec("update PCI_ZBB_T set shsw='"+ m_sSHSW + "' where SysCaseID='" + m_sSysCaseId + "'");
        sqlReport->exec("update PCI_ZBB_T set shbfz='"+ m_sCZBFZ + "' where SysCaseID='" + m_sSysCaseId + "'");
        sqlReport->exec("update PCI_ZBB_T set IABP='"+ m_sIABP + "' where SysCaseID='" + m_sSysCaseId + "'");
    }
    else
    {
        sqlReport->exec("insert into PCI_ZBB_T(szsw,shsw,shbfz,IABP,SysCaseID) values('"+ m_sSZSW + "','"+ m_sSHSW + "','"+ m_sCZBFZ + "','"+ m_sIABP + "','" + m_sSysCaseId + "')");
    }


    //测试修改结果（PCI_ZBB_T）

    sqlReport->exec("select szsw,shsw,shbfz,IABP,IABPStatus from PCI_ZBB_T where SysCaseID='" + m_sSysCaseId + "'");
    while(sqlReport->next())
    {
        qDebug()<< "数据库中:\n" << sqlReport->value(0).toString() << "\n"
        << sqlReport->value(1).toString() << "\n"
        << sqlReport->value(2).toString() << "\n"
        << sqlReport->value(3).toString() << "\n";
    }
    qDebug()<< "程序中:\n" << m_sSZSW << "\n" << m_sSHSW << "\n"
            << m_sCZBFZ << "\n" << m_sIABP << "\n";




    /******** 清空医学用语全局变量的缓存 ********/
    m_lCYSHY.clear();
    m_lCYJSY.clear();
    m_lCYYZ.clear();
    /******** 获取最新的医学用语字符串列表 ********/
    for(int i = 0;i < ui->m_lstwCYSHY->count();i++)
    {
        if(ui->m_lstwCYSHY->item(i)->text().remove(" ") == "")
            continue;
        m_lCYSHY.append(ui->m_lstwCYSHY->item(i)->text().remove("//"));
    }
    for(int i = 0;i < ui->m_lstwCYJSY->count();i++)
    {
        if(ui->m_lstwCYJSY->item(i)->text().remove(" ") == "")
            continue;
        m_lCYJSY.append(ui->m_lstwCYJSY->item(i)->text().remove("//"));
    }
    for(int i = 0;i < ui->m_lstwCYYZ->count();i++)
    {
        if(ui->m_lstwCYYZ->item(i)->text().remove(" ") == "")
            continue;
        m_lCYYZ.append(ui->m_lstwCYYZ->item(i)->text().remove("//"));
    }
    /******** 将CathBook_T表中的SSQK,JSY,SHYZ三列内容全部置空 ********/
    sqlReport->exec("update CathBook_T set SSQK=''");
    sqlReport->exec("update CathBook_T set JSY=''");
    sqlReport->exec("update CathBook_T set SHYZ=''");
    /******** 获取CathBook_T表中的记录数 ********/
    int nRecordCount = 0;
    sqlReport->exec("select * from CathBook_T");
    while(sqlReport->next())
        nRecordCount++;
//    //测试
//    qDebug() << "CathBook_T记录数：" << nRecordCount;
    /******** 将医学用语缓存列表中的内容更新至数据库 ********/
    int i = 0;
    foreach(QString str, m_lCYSHY)
    {
        i++;
        sqlReport->exec("update CathBook_T set SSQK='" + str + "' where ID='" + QString::number(i) + "'");

//        //有待完善
//        //如果要更新的医学用语总数超过表中的总记录数则不在继续更新
//        if(i > nRecordCount)
//            return;
//        else
//        {
//            sqlReport->exec("update CathBook_T set SSQK='" + str + "' where ID='" + QString::number(i) + "'");
//        }
    }
    i = 0;
    foreach(QString str, m_lCYJSY)
    {
        i++;
        sqlReport->exec("update CathBook_T set JSY='" + str + "' where ID='" + QString::number(i) + "'");

//        //有待完善
//        if(i > nRecordCount)
//            return;
//        else
//        {
//            sqlReport->exec("update CathBook_T set JSY='" + str + "' where ID='" + QString::number(i) + "'");
//        }
    }
    i = 0;
    foreach(QString str, m_lCYYZ)
    {
        i++;
        sqlReport->exec("update CathBook_T set SHYZ='" + str + "' where ID='" + QString::number(i) + "'");

//        //有待完善
//        if(i > nRecordCount)
//            return;
//        else
//        {
//            sqlReport->exec("update CathBook_T set SHYZ='" + str + "' where ID='" + QString::number(i) + "'");
//        }
    }

}

/**
 * @brief CWidgetPatientState::UpdateReportTable
 */
void CWidgetPatientState::UpdateReportTable()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sSSQK="";
    QString sJSY="";
    QString sSHYZ="";
    QString sSqlReport="select ssqk,jsy,shyz from BB_JLYZ where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReport);
    while(sqlReport->next())
    {
        sSSQK=sqlReport->value(0).toString();
        sJSY=sqlReport->value(1).toString();
        sSHYZ=sqlReport->value(2).toString();
    }

    sSqlReport="update operateitem set inoperate='"+sSSQK+"',statebefore='"+sJSY+"',advice='"+sSHYZ+"' where SysCaseID ='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReport);

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 获取SysCaseId
 * @param pSysCaseId 传至此界面的SysCaseId
 */
void CWidgetPatientState::SetSysCaseId(const QString pSysCaseId)
{
    m_sSysCaseId = pSysCaseId;
    qDebug() << pSysCaseId;
    this->SetSqDB();
}

/**
 * @brief 从数据库中读取信息初始化UI界面信息
 */
void CWidgetPatientState::UpdateUIFromDatabase()
{
    this->SetSqDB();
}

/**
 * @brief 从UI界面中读取信息初始化数据库信息
 */
void CWidgetPatientState::UpdateDatabaseFromUI()
{
    this->UpdateSqDb();
    this->UpdateReportTable();
}


/**
 * @brief 访问数据库
 * @param pSqlDB
 */
void CWidgetPatientState::SetSqDB()
{

    /******** 默认术中存活 ********/

    /******** 存储从数据库中读取的各类医学用语 ********/
    QStringList lLstwCYSHYItems;
    QStringList lLstwCYJSItems;
    QStringList lLstwCYYZItems;
    /******** 获取数据库中的医学用语字符串 ********/
    QSqlQuery* sqlReport = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlReport->exec("select SSQK,JSY,SHYZ from CathBook_T");
    while(sqlReport->next())
    {
        lLstwCYSHYItems.append(sqlReport->value(0).toString());
        lLstwCYJSItems.append(sqlReport->value(1).toString());
        lLstwCYYZItems.append(sqlReport->value(2).toString());
    }
    /******** 去除字符串列表中的空字符串 ********/
    lLstwCYSHYItems.removeAll("");
    lLstwCYJSItems.removeAll("");
    lLstwCYYZItems.removeAll("");
    /******** 将从数据库中读取出的医学用语存入全局变量 ********/
    m_lCYSHY = lLstwCYSHYItems;
    m_lCYJSY = lLstwCYJSItems;
    m_lCYYZ = lLstwCYYZItems;
    /******** 添加医学用语至各个列表中 ********/
    foreach(QString item, lLstwCYSHYItems)
    {
        ui->m_lstwCYSHY->addItem(item);        
    }
    foreach(QString item, lLstwCYJSItems)
    {
        ui->m_lstwCYJSY->addItem(item);  
    }
    foreach(QString item, lLstwCYYZItems)
    {
        ui->m_lstwCYYZ->addItem(item);       
    }




    /******** 获取ID,查找病人状态信息 ********/

    sqlReport->exec("select szsw,shsw,shbfz,IABP,IABPStatus from PCI_ZBB_T where SysCaseID='" + m_sSysCaseId + "'");
    qDebug() << "select szsw,shsw,shbfz,IABP,IABPStatus from PCI_ZBB_T where SysCaseID='" + m_sSysCaseId + "'";
    while(sqlReport->next())
    {
        m_sSZSW = sqlReport->value(0).toString();
        m_sSHSW = sqlReport->value(1).toString();
        m_sCZBFZ = sqlReport->value(2).toString();
        m_sIABP = sqlReport->value(3).toString();
//        qDebug() << m_sSZSW;
//        qDebug() << m_sSHSW;
//        qDebug() << m_sCZBFZ;
//        qDebug() << m_sIABP;
    }

//    //测试信息初始化
//    QString sSZSWYY = "心源性死亡/与PCI操作无关";
//    QString sSHSWYY = "非心源性死亡/不确定";
//    QString sCZBFZ = "术后心梗/急诊外科手术/对比剂过敏/其它/脏器出血";
//    m_sSZSW = "";
//    m_sSHSW = "";
//    m_sCZBFZ = "";
//    m_sIABP = "";

    /******** 根据数据库中的信息，初始化控件的选中状态 ********/
    QString sJudgeFalse = "0";
    if(m_sSZSW != sJudgeFalse && m_sSZSW.contains("/"))
    {
        ui->m_chkSZSW->setChecked(1);
        on_m_chkSZSW_clicked(1);       
        ui->m_cmbSZXYX->setCurrentText(m_sSZSW.split("/").at(0));
        ui->m_cmbSZPCICZ->setCurrentText(m_sSZSW.split("/").at(1));
    }
    else
    {
        if(m_sSHSW != sJudgeFalse && m_sSHSW.contains("/"))
        {
            ui->m_chkSHSW->setChecked(1);
            on_m_chkSHSW_clicked(1);
            ui->m_cmbSHXYX->setCurrentText(m_sSHSW.split("/").at(0));
            ui->m_cmbSHPCICZ->setCurrentText(m_sSHSW.split("/").at(1));
        }
        else
        {
            if(m_sCZBFZ != sJudgeFalse && m_sCZBFZ !="")
            {
                ui->m_chkCZBFZ->setChecked(1);
                on_m_chkCZBFZ_clicked(1);
                m_lCZBFZContent = m_sCZBFZ.split("/");
                /******** 遍历m_grpBFZ,初始化复选框 ********/
                auto alistgrpBFZ = ui->m_grpBFZ->children();
                for(int i = 0;i < alistgrpBFZ.length();i++)
                {
                    if(alistgrpBFZ.at(i)->inherits("QCheckBox"))
                    {
                        auto aCurChk = qobject_cast<QCheckBox*>(alistgrpBFZ.at(i));
                        QString sCurCheckbox = aCurChk->text();
                        if(m_lCZBFZContent.contains(sCurCheckbox))
                            aCurChk->setChecked(1);
                        if(sCurCheckbox == "其它")
                        {
                            foreach(QString str, m_lCZBFZContent)
                            {
                                if(str.split(";")[0] == "其它")
                                {
                                    aCurChk->setChecked(1);
                                    ui->m_lineBRZTQT->setText(str.split(";")[1]);
                                    ui->m_lineBRZTQT->show();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(m_sIABP != sJudgeFalse && m_sIABP != "")
    {
        ui->m_chkIABP->setChecked(1);
        on_m_chkIABP_clicked(1);

        /******** 遍历m_grpBFZ,初始化复选框 ********/
        auto alistwgtIABP = ui->m_wgtIABP->children();
        for(int i = 0;i < alistwgtIABP.length();i++)
        {
            if(alistwgtIABP.at(i)->inherits("QRadioButton"))
            {
                auto aCurRadbtn = qobject_cast<QRadioButton*>(alistwgtIABP.at(i));
                QString sCurRadbtn = aCurRadbtn->text();
                if(sCurRadbtn == m_sIABP)
                    aCurRadbtn->setChecked(1);
            }
        }
    }




    /******** 根据数据库中的信息，初始化报告输出内容 ********/

    sqlReport->exec("select ssqk,jsy,shyz from BB_JLYZ where SysCaseID='" + m_sSysCaseId + "'");
    while(sqlReport->next())
    {
        QString str = "";
        m_sInOperate = sqlReport->value(0).toString();
        m_sStateBefore = sqlReport->value(1).toString();
        m_sAdvice = sqlReport->value(2).toString();
    }
    QString sTempInOperate = m_sInOperate;

//    //测试信息初始化
//    m_sInOperate = "";
//    m_sStateBefore = "";
//    m_sAdvice = "";
    //初始化报告输出文本框
    ui->m_txtbCYSHY->setText(m_sInOperate.replace("//",";"));
    ui->m_txtbCYJSY->setText(m_sStateBefore.replace("//",";"));
    ui->m_txtbCYYZ->setText(m_sAdvice);
    m_sInOperate.replace(";","//");
    m_sStateBefore.replace(";","//");
    //初始化已选择列表
    if(m_sInOperate != "")
    {
        QStringList lStr = m_sInOperate.split("//");
        foreach(QString str, lStr)
        {
            ui->m_lstwCYSHY_choiced->addItem(str);
        }
    }
    if(m_sStateBefore != "")
    {
        QStringList lStr = m_sStateBefore.split("//");
        foreach(QString str, lStr)
        {
            ui->m_lstwCYJSY_choiced->addItem(str);
        }
    }
    if(m_sAdvice != "")
    {
        QStringList lStr = m_sAdvice.split(";\n");
        lStr.removeAll("");
        foreach(QString str, lStr)
        {
           ui->m_lstwCYYZ_choiced->addItem(str.split(".")[1]);
        }
    }

//    //测试，查询表的列名
//    sqlReport->exec("select name from syscolumns where id=object_id('BB_JLYZ')");
//    while(sqlReport->next())
//        qDebug() << sqlReport->value(0).toString();

//    //测试，查询数据库名、数据库中的表名
//    QSqlQuery* sqlTest = new QSqlQuery(SQLDB::GetCathLabStock());
//    sqlTest->exec("select name from sysobjects where type='U'");
////    //sqlReport->exec("select Name From Master..SysDataBases Where DbId=(Select Dbid From Master..SysProcesses Where Spid = @@spid)");
//    while(sqlTest->next())
//    {
//       qDebug() << sqlTest->value(0).toString() << "\n";
//    }

//    //测试，向CathBook_T插入内容
//    for(int i = 9;i <= 100;i++)
//    {
//        sqlReport->exec("insert into CathBook_T(LCZD,KJYY,JSY,SHYZ,SSQK,SZZT,ZY_JieLun) values('" + QString::number(i) + "','" + QString::number(i) + "','" + QString::number(i) + "','" + QString::number(i)
//                        + "','" + QString::number(i) + "','" + QString::number(i) + "','" + QString::number(i) + "')");
//    }

//    //测试，修改 CathBook_T内容
//    for(int i = 1;i <= 10;i++)
//    {
//        sqlReport->exec("update CathBook_T set LCZD='" + QString::number(i) + "',KJYY='" + QString::number(i) + "',JSY='" + QString::number(i)
//                        + "',SHYZ='" + QString::number(i) + "',SSQK='" + QString::number(i) + "',SZZT='" + QString::number(i) + "',ZY_JieLun='" + QString::number(i)
//                        + "' where ID='" + QString::number(i) + "'");
//    }

//    //测试，查询表中的所有记录
//    sqlReport->exec("select szsw,shsw,shbfz,IABP,IABPStatus from PCI_ZBB_T where SysCaseID='" + m_sSysCaseId + "'");
//    qDebug() << "PCI_ZBB_T记录：";
//    while(sqlReport->next())
//    {
//        qDebug() << sqlReport->value(0).toString()
//            << sqlReport->value(1).toString()
//            << sqlReport->value(2).toString()
//            << sqlReport->value(3).toString()
//            << sqlReport->value(4).toString();
//    }
}

/**
 * @brief 列表内容查重
 * @param sItemText 选定项的文本内容
 * @param listWidget 列表对象
 */
bool CWidgetPatientState::CheckDuplicate(QString sItemText, QListWidget *pListWidget)
{
    bool bExist = true;
    QString sChoiceString = sItemText;
    QString sCurrentString = "";
    int row = 0;
    while(row < (pListWidget->count()))
    {
        sCurrentString = pListWidget->item(row)->text();
        if(sChoiceString == sCurrentString)
            return bExist;
        row++;
    }
    bExist = false;
    return bExist;
}

/**
 * @brief 遍历已选择列表,生成报告输出
 * @param pListWidgetChoiced 已选择列表
 * @param pTextBrowserOutput 报告输出文本框
 */
void CWidgetPatientState::GenerateOutput(QListWidget *pListWidgetChoiced, QTextBrowser *pTextBrowserOutput)
{
    int row = 0;
    QString sOutputStr = "";
    while(row < (pListWidgetChoiced->count()))
    {
        sOutputStr += pListWidgetChoiced->item(row)->text() + ";";
        row++;
    }
    sOutputStr = sOutputStr.left(sOutputStr.length() - 1);
    pTextBrowserOutput->setText(sOutputStr);
}

/**
 * @brief 遍历已选择列表,生成报告输出
 * @param pListWidgetChoiced 已选择列表
 * @param pTextBrowserOutput 报告输出文本框
 */
void CWidgetPatientState::GenerateCYYZOutput(QListWidget *pListWidgetChoiced, QTextBrowser *pTextBrowserOutput)
{
    int row = 0;
    QString sOutputStr = "";
    while(row < pListWidgetChoiced->count())
    {
        sOutputStr += QString::number(row + 1) + "."
                + pListWidgetChoiced->item(row)->text().remove(";") + ";\n";
        row++;
    }
    pTextBrowserOutput->setText(sOutputStr);
}

/**
 * @brief 常用手术语列表中的一项被单击
 * @param item 选中的项
 */
void CWidgetPatientState::on_m_lstwCYSHY_itemClicked(QListWidgetItem *item)
{
    //m_lstwCYSHYSelected = item->text();
}

/**
 * @brief 将选中的常用手术语添加进已选择列表，并生成报告输出
 * @param
 */
void CWidgetPatientState::on_m_btnCYSHY_clicked()
{
    if(ui->m_lstwCYSHY->selectedItems().count())
    {
        m_lstwCYSHYSelected = ui->m_lstwCYSHY->selectedItems()[0]->text().remove("//");
        if(m_lstwCYSHYSelected.remove(" ") == "")
           return;
        if(!(CheckDuplicate(m_lstwCYSHYSelected, ui->m_lstwCYSHY_choiced)))
        {
            ui->m_lstwCYSHY_choiced->addItem(new QListWidgetItem(m_lstwCYSHYSelected));
            GenerateOutput(ui->m_lstwCYSHY_choiced, ui->m_txtbCYSHY);
        }
    }

}

/**
 * @brief 常用结束语列表中的一项被单击
 * @param item 选中的项
 */
void CWidgetPatientState::on_m_lstwCYJSY_itemClicked(QListWidgetItem *item)
{
    //m_lstwCYJSYSelected = item->text();
}

/**
 * @brief 将选中的常用结束语添加进已选择列表，并生成报告输出
 * @param
 */
void CWidgetPatientState::on_m_btnCYJSY_clicked()
{
    if(ui->m_lstwCYJSY->selectedItems().count())
    {
        m_lstwCYJSYSelected = ui->m_lstwCYJSY->selectedItems()[0]->text().remove("//");
        if(m_lstwCYJSYSelected.remove(" ") == "")
           return;

        /******** 选中的项在已选列表中不存在时，才能被添加进已选列表 ********/
        if(!(CheckDuplicate(m_lstwCYJSYSelected, ui->m_lstwCYJSY_choiced)))
        {
          ui->m_lstwCYJSY_choiced->addItem(new QListWidgetItem(m_lstwCYJSYSelected));
          GenerateOutput(ui->m_lstwCYJSY_choiced, ui->m_txtbCYJSY);
        }
    }
}

/**
 * @brief 常用医嘱列表中的一项被单击
 * @param item 选中的项
 */
void CWidgetPatientState::on_m_lstwCYYZ_itemClicked(QListWidgetItem *item)
{
    //m_lstwCYYZSelected = item->text();
}

/**
 * @brief 将选中的常用医嘱添加进已选择列表，并生成报告输出
 * @param
 */
void CWidgetPatientState::on_m_btnCYYZ_clicked()
{
    if(ui->m_lstwCYYZ->selectedItems().count())
    {
        m_lstwCYYZSelected = ui->m_lstwCYYZ->selectedItems()[0]->text().remove("//");
        if(m_lstwCYYZSelected.remove(" ") == "")
           return;
        if(!(CheckDuplicate(m_lstwCYYZSelected, ui->m_lstwCYYZ_choiced)))
        {
            ui->m_lstwCYYZ_choiced->addItem(new QListWidgetItem(m_lstwCYYZSelected));
            GenerateCYYZOutput(ui->m_lstwCYYZ_choiced, ui->m_txtbCYYZ);
        }
    }
}

/**
 * @brief 双击常用手术语列表中的项，将其添加至已选择列表
 * @param item 选中的项
 */
void CWidgetPatientState::on_m_lstwCYSHY_itemDoubleClicked(QListWidgetItem *item)
{
    ui->m_lstwCYSHY->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_lstwCYSHYSelected = item->text().remove("//");
    if(m_lstwCYSHYSelected.remove(" ") == "")
       return;
    if(!(CheckDuplicate(m_lstwCYSHYSelected, ui->m_lstwCYSHY_choiced)))
    {
        ui->m_lstwCYSHY_choiced->addItem(new QListWidgetItem(m_lstwCYSHYSelected));
        GenerateOutput(ui->m_lstwCYSHY_choiced, ui->m_txtbCYSHY);
    }
}

/**
 * @brief 双击常用结束语列表中的项，将其添加至已选择列表
 * @param item 选中的项
 */
void CWidgetPatientState::on_m_lstwCYJSY_itemDoubleClicked(QListWidgetItem *item)
{
    ui->m_lstwCYJSY->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_lstwCYJSYSelected = item->text().remove("//");
    if(m_lstwCYJSYSelected.remove(" ") == "")
       return;

    /******** 选中的项在已选列表中不存在时，才能被添加进已选列表 ********/
    if(!(CheckDuplicate(m_lstwCYJSYSelected, ui->m_lstwCYJSY_choiced)))
    {
      ui->m_lstwCYJSY_choiced->addItem(new QListWidgetItem(m_lstwCYJSYSelected));
      GenerateOutput(ui->m_lstwCYJSY_choiced, ui->m_txtbCYJSY);
    }

}

/**
 * @brief 双击常用医嘱列表中的项，将其添加至已选择列表
 * @param item 选中的项
 */
void CWidgetPatientState::on_m_lstwCYYZ_itemDoubleClicked(QListWidgetItem *item)
{
    ui->m_lstwCYYZ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_lstwCYYZSelected = item->text().remove("//");
    if(m_lstwCYYZSelected.remove(" ") == "")
       return;

    if(!(CheckDuplicate(m_lstwCYYZSelected, ui->m_lstwCYYZ_choiced)))
    {
        ui->m_lstwCYYZ_choiced->addItem(new QListWidgetItem(m_lstwCYYZSelected));
        GenerateCYYZOutput(ui->m_lstwCYYZ_choiced, ui->m_txtbCYYZ);
    }

}

/**
 * @brief 单击添加按钮，向常用手术语列表中添加新的项
 */
void CWidgetPatientState::on_m_btnAddCYSHY_clicked()
{
   if(ui->m_lstwCYSHY->count())
   {
       if(ui->m_lstwCYSHY->item(ui->m_lstwCYSHY->count() - 1)->text().remove(" ") == "")
       {
            ui->m_lstwCYSHY->editItem(ui->m_lstwCYSHY->item(ui->m_lstwCYSHY->count() - 1));
       }
       else
       {
           QListWidgetItem *item;
           ui->m_lstwCYSHY->addItem(new QListWidgetItem(""));
           item = ui->m_lstwCYSHY->item(ui->m_lstwCYSHY->count() - 1);
           item->setFlags(item->flags() | Qt::ItemIsEditable);
           ui->m_lstwCYSHY->setCurrentItem(item);
           ui->m_lstwCYSHY->editItem(item);
       }
   }
   else
   {
       QListWidgetItem *item;
       ui->m_lstwCYSHY->addItem(new QListWidgetItem(""));
       item = ui->m_lstwCYSHY->item(ui->m_lstwCYSHY->count() - 1);
       item->setFlags(item->flags() | Qt::ItemIsEditable);
       ui->m_lstwCYSHY->setCurrentItem(item);
       ui->m_lstwCYSHY->editItem(item);
   }
}

/**
 * @brief 单击删除按钮，删除常用手术语列表中的项
 */
void CWidgetPatientState::on_m_btnDelCYSHY_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYSHY->selectedItems().count())
    {
        item = ui->m_lstwCYSHY->selectedItems()[0];
        delete item;
    }
}

/**
 * @brief 单击修改按钮，修改常用手术语列表中的项
 */
void CWidgetPatientState::on_m_btnAlterCYSHY_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYSHY->selectedItems().count())
    {
        item = ui->m_lstwCYSHY->selectedItems()[0];
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->m_lstwCYSHY->editItem(item);
    }
}

/**
 * @brief 单击添加按钮，向常用结束语列表中添加新的项
 */
void CWidgetPatientState::on_m_btnAddCYJSY_clicked()
{
    if(ui->m_lstwCYJSY->count())
    {
        if(ui->m_lstwCYJSY->item(ui->m_lstwCYJSY->count() - 1)->text().remove(" ") == "")
        {
             ui->m_lstwCYJSY->editItem(ui->m_lstwCYJSY->item(ui->m_lstwCYJSY->count() - 1));
        }
        else
        {
            QListWidgetItem *item;
            ui->m_lstwCYJSY->addItem(new QListWidgetItem(""));
            item = ui->m_lstwCYJSY->item(ui->m_lstwCYJSY->count() - 1);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            ui->m_lstwCYJSY->setCurrentItem(item);
            ui->m_lstwCYJSY->editItem(item);
        }
    }
    else
    {
        QListWidgetItem *item;
        ui->m_lstwCYJSY->addItem(new QListWidgetItem(""));
        item = ui->m_lstwCYJSY->item(ui->m_lstwCYJSY->count() - 1);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->m_lstwCYJSY->setCurrentItem(item);
        ui->m_lstwCYJSY->editItem(item);
    }
}

/**
 * @brief 单击删除按钮，删除常用结束语列表中的项
 */
void CWidgetPatientState::on_m_btnDelCYJSY_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYJSY->selectedItems().count())
    {
        item = ui->m_lstwCYJSY->selectedItems()[0];
        delete item;
    }
}

/**
 * @brief 单击修改按钮，修改常用结束语列表中的项
 */
void CWidgetPatientState::on_m_btnAlterCYJSY_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYJSY->selectedItems().count())
    {
        item = ui->m_lstwCYJSY->selectedItems()[0];
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->m_lstwCYJSY->editItem(item);
    }
}

/**
 * @brief 单击添加按钮，向常用医嘱列表中添加新的项
 */
void CWidgetPatientState::on_m_btnAddCYYZ_clicked()
{
    if(ui->m_lstwCYYZ->count())
    {
        if(ui->m_lstwCYYZ->item(ui->m_lstwCYYZ->count() - 1)->text().remove(" ") == "")
        {
             ui->m_lstwCYYZ->editItem(ui->m_lstwCYYZ->item(ui->m_lstwCYYZ->count() - 1));
        }
        else
        {
            QListWidgetItem *item;
            ui->m_lstwCYYZ->addItem(new QListWidgetItem(""));
            item = ui->m_lstwCYYZ->item(ui->m_lstwCYYZ->count() - 1);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            ui->m_lstwCYYZ->setCurrentItem(item);
            ui->m_lstwCYYZ->editItem(item);
        }
    }
    else
    {
        QListWidgetItem *item;
        ui->m_lstwCYYZ->addItem(new QListWidgetItem(""));
        item = ui->m_lstwCYYZ->item(ui->m_lstwCYYZ->count() - 1);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->m_lstwCYYZ->setCurrentItem(item);
        ui->m_lstwCYYZ->editItem(item);
    }
}

/**
 * @brief 单击删除按钮，删除常用医嘱列表中的项
 */
void CWidgetPatientState::on_m_btnDelCYYZ_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYYZ->selectedItems().count())
    {
        item = ui->m_lstwCYYZ->selectedItems()[0];
        delete item;
    }
}

/**
 * @brief 单击修改按钮，修改常用医嘱列表中的项
 */
void CWidgetPatientState::on_m_btnAlterCYYZ_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYYZ->selectedItems().count())
    {
        item = ui->m_lstwCYYZ->selectedItems()[0];
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->m_lstwCYYZ->editItem(item);
    }
}

/**
 * @brief CWidgetPatientState::on_groupBox_4_clicked
 */
void CWidgetPatientState::on_groupBox_4_clicked()
{

}

/**
 * @brief 单击删除按钮，删除常用结束语列表中的项
 */
void CWidgetPatientState::on_m_btnDelCYSHY_choiced_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYSHY_choiced->selectedItems().count())
    {
        item = ui->m_lstwCYSHY_choiced->selectedItems()[0];
        delete item;
    }
    GenerateOutput(ui->m_lstwCYSHY_choiced, ui->m_txtbCYSHY);
}

/**
 * @brief 单击删除按钮，删除常用结束语列表中的项
 */
void CWidgetPatientState::on_m_btnDelCYJSY_choiced_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYJSY_choiced->selectedItems().count())
    {
        item = ui->m_lstwCYJSY_choiced->selectedItems()[0];
        delete item;
    }
   GenerateOutput(ui->m_lstwCYJSY_choiced, ui->m_txtbCYJSY);
}

/**
 * @brief 单击删除按钮，删除常用医嘱列表中的项
 */
void CWidgetPatientState::on_m_btnDelCYYZ_choiced_clicked()
{
    QListWidgetItem *item;
    if(ui->m_lstwCYYZ_choiced->selectedItems().count())
    {
        item = ui->m_lstwCYYZ_choiced->selectedItems()[0];
        delete item;
    }
    GenerateCYYZOutput(ui->m_lstwCYYZ_choiced, ui->m_txtbCYYZ);
}

/**
 * @brief CWidgetPatientState::on_m_chkOther_clicked
 * @param checked
 */
void CWidgetPatientState::on_m_chkOther_clicked(bool checked)
{
    if(checked)
    {
        ui->m_lineBRZTQT->show();
    }
    else
    {
        ui->m_lineBRZTQT->hide();
    }
}
