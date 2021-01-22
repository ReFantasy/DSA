 #include "cwidgetpathologyinfo.h"
#include "ui_cwidgetpathologyinfo.h"

CWidgetPathologyInfo::CWidgetPathologyInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetPathologyInfo)
{
    ui->setupUi(this);
    m_lWidget=nullptr;

    /******** 初始化冠脉树图 ********/
    this->m_nGMType=this->GetGMGXType();
    if(this->m_nGMType<0)
    {
        this->m_nGMType=0;
    }

    /******** 初始化冠脉树图 ********/
    m_wgtPaintBoard=new CPaintBoard();
    ui->m_layoutShow->addWidget(m_wgtPaintBoard);
    m_wgtPaintBoard->SetVesselTree(this->m_nGMType);


    ui->m_ckbCZBB->setChecked(1);


    m_nSQLItemCount=0;//10-13

    //王家琪
    //初始化combobx下拉菜单
    /**
     * @brief 桥血管右侧下拉菜单初始化
     */
    const int NumberQXGY=6;
    QString NameQXGY[NumberQXGY]={NULL,"开口","近段","中段","远段","全程"};
    for(int i=0;i<NumberQXGY;i++)
    {
        ui->m_cmbQXGY->addItem(NameQXGY[i]);
    }


    /******** 初始化病变信息表 ********/
    QStringList sHeaderBB = QString("病变描述").simplified().split("/");
    m_modelBBInfo= new QStandardItemModel();
    m_modelBBInfo->setHorizontalHeaderLabels(sHeaderBB);
    //载入模型
    ui->m_tblBBInfo->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->m_tblBBInfo->setModel(m_modelBBInfo);
    ui->m_tblBBInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblBBInfo->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblBBInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblBBInfo->setColumnWidth(0,30);
    ui->m_tblBBInfo->horizontalHeader()->setStretchLastSection(1);
    ui->m_tblBBInfo->show();




    //**********初始化部分控件***************//
    ui->m_radBSF->setChecked(true);
    m_nZQZ=0;
    m_nFWZZ=0;
    m_nFWZY=0;
    ui->m_radLJFZW->setChecked(true);
    ui->m_radBZW->setChecked(true);   
}



CWidgetPathologyInfo::~CWidgetPathologyInfo()
{
    delete ui;
}


// /******** 存在病变 ********/
void CWidgetPathologyInfo::on_m_ckbCZBB_toggled(bool checked)
{
    if(checked)
    {
        ui->m_wgtInfo->show();
        ui->m_wgtShowPic->show();
        m_sIsHaveBB=QString::number(0);
    }
    else
    {
        ui->m_wgtInfo->hide();
        ui->m_wgtShowPic->hide();
        m_sIsHaveBB=QString::number(1);
    }
}


//10-4/******** 存在病变的四种状态 ********/
/**
 * @brief 点击一般病变按钮后，下面的所有组都可以用
 */
void CWidgetPathologyInfo::on_m_radYBBB_clicked()
{
    if(ui->m_radYBBB->isChecked())
    {
        ui->m_grpSFBS->setEnabled(true);
        ui->m_grpFW->setEnabled(true);
        ui->m_grpBBLX->setEnabled(true);
        ui->m_grpXZL->setEnabled(true);
        ui->m_grpXT->setEnabled(true);
        ui->m_grpGH->setEnabled(true);
        ui->m_grpXS->setEnabled(true);
        ui->m_grpXL->setEnabled(true);
        ui->m_grpLJFZ->setEnabled(true);
        ui->m_grpBZ->setEnabled(true);
    }
}
/**
 * @brief 点击瘤样扩张后，闭塞、钙化、血栓、血流、累及分支不可用
 */

void CWidgetPathologyInfo::on_m_radLYKZ_clicked()
{
    if(ui->m_radLYKZ->isChecked())
    {
        ui->m_grpSFBS->setEnabled(false);
        ui->m_grpFW->setEnabled(true);
        ui->m_grpBBLX->setEnabled(true);
        ui->m_grpXZL->setEnabled(true);
        ui->m_grpXT->setEnabled(true);
        ui->m_grpGH->setEnabled(false);
        ui->m_grpXS->setEnabled(false);
        ui->m_grpXL->setEnabled(false);
        ui->m_grpLJFZ->setEnabled(false);
        ui->m_grpBZ->setEnabled(true);

    }
}


/**
 * @brief 点击夹层按钮后，除备注外，均不可用
 */
void CWidgetPathologyInfo::on_m_radJC_clicked()
{
    if(ui->m_radJC->isChecked())
    {
        ui->m_grpSFBS->setEnabled(false);
        ui->m_grpFW->setEnabled(false);
        ui->m_grpBBLX->setEnabled(false);
        ui->m_grpXZL->setEnabled(false);
        ui->m_grpXT->setEnabled(false);
        ui->m_grpGH->setEnabled(false);
        ui->m_grpXS->setEnabled(false);
        ui->m_grpXL->setEnabled(false);
        ui->m_grpLJFZ->setEnabled(false);
        ui->m_grpBZ->setEnabled(true);
    }
}


 /**
 * @brief 点击管腔不规则后，除狭窄率，备注外，其他均不可用
 */
void CWidgetPathologyInfo::on_m_radGQ_clicked()
{
    if(ui->m_radGQ->isChecked())
    {
        ui->m_grpSFBS->setEnabled(false);
        ui->m_grpFW->setEnabled(false);
        ui->m_grpBBLX->setEnabled(false);
        ui->m_grpXZL->setEnabled(true);
        ui->m_grpXT->setEnabled(false);
        ui->m_grpGH->setEnabled(false);
        ui->m_grpXS->setEnabled(false);
        ui->m_grpXL->setEnabled(false);
        ui->m_grpLJFZ->setEnabled(false);
        ui->m_grpBZ->setEnabled(true);
    }

}
//////////////////////可以在控制左右冠的时候

/**
 * @brief 实现了右冠对下拉菜单内的不同文本的控制
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radYG_toggled(bool checked)
{
    //遍历本地缓存，找到右冠对应的血管位置存入临时列表中
    QStringList lTemp;
    foreach(QString temp,m_lYGAndZG)
    {
        if(temp.split("/")[1] == "0")
            lTemp.append(temp.split("/")[0]);
    }
    if(checked)
    {
        for(int i=0;i<lTemp.length();i++)
        {
            ui->m_cmbQXGZ->addItem(lTemp[i]);
        }
    }
    else
    {
        for(int i=lTemp.length()-1;i>=0;i--)
        {
            ui->m_cmbQXGZ->removeItem(i);
        }
    }
}


/**
 * @brief 左冠下拉菜单控制
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radZG_toggled(bool checked)
{
    //遍历本地缓存，找到右冠对应的血管位置存入临时列表中
    QStringList lTemp;
    foreach(QString temp,m_lYGAndZG)
    {
        if(temp.split("/")[1] == "1")
            lTemp.append(temp.split("/")[0]);
    }
    if(checked)
    {
        for(int i=0;i<lTemp.length();i++)
        {
            ui->m_cmbQXGZ->addItem(lTemp[i]);
        }
    }
    else
    {
        for(int i=lTemp.length()-1;i>=0;i--)
        {
            ui->m_cmbQXGZ->removeItem(i);
        }
    }
}



/**
 * @brief 左右冠的时候对应的累及血管
 * @param arg1
 */
void CWidgetPathologyInfo::on_m_cmbQXGZ_currentIndexChanged(const QString &arg1)
{
//现在考虑ZYM那边的冠脉类型，考虑左右冠脉对应的累及血管，添加累及分支
    QString sCondition;
    QString sGMType;
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="select GMType from BB_BBQT where SysCaseID ='"+m_sSysCaseId+"'";//读ZYM的表
    sqlReport->exec(sqlquery);
    while(sqlReport->next())
    {
        sGMType=sqlReport->value(0).toString();
    }

//第一种情况
    if(sGMType=="右优势型")
    {
        //右冠被选中0-0
        if(ui->m_radYG->isChecked())
        {
            //只考虑左右冠脉对应的累及血管，还没添加累及分支
            ui->m_cmbLJXGZ->clear();
            ui->m_cmbLJFZ->clear();
            sCondition = "00" + arg1;
            AddItemToList(GetCmbItemList(sCondition));
        }


        //左冠被选中时的累及血管0-1
        if(ui->m_radZG->isChecked())
        {
            ui->m_cmbLJXGZ->clear();
            ui->m_cmbLJFZ->clear();
            sCondition = "01" + arg1;
            AddItemToList(GetCmbItemList(sCondition));

        }
}

//第二种情况
        else if(sGMType=="左优势型")
        {   //右冠被选中 1-0
            if(ui->m_radYG->isChecked())
            {
                ui->m_cmbLJXGZ->clear();
                ui->m_cmbLJFZ->clear();
                sCondition = "10" + arg1;
                AddItemToList(GetCmbItemList(sCondition));
            }


            //左冠被选中 1-1
            else if(ui->m_radZG->isChecked())
            {
                ui->m_cmbLJXGZ->clear();
                ui->m_cmbLJFZ->clear();
                sCondition = "11" + arg1;
                AddItemToList(GetCmbItemList(sCondition));
            }
        }


//10-23 均衡型匹配

//第三种情况
        else if(sGMType=="均衡型")
        {
            //右冠被选中2-0
            if(ui->m_radYG->isChecked())
            {
                ui->m_cmbLJXGZ->clear();
                ui->m_cmbLJFZ->clear();
                sCondition = "20" + arg1;
                qDebug() << sCondition;
                AddItemToList(GetCmbItemList(sCondition));
            }

            //左管被选择2-1
            else if(ui->m_radZG->isChecked())
            {
                ui->m_cmbLJXGZ->clear();
                ui->m_cmbLJFZ->clear();
                sCondition = "21" + arg1;
                AddItemToList(GetCmbItemList(sCondition));
            }
        }
    delete sqlReport;
    sqlReport=NULL;
}




/**
 * @brief 累及分支后面的解释的槽函数
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radLJFZW_toggled(bool checked)
{
    if(checked)
        ui->m_cmbLJFZ->setEnabled(false);

    else
        ui->m_cmbLJFZ->setEnabled(true);

}


/**
 * @brief 备注的槽函数
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radBZW_toggled(bool checked)
{
    if(checked)
    {
        ui->m_lineBZ->setEnabled(false);
        ui->m_lineBZ->clear();
    }
    else
        ui->m_lineBZ->setEnabled(true);
}

/**
 * @brief 桥血管选中后，累计血管不可用
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radQXG_toggled(bool checked)
{
    if(checked)
        ui->m_cmbLJXGZ->setEnabled(false);
    else
        ui->m_cmbLJXGZ->setEnabled(true);
    this->InitQXGComboBox(checked);
}


//最新修改
/**
 * @brief 是否闭塞的状态切换
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radBSS_toggled(bool checked)
{
    const int NumberBSTime=2;
    QString BSTime[NumberBSTime]={"<=3个月", ">3个月"};

    if(checked)
    {
        ui->m_cmbSFBS->setEnabled(true);
        for(int i=0;i<NumberBSTime;i++)
        {
            ui->m_cmbSFBS->addItem(BSTime[i]);
        }
    }
    else
    {
        for(int i=NumberBSTime-1;i>=0;i--)
        {
            ui->m_cmbSFBS->removeItem(i);
        }
        ui->m_cmbSFBS->setEnabled(false);
    }

}

//10-6
/**
 * @brief 实现狭窄率的准确率和范围率只能二选一
 * @param checked
 */
void CWidgetPathologyInfo::on_m_radZQZ_toggled(bool checked)//准确值的状态切换
{
    if(checked)
    {
        ui->m_spbZQZ->setEnabled(true);
        ui->m_spbFWZZ->setEnabled(false);
        ui->m_spbFWZY->setEnabled(false);
        ui->m_spbFWZZ->setValue(0);
        ui->m_spbFWZY->setValue(0);
    }
    else
    {
        ui->m_spbZQZ->setEnabled(false);
        ui->m_spbZQZ->setValue(0);
        ui->m_spbFWZZ->setEnabled(true);
        ui->m_spbFWZY->setEnabled(true);
    }
}
void CWidgetPathologyInfo::on_m_radFWZ_toggled(bool checked)//范围值的状态切换
{
    if(checked)
    {
        ui->m_spbZQZ->setEnabled(false);
        ui->m_spbZQZ->setValue(0);
        ui->m_spbFWZZ->setEnabled(true);
        ui->m_spbFWZY->setEnabled(true);
    }
    else
    {
        ui->m_spbZQZ->setEnabled(true);
        ui->m_spbFWZZ->setEnabled(false);
        ui->m_spbFWZY->setEnabled(false);
        ui->m_spbFWZZ->setValue(0);
        ui->m_spbFWZY->setValue(0);
    }
}


//10-5
/**
 * @brief 将获取已被选择的radiobutton的名称
 * @return
 */
QString CWidgetPathologyInfo::GetButtonText(const QGroupBox *grp)
{
    auto grpList=grp->children();
    for(int i=0;i<grpList.length();i++)
    {
        if(grpList.at(i)->inherits("QRadioButton"))
        {
            auto currentRadbutton=qobject_cast<QRadioButton*>(grpList.at(i));
            if(grp->isEnabled()==false)   //判断当前按钮是否可以，不可用则不会输出
                return NULL;
            else if(currentRadbutton->isChecked())
                return currentRadbutton->text();
        }
    }
}

/**
 * @brief 获取combobox的内容
 * @param grp
 * @return
 */
QString CWidgetPathologyInfo::on_m_cmbQXGZ_currentTextChanged(const QString &arg1)  //桥血管左侧下拉框
{
    return arg1;
}
QString CWidgetPathologyInfo::on_m_cmbQXGY_currentTextChanged(const QString &arg1)  //桥血管右侧下拉框
{
    return arg1;
}
QString CWidgetPathologyInfo::on_m_cmbLJXGZ_currentTextChanged(const QString &arg1)  //累及血管左侧下拉框
{
    if(ui->m_cmbLJXGZ->isEnabled()==true)
        return arg1;
    else
        return NULL;
}
/**
 * @brief 累及分支的内容获取
 * @param arg1
 */
QString CWidgetPathologyInfo::on_m_cmbLJFZ_currentTextChanged(const QString &arg1)
{
    if(ui->m_cmbLJFZ->isEnabled()==true)
        return arg1;
    else
        return NULL;
}


/**
 * @brief 获取是否闭塞的内容
 * @param arg1
 */
QString CWidgetPathologyInfo::on_m_cmbSFBS_currentTextChanged(const QString &arg1)
{
    if(ui->m_cmbSFBS->isEnabled()==true)
        return arg1;
    else
        return NULL;
}


/**
 * @brief 获取QSpinBox内容，狭窄率的准确值和范围值
 * @param arg1
 */
int CWidgetPathologyInfo::on_m_spbZQZ_valueChanged(const int arg1)//准确值
{
    if(ui->m_spbZQZ->isEnabled())
        return arg1;
    else
        return 0;
}
int CWidgetPathologyInfo::on_m_spbFWZZ_valueChanged(const int arg1)//范围值左侧
{
    if(ui->m_spbFWZZ->isEnabled())
        return arg1;
    else return 0;
}
int CWidgetPathologyInfo::on_m_spbFWZY_valueChanged(const int arg1)//范围值右侧
{
    if(ui->m_spbFWZZ->isEnabled())
        return arg1;
    else
        return 0;
}
QString CWidgetPathologyInfo::GetLineEditText(const QLineEdit *linEdit)//获取备注内容
{
    return linEdit->text();
}



/**
 * @brief 最后显示之前选择的结果Listwidget
 * @param lstw 显示框
 * @param str全部选择结果的信息
 */
void CWidgetPathologyInfo::SetListWidgetText(QListWidget *lstw,QString str)
{
    lstw->addItem(str);
}


/**
 * @brief 更新信息并显示
 */
void CWidgetPathologyInfo::on_m_btnGX_clicked()
{
    //*************检查是否有应选而未选的按钮***********//
    while(CheckAllButtonStatus())
    {
        int status =CheckAllButtonStatus();
        QStringList AllGroupBox={"病变性质","病变血管位置","是否100%闭塞","范围",
                                 "病变类型","狭窄率","形态","钙化","血栓",
                                 "TIMI血流","累及分支","备注"};
        QString ErrorGrp=AllGroupBox.at(status-1);//
        QMessageBox *Qmeb=new QMessageBox;
        Qmeb->warning(NULL, "warning", "请选择"+ErrorGrp+"的内容", QMessageBox::Yes);
        if(Qmeb->Yes)
        {
            qDebug()<<"Try it Again";
            return ;
        }

    }

    //10-5更新获取病变性质和病变位置的radiobutton内容
    //10-6获取桥血管后两个combobox的内容,累及血管后的combobox内容
    m_sstrQXGZ = on_m_cmbQXGZ_currentTextChanged(ui->m_cmbQXGZ->currentText());//桥血管左
    m_sstrQXGZ=m_sstrQXGZ.remove(" ");
    m_sstrQXGY = on_m_cmbQXGY_currentTextChanged(ui->m_cmbQXGY->currentText());//桥血管右
    m_lShowInfo<<m_sstrQXGZ<<m_sstrQXGY;

    m_sstrLJXG = on_m_cmbLJXGZ_currentTextChanged(ui->m_cmbLJXGZ->currentText());//累及分支
    if(m_sstrLJXG!=NULL)
    {
        m_lShowInfo<<"-"<<m_sstrLJXG;//存储到一个QString链表中
    }

    //10-6获取闭塞状态
    m_sstrSFBS=on_m_cmbSFBS_currentTextChanged(ui->m_cmbSFBS->currentText());
    if(m_sstrSFBS!=NULL)
    {
        m_lShowInfo<<"100%闭塞"+m_sstrSFBS;
    }


    //获取病变范围
    m_sstrFW=GetButtonText(ui->m_grpFW);
    if(ui->m_grpFW->isEnabled())
    {
        if(m_sstrFW!="无")
        {
            m_lShowInfo<<m_sstrFW+"性";
        }
    }


    //获取病变类型
    m_sstrBBLX=GetButtonText(ui->m_grpBBLX);
    if(ui->m_grpBBLX->isEnabled())
    {
        if(m_sstrBBLX!="无")
        {
            m_lShowInfo<<m_sstrBBLX;
        }
    }

    //病变性质
    m_sstrBBXZ = GetButtonText(ui->m_grpBBXZ);//病变性质

    m_sstrBBWZ = GetButtonText(ui->m_grpBBWZ);//病变位置

    //10-6获取狭窄率的准确值和范围值
    QString strXZL;//狭窄率
    if(ui->m_spbZQZ->isEnabled()==true&&ui->m_spbFWZZ->isEnabled()==false)
    {
        m_nZQZ= on_m_spbZQZ_valueChanged(ui->m_spbZQZ->value());
        strXZL=QString::number(m_nZQZ)+"%";

        //当病变类型为无时，为了语句明确，添加狭窄率表示
        if(m_sstrBBLX=="无"||ui->m_grpBBLX->isEnabled()==false)
        {
            m_lShowInfo<<"狭窄率"+strXZL+",";
        }
        else
            m_lShowInfo<<strXZL+",";
    }
    else if(ui->m_spbFWZZ->isEnabled()==true&&ui->m_spbZQZ->isEnabled()==false)
    {
        m_nFWZZ=on_m_spbFWZZ_valueChanged(ui->m_spbFWZZ->value());
        m_nFWZY=on_m_spbFWZY_valueChanged(ui->m_spbFWZY->value());
        strXZL=QString::number(m_nFWZZ)+"%-"+QString::number(m_nFWZY)+"%";

        //当病变类型为无时，为了语句明确，添加狭窄率表示
        if(m_sstrBBLX=="无"||ui->m_grpBBLX->isEnabled()==false)
        {
            m_lShowInfo<<"狭窄率"+strXZL+",";
        }
        else
            m_lShowInfo<<strXZL+",";
        //m_lShowInfo<<strXZL+",";
    }
    else
    {
        strXZL="";
        m_lShowInfo<<",";
    }

    //获取病变形态状态
    m_sstrXT=GetButtonText(ui->m_grpXT);//形态
    if(ui->m_grpXT->isEnabled())
    {
        m_lShowInfo<<"病变呈"+m_sstrXT+",";
    }

    //获取钙化状态
    m_sstrGH=GetButtonText(ui->m_grpGH);//钙化
    if(ui->m_grpGH->isEnabled())
    {
        m_lShowInfo<<m_sstrGH+"钙化,";
    }

    //获取血栓状态
    m_sstrXS=GetButtonText(ui->m_grpXS);//血栓
    if(ui->m_grpXS->isEnabled())
    {
        m_lShowInfo<<m_sstrXS+"血栓,";
    }

    //获取血流状态
    m_sstrXL=GetButtonText(ui->m_grpXL);//血流
    if(ui->m_grpXL->isEnabled())
    {
        m_lShowInfo<<"TIMI血流"+m_sstrXL+",";
    }


    //10-6累及分支的内容
    m_sstrLJFZ=on_m_cmbLJFZ_currentTextChanged(ui->m_cmbLJFZ->currentText());//累及分支
    if(ui->m_cmbLJFZ->isEnabled())
    {
        if(ui->m_cmbLJFZ->currentText()!=NULL)
        {
            m_lShowInfo<<"累及分支"+m_sstrLJFZ+",";
        }
    }


    //获取备注状态
    m_sstrBZ=GetLineEditText(ui->m_lineBZ);
    if(ui->m_radBZW->isChecked()==true)
        m_sstrBZ="";
    else if(ui->m_radBZY->isChecked()==true)
        m_lShowInfo<<m_sstrBZ;

    //*************添加数据库中的SysCaseID************
    InsertSQL_SysCaseID();//获取到m_nLastID（***最重要***）

    m_sstrConclusion=m_lShowInfo.join("");
    m_lShowInfo.clear();


    //实现往Qtableview中插入数据的功能
    m_modelBBInfo->setItem(m_nNumListItem-1,0,new QStandardItem(m_sstrConclusion));

    //更新数据库，页面切换只进行无病变的信息插入，有病变的用按钮控制
    UpdateSqDB();
    return ;
}

//********************重要************************
//////////////////////////////////////////////////////////////
/**
 * 接收SysCaseId
 * @brief CWidgetPathologyInfo::SetSysCaseId
 * @param pSysCaseId
 */
void CWidgetPathologyInfo::SetSysCaseId(const QString pSysCaseId)
{
    m_sSysCaseId=pSysCaseId;
    this->SetSqDB();
}
///////////////////////////////////////////////////////////////


/**
 * @brief 访问数据库，更新ui
 */
void CWidgetPathologyInfo::SetSqDB()
{  
    int i=0;//紧接着的遍历用的

    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());//再查询剩余的记录

    QString sDelete="delete from BB_BB where SysCaseID= '"+m_sSysCaseId+"'and isHaveBB=1";
    sqlReport->exec(sDelete);

    QString sQuery="select * from BB_BB where SysCaseID= '"+m_sSysCaseId+"' order by ID";
    sqlReport->exec(sQuery);
    while(sqlReport->next())
    {
        ////////////////////////////////////
        // lyh
        m_modelBBInfo->setItem(i,0,new QStandardItem(sqlReport->value(22).toString()));

        m_nIndexToId[i]=sqlReport->value(0).toInt();
        i++;
        m_nSQLItemCount++;
        m_nNumListItem++;
    }
    delete sqlReport;
    sqlReport=NULL;


    ///YL
    //**********初始化下拉菜单临时缓存(血管位置，累及血管，受累分支)***************//
    InitializeCmbsItem();
    UpdateQXGItem();
}


/**
 * @brief UpdateSqDB   更新数据库内容，向数据库插入当前页面的信息
 */
void CWidgetPathologyInfo::UpdateSqDB()
{
    m_sIdLast=QString::number(m_nLastID);//转换成字符串

    UpdateSQL_bbRocord();//bbRecord
    UpdateSQL_BBXZ();//BBXZ
    UpdateSQL_bbgm();//bbgm
    UpdateSQL_BS();//BS
    UpdateSQL_FW();//FW
    UpdateSQL_BType();//Btype
    UpdateSQL_XT();//XT
    UpdateSQL_GH();//GH
    UpdateSQL_XS();//XS
    UpdateSQL_TIMI();//TIMI
    UpdateSQL_FZ();//FZ
    UpdateSQL_BZ();//BZ
    UpdateSQL_bbzywz();//bbzywz
    UpdateSQL_bbxxwz();//bbxxwz
    UpdateSQL_bbljxg();//bbljxg
    UpdateSQL_xzl();//xzl
    UpdateSQL_isHaveBB();//isHaveBB
}

/**
 * @brief CWidgetPathologyInfo::UpdateReportTable
 */
void CWidgetPathologyInfo::UpdateReportTable()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sBBRec="";
    QString sSqlReport="select bbRecord from BB_BB where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReport);
    while(sqlReport->next())
    {
        sBBRec+=sqlReport->value(0).toString();
    }

    sSqlReport="update operateitem set bbresult='"+sBBRec+"' where SysCaseID ='"+m_sSysCaseId+"'";
    sqlReport->exec(sSqlReport);

    delete sqlReport;
    sqlReport=NULL;
}


/**
 * @brief 获取是否病变的信息(已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetisHaveBB_ButtonFromSqDB(QString str)
{
    if(str=="0")//有病
    {
        ui->m_ckbCZBB->setChecked(true);
        ui->m_wgtInfo->show();
        ui->m_wgtShowPic->show();
    }
    else if(str=="1")
    {
        ui->m_ckbCZBB->setChecked(false);
        ui->m_wgtInfo->hide();
        ui->m_wgtShowPic->hide();
    }
}


/**
 * @brief 从数据库读病变性质(已改完)
 * @param str(
 */
void CWidgetPathologyInfo::GetBBXZ_ButtonFromSqDB(QString str)
{

    if(QString::compare(str,"一般病变")==0)
    {
        ui->m_radYBBB->setChecked(true);
        on_m_radYBBB_clicked();
    }
    else if(QString::compare(str,"瘤样扩张")==0)
    {
        ui->m_radLYKZ->setChecked(true);
        on_m_radLYKZ_clicked();
    }
    else if(QString::compare(str,"夹层")==0)
    {
        ui->m_radJC->setChecked(true);
        on_m_radJC_clicked();
    }
    else if(QString::compare(str,"管腔不规则")==0)
    {
        ui->m_radGQ->setChecked(true);
        on_m_radGQ_clicked();
    }
    else
        return ;
}

/**
 * @brief 从数据库读病变冠脉（已改完）
 * @param str
 */
void CWidgetPathologyInfo::Getbbgm_ButtonFromSqDB(QString str)
{
    if(str=="右冠")
        ui->m_radYG->setChecked(true);
    else if(str=="左冠")
        ui->m_radZG->setChecked(true);
    else if(str=="桥血管")
    {
        ui->m_radQXG->setChecked(true);
        on_m_radQXG_toggled(1);
    }
    else
        return ;
}

/**
 * @brief QXGZ的信息，，桥血管左侧第一个combobox（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetQxgz_ComboboxFromSqDB(QString str)
{
    ui->m_cmbQXGZ->setCurrentText(str);
}
/**
 * @brief QXGY的信息，桥血管左侧第二个的combobox（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetQxgy_ComboboxFromSqDB(QString str)
{
    ui->m_cmbQXGY->setCurrentText(str);
}

/**
 * @brief LJXG的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetLJXG_ComboboxFromSqDB(QString str)
{
    ui->m_cmbLJXGZ->setCurrentText(str);
}


/**
 * @brief BS的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetBS_ButtonFromSqDB(QString str1,QString str2)
{
    if(str1=="否")
        ui->m_radBSF->setChecked(true);
    else if(str1=="是")
    {
        ui->m_radBSS->setChecked(true);
        ui->m_cmbSFBS->setCurrentText(str2);
    }
}

/**
 * @brief 狭窄率的信息(已改完)
 * @param strmin
 * @param strmax
 */
void CWidgetPathologyInfo::GetXZL_ButtonFromSqDB(int strmin,int strmax)
{
    if(strmin==strmax)
    {
        ui->m_radZQZ->setChecked(true);
        on_m_radZQZ_toggled(1);
        ui->m_spbZQZ->setValue(strmin);
    }
    else
    {
        on_m_radFWZ_toggled(1);
        ui->m_radFWZ->setChecked(true);
        ui->m_spbFWZZ->setValue(strmin);
        ui->m_spbFWZY->setValue(strmax);
    }
}

/**
 * @brief FW的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetFW_ButtonFromSqDB(QString str)
{

    if(QString::compare(str,"无")==0)
        ui->m_radFWW->setChecked(true);
    else if(QString::compare(str,"局限")==0)
        ui->m_radJX->setChecked(true);
    else if(QString::compare(str,"节段")==0)
        ui->m_radJD->setChecked(true);
    else if(QString::compare(str,"弥漫")==0)
        ui->m_radMM->setChecked(true);
    else
        return ;
}
/**
 * @brief 病变类型信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetBType_ButtonFromSqDB(QString str)
{

    if(QString::compare(str,"无")==0)
        ui->m_radLXW->setChecked(true);
    else if(QString::compare(str,"再狭窄")==0)
        ui->m_radZXZ->setChecked(true);
    else if(QString::compare(str,"原支架内再狭窄")==0)
        ui->m_radYZJ->setChecked(true);
    else if(QString::compare(str,"NULL")==0)
        ui->m_radLXW->setChecked(true);
    else
        return ;
}


/**
 * @brief 形态的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetXT_ButtonFromSqDB(QString str)
{

    if(QString::compare(str,"同心")==0)
        ui->m_radTX->setChecked(true);
    else if(QString::compare(str,"偏心")==0)
        ui->m_radPX->setChecked(true);
    else if(QString::compare(str,"NULL")==0)
        ui->m_radTX->setChecked(true);
    else
        return ;
}


/**
 * @brief 钙化的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetGH_ButtonFromSqDB(QString str)
{
    if(QString::compare(str,"无")==0)
        ui->m_radGHW->setChecked(true);
    else if(QString::compare(str,"NULL")==0)
        ui->m_radGHW->setChecked(true);
    else if(QString::compare(str,"轻度")==0)
        ui->m_radQD->setChecked(true);
    else if(QString::compare(str,"重度")==0)
        ui->m_radZD->setChecked(true);
    else
        return ;

}


/**
 * @brief 血栓的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetXS_ButtonFromSqDB(QString str)
{
    if(QString::compare(str,"无")==0)
        ui->m_radXSW ->setChecked(true);
    else if(QString::compare(str,"NULL")==0)
        ui->m_radXSW ->setChecked(true);
    else if(QString::compare(str,"有")==0)
        ui->m_radXSY->setChecked(true);
    else
        return ;
}


/**
 * @brief TIMI血流（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetTIMI_ButtonFromSqDB(QString str)
{
    if(QString::compare(str,"0级")==0)
        ui->m_rad0J->setChecked(true);
    else if(QString::compare(str,"Ⅰ级")==0)
        ui->m_rad1J->setChecked(true);
    else if(QString::compare(str,"Ⅱ级")==0)
        ui->m_rad2J->setChecked(true);
    else if(QString::compare(str,"Ⅲ级")==0)
        ui->m_rad3J->setChecked(true);
    else
        return ;
}


/**
 * @brief 从数据库获取累及分支（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetFZ_ButtonFromSqDB(QString str)
{
    if(QString::compare(str,"NULL")==0)
        ui->m_radLJFZW ->setChecked(true);
    else
    {
        ui->m_radLJFZY->setChecked(true);
        ui->m_cmbLJFZ->setCurrentText(str);
    }

}


/**
 * @brief 备注的信息(已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetBZ_ButtonFromSqDB(QString str)
{
    if(QString::compare(str,"NULL")==0)
        ui->m_radBZW ->setChecked(true);
    else
    {
        ui->m_radBZY->setChecked(true);
        ui->m_lineBZ->setText(str);
    }
}


/**
 * @brief 病变记录的信息（已改完）
 * @param str
 */
void CWidgetPathologyInfo::GetbbRecord_ButtonFromSqDB(QString str)
{
    qDebug()<<"GetbbRecord_ButtonFromSqDB"<<str;
}

/**
 * @brief 获取单个grp中是否有应选而未选的按钮的信息
 */
bool CWidgetPathologyInfo::GetButtonStatus(const QGroupBox *grp)
{
    int nNoCheckCount=0;//记录未选的按钮数量
    int nRadioButtoncount=0;//记录Radbut的数量
    auto grpList=grp->children();
    for(int i=0;i<grpList.length();i++)
    {
        if(grpList.at(i)->inherits("QRadioButton"))
        {
            nRadioButtoncount++;
            auto currentRadbutton=qobject_cast<QRadioButton*>(grpList.at(i));
            if(grp->isEnabled()==false)   //判断当前按钮是否可以，不可用则不存在应选而未选的状态
                return 0;
            else if(grp->isEnabled()==true&&currentRadbutton->isChecked()==true)//存在应选而未选的状态
                return 0;
            else if(grp->isEnabled()==true&&currentRadbutton->isChecked()==false)
                nNoCheckCount++;
        }
    }
    if(nNoCheckCount==nRadioButtoncount)//未选的按钮数量等于按钮组数量， 即全未选！！
        return 1;
}


/**
 * @brief 获取整个界面是否有应选而未选的按钮信息
 * @return
 */
int CWidgetPathologyInfo::CheckAllButtonStatus()
{
    if(GetButtonStatus(ui->m_grpBBXZ))
        return 1;
    else if(GetButtonStatus(ui->m_grpBBWZ))
        return 2;
    else if(GetButtonStatus(ui->m_grpSFBS))
        return 3;
    else if(GetButtonStatus(ui->m_grpFW))
        return 4;
    else if(GetButtonStatus(ui->m_grpBBLX))
        return 5;
    else if(GetButtonStatus(ui->m_grpXZL))
        return 6;
    else if(GetButtonStatus(ui->m_grpXT))
        return 7;
    else if(GetButtonStatus(ui->m_grpGH))
        return 8;
    else if(GetButtonStatus(ui->m_grpXS))
        return 9;
    else if(GetButtonStatus(ui->m_grpXL))
        return 10;
    else if(GetButtonStatus(ui->m_grpLJFZ))
        return 11;
    else if(GetButtonStatus(ui->m_grpBZ))
        return 12;
    else
        return 0;
}


/**
 * @brief  插入SysCaseID的信息
 */
void CWidgetPathologyInfo::InsertSQL_SysCaseID()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    QStringList sOldID;
    QStringList sNewID;

    //*******遍历找差集*********//
    //旧的ID数组
    QString sQueryId="select ID from BB_BB where SysCaseID='"+m_sSysCaseId+"' order by ID";
    sqlReport->exec(sQueryId);
    while(sqlReport->next())
    {
        sOldID<<sqlReport->value(0).toString();
    }
    //插入操作，ID有了变化
    QString sInsert="insert into BB_BB(SysCaseID) values('"+m_sSysCaseId+"')";
    sqlReport->exec(sInsert);
    //
    //新的ID数组
    QString sQuery="select ID from BB_BB where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sQuery);
    while(sqlReport->next())
    {
        sNewID<<sqlReport->value(0).toString();
    }
    //进行比较
    QStringList Result;

    for(QString str:sNewID)
    {
        if(!sOldID.contains(str))
        {
            Result<<str;
        }
    }
    //得到最新的ID
    qDebug()<<"new ID:"<<Result.at(0);
    m_nLastID=Result.at(0).toInt();

    m_nSQLItemCount++;//数据库中数据个数加一
    m_nNumListItem++;//TableView中数据加一

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 向数据库存入病变性质的信息
 */
void CWidgetPathologyInfo::UpdateSQL_BBXZ()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="update BB_BB set BBXZ ='"+m_sstrBBXZ+"' where Id="+m_sIdLast;
    sqlReport->exec(sqlquery);
    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新数据库中的bbRecord
 */
void CWidgetPathologyInfo::UpdateSQL_bbRocord()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="update BB_BB set bbRecord ='"+m_sstrConclusion+"' where Id="+m_sIdLast;
    sqlReport->exec(sqlquery);
    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新数据库中的bbgm
 */
void CWidgetPathologyInfo::UpdateSQL_bbgm()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="update BB_BB set bbgm  ='"+m_sstrBBWZ+"' where Id="+m_sIdLast;
    sqlReport->exec(sqlquery);

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新数据库中的 BS
 */
void CWidgetPathologyInfo::UpdateSQL_BS()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QSqlQuery *sqlReport1=new QSqlQuery(SQLDB::GetDfytCathLab());
    QSqlQuery *sqlReport2=new QSqlQuery(SQLDB::GetDfytCathLab());
    //如果闭塞按钮不可用，则不存
    if(ui->m_grpSFBS->isEnabled()==false)
    {
        QString sqlquery="update BB_BB set BS ='' where Id="+m_sIdLast;
        sqlReport->exec(sqlquery);
        QString sqlquery1="update BB_BB set CTO ='"+m_sstrSFBS+"' where Id="+m_sIdLast;//11-5
        sqlReport1->exec(sqlquery1);
    }


    //若可用，则正常存
    else if(ui->m_radBSS->isChecked()==true)
    {
        QString BSText="是";
        QString sqlquery1="update BB_BB set CTO ='"+m_sstrSFBS+"' where Id="+m_sIdLast;
        sqlReport1->exec(sqlquery1);
        QString sqlquery2="update BB_BB set BS ='"+BSText+"' where Id="+m_sIdLast;
        sqlReport2->exec(sqlquery2);
    }
    else if(ui->m_radBSF->isChecked()==true)
    {
        QString BSText="否";
        QString sqlquery1="update BB_BB set CTO ='"+m_sstrSFBS+"' where Id="+m_sIdLast;
        sqlReport1->exec(sqlquery1);
        QString sqlquery2="update BB_BB set BS ='"+BSText+"' where Id="+m_sIdLast;
        sqlReport2->exec(sqlquery2);
    }
}

/**
 * @brief 更新数据库中的FW
 */
void CWidgetPathologyInfo::UpdateSQL_FW()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="update BB_BB set FW ='"+m_sstrFW+"' where Id="+m_sIdLast;
    sqlReport->exec(sqlquery);

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新数据中的BType
 */
void CWidgetPathologyInfo::UpdateSQL_BType()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="update BB_BB set BType ='"+m_sstrBBLX+"' where Id="+m_sIdLast;
    sqlReport->exec(sqlquery);

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新数据库中的XT
 */
void CWidgetPathologyInfo::UpdateSQL_XT()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery="update BB_BB set XT ='"+m_sstrXT+"' where Id="+m_sIdLast;
    sqlReport->exec(sqlquery);
    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief 更新数据库中的GH
 */
void CWidgetPathologyInfo::UpdateSQL_GH()
{
    QSqlQuery *sqlReport7=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery7="update BB_BB set GH ='"+m_sstrGH+"' where Id="+m_sIdLast;
    sqlReport7->exec(sqlquery7);
}

/**
 * @brief 更新数据库中的XS
 */
void CWidgetPathologyInfo::UpdateSQL_XS()
{
    QSqlQuery *sqlReport8=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery8="update BB_BB set XS ='"+m_sstrXS+"' where Id="+m_sIdLast;
    sqlReport8->exec(sqlquery8);
}

/**
 * @brief 更新数据库中的TIMI
 */
void CWidgetPathologyInfo::UpdateSQL_TIMI()
{
    QSqlQuery *sqlReport9=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery9="update BB_BB set TIMI ='"+m_sstrXL+"' where Id="+m_sIdLast;
    sqlReport9->exec(sqlquery9);
}

/**
 * @brief 更新数据库中FZ
 */
void CWidgetPathologyInfo::UpdateSQL_FZ()
{
    QSqlQuery *sqlReport10=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery10="update BB_BB set FZ ='"+m_sstrLJFZ+"' where Id="+m_sIdLast;
    sqlReport10->exec(sqlquery10);
}

/**
 * @brief 更新数据库中的BZ
 */
void CWidgetPathologyInfo::UpdateSQL_BZ()
{
    QSqlQuery *sqlReport11=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery11="update BB_BB set BZ ='"+m_sstrBZ+"' where Id="+m_sIdLast;
    sqlReport11->exec(sqlquery11);
}

/**
 * @brief 更新数据库中isHaveBB
 */
void CWidgetPathologyInfo::UpdateSQL_isHaveBB()
{
    QSqlQuery *sqlReport17=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery17="update BB_BB set isHaveBB ='"+m_sIsHaveBB +"' where Id="+m_sIdLast;//默认给0，即默认有病
    sqlReport17->exec(sqlquery17);
    qDebug()<<"click 1 m_nSQLItemCount"<<m_nSQLItemCount;
}

/**
 * @brief 更新数据库中bbzywz，也就是桥血管左侧第一个文本框
 */
void CWidgetPathologyInfo::UpdateSQL_bbzywz()
{
    QSqlQuery *sqlReport12=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery12="update BB_BB set bbzywz ='"+m_sstrQXGZ+"' where Id="+m_sIdLast;
    sqlReport12->exec(sqlquery12);
}

/**
 * @brief 更新数据库中Updatebbxxwz，也就是桥血管左侧第二个文本框
 */
void CWidgetPathologyInfo::UpdateSQL_bbxxwz()
{
    QSqlQuery *sqlReport13=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sqlquery13="update BB_BB set bbxxwz ='"+m_sstrQXGY+"' where Id="+m_sIdLast;
    sqlReport13->exec(sqlquery13);
}

/**
 * @brief 更新数据库中bbljxg
 */
void CWidgetPathologyInfo::UpdateSQL_bbljxg()
{    QSqlQuery *sqlReport14=new QSqlQuery(SQLDB::GetDfytCathLab());
     QString sqlquery14="update BB_BB set bbljwz ='"+m_sstrLJXG+"' where Id="+m_sIdLast;
     sqlReport14->exec(sqlquery14);
}

/**
 * @brief 更新数据库中XZL
 */
void CWidgetPathologyInfo::UpdateSQL_xzl()
{
    QSqlQuery *sqlReport15=new QSqlQuery(SQLDB::GetDfytCathLab());
    QSqlQuery *sqlReport16=new QSqlQuery(SQLDB::GetDfytCathLab());
    if(ui->m_spbZQZ->isEnabled())
    {
        QString sZQZ=QString::number(m_nZQZ);
        QString sqlquery15="update BB_BB set xzlmin ='"+sZQZ+"' where Id="+m_sIdLast;
        sqlReport15->exec(sqlquery15);
        QString sqlquery16="update BB_BB set xzlmax ='"+sZQZ+"' where Id="+m_sIdLast;
        sqlReport16->exec(sqlquery16);
    }
    else
    {
        QString sFWZZ=QString::number(m_nFWZZ);
        QString sFWZY=QString::number(m_nFWZY);
        QString sqlquery15="update BB_BB set xzlmin ='"+sFWZZ+"' where Id="+m_sIdLast;
        sqlReport15->exec(sqlquery15);
        QString sqlquery16="update BB_BB set xzlmax ='"+sFWZY+"' where Id="+m_sIdLast;
        sqlReport16->exec(sqlquery16);
    }
}

/**
 * @brief CWidgetPathologyInfo::UpdateUIFromDatabase 读取数据库，更新ui
 */
void CWidgetPathologyInfo::UpdateUIFromDatabase()
{
    // 初始化冠脉树图
    /******** 初始化冠脉树图 ********/
    this->m_nGMType=this->GetGMGXType();
    if(this->m_nGMType<0)
    {
        this->m_nGMType=0;
    }
    m_wgtPaintBoard->SetVesselTree(this->m_nGMType);

    // 初始化桥血管
    this->UpdateQXGItem();
    this->InitQXGComboBox(ui->m_radQXG->isChecked());

    this->InitYGComboBox(ui->m_radYG->isChecked());
    this->InitZGComboBox(ui->m_radZG->isChecked());
}
/**
 * @brief UpdateDatabaseFromUI  读取UI，更新数据库
 */
void CWidgetPathologyInfo::UpdateDatabaseFromUI()
{
    //不存在病变，在页面切换时将无病的信息存入数据库中
    if(m_sIsHaveBB.toInt()==1)
    {
        int NoBBCount=0;
        QSqlQuery *sqlNoCount=new QSqlQuery(SQLDB::GetDfytCathLab());
        QSqlQuery *sqlNoBB=new QSqlQuery(SQLDB::GetDfytCathLab());

        //获取没有病变的个数
        QString sqlNoBBCount="select count(*) from BB_BB where SysCaseID='"+m_sSysCaseId+"'and isHaveBB=1";
        sqlNoCount->exec(sqlNoBBCount);
        while(sqlNoCount->next())
        {
            NoBBCount=sqlNoCount->value(0).toInt();
        }

        //如果没有病变的个数>1,则不再继续添加
        //否则，添加一条无病变的信息
        if(NoBBCount>=1)
            return ;
        else
        {
            QString sqlquNoBB="insert into BB_BB (SysCaseID,isHaveBB) values ('" + m_sSysCaseId + "','1')";
            sqlNoBB->exec(sqlquNoBB);
        }
    }
    this->UpdateReportTable();
}

void CWidgetPathologyInfo::InitQXGComboBox(bool checked)
{   
    if(checked)
    {
        ui->m_cmbQXGZ->clear();
        ui->m_cmbLJXGZ->clear();
        for(int i=0;i<m_slstQXG.length();i++)
        {
            ui->m_cmbQXGZ->addItem(m_slstQXG.at(i));
        }
    }
}

void CWidgetPathologyInfo::InitYGComboBox(bool checked)
{    
    //遍历本地缓存，找到右冠对应的血管位置存入临时列表中
    QStringList lTemp;
    foreach(QString temp,m_lYGAndZG)
    {
        if(temp.split("/")[1] == "0")
            lTemp.append(temp.split("/")[0]);
    }
    if(checked)
    {
        ui->m_cmbQXGZ->clear();
        ui->m_cmbLJXGZ->clear();
        for(int i=0;i<lTemp.length();i++)
        {
            ui->m_cmbQXGZ->addItem(lTemp[i]);
        }
        qDebug()<<ui->m_cmbQXGZ->count();
    }
}

void CWidgetPathologyInfo::InitZGComboBox(bool checked)
{  
    //遍历本地缓存，找到右冠对应的血管位置存入临时列表中
    QStringList lTemp;
    foreach(QString temp,m_lYGAndZG)
    {
        if(temp.split("/")[1] == "1")
            lTemp.append(temp.split("/")[0]);
    }
    if(checked)
    {
        ui->m_cmbQXGZ->clear();
        ui->m_cmbLJXGZ->clear();
        for(int i=0;i<lTemp.length();i++)
        {
            ui->m_cmbQXGZ->addItem(lTemp[i]);
        }
    }
}

/**
 * @brief CWidgetPathologyInfo::GetGMGXType
 * @return
 */
int CWidgetPathologyInfo::GetGMGXType()
{
   int nType=-1;
    /********* 获取冠脉类型 *********/
   QSqlQuery* sqlReport = new QSqlQuery(SQLDB::GetDfytCathLab());
   QString sTypeGMGX = "";
   QString sqlType="select GMType from BB_BBQT where SysCaseID ='"+m_sSysCaseId+"'";
   sqlReport->exec(sqlType);
   while(sqlReport->next())
   {
       sTypeGMGX = sqlReport->value(0).toString();
   }
   delete sqlReport;
   sqlReport=NULL;

   /********* 转换冠脉类型为数字*********/
   if(sTypeGMGX == "右优势型")
   {
       nType=Right;
   }
   if(sTypeGMGX == "左优势型")
   {
       nType=Left;
   }
   if(sTypeGMGX == "均衡型")
   {
       nType=Balance;
   }
   return nType;
}


/**
 * @brief 双击Item初始化UI界面
 * @param index
 */
void CWidgetPathologyInfo::on_m_tblBBInfo_doubleClicked(const QModelIndex &index)
{
    //更新一下m_nIndexToId
    int i=0;
    QSqlQuery *sqlReport1=new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlReport1->exec("select * from BB_BB where SysCaseID= '"+m_sSysCaseId+"' order by ID");
    while(sqlReport1->next())
    {
        m_nIndexToId[i]=sqlReport1->value(0).toInt();
        i++;
    }


    m_nCurrenItemID=m_nIndexToId[ui->m_tblBBInfo->currentIndex().row()];//当前点击item的ID号。可进行操作数据库内容

    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString nCurrenItemID=QString::number(m_nCurrenItemID);
    QString sqlquery="select * from BB_BB where ID= '"+nCurrenItemID+"'";//在sql语句中加变量
    sqlReport->exec(sqlquery);
    while(sqlReport->next())
    {

        //
        GetBBXZ_ButtonFromSqDB(sqlReport->value(8).toString());//BBXZ
        Getbbgm_ButtonFromSqDB(sqlReport->value(2).toString());//bbgm
        ui->m_cmbQXGZ->setCurrentText(NULL);
        GetQxgz_ComboboxFromSqDB(sqlReport->value(3).toString());//bbzywz
        ui->m_cmbQXGY->setCurrentText(NULL);
        GetQxgy_ComboboxFromSqDB(sqlReport->value(4).toString());//bbxxwz
        ui->m_cmbLJXGZ->setCurrentText(NULL);
        GetLJXG_ComboboxFromSqDB(sqlReport->value(5).toString());//bbljwz
        GetXZL_ButtonFromSqDB(sqlReport->value(6).toInt(),sqlReport->value(7).toInt());//xzlmin和max
        GetBS_ButtonFromSqDB(sqlReport->value(9).toString(),sqlReport->value(19).toString());//BS
        GetFW_ButtonFromSqDB(sqlReport->value(10).toString());//FW
        GetBType_ButtonFromSqDB(sqlReport->value(11).toString());//BType
        GetXT_ButtonFromSqDB(sqlReport->value(12).toString());//XT
        GetGH_ButtonFromSqDB(sqlReport->value(13).toString());//GH
        GetXS_ButtonFromSqDB(sqlReport->value(14).toString());//XS
        GetTIMI_ButtonFromSqDB(sqlReport->value(15).toString());//TIMI
        GetFZ_ButtonFromSqDB(sqlReport->value(16).toString());//FZ
        GetBZ_ButtonFromSqDB(sqlReport->value(17).toString());//BZ
        GetisHaveBB_ButtonFromSqDB(sqlReport->value(18).toString());//isHaveBB
        GetbbRecord_ButtonFromSqDB(sqlReport->value(22).toString());//bbRecord
    }

}

/**
 * @brief 单击事件，获取要删除的ID
 * @param index
 */
void CWidgetPathologyInfo::on_m_tblBBInfo_clicked(const QModelIndex &index)
{
    m_sDeleteIndex=ui->m_tblBBInfo->currentIndex().row();
}


/**
 * @brief 控制删除item
 */
void CWidgetPathologyInfo::on_m_btnSCInfo_clicked()
{
    //**********更新一下整个显示列表，让最新的ID写入到m_nIndexToId[]列表中，方便删除**********
    int i=0;
    QSqlQuery *sqlReport1=new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlReport1->exec("select * from BB_BB where SysCaseID= '"+m_sSysCaseId+"' order by ID");
    while(sqlReport1->next())
    {
        m_nIndexToId[i]=sqlReport1->value(0).toInt();
        i++;
    }
    
    
    m_nCurrenItemID=m_nIndexToId[m_sDeleteIndex];//当前点击item的ID号。可进行操作数据库内容


    //正确选择要删除的信息的Index
    if(m_sDeleteIndex==-1)

    {
        QMessageBox *Qmeb=new QMessageBox;
        Qmeb->warning(NULL, "warning", "请正确选择删除的信息", QMessageBox::Yes);
        if(Qmeb->Yes)
        {
            return ;
        }
    }


    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString nCurrenItemID=QString::number(m_nCurrenItemID);
    QString sqlquery="delete from BB_BB where ID= '"+nCurrenItemID+"'";//在sql语句中加变量
    qDebug()<<"delete from BB_BB where ID= '"+nCurrenItemID+"'";
    sqlReport->exec(sqlquery);

    m_modelBBInfo->removeRow(ui->m_tblBBInfo->currentIndex().row());//在Qtableview中删除所选条目

    while(m_sDeleteIndex<m_nNumListItem-1)
    {
        m_nIndexToId[m_sDeleteIndex]=m_nIndexToId[m_sDeleteIndex+1];
        m_sDeleteIndex++;
    }
    m_nIndexToId[m_nNumListItem]=NULL;//注意**
    m_nSQLItemCount--;
    m_nNumListItem--;

    m_sDeleteIndex=-1;

}

/**
 * @brief CWidgetPathologyInfo::GetCmbItemList
 * @param 选择的条件
 * @return
 */
QStringList CWidgetPathologyInfo::GetCmbItemList(QString sCondition)
{
    QStringList lResult;
    //查询临时变量中某条记录时所用的编码
    QString sCodeLJFZ;
    QString sCodeSLFZ;
    foreach(QString temp, m_lLJXGSLFZ)
    {
        QStringList lTemp = temp.split("/");
        if(sCondition == lTemp.at(lTemp.count() - 1))
        {
            sCodeLJFZ += lTemp.at(4) + lTemp.at(5) + lTemp.at(6);
            sCodeSLFZ += lTemp.at(7) + lTemp.at(8) + lTemp.at(9);
            break;
        }
        lTemp.clear();
    }
    //解读编码
    QStringList lCodeLJFZ;
    QStringList lCodeSLFZ;
    sCodeLJFZ.remove("(");
    sCodeLJFZ.remove(")");
    sCodeLJFZ.remove("'");
    sCodeSLFZ.remove("(");
    sCodeSLFZ.remove(")");
    sCodeSLFZ.remove("'");
    lCodeLJFZ = sCodeLJFZ.split(",");
    lCodeSLFZ = sCodeSLFZ.split(",");
    //获取菜单项
    foreach(QString sTag, lCodeLJFZ)
    {
        if(sTag == "")
            break;
        foreach(QString temp, m_lLJXGSLFZ)
        {
            QStringList lTemp = temp.split("/");
            if(sTag == lTemp.at(3))
            {
                lResult.append(lTemp.at(1));
                break;
            }
            lTemp.clear();
        }
    }
    lResult.append("//");
    foreach(QString sTag, lCodeSLFZ)
    {
        if(sTag == "")
            break;
        foreach(QString temp, m_lLJXGSLFZ)
        {
            QStringList lTemp = temp.split("/");
            if(sTag == lTemp.at(3))
            {
                lResult.append(lTemp.at(1));
                break;
            }
            lTemp.clear();
        }
    }
    return lResult;
}

/**
 * @brief CWidgetPathologyInfo::AddItemToList
 * @param 将要添加的项
 */
void CWidgetPathologyInfo::AddItemToList(QStringList lItemList)
{
    int nFlag = 0;
    //nFlag = 0时，往累及分支下拉菜单中添加；nFlag = 1时，往受累分支下拉菜单中添加
    foreach(QString temp, lItemList)
    {
        if(temp != "//")
        {
            if(!nFlag)
                ui->m_cmbLJXGZ->addItem(temp);
            else
                ui->m_cmbLJFZ->addItem(temp);
        }
        else
            nFlag = 1;
    }
}

/**
 * @brief 将血管位置下拉菜单(右冠左冠)的信息累计血管、受累分支下拉菜单的信息，从数据库中读取出来，并存入临时缓存中。
 */
void CWidgetPathologyInfo::InitializeCmbsItem()
{
    /********* 初始化缓存 *********/
    m_lYGAndZG.clear();
    m_lLJXGSLFZ.clear();
    QSqlQuery* sqlReport = new QSqlQuery(SQLDB::GetDfytCathLab());
    /********* 获取冠脉类型 *********/
    QString sTypeGMGX = "";
    QString sqlquery="select GMType from BB_BBQT where SysCaseID ='"+m_sSysCaseId+"'";//读ZYM的表
    sqlReport->exec(sqlquery);
    while(sqlReport->next())
    {
        sTypeGMGX = sqlReport->value(0).toString();
    }
    /********* 转换冠脉类型为数字(右0左1均2) *********/
    if(sTypeGMGX == "右优势型")
        sTypeGMGX = "0";
    if(sTypeGMGX == "左优势型")
        sTypeGMGX = "1";
    if(sTypeGMGX == "均衡型")
        sTypeGMGX = "2";

    /********* 从数据库中读取并记录血管位置(右冠左冠)下拉菜单项 *********/
    sqlquery="select Vessel_Name,UpID from R_Vessel_T where GMType ='" + sTypeGMGX + "'";
    sqlReport->exec(sqlquery);
    while(sqlReport->next())
    {
        m_lYGAndZG<<sqlReport->value(0).toString().remove(" ") + "/" + sqlReport->value(1).toString();
    }
    /********* 从数据库中读取并记录类及血管下拉菜单项 *********/
    sqlReport->exec("select GMType,Vessel_Name,UpID,Vessel_Tag,R_LJ,L_LJ,M_LJ,R_FZ,L_FZ,M_FZ from R_Vessel_T");
    while(sqlReport->next())
    {
        QString sTemp = "";
        for(int i = 0;i < 10;i++)
        {
            sTemp += sqlReport->value(i).toString().remove(" ") + "/";
        }
        //组成查询所用的编码
        sTemp += sqlReport->value(0).toString().remove(" ") + sqlReport->value(2).toString().remove(" ") + sqlReport->value(1).toString().remove(" ");
        m_lLJXGSLFZ.append(sTemp);
    }
    delete sqlReport;
    sqlReport=NULL;
}


/**
 * @brief 将血管位置下拉菜单(桥血管)的信息从数据库中读取出来，并存入临时缓存中。
 */
void CWidgetPathologyInfo::UpdateQXGItem()
{
    this->m_nGMType=this->GetGMGXType();
    if(this->m_nGMType<0)
    {
        this->m_nGMType=0;
    }
    m_wgtPaintBoard->SetVesselTree(this->m_nGMType);

    // 清空缓存
    m_slstQXG.clear();
    m_lYGAndZG.clear();

    QSqlQuery* sqlReport = new QSqlQuery(SQLDB::GetDfytCathLab());
    /********* 从数据库中读取并记录血管位置(右冠左冠)下拉菜单项 *********/
    QString sqlquery="select Vessel_Name,UpID from R_Vessel_T where GMType ='" + QString::number(m_nGMType) + "'";
    sqlReport->exec(sqlquery);
    while(sqlReport->next())
    {
        m_lYGAndZG<<sqlReport->value(0).toString().remove(" ") + "/" + sqlReport->value(1).toString();
    }
    /********* 从数据库中读取并记录血管位置(桥血管)下拉菜单项 *********/
    sqlquery="select startblood,endblood from BB_CABG where SysCaseID='"+m_sSysCaseId+"'";
    sqlReport->exec(sqlquery);
    while(sqlReport->next())
    {
        m_slstQXG.append(sqlReport->value(0).toString()+"-"+sqlReport->value(1).toString());
    }
    delete sqlReport;
    sqlReport=NULL;
}
