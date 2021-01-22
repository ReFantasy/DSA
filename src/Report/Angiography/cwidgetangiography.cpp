#include "cwidgetangiography.h"
#include "ui_cwidgetangiography.h"

CWidgetAngiography::CWidgetAngiography(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetAngiography)
{
    ui->setupUi(this);

    /******** 自定义RadioButton ********/
    ui->m_lineYGKK->setEnabled(false);
    ui->m_lineZZGKK->setEnabled(false);
    //ui->m_lineZZGKK->hide();


    /******** 设置诊断结果  造影结论 只读********/
    ui->m_txtZDJG->setReadOnly(true);
    ui->m_txtZYJL->setReadOnly(true);

    /******** 设置右冠开口 ********/
    ui->RB_RightGuanNormal->setChecked(true);
    /******** 设置右冠开口 点击异常显示文本框，正常隐藏文本框********/
    connect(ui->RB_RightGuanAbnormal,&QRadioButton::clicked,this,&CWidgetAngiography::on_RB_RightGuanAbnormal_clicked);
    connect(ui->RB_RightGuanNormal,&QRadioButton::clicked,this,&CWidgetAngiography::on_RB_RightGuanNormal_clicked);


    /******** 设置左主干 ********/
    ui->RB_LeftZhuGanNormal->setChecked(true);
    /******** 设置左主干 点击异常显示文本框，正常隐藏文本框********/
    connect(ui->RB_LeftZhuGanAbnormal,&QRadioButton::clicked,this,&CWidgetAngiography::on_RB_LeftZhuGanAbnormal_clicked);
    connect(ui->RB_LeftZhuGanNormal,&QRadioButton::clicked,this,&CWidgetAngiography::on_RB_LeftZhuGanNormal_clicked);


    /******** 设置CABG默认选中 ********/
    ui->m_lstwCABG->setCurrentRow(0);
    ui->m_lstwCABGRight->setCurrentRow(0);



    /******** 设置侧枝循环 ********/
    ui->m_radXLgrade1->setChecked(true);
    ui->m_lstwCZXHLeft->setCurrentRow(0);
    ui->m_lstwCZXHRight->setCurrentRow(0);


    /******** 设置钙化影 ********/
    ui->m_radGZ->setChecked(true);

    /******** 设置左心室造影 ********/
    ZXSInit();


    /******** CABG默认隐藏 ********/
    ui->m_wgtCABG->hide();
    /******** 侧枝循环默认隐藏 ********/
    ui->m_wgtCZXH->hide();
    /******** 钙化影 ********/
    ui->m_wgtGHY->hide();

    ui->m_wgtJWPCI->hide();
    ui->m_wgtZXSZY->hide();


    /******** 初始化显影位置 ********/
    //lyh
    m_sPosXY="";
    const int nNumberVessel=10;
    QString sNameVessel[nNumberVessel]={"RCAp","RCAm","RCAd","PD","AV",
                                        "PL1","PL2","PL3","pDSP","AM1"};
    for (int i=0;i<nNumberVessel;i++)
    {
        m_vPosXY.push_back(sNameVessel[i]);
    }
    m_lstwPosXY = new QListWidget();
    for (int i = 0; i<m_vPosXY.size(); i++)
    {
        QListWidgetItem *lstwItem = new QListWidgetItem(m_lstwPosXY);
        lstwItem->setData(Qt::UserRole, i);
        m_lstwPosXY->addItem(lstwItem);

        QString sNameCurr=QString("%1/").arg(m_vPosXY[i]);
        QCheckBox *ckbNameVessel = new QCheckBox();
        ckbNameVessel->setText(sNameCurr);

        m_lstwPosXY->setItemWidget(lstwItem, ckbNameVessel);
        connect(ckbNameVessel, SIGNAL(stateChanged(int)), this, SLOT(UserStateChangedZYWZ(int)));
    }
    QLineEdit *LineEdit = new QLineEdit();
    LineEdit->setReadOnly(true);
    ui->m_cmbXYWZ->setLineEdit(LineEdit);
    ui->m_cmbXYWZ->setModel(m_lstwPosXY->model());
    ui->m_cmbXYWZ->setView(m_lstwPosXY);
    connect(LineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(UserTextChangedZYWZ(const QString &)));
    for (int i = 0; i<m_vPosXY.size(); i++)
    {
        QListWidgetItem *pItem = m_lstwPosXY->item(i);
        QWidget *pWidget = m_lstwPosXY->itemWidget(pItem);
        QCheckBox *chkCurr = (QCheckBox *)pWidget;
        if(chkCurr->isChecked())
        {
            m_sPosXY+=chkCurr->text();
        }
    }
    ui->m_cmbXYWZ->lineEdit()->setText(m_sPosXY);



    /******** 干预血管 ********/
    //lyh
    m_sGYXG="";
    const int nNumberXG=17;
    QString sNameXG[nNumberXG]={"RCA","AM1","AM2","RPDA","RPLS",
                                "LM","LAD","D1","D2","LCX","LMD",
                                "S1","S2","PL","LPDA","LPLS","Ramus"};
    for (int i=0;i<nNumberXG;i++)
    {
        m_vGYXG.push_back(sNameXG[i]);
    }
    m_lstwGYXG = new QListWidget();
    for (int i = 0; i<m_vGYXG.size(); i++)
    {
        QListWidgetItem *lstwItem = new QListWidgetItem(m_lstwGYXG);
        m_lstwGYXG->addItem(lstwItem);
        lstwItem->setData(Qt::UserRole, i);
        m_lstwGYXG->addItem(lstwItem);

        QString sNameControl=QString("%1/").arg(sNameXG[i]);
        QCheckBox *chkGYXG = new QCheckBox();
        chkGYXG->setText(sNameControl);

        m_lstwGYXG->setItemWidget(lstwItem,chkGYXG);
        connect(chkGYXG, SIGNAL(stateChanged(int)), this, SLOT(UserStateChangedGYXG(int)));

    }

    QLineEdit *lineGYXG = new QLineEdit();
    lineGYXG->setReadOnly(true);
    ui->m_cmbGYXG->setLineEdit(lineGYXG);
    ui->m_cmbGYXG->setModel(m_lstwGYXG->model());
    ui->m_cmbGYXG->setView(m_lstwGYXG);
    connect(lineGYXG, SIGNAL(textChanged(const QString &)), this, SLOT(UserTextChangedGYXG(const QString &)));
    for (int i = 0; i<m_vGYXG.size(); i++)
    {
        QListWidgetItem *lstwItem = m_lstwGYXG->item(i);
        QWidget *wgtItem = m_lstwGYXG->itemWidget(lstwItem);
        QCheckBox *chkCurr = (QCheckBox *)wgtItem;
        if(chkCurr->isChecked())
        {
            m_sGYXG+=chkCurr->text()+" ";
        }
    }
    ui->m_cmbGYXG->lineEdit()->setText(m_sGYXG);


    ui->m_radYYS->setChecked(true);




    /*************初始化诊断结论**************/
    UpdateZDJG();

    /****************初始化造影结论******************/
    //设置造影结论的下拉框默认为-1
    //ui->m_cmbDZBB->setCurrentIndex(-1);
    //    ui->m_cmbSZBBFirst->setCurrentIndex(-1);
    //    ui->m_cmbSZBBSecond->setCurrentIndex(-1);

    //    ui->m_cmbLeftDoubleFirst->setCurrentIndex(-1);
    //    ui->m_cmbLeftDoubleSecond->setCurrentIndex(-1);

    //    ui->m_cmbLeftThreefirst->setCurrentIndex(-1);
    //    ui->m_cmbLeftThreeSecond->setCurrentIndex(-1);
    //    ui->m_cmbLeftThreeThird->setCurrentIndex(-1);

    //讲造影结论的选择框放到List里，保证选择时候的顺序
    m_ListZYJL.push_back(ui->m_ckbZYJL_ZC);
    m_ListZYJL.push_back(ui->m_ckbZYJL_LJ);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_PCI);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_GXB);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_CABG);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_DZBB);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_SZBB);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_ZZG);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_LeftLAD);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_LeftLCX);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_LeftRCA);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_LeftDouble);
    m_ListZYJL.push_back(ui->m_ckbZYMJL_LeftThree);


    /****************造影结论状态改变******************/
    auto alistZYJL=ui->groupBox_11->children();
    for(int i=0;i<alistZYJL.length();i++)
    {
        if( alistZYJL.at(i)->inherits("QCheckBox"))
        {
            auto aControl=qobject_cast<QCheckBox*>(alistZYJL.at(i));

            connect(aControl,&QCheckBox::stateChanged,this,&CWidgetAngiography::UpdateZYJL);

        }

    }

    //造影结论下拉框改变数据触发信号
    void(QComboBox:: *cmbDZBB)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbDZBB,cmbDZBB,this,&CWidgetAngiography::UpdateZYJL);

    void(QComboBox:: *cmbSZBBFirst)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbSZBBFirst,cmbSZBBFirst,this,&CWidgetAngiography::UpdateZYJL);
    void(QComboBox:: *cmbSZBBSecond)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbSZBBSecond,cmbSZBBSecond,this,&CWidgetAngiography::UpdateZYJL);

    void(QComboBox:: *cmbLeftDoubleFirst)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbLeftDoubleFirst,cmbLeftDoubleFirst,this,&CWidgetAngiography::UpdateZYJL);
    void(QComboBox:: *cmbLeftDoubleSecond)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbLeftDoubleSecond,cmbLeftDoubleSecond,this,&CWidgetAngiography::UpdateZYJL);

    void(QComboBox:: *cmbLeftThreefirst)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbLeftThreefirst,cmbLeftThreefirst,this,&CWidgetAngiography::UpdateZYJL);
    void(QComboBox:: *cmbLeftThreeSecond)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbLeftThreeSecond,cmbLeftThreeSecond,this,&CWidgetAngiography::UpdateZYJL);
    void(QComboBox:: *cmbLeftThreeThird)(int) = &QComboBox::currentIndexChanged;
    connect(ui->m_cmbLeftThreeThird,cmbLeftThreeThird,this,&CWidgetAngiography::UpdateZYJL);

    //SetIdPatient(m_sIdPatient);
    //SetSysCaseId(m_sSysCaseID);
    //m_sSysCaseID = "DG120180917150009";

    connect(this, SIGNAL(IndexSignal(int)), this, SLOT(UserStateChanged(int)));


}

void CWidgetAngiography::UpdateUIFromDatabase(){
    SetSqDB();
}

void CWidgetAngiography::UpdateDatabaseFromUI()
{
    UpdateSqDB();
    this->UpdateReportTable();
}

CWidgetAngiography::~CWidgetAngiography()
{
    delete ui;
}

/**
 * @brief 获取listWidget中选中的checkbox
 * @param pListWidget
 * @return
 */
QString CWidgetAngiography::GetListWidgetText(QListWidget *pListWidget)
{
    QString sCurr="";
    for (int i=0;i<pListWidget->count();i++)
    {
        QListWidgetItem *pItem = pListWidget->item(i);
        QWidget *pWidget = pListWidget->itemWidget(pItem);
        QCheckBox *pCheckBox = (QCheckBox *)pWidget;
        if(pCheckBox->isChecked())
        {
            sCurr+=pCheckBox->text();
        }
    }
    //sCurr.chop(1);
    return sCurr;
}


/**
 * @brief 初始化函数
 */
void CWidgetAngiography::SetSqDB(){

    sqlBB_BBQTInit();
    sqlBB_CABGInit();
    sqlBB_CZXHInit();
    sqlBB_GHYInit();
    sqlBB_ZXSInit();
    sqlBB_JLYZInit();


}
/**
 * @brief 更新数据库函数
 */
void CWidgetAngiography::UpdateSqDB(){

    updateSQLBB_BBQT();
    updateSQLBB_CABG();
    updateSQLBB_CZXH();
    updateSQLBB_GHY();
    updateSQLBB_ZXS();
    updateSQLBB_JLYZ();
}

/**
 * @brief CWidgetAngiography::UpdateReportTable
 */
void CWidgetAngiography::UpdateReportTable()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sSqlReport;


    sSqlReport="update operateitem set afterdiagnosis='"+m_sAngiographyRes+"',contrastresult='"+m_sDiagnoseRes+"' where SysCaseID ='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlReport);

    delete sqlReport;
    sqlReport=NULL;
}

/**
 * @brief CWidgetAngiography::SetSysCaseId
 * @param pIdPatient
 */
void CWidgetAngiography::SetSysCaseId(const QString pSysCaseId)
{
    m_sSysCaseID=pSysCaseId;
    this->SetSqDB();
}


void CWidgetAngiography::on_pushButton_6_clicked()
{
    UpdateSqDB();

}
void CWidgetAngiography::on_m_chkCABG_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtCABG->show();
    }
    else
    {
        ui->m_wgtCABG->hide();
        ui->m_lstwCABGResult->clear();
        m_sCABGstartblood.clear();
        m_sCABGendblood.clear();
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_chkCZXH_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtCZXH->show();
    }
    else
    {
        ui->m_wgtCZXH->hide();
        ui->m_lstwCZXHResult->clear();
        m_sCZXHTIMI.clear();
        m_sCZXHstartblood.clear();
        m_sCZXHendblood.clear();
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_chkGHY_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtGHY->show();
    }
    else
    {
        ui->m_wgtGHY->hide();
        ui->m_lstwGHXResult->clear();
        m_sGHYghType.clear();
        m_sGHYghType.clear();
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_chkZXSZY_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtZXSZY->show();
    }
    else
    {
        ui->m_wgtZXSZY->hide();
        ZXSInit();

    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_chkJWPCI_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtJWPCI->show();
    }
    else
    {
        ui->m_wgtJWPCI->hide();
        ui->m_cmbXYWZ->lineEdit()->clear();
        m_sJwpciwz="";
        for (int i = 0; i<m_vPosXY.size(); i++)
        {
            QListWidgetItem *pItem = m_lstwPosXY->item(i);
            QWidget *pWidget = m_lstwPosXY->itemWidget(pItem);
            QCheckBox *chkCurr = (QCheckBox *)pWidget;
            if(chkCurr->isChecked())
            {
                chkCurr->setChecked(false);
            }
        }
    }
    UpdateZDJG();
}

void CWidgetAngiography::UserStateChangedGYXG(int state)
{
    QString sGYXG=this->GetListWidgetText(m_lstwGYXG);
    ui->m_cmbGYXG->lineEdit()->setText(sGYXG);
}

void CWidgetAngiography::UserTextChangedGYXG(const QString &text)
{
    QString sGYXG=this->GetListWidgetText(m_lstwGYXG);
    ui->m_cmbGYXG->lineEdit()->setText(sGYXG);
}

/**
 * @brief CWidgetAngiography::UserStateChanged
 * @param state
 */
void CWidgetAngiography::UserStateChangedZYWZ(int state)
{
    QString sPosXY=this->GetListWidgetText(m_lstwPosXY);
    ui->m_cmbXYWZ->lineEdit()->setText(sPosXY);
}

void CWidgetAngiography::UserTextChangedZYWZ(const QString &text)
{
    QString sPosXY=this->GetListWidgetText(m_lstwPosXY);
    ui->m_cmbXYWZ->lineEdit()->setText(sPosXY);
}


void CWidgetAngiography::on_RB_RightGuanAbnormal_clicked()
{
    if(ui->RB_RightGuanAbnormal->isChecked()){
        ui->m_lineYGKK->setEnabled(true);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_RB_RightGuanNormal_clicked()
{
    if(ui->RB_RightGuanNormal->isChecked()){
        ui->m_lineYGKK->setEnabled(false);
        ui->m_lineYGKK->setText("");
    }
    UpdateZDJG();

}

void CWidgetAngiography::on_RB_LeftZhuGanAbnormal_clicked()
{
    if(ui->RB_LeftZhuGanAbnormal->isChecked()){
        ui->m_lineZZGKK->setEnabled(true);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_RB_LeftZhuGanNormal_clicked()
{
    if(ui->RB_LeftZhuGanNormal->isChecked()){
        ui->m_lineZZGKK->setEnabled(false);
        ui->m_lineZZGKK->setText("");
    }

    UpdateZDJG();
}
/**
 * @brief CABG选择按钮点击事件
 */
void CWidgetAngiography::on_m_btnCABGChoice_clicked()
{

    if(ui->m_lstwCABG->currentItem()->text()==ui->m_lstwCABGRight->currentItem()->text()){

    }else{
        for (int reslutNumber = 0; reslutNumber < ui->m_lstwCABGResult->count(); reslutNumber++)

        {

            //            QString itemReslut =ui->m_lstwCABGResult->item(reslutNumber)->text();

            //            if (itemReslut == ui->m_lstwCABG->currentItem()->text()+"-"+ui->m_lstwCABGRight->currentItem()->text())

            //            {

            //                return;

            //            }

        }
        ui->m_lstwCABGResult->addItem(ui->m_lstwCABG->currentItem()->text()+"-"+ui->m_lstwCABGRight->currentItem()->text());
        m_sCABGstartblood.append(ui->m_lstwCABG->currentItem()->text());
        m_sCABGendblood.append(ui->m_lstwCABGRight->currentItem()->text());
    }

    UpdateZDJG();
}

/**
 * @brief 双击删除CBGResult选中项 同时删除m_sListstartblood m_sListendblood 对应项
 * @param item
 */
void CWidgetAngiography::on_m_lstwCABGResult_itemDoubleClicked(QListWidgetItem *item)
{

    //        int iRemoveItem = ui->m_lstwCABGResult->currentRow();
    //        ui->m_lstwCABGResult->removeItemWidget(item);
    //        m_sCABGstartblood.removeAt(iRemoveItem);
    //        m_sCABGendblood.removeAt(iRemoveItem);
    //        delete item;
    //        UpdateZDJG();
}
/**
 * @brief 侧枝循环选择按钮点击事件
 */
void CWidgetAngiography::on_m_btnCZXHChoice_clicked()
{
    QString addItemXL="";
    auto alistXL=ui->m_grpXL->children();
    for(int i=0;i<alistXL.length();i++)
    {
        if( alistXL.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(alistXL.at(i));
            QString sControl=aControl->text();
            if(aControl->isChecked()){
                addItemXL="血流等级"+aControl->text();
                m_sCZXHTIMI.append(aControl->text());
            }

        }
    }


    if(ui->m_lstwCZXHLeft->currentItem()->text()==ui->m_lstwCZXHRight->currentItem()->text()){

    }else{


        QString addItemResult = "由"+ui->m_lstwCZXHLeft->currentItem()->text()+"至"+ui->m_lstwCZXHRight->currentItem()->text()+"形成侧枝循环,"+addItemXL;

        ui->m_lstwCZXHResult->addItem(addItemResult);
        m_sCZXHstartblood.append(ui->m_lstwCZXHLeft->currentItem()->text());
        m_sCZXHendblood.append(ui->m_lstwCZXHRight->currentItem()->text());
        UpdateZDJG();

    }

}

/**
 * @brief 双击删除CZXHResult选中项
 * @param item
 */
void CWidgetAngiography::on_m_lstwCZXHResult_itemDoubleClicked(QListWidgetItem *item)
{
    //    int iRemoveItem = ui->m_lstwCZXHResult->currentRow();
    //    ui->m_lstwCZXHResult->removeItemWidget(item);
    //    m_sCZXHstartblood.removeAt(iRemoveItem);
    //    m_sCZXHendblood.removeAt(iRemoveItem);
    //    delete item;
    //    UpdateZDJG();
}
/**
 * @brief 钙化影选择按钮点击事件
 */
void CWidgetAngiography::on_m_btnGHXChoice_clicked()
{
    QStringList slistWZ;
    auto alistWZ=ui->m_grpWZ->children();
    for(int i=0;i<alistWZ.length();i++)
    {
        if( alistWZ.at(i)->inherits("QCheckBox"))
        {
            auto aControl=qobject_cast<QCheckBox*>(alistWZ.at(i));
            QString sControl=aControl->text();
            if(aControl->isChecked()){
                slistWZ.append(aControl->text());
            }

        }
    }

    QString slistWZResult;//结论显示字段
    QString sWZResult;//存放数据库字段
    for (int i = 0;i<slistWZ.size();i++) {
        slistWZResult+=slistWZ[i]+"、";
        sWZResult+=slistWZ[i]+" ";
    }
    slistWZResult.chop(1);
    sWZResult.chop(1);
    if(slistWZResult==nullptr){
        return;
    }

    m_sGHYghblood.append(sWZResult);//存放到字段

    if(ui->m_radGZ->isChecked()){

        QString addItemResult = ui->m_radGZ->text()+"走行区域可见"+slistWZResult+"钙化影";
        for (int reslutNumber = 0; reslutNumber < ui->m_lstwGHXResult->count(); reslutNumber++){

            QString itemReslut =ui->m_lstwGHXResult->item(reslutNumber)->text();
            //            if (itemReslut == addItemResult)
            //            {
            //                return;
            //            }
        }
        ui->m_lstwGHXResult->addItem(addItemResult);
        m_sGHYghType.append(ui->m_radGZ->text());
        UpdateZDJG();
    }else{


        QString addItemResult = slistWZResult+"走行区域可见"+ui->m_radDPZ->text()+"钙化影";
        for (int reslutNumber = 0; reslutNumber < ui->m_lstwGHXResult->count(); reslutNumber++){

            QString itemReslut =ui->m_lstwGHXResult->item(reslutNumber)->text();
            //            if (itemReslut == addItemResult)
            //            {
            //                return;
            //            }
        }

        ui->m_lstwGHXResult->addItem(addItemResult);
        m_sGHYghType.append(ui->m_radDPZ->text());
        UpdateZDJG();
    }


}
/**
 * @brief 双击删除钙化影Result选中项
 * @param item
 */
void CWidgetAngiography::on_m_lstwGHXResult_itemDoubleClicked(QListWidgetItem *item)
{
    //    int iRemoveItem = ui->m_lstwGHXResult->currentRow();
    //    ui->m_lstwGHXResult->removeItemWidget(item);
    //    m_sGHYghblood.removeAt(iRemoveItem);
    //    m_sGHYghType.removeAt(iRemoveItem);
    //    delete item;
    //    UpdateZDJG();
}
/**
 * @brief 血管外形正常隐藏界面，异常显示界面
 */
void CWidgetAngiography::on_RB_ShapeNormal_clicked()
{

    ui->m_wgtShapeYC->hide();
    ui->m_lineSXFS->setReadOnly(true);
    ui->m_radQC_ZC->setChecked(true);
    ui->m_radQJD_ZC->setChecked(true);
    ui->m_radXJ_ZC->setChecked(true);;
    ui->m_radGM_ZC->setChecked(true);
    ui->m_radHJD_ZC->setChecked(true);
    ui->m_radJG_ZC->setChecked(true);
    ui->m_radHC_ZC->setChecked(true);


    ui->m_ckbQC->setChecked(false);
    ui->m_ckbQJD->setChecked(false);
    ui->m_ckbXJ->setChecked(false);
    ui->m_ckbGM->setChecked(false);
    ui->m_ckbHJD->setChecked(false);
    ui->m_ckbJG->setChecked(false);
    ui->m_ckbHC->setChecked(false);
    UpdateZDJG();
}

void CWidgetAngiography::on_RB_ShapeAbnormal_clicked()
{
    ui->m_wgtShapeYC->show();
    UpdateZDJG();
}


/**
 * @brief 设置血管外形前侧的逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbQC_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radQC_ZC->isChecked()){
        //           ui->m_radQC_JD->setChecked(true);
        //       }
    }else{
        ui->m_radQC_ZC->setChecked(true);
    }


    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQC_ZC_clicked()
{
    if(ui->m_radQC_ZC->isChecked()){
        ui->m_ckbQC->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQC_JD_clicked()
{
    if(ui->m_ckbQC->isChecked()){

    }else{
        ui->m_ckbQC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQC_WHD_clicked()
{
    if(ui->m_ckbQC->isChecked()){

    }else{
        ui->m_ckbQC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQC_FCYD_clicked()
{
    if(ui->m_ckbQC->isChecked()){

    }else{
        ui->m_ckbQC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQC_SBL_clicked()
{
    if(ui->m_ckbQC->isChecked()){

    }else{
        ui->m_ckbQC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQC_BQD_clicked()
{
    if(ui->m_ckbQC->isChecked()){

    }else{
        ui->m_ckbQC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}
/**
 * @brief 设置前基底的操作逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbQJD_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radQJD_ZC->isChecked()){
        //           ui->m_radQJD_JD->setChecked(true);
        //       }
    }else{
        ui->m_radQJD_ZC->setChecked(true);
    }
    UpdateZDJG();

}


void CWidgetAngiography::on_m_radQJD_ZC_clicked()
{
    if(ui->m_radQJD_ZC->isChecked()){
        ui->m_ckbQJD->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQJD_JD_clicked()
{
    if(ui->m_ckbQJD->isChecked()){

    }else{
        ui->m_ckbQJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQJD_WHD_clicked()
{
    if(ui->m_ckbQJD->isChecked()){

    }else{
        ui->m_ckbQJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQJD_FCYD_clicked()
{
    if(ui->m_ckbQJD->isChecked()){

    }else{
        ui->m_ckbQJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQJD_SBL_clicked()
{
    if(ui->m_ckbQJD->isChecked()){

    }else{
        ui->m_ckbQJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radQJD_BQD_clicked()
{
    if(ui->m_ckbQJD->isChecked()){

    }else{
        ui->m_ckbQJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}
/**
 * @brief 设置心尖的操作逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbXJ_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radXJ_ZC->isChecked()){
        //           ui->m_radXJ_JD->setChecked(true);
        //       }
    }else{
        ui->m_radXJ_ZC->setChecked(true);
    }
    UpdateZDJG();

}

void CWidgetAngiography::on_m_radXJ_ZC_clicked()
{
    if(ui->m_radXJ_ZC->isChecked()){
        ui->m_ckbXJ->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radXJ_JD_clicked()
{
    if(ui->m_ckbXJ->isChecked()){

    }else{
        ui->m_ckbXJ->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radXJ_WHD_clicked()
{
    if(ui->m_ckbXJ->isChecked()){

    }else{
        ui->m_ckbXJ->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radXJ_FCYD_clicked()
{
    if(ui->m_ckbXJ->isChecked()){

    }else{
        ui->m_ckbXJ->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radXJ_SBL_clicked()
{
    if(ui->m_ckbXJ->isChecked()){

    }else{
        ui->m_ckbXJ->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radXJ_BQD_clicked()
{
    if(ui->m_ckbXJ->isChecked()){

    }else{
        ui->m_ckbXJ->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}
/**
 * @brief 设置膈面的操作逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbGM_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radGM_ZC->isChecked()){
        //           ui->m_radGM_JD->setChecked(true);
        //       }
    }else{
        ui->m_radGM_ZC->setChecked(true);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radGM_ZC_clicked()
{
    if(ui->m_radGM_ZC->isChecked()){
        ui->m_ckbGM->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radGM_JD_clicked()
{
    if(ui->m_ckbGM->isChecked()){

    }else{
        ui->m_ckbGM->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radGM_WHD_clicked()
{

    if(ui->m_ckbGM->isChecked()){

    }else{
        ui->m_ckbGM->setCheckState(Qt::Checked);
    }
    UpdateZDJG();

}

void CWidgetAngiography::on_m_radGM_FCYD_clicked()
{

    if(ui->m_ckbGM->isChecked()){

    }else{
        ui->m_ckbGM->setCheckState(Qt::Checked);
    }
    UpdateZDJG();

}

void CWidgetAngiography::on_m_radGM_SBL_clicked()
{

    if(ui->m_ckbGM->isChecked()){

    }else{
        ui->m_ckbGM->setCheckState(Qt::Checked);
    }
    UpdateZDJG();

}

void CWidgetAngiography::on_m_radGM_BQD_clicked()
{

    if(ui->m_ckbGM->isChecked()){

    }else{
        ui->m_ckbGM->setCheckState(Qt::Checked);
    }
    UpdateZDJG();

}

/**
 * @brief 设置后基底的操作逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbHJD_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radHJD_ZC->isChecked()){
        //           ui->m_radHJD_JD->setChecked(true);
        //       }
    }else{
        ui->m_radHJD_ZC->setChecked(true);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHJD_ZC_clicked()
{
    if(ui->m_radHJD_ZC->isChecked()){
        ui->m_ckbHJD->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHJD_JD_clicked()
{

    if(ui->m_ckbHJD->isChecked()){

    }else{
        ui->m_ckbHJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHJD_WHD_clicked()
{
    if(ui->m_ckbHJD->isChecked()){

    }else{
        ui->m_ckbHJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHJD_FCYD_clicked()
{
    if(ui->m_ckbHJD->isChecked()){

    }else{
        ui->m_ckbHJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHJD_SBL_clicked()
{
    if(ui->m_ckbHJD->isChecked()){

    }else{
        ui->m_ckbHJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHJD_BQD_clicked()
{
    if(ui->m_ckbHJD->isChecked()){

    }else{
        ui->m_ckbHJD->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

/**
 * @brief 设置间隔的操作逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbJG_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radJG_ZC->isChecked()){
        //           ui->m_radJG_JD->setChecked(true);
        //       }
    }else{
        ui->m_radJG_ZC->setChecked(true);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJG_ZC_clicked()
{
    if(ui->m_radJG_ZC->isChecked()){
        ui->m_ckbJG->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJG_JD_clicked()
{
    if(ui->m_ckbJG->isChecked()){

    }else{
        ui->m_ckbJG->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJG_WHD_clicked()
{
    if(ui->m_ckbJG->isChecked()){

    }else{
        ui->m_ckbJG->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJG_FCYD_clicked()
{
    if(ui->m_ckbJG->isChecked()){

    }else{
        ui->m_ckbJG->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJG_SBL_clicked()
{
    if(ui->m_ckbJG->isChecked()){

    }else{
        ui->m_ckbJG->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJG_BQD_clicked()
{
    if(ui->m_ckbJG->isChecked()){

    }else{
        ui->m_ckbJG->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}
/**
 * @brief 设置后侧的操作逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_ckbHC_stateChanged(int arg1)
{
    if(arg1==2){
        //       if(ui->m_radHC_ZC->isChecked()){
        //           ui->m_radHC_JD->setChecked(true);
        //       }
    }else{
        ui->m_radHC_ZC->setChecked(true);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHC_ZC_clicked()
{
    if(ui->m_radHC_ZC->isChecked()){
        ui->m_ckbHC->setCheckState(Qt::Unchecked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHC_JD_clicked()
{
    if(ui->m_ckbHC->isChecked()){

    }else{
        ui->m_ckbHC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHC_WHD_clicked()
{
    if(ui->m_ckbHC->isChecked()){

    }else{
        ui->m_ckbHC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHC_FCYD_clicked()
{
    if(ui->m_ckbHC->isChecked()){

    }else{
        ui->m_ckbHC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHC_SBL_clicked()
{
    if(ui->m_ckbHC->isChecked()){

    }else{
        ui->m_ckbHC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radHC_BQD_clicked()
{
    if(ui->m_ckbHC->isChecked()){

    }else{
        ui->m_ckbHC->setCheckState(Qt::Checked);
    }
    UpdateZDJG();
}
/**
 * @brief 更新诊断结果
 */
void CWidgetAngiography::UpdateZDJG(){

    QString resZDJG;
    QString resGMGX;
    QString resYGKK;
    QString resZZGKK;
    QString resCABG;
    QString resCZXH;
    QString resGHY;
    QString resJWPCIZJY;
    QString resZXSZY;

    UpdateBB_BBQT();//获取冠脉供血 右冠开口结果 左主干结果

    resGMGX="冠脉供血为"+m_sGMType+"、";

    //右冠开口结果
    if(m_sYgkk=="正常"){
        resYGKK = "右冠开口正常、";
    }else{
        resYGKK = "右冠开口异常"+m_sYgkk+"、";
    }



    //左主干结果
    if(m_sZzgkk=="正常"){
        resZZGKK = "左主干开口正常、";
    }else{
        resZZGKK = "左主干开口异常"+m_sZzgkk+"、";
    }


    //CABG结果
    if(ui->m_chkCABG->isChecked()){


        for (int reslutNumber = 0; reslutNumber < ui->m_lstwCABGResult->count(); reslutNumber++)

        {
            QString itemReslut =ui->m_lstwCABGResult->item(reslutNumber)->text();

            resCABG+=itemReslut+"、";

        }
        if(resCABG==nullptr){

            resCABG="";
        }else{
            resCABG.chop(1);
            resCABG+="有桥血管、";
        }

    }

    //侧枝循环结果

    if(ui->m_chkCZXH->isChecked()){
        for (int reslutNumber = 0; reslutNumber < ui->m_lstwCZXHResult->count(); reslutNumber++)

        {

            QString itemReslut =ui->m_lstwCZXHResult->item(reslutNumber)->text();

            resCZXH+=itemReslut+"、";

        }
        if(resCZXH==nullptr){

            resCZXH="";
        }else{
            resCZXH.chop(1);
            resCZXH+="、";
        }
    }


    //钙化影结果
    if(ui->m_chkGHY->isChecked()){
        for (int reslutNumber = 0; reslutNumber < ui->m_lstwGHXResult->count(); reslutNumber++)

        {

            QString itemReslut =ui->m_lstwGHXResult->item(reslutNumber)->text();

            resGHY+=itemReslut+"、";

        }
        if(resGHY==nullptr){

            resGHY="";
        }else{
            resGHY.chop(1);
            resGHY+="、";
        }
    }
    //JWPCI结果
    if(ui->m_chkJWPCI->isChecked()){
        if(ui->m_cmbXYWZ->currentText()==nullptr){

        }else{
            resJWPCIZJY+=ui->m_cmbXYWZ->currentText();
            resJWPCIZJY.chop(1);
            resJWPCIZJY+="为既往显影位置。";
        }
    }
    //左心室造影结果


    if(ui->m_chkZXSZY->isChecked()){
        if(ui->RB_ShapeNormal->isChecked()){
            resZXSZY+="外形大小正常、";

        }else{
            resZXSZY+="外形大小异常、";

        }
        if(ui->m_radXQDXNormal->isChecked()){

            resZXSZY+="心腔大小正常、";
        }else{
            resZXSZY+="心腔大小增大、";

        }


        resZXSZY +="舒张末期容量："+ui->m_lineSZMQRL->text()+"ml、";

        resZXSZY +="收缩末期容量："+ui->m_lineSSMQRL->text()+"ml、";

        resZXSZY +="射血分数："+ui->m_lineSXFS->text()+"%、";



        if(ui->RB_ShapeNormal->isChecked()){

        }else{
            //前侧
            auto alistQC=ui->m_grpQC->children();
            for(int i=0;i<alistQC.length();i++)
            {
                if( alistQC.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistQC.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="前侧"+sControl+"、";

                    }

                }
            }
            //前基底
            auto alistQJD=ui->m_grpQJD->children();
            for(int i=0;i<alistQJD.length();i++)
            {
                if( alistQJD.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistQJD.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="前基底"+sControl+"、";

                    }

                }
            }
            //心尖
            auto alistXJ=ui->m_grpXJ->children();
            for(int i=0;i<alistXJ.length();i++)
            {
                if( alistXJ.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistXJ.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="心尖"+sControl+"、";

                    }

                }
            }
            //膈面
            auto alistGM=ui->m_grpGM->children();
            for(int i=0;i<alistGM.length();i++)
            {
                if( alistGM.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistGM.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="膈面"+sControl+"、";

                    }

                }
            }
            //后基底
            auto alistHJD=ui->m_grpHJD->children();
            for(int i=0;i<alistHJD.length();i++)
            {
                if( alistHJD.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistHJD.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="后基底"+sControl+"、";

                    }

                }
            }
            //间隔
            auto alistJG=ui->m_grpJG->children();
            for(int i=0;i<alistJG.length();i++)
            {
                if( alistJG.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistJG.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="间隔"+sControl+"、";

                    }

                }
            }
            //后侧
            auto alistHC=ui->m_grpHC->children();
            for(int i=0;i<alistHC.length();i++)
            {
                if( alistHC.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistHC.at(i));
                    QString sControl=aControl->text();
                    if(aControl->isChecked()){

                        resZXSZY+="后侧"+sControl+"、";
                    }

                }
            }
        }
    }


    resZDJG = resGMGX+resYGKK+resZZGKK+resCABG+resCZXH+resGHY+resJWPCIZJY+resZXSZY;
    resZDJG.chop(1);
    m_sDiagnoseRes=resZDJG;
    ui->m_txtZDJG->setText(resZDJG);
}

void CWidgetAngiography::on_m_lineYGKK_textChanged(const QString &arg1)
{
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radYYS_clicked()
{
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radZYS_clicked()
{
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radJH_clicked()
{
    UpdateZDJG();
}

void CWidgetAngiography::on_m_lineZZGKK_textChanged(const QString &arg1)
{
    UpdateZDJG();
}

void CWidgetAngiography::on_m_radXQDXNormal_toggled(bool checked)
{
    UpdateZDJG();
}

void CWidgetAngiography::on_m_cmbXYWZ_currentTextChanged(const QString &arg1)
{
    UpdateZDJG();
}
/**
 * @brief 射血分数实现逻辑
 * @param arg1
 */
void CWidgetAngiography::on_m_lineSZMQRL_textChanged(const QString &arg1)
{   double dSZMQRL = ui->m_lineSZMQRL->text().toDouble();
    double dSSZMRL = ui->m_lineSSMQRL->text().toDouble();
    double dSXFS = (dSZMQRL-dSSZMRL)/dSZMQRL;
    ui->m_lineSXFS->setText(QString::number(dSXFS));
    UpdateZDJG();
}

void CWidgetAngiography::on_m_lineSSMQRL_textChanged(const QString &arg1)
{
    double dSZMQRL = ui->m_lineSZMQRL->text().toDouble();
    double dSSZMRL = ui->m_lineSSMQRL->text().toDouble();
    double dSXFS = (dSZMQRL-dSSZMRL)/dSZMQRL;
    ui->m_lineSXFS->setText(QString::number(dSXFS));
    UpdateZDJG();
}

void CWidgetAngiography::on_m_cmbJYBCL_currentTextChanged(const QString &arg1)
{
    if(arg1 == "即刻PCI"){
        ui->m_cmbGYXG->setEnabled(true);
    }else{
        ui->m_cmbGYXG->lineEdit()->setText("");
        ui->m_cmbGYXG->setEnabled(false);

        for (int i = 0; i<m_vGYXG.size(); i++)
        {
            QListWidgetItem *lstwItem = m_lstwGYXG->item(i);
            QWidget *wgtItem = m_lstwGYXG->itemWidget(lstwItem);
            QCheckBox *chkCurr = (QCheckBox *)wgtItem;
            if(chkCurr->isChecked())
            {
                chkCurr->setChecked(false);
            }
        }
    }
}
/**
 * @brief 更新造影结论
 * @param arg
 */
void CWidgetAngiography::UpdateZYJL(int arg)
{
    m_sZYJL="";
    for (int i = 0;i<m_ListZYJL.size();i++) {
        if(m_ListZYJL[i]->isChecked()){
            m_sZYJL= m_sZYJL+m_ListZYJL[i]->text()+"、";
            if(m_ListZYJL[i]->text()=="单支病变"){
                m_sZYJL.chop(1);
                m_sZYJL=m_sZYJL+":"+ui->m_cmbDZBB->currentText()+"、";
            }
            if(m_ListZYJL[i]->text()=="双支病变"){
                m_sZYJL.chop(1);
                if(ui->m_cmbSZBBFirst->currentText()==""||ui->m_cmbSZBBSecond->currentText()==""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbSZBBFirst->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbSZBBSecond->currentText()+"、";
                }else{
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbSZBBFirst->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbSZBBSecond->currentText()+"、";
                }

            }
            if(m_ListZYJL[i]->text()=="左主干+双支病变"){
                m_sZYJL.chop(1);
                if(ui->m_cmbLeftDoubleFirst->currentText()==""||ui->m_cmbLeftDoubleSecond->currentText()==""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftDoubleFirst->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftDoubleSecond->currentText()+"、";
                }else{
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftDoubleFirst->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftDoubleSecond->currentText()+"、";
                }

            }

            if(m_ListZYJL[i]->text()=="左主干+三支病变"){
                m_sZYJL.chop(1);
                if(ui->m_cmbLeftThreefirst->currentText()==""&&ui->m_cmbLeftThreeSecond->currentText()!=""&&ui->m_cmbLeftThreeThird->currentText()!=""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }
                if(ui->m_cmbLeftThreeSecond->currentText()==""&&ui->m_cmbLeftThreefirst->currentText()!=""&&ui->m_cmbLeftThreeThird->currentText()!=""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }
                if (ui->m_cmbLeftThreeThird->currentText()==""&&ui->m_cmbLeftThreefirst->currentText()!=""&&ui->m_cmbLeftThreeSecond->currentText()!=""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }
                if(ui->m_cmbLeftThreefirst->currentText()!=""&&ui->m_cmbLeftThreeSecond->currentText()!=""&&ui->m_cmbLeftThreeThird->currentText()!=""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText()+"+";
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }

                if(ui->m_cmbLeftThreefirst->currentText()!=""&&ui->m_cmbLeftThreeSecond->currentText()==""&&ui->m_cmbLeftThreeThird->currentText()==""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }
                if(ui->m_cmbLeftThreeSecond->currentText()!=""&&ui->m_cmbLeftThreefirst->currentText()==""&&ui->m_cmbLeftThreeThird->currentText()==""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }
                if(ui->m_cmbLeftThreeThird->currentText()!=""&&ui->m_cmbLeftThreefirst->currentText()==""&&ui->m_cmbLeftThreeSecond->currentText()==""){
                    m_sZYJL=m_sZYJL+":"+ui->m_cmbLeftThreefirst->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeSecond->currentText();
                    m_sZYJL=m_sZYJL+ui->m_cmbLeftThreeThird->currentText()+"、";
                }
            }
        }
    }
    m_sAngiographyRes=m_sZYJL;
    m_sAngiographyRes.chop(1);
    ui->m_txtZYJL->setText(m_sZYJL);
}




void CWidgetAngiography::UpdateBB_BBQT(){

    //冠脉供血结果;
    auto alistGMGX=ui->m_grpGMGX->children();
    for(int i=0;i<alistGMGX.length();i++)
    {
        if( alistGMGX.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(alistGMGX.at(i));
            QString sControl=aControl->text();
            if(aControl->isChecked()){
                m_sGMType=aControl->text();
            }

        }
    }

    //右冠开口结果
    if(ui->RB_RightGuanNormal->isChecked()){
        m_sYgkk = "正常";
    }else{
        m_sYgkk = ui->m_lineYGKK->text();
    }

    //左主干结果
    if(ui->RB_LeftZhuGanNormal->isChecked()){
        m_sZzgkk = "正常";
    }else{
        m_sZzgkk = ui->m_lineZZGKK->text();
    }



}

/**
 * @brief CWidgetAngiography::获取左心室需要提交数据库的数据
 */
void CWidgetAngiography::UpdateBB_ZXS(){



    if(ui->m_chkZXSZY->isChecked()){
        if(ui->RB_ShapeNormal->isChecked()){

            m_sZXSFigure = "正常";
        }else{

            m_sZXSFigure = "异常";
        }
        if(ui->m_radXQDXNormal->isChecked()){
            m_sZXSHeart_Size = "正常";

        }else{

            m_sZXSHeart_Size = "增大";
        }



        m_sZXSszq = ui->m_lineSZMQRL->text();

        m_sZXSssq=ui->m_lineSSMQRL->text();

        m_sZXSsxfs= ui->m_lineSXFS->text();



        //前侧
        auto alistQC=ui->m_grpQC->children();
        for(int i=0;i<alistQC.length();i++)
        {
            if( alistQC.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistQC.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSQC = sControl;
                }

            }
        }
        //前基底
        auto alistQJD=ui->m_grpQJD->children();
        for(int i=0;i<alistQJD.length();i++)
        {
            if( alistQJD.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistQJD.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSQJD = sControl;
                }

            }
        }
        //心尖
        auto alistXJ=ui->m_grpXJ->children();
        for(int i=0;i<alistXJ.length();i++)
        {
            if( alistXJ.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistXJ.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSXJ =sControl;
                }

            }
        }
        //膈面
        auto alistGM=ui->m_grpGM->children();
        for(int i=0;i<alistGM.length();i++)
        {
            if( alistGM.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistGM.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSGM = sControl;
                }

            }
        }
        //后基底
        auto alistHJD=ui->m_grpHJD->children();
        for(int i=0;i<alistHJD.length();i++)
        {
            if( alistHJD.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistHJD.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSHJD =sControl;
                }

            }
        }
        //间隔
        auto alistJG=ui->m_grpJG->children();
        for(int i=0;i<alistJG.length();i++)
        {
            if( alistJG.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistJG.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSJG =sControl;
                }

            }
        }
        //后侧
        auto alistHC=ui->m_grpHC->children();
        for(int i=0;i<alistHC.length();i++)
        {
            if( alistHC.at(i)->inherits("QRadioButton"))
            {
                auto aControl=qobject_cast<QRadioButton*>(alistHC.at(i));
                QString sControl=aControl->text();
                if(aControl->isChecked()){


                    m_sZXSHC = sControl;
                }

            }
        }
    }





}
/****************************BBQT表的拉取初始化与更新函数***************************************************/
//拉取数据后的初始化函数
void CWidgetAngiography::sqlBB_BBQTInit(){
    getSQLBB_BBQT();

    auto alistGMGX=ui->m_grpGMGX->children();
    for(int i=0;i<alistGMGX.length();i++)
    {
        if( alistGMGX.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(alistGMGX.at(i));
            QString sControl=aControl->text();
            if(sControl==m_sGMType){
                aControl->setChecked(true);
            }

        }
    }

    if(m_sZzgkk == "正常"){
        ui->RB_LeftZhuGanNormal->setChecked(true);
    }else{
        ui->RB_LeftZhuGanAbnormal->setChecked(true);
        ui->m_lineZZGKK->setText(m_sZzgkk);
        ui->m_lineZZGKK->setEnabled(true);
    }

    getSQLBB_BBQT();

    if(m_sYgkk == "正常"){
        ui->RB_RightGuanNormal->setChecked(true);

    }else{

        ui->RB_RightGuanAbnormal->setChecked(true);
        ui->m_lineYGKK->setText(m_sYgkk);
        ui->m_lineYGKK->setEnabled(true);
    }

    //既往PCI支架显影位置初始化

    if(m_sJwpciwz!=nullptr){
        ui->m_chkJWPCI->setChecked(true);
        ui->m_wgtJWPCI->show();

        ui->m_cmbXYWZ->lineEdit()->setText(m_sJwpciwz);


        QString sPCIIsChecked;
        for(int i=0;i<m_sJwpciwz.size();i++){
            if(m_sJwpciwz[i]!="/"){
                sPCIIsChecked+=m_sJwpciwz[i];
            }else{
                sPCIIsChecked+=m_sJwpciwz[i];
                for (int j = 0; j<m_vPosXY.size(); j++)
                {
                    QListWidgetItem *pItem = m_lstwPosXY->item(j);
                    QWidget *pWidget = m_lstwPosXY->itemWidget(pItem);
                    QCheckBox *chkCurr = (QCheckBox *)pWidget;

                    if(chkCurr->text()==sPCIIsChecked)
                    {
                        chkCurr->setChecked(true);

                    }

                }
                sPCIIsChecked="";
            }
        }


    }

}

//数据库函数 获取数据
void CWidgetAngiography::getSQLBB_BBQT(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlBBQT="select * from BB_BBQT where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlBBQT);



    while(sqlStorge->next())
    {

        m_sGMType= sqlStorge->value(2).toString();
        m_sZzgkk=sqlStorge->value(3).toString();
        m_sYgkk = sqlStorge->value(4).toString();
        m_sJwpciwz = sqlStorge->value(5).toString();

    }


}
//数据库函数 更新函数
void CWidgetAngiography::updateSQLBB_BBQT(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());

    m_sJwpciwz=ui->m_cmbXYWZ->lineEdit()->text();
    QString sSqlBBQT="select * from BB_BBQT where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlBBQT);
    if (sqlStorge->last()){

        sSqlBBQT="update BB_BBQT set GMType = '"+m_sGMType+"',Zzgkk = '"+m_sZzgkk+"', Ygkk= '"+m_sYgkk+"',Jwpciwz = '"+m_sJwpciwz+"' where SysCaseID = '"+m_sSysCaseID+"'";;


    }else{
        sSqlBBQT="insert into  BB_BBQT (SysCaseID,GMType,Zzgkk,Ygkk,Jwpciwz) values  ('"+m_sSysCaseID+"','"+m_sGMType+"','"+m_sZzgkk+"','"+m_sYgkk+"','"+m_sJwpciwz+"')";

    }
    sqlStorge->exec(sSqlBBQT);
    delete sqlStorge;
    sqlStorge=NULL;
}


/****************************CABG表的拉取初始化与更新函数***************************************************/
void CWidgetAngiography::getSQLBB_CABG(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlCABG="select * from BB_CABG where SysCaseID='"+m_sSysCaseID+"' ";

    sqlStorge->exec(sSqlCABG);

    while(sqlStorge->next())
    {

        m_sCABGstartblood.append(sqlStorge->value(2).toString());
        m_sCABGendblood.append(sqlStorge->value(3).toString());



    }


}
void CWidgetAngiography::sqlBB_CABGInit(){
    getSQLBB_CABG();

    if(m_sCABGstartblood.size()>0){
        ui->m_chkCABG->setChecked(true);
        ui->m_wgtCABG->show();
    }

    for(int num = 0;num < m_sCABGstartblood.size();num++){
        ui->m_lstwCABGResult->addItem(m_sCABGstartblood.at(num)+"-"+m_sCABGendblood.at(num));
    }


    UpdateZDJG();

}

void CWidgetAngiography::updateSQLBB_CABG(){

    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlDeleteCABG="delete from BB_CABG where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlDeleteCABG);


    for(int num = 0;num < m_sCABGstartblood.size();num++){
        QString sSqlInsertCABG="insert into BB_CABG (SysCaseID, startblood,endblood) values ('"+m_sSysCaseID+"', '"+m_sCABGstartblood.at(num)+"','"+m_sCABGendblood.at(num)+"')";
        sqlStorge->exec(sSqlInsertCABG);
    }

    delete sqlStorge;
    sqlStorge=NULL;
}
/****************************CZXH表的拉取初始化与更新函数***************************************************/
void CWidgetAngiography::getSQLBB_CZXH(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlCABG="select * from BB_CZXH where SysCaseID='"+m_sSysCaseID+"' ";

    sqlStorge->exec(sSqlCABG);



    while(sqlStorge->next())
    {

        m_sCZXHTIMI.append(sqlStorge->value(2).toString());
        m_sCZXHstartblood.append(sqlStorge->value(3).toString());
        m_sCZXHendblood.append(sqlStorge->value(4).toString());

    }


}

void CWidgetAngiography::sqlBB_CZXHInit(){
    getSQLBB_CZXH();
    if(m_sCZXHstartblood.size()>0){
        ui->m_chkCZXH->setChecked(true);
        ui->m_wgtCZXH->show();
    }

    for(int num = 0;num < m_sCZXHstartblood.size();num++){
        ui->m_lstwCZXHResult->addItem("由"+m_sCZXHstartblood.at(num)+"至"+m_sCZXHendblood.at(num)+"形成侧枝循环,血流等级"+m_sCZXHTIMI.at(num));
    }




    UpdateZDJG();

}

void CWidgetAngiography::updateSQLBB_CZXH(){

    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlDeleteCZXH="delete from BB_CZXH where SysCaseID='"+m_sSysCaseID+"' ";

    sqlStorge->exec(sSqlDeleteCZXH);


    for(int num = 0;num < m_sCZXHstartblood.size();num++){
        QString sSqlInsertCZXH="insert into BB_CZXH (SysCaseID, TIMI,startblood,endblood) values ('"+m_sSysCaseID+"', '"+m_sCZXHTIMI.at(num)+"','"+m_sCZXHstartblood.at(num)+"','"+m_sCZXHendblood.at(num)+"')";
        sqlStorge->exec(sSqlInsertCZXH);
    }

}

/****************************GHY表的拉取初始化与更新函数***************************************************/
void CWidgetAngiography::getSQLBB_GHY(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlGHY="select * from BB_GHY where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlGHY);


    while(sqlStorge->next())
    {

        m_sGHYghType.append(sqlStorge->value(2).toString());
        m_sGHYghblood.append(sqlStorge->value(3).toString());


    }


}

void CWidgetAngiography::sqlBB_GHYInit(){
    getSQLBB_GHY();
    if(m_sGHYghType.size()>0){
        ui->m_chkGHY->setChecked(true);
        ui->m_wgtGHY->show();
    }
    for(int num = 0;num < m_sGHYghType.size();num++){
        if(m_sGHYghType.at(num)=="管状"){
            QString addItemResult = m_sGHYghType.at(num)+"走行区域可见"+m_sGHYghblood.at(num)+"钙化影";
            ui->m_lstwGHXResult->addItem(addItemResult);
        }else{

            QString addItemResult = m_sGHYghblood.at(num)+"走行区域可见"+m_sGHYghType.at(num)+"钙化影";

            ui->m_lstwGHXResult->addItem(addItemResult);
        }

    }
    UpdateZDJG();

}

void CWidgetAngiography::updateSQLBB_GHY(){

    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlDeleteGHY="delete from BB_GHY where SysCaseID='"+m_sSysCaseID+"' ";

    sqlStorge->exec(sSqlDeleteGHY);


    for(int num = 0;num < m_sGHYghType.size();num++){
        QString sSqlInsertGHY="insert into BB_GHY (SysCaseID,ghType,ghblood) values ('"+m_sSysCaseID+"','"+m_sGHYghType.at(num)+"','"+m_sGHYghblood.at(num)+"')";
        sqlStorge->exec(sSqlInsertGHY);
    }

}

/****************************ZXS表的拉取初始化与更新函数***************************************************/
void CWidgetAngiography::getSQLBB_ZXS(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlZXS="select * from BB_ZXS where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlZXS);


    while(sqlStorge->next())
    {

        m_sZXSFigure = sqlStorge->value(2).toString();

        m_sZXSFigure = sqlStorge->value(2).toString();
        m_sZXSHeart_Size= sqlStorge->value(3).toString();
        m_sZXSszq= sqlStorge->value(4).toString();
        m_sZXSssq= sqlStorge->value(5).toString();

        m_sZXSsxfs= sqlStorge->value(6).toString();
        m_sZXSQJD= sqlStorge->value(7).toString();
        m_sZXSQC= sqlStorge->value(8).toString();
        m_sZXSXJ= sqlStorge->value(9).toString();
        m_sZXSGM= sqlStorge->value(10).toString();
        m_sZXSHJD= sqlStorge->value(11).toString();
        m_sZXSJG= sqlStorge->value(12).toString();
        m_sZXSHC= sqlStorge->value(13).toString();


    }

}

void CWidgetAngiography::sqlBB_ZXSInit(){
    getSQLBB_ZXS();

    if(m_sZXSFigure != nullptr){
        ui->m_chkZXSZY->setChecked(true);
        ui->m_wgtZXSZY->show();


        if(m_sZXSFigure == "正常"){
            ui->RB_ShapeNormal->setChecked(true);
        }else{
            ui->RB_ShapeAbnormal->setChecked(true);
            ui->m_wgtShapeYC->show();
        }


        if(m_sZXSHeart_Size=="正常"){
            ui->m_radXQDXNormal->setChecked(true);
        }else{

            ui->m_radXQDXAbnormal->setChecked(true);
        }

        ui->m_lineSZMQRL->setText(m_sZXSszq);
        ui->m_lineSSMQRL->setText(m_sZXSssq);

        ui->m_lineSXFS->setText(m_sZXSsxfs);


        if(m_sZXSQC!="正常"){
            ui->m_ckbQC->setChecked(true);

            auto alistQC=ui->m_grpQC->children();
            for(int i=0;i<alistQC.length();i++)
            {
                if( alistQC.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistQC.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSQC){
                        aControl->setChecked(true);
                    }

                }
            }
        }

        //QJD
        if(m_sZXSQJD!="正常"){
            ui->m_ckbQJD->setChecked(true);

            auto alistQJD=ui->m_grpQJD->children();
            for(int i=0;i<alistQJD.length();i++)
            {
                if( alistQJD.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistQJD.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSQJD){
                        aControl->setChecked(true);
                    }

                }
            }
        }

        //XJ
        if(m_sZXSXJ!="正常"){
            ui->m_ckbXJ->setChecked(true);

            auto alistXJ=ui->m_grpXJ->children();
            for(int i=0;i<alistXJ.length();i++)
            {
                if( alistXJ.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistXJ.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSXJ){
                        aControl->setChecked(true);
                    }

                }
            }
        }

        //GM
        if(m_sZXSGM!="正常"){
            ui->m_ckbGM->setChecked(true);

            auto alistGM=ui->m_grpGM->children();
            for(int i=0;i<alistGM.length();i++)
            {
                if( alistGM.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistGM.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSGM){
                        aControl->setChecked(true);
                    }

                }
            }
        }

        //HJD
        if(m_sZXSHJD!="正常"){
            ui->m_ckbHJD->setChecked(true);

            auto alistHJD=ui->m_grpHJD->children();
            for(int i=0;i<alistHJD.length();i++)
            {
                if( alistHJD.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistHJD.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSHJD){
                        aControl->setChecked(true);
                    }

                }
            }
        }

        //JG
        if(m_sZXSJG!="正常"){
            ui->m_ckbJG->setChecked(true);

            auto alistJG=ui->m_grpJG->children();
            for(int i=0;i<alistJG.length();i++)
            {
                if( alistJG.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistJG.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSJG){
                        aControl->setChecked(true);
                    }

                }
            }
        }

        //HC
        if(m_sZXSHC!="正常"){
            ui->m_ckbHC->setChecked(true);

            auto alistHC=ui->m_grpHC->children();
            for(int i=0;i<alistHC.length();i++)
            {
                if( alistHC.at(i)->inherits("QRadioButton"))
                {
                    auto aControl=qobject_cast<QRadioButton*>(alistHC.at(i));
                    QString sControl=aControl->text();
                    if(sControl==m_sZXSHC){
                        aControl->setChecked(true);
                    }

                }
            }
        }

    }




    UpdateZDJG();

}

void CWidgetAngiography::updateSQLBB_ZXS(){

    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());

    UpdateBB_ZXS();


    QString sSqlZXS="select * from BB_ZXS where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlZXS);
    if(sqlStorge->last()){
        sSqlZXS="update BB_ZXS set Figure = '"+m_sZXSFigure+"',Heart_Size = '"+m_sZXSHeart_Size+"', szq= '"+m_sZXSszq+"',ssq = '"+m_sZXSssq+"',sxfs = '"+m_sZXSsxfs+"',QJD = '"+m_sZXSQJD+"',QC = '"+m_sZXSQC+"',XJ = '"+m_sZXSXJ+"',GM = '"+m_sZXSGM+"',HJD = '"+m_sZXSHJD+"',HC = '"+m_sZXSHC+"',JG = '"+m_sZXSJG+"' where SysCaseID = '"+m_sSysCaseID+"'";

    }else{
        sSqlZXS = "insert into  BB_ZXS (SysCaseID,Figure,Heart_Size,szq,ssq,sxfs,QJD,QC,XJ,GM,HJD,HC,JG) values  ('"+m_sSysCaseID+"','"+m_sZXSFigure+"','"+m_sZXSHeart_Size+"','"+m_sZXSszq+"','"+m_sZXSssq+"','"+m_sZXSsxfs+"','"+m_sZXSQJD+"','"+m_sZXSQC+"','"+m_sZXSXJ+"','"+m_sZXSGM+"','"+m_sZXSHJD+"','"+m_sZXSHC+"','"+m_sZXSJG+"')";
    }
    sqlStorge->exec(sSqlZXS);
}



/****************************JLYZ表的拉取初始化与更新函数***************************************************/
void CWidgetAngiography::getSQLBB_JLYZ(){
    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    QString sSqlJLYZ="select * from BB_JLYZ where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlJLYZ);

    while(sqlStorge->next())
    {
        m_sJLYZzyjl=sqlStorge->value(2).toString();
        m_sJLYZjyb=sqlStorge->value(3).toString();
        m_sJLYZgyxg=sqlStorge->value(4).toString();



    }

    m_sZYJL = m_sJLYZzyjl;

}

void CWidgetAngiography::sqlBB_JLYZInit(){
    getSQLBB_JLYZ();
    ui->m_txtZYJL->setText(m_sJLYZzyjl);
    ui->m_cmbJYBCL->setCurrentText(m_sJLYZjyb);
    ui->m_cmbGYXG->lineEdit()->setText(m_sJLYZgyxg);

    if(m_sJLYZjyb!="即刻PCI"){

        ui->m_cmbGYXG->setEnabled(false);
    }
    if(m_sJLYZjyb==""){

        ui->m_cmbGYXG->setEnabled(true);
    }

    QString sJLYZIsChecked;
    for(int i=0;i<m_sJLYZgyxg.size();i++){
        if(m_sJLYZgyxg[i]!="/"){
            sJLYZIsChecked+=m_sJLYZgyxg[i];
        }else{

            for (int i = 0; i<m_vGYXG.size(); i++)
            {
                QListWidgetItem *lstwItem = m_lstwGYXG->item(i);
                QWidget *wgtItem = m_lstwGYXG->itemWidget(lstwItem);
                QCheckBox *chkCurr = (QCheckBox *)wgtItem;

                if(chkCurr->text()==sJLYZIsChecked)
                {
                    chkCurr->setChecked(true);
                }
            }
            sJLYZIsChecked="";
        }
    }


    QString m_sZYJLisChecked;

    for(int i=0;i<m_sJLYZzyjl.size();i++){

        if(m_sJLYZzyjl[i]!="、"&&m_sJLYZzyjl[i]!=":"){
            m_sZYJLisChecked+=m_sJLYZzyjl[i];
        }else{

            auto alistZYJL=ui->groupBox_11->children();
            for(int j=0;j<alistZYJL.length();j++)
            {

                if( alistZYJL.at(j)->inherits("QCheckBox"))
                {
                    auto aControl=qobject_cast<QCheckBox*>(alistZYJL.at(j));

                    if(aControl->text()==m_sZYJLisChecked){
                        aControl->setChecked(true);


                    }

                }

            }
            if(m_sZYJLisChecked=="单支病变"){

                QString s;
                for(int k=i+1;k<m_sJLYZzyjl.size();k++){
                    if(m_sJLYZzyjl[k]!="、"){
                        s+=m_sJLYZzyjl[k];
                    }else{
                        ui->m_cmbDZBB->setCurrentText(s);

                        i=k;
                        break;
                    }
                }

            }
            if(m_sZYJLisChecked=="双支病变"){
                QString s;
                int count =0;
                for(int k=i+1;k<m_sJLYZzyjl.size();k++){

                    if(m_sJLYZzyjl[k]!="、"){
                        if(m_sJLYZzyjl[k]=="+"){
                            count++;

                            ui->m_cmbSZBBFirst->setCurrentText(s);
                            s="";
                            continue;
                        }
                        s+=m_sJLYZzyjl[k];
                    }else{
                        if(count == 1){
                            ui->m_cmbSZBBSecond->setCurrentText(s);
                            s="";
                            i=k;

                            break;
                        }else{


                            ui->m_cmbSZBBFirst->setCurrentText(s);
                            s="";
                            i=k;
                            break;
                        }


                    }
                }
            }
            if(m_sZYJLisChecked=="左主干+双支病变"){
                QString s;
                int count =0;
                for(int k=i+1;k<m_sJLYZzyjl.size();k++){

                    if(m_sJLYZzyjl[k]!="、"){
                        if(m_sJLYZzyjl[k]=="+"){
                            count++;

                            ui->m_cmbLeftDoubleFirst->setCurrentText(s);
                            s="";
                            continue;
                        }
                        s+=m_sJLYZzyjl[k];

                    }else{

                        if(count==1){
                            ui->m_cmbLeftDoubleSecond->setCurrentText(s);
                            s="";
                            i=k;

                            break;
                        }else{
                            ui->m_cmbLeftDoubleFirst->setCurrentText(s);
                            s="";
                            i=k;

                            break;
                        }


                    }
                }

            }

            if(m_sZYJLisChecked=="左主干+三支病变"){
                QString s;
                int count =0;
                for(int k=i+1;k<m_sJLYZzyjl.size();k++){

                    if(m_sJLYZzyjl[k]!="、"){
                        if(m_sJLYZzyjl[k]=="+"){
                            count++;
                            if(count==1){
                                ui->m_cmbLeftThreefirst->setCurrentText(s);

                            }else{
                                ui->m_cmbLeftThreeSecond->setCurrentText(s);
                            }

                            s="";
                            continue;
                        }
                        s+=m_sJLYZzyjl[k];
                    }else{

                        if(count==0){
                            ui->m_cmbLeftThreefirst->setCurrentText(s);
                            s="";
                            i=k;

                            break;
                        }else if(count==1){
                            ui->m_cmbLeftThreeSecond->setCurrentText(s);
                            s="";
                            i=k;

                            break;
                        }
                        else
                        {
                            ui->m_cmbLeftThreeThird->setCurrentText(s);
                            s="";
                            i=k;

                            break;
                        }





                    }
                }

            }
            m_sZYJLisChecked="";

        }
    }

    for(int i = 0;i<m_ListZYJL.size();i++){
        if(m_ListZYJL[i]->text()=="单支病变"){
            if(m_ListZYJL[i]->isChecked()){

            }else{
                ui->m_cmbDZBB->setEnabled(0);
            }
        }

        if(m_ListZYJL[i]->text()=="双支病变"){
            if(m_ListZYJL[i]->isChecked()){

            }else{
                ui->m_cmbSZBBFirst->setEnabled(0);
                ui->m_cmbSZBBSecond->setEnabled(0);
            }
        }

        if(m_ListZYJL[i]->text()=="左主干+双支病变"){
            if(m_ListZYJL[i]->isChecked()){

            }else{
                ui->m_cmbLeftDoubleFirst->setEnabled(0);
                ui->m_cmbLeftDoubleSecond->setEnabled(0);
            }
        }

        if(m_ListZYJL[i]->text()=="左主干+三支病变"){
            if(m_ListZYJL[i]->isChecked()){

            }else{
                ui->m_cmbLeftThreefirst->setEnabled(0);
                ui->m_cmbLeftThreeSecond->setEnabled(0);
                ui->m_cmbLeftThreeThird->setEnabled(0);
            }
        }

    }

}

void CWidgetAngiography::updateSQLBB_JLYZ(){

    QSqlQuery *sqlStorge=new QSqlQuery(SQLDB::GetDfytCathLab());


    m_sJLYZzyjl = m_sZYJL;
    m_sJLYZjyb = ui->m_cmbJYBCL->currentText();
    m_sJLYZgyxg = ui->m_cmbGYXG->lineEdit()->text();


    QString sSqlJLYZ="select * from BB_JLYZ where SysCaseID='"+m_sSysCaseID+"' ";
    sqlStorge->exec(sSqlJLYZ);
    if (sqlStorge->last())

    {

        sSqlJLYZ="update BB_JLYZ set zyjl = '"+m_sJLYZzyjl+"',jyb = '"+m_sJLYZjyb+"', gyxg= '"+m_sJLYZgyxg+"' where SysCaseID = '"+m_sSysCaseID+"'";


    }else{
        sSqlJLYZ="insert into  BB_JLYZ (SysCaseID,zyjl,jyb,gyxg) values  ('"+m_sSysCaseID+"','"+m_sJLYZzyjl+"','"+m_sJLYZjyb+"','"+m_sJLYZgyxg+"')";

    }
    sqlStorge->exec(sSqlJLYZ);

}

/**
 * @brief CWidgetAngiography::造影结论初始化
 */
void CWidgetAngiography::ZXSInit(){

    m_sZXSFigure =nullptr;
    m_sZXSHeart_Size=nullptr;
    m_sZXSszq=nullptr;
    m_sZXSssq=nullptr;
    m_sZXSsxfs=nullptr;
    m_sZXSQJD=nullptr;
    m_sZXSQC=nullptr;
    m_sZXSXJ=nullptr;
    m_sZXSGM=nullptr;
    m_sZXSHJD=nullptr;
    m_sZXSJG=nullptr;
    m_sZXSHC=nullptr;


    ui->RB_ShapeNormal->setChecked(true);
    ui->m_wgtShapeYC->hide();
    ui->m_radXQDXNormal->setChecked(true);
    ui->m_lineSZMQRL->setText("0.0");
    ui->m_lineSZMQRL->setValidator(new QDoubleValidator());
    ui->m_lineSSMQRL->setValidator(new QDoubleValidator());
    ui->m_lineSSMQRL->setText("0.0");
    ui->m_lineSXFS->setText("0.0");
    ui->m_lineSXFS->setReadOnly(true);
    ui->m_radQC_ZC->setChecked(true);
    ui->m_radQJD_ZC->setChecked(true);
    ui->m_radXJ_ZC->setChecked(true);;
    ui->m_radGM_ZC->setChecked(true);
    ui->m_radHJD_ZC->setChecked(true);
    ui->m_radJG_ZC->setChecked(true);
    ui->m_radHC_ZC->setChecked(true);


    ui->m_ckbQC->setChecked(false);
    ui->m_ckbQJD->setChecked(false);
    ui->m_ckbXJ->setChecked(false);
    ui->m_ckbGM->setChecked(false);
    ui->m_ckbHJD->setChecked(false);
    ui->m_ckbJG->setChecked(false);
    ui->m_ckbHC->setChecked(false);
}

void CWidgetAngiography::on_m_lstwCABGRight_itemDoubleClicked(QListWidgetItem *item)
{
    if(ui->m_lstwCABG->currentItem()->text()==ui->m_lstwCABGRight->currentItem()->text()){

    }else{
        for (int reslutNumber = 0; reslutNumber < ui->m_lstwCABGResult->count(); reslutNumber++)

        {

            //            QString itemReslut =ui->m_lstwCABGResult->item(reslutNumber)->text();

            //            if (itemReslut == ui->m_lstwCABG->currentItem()->text()+"-"+ui->m_lstwCABGRight->currentItem()->text())

            //            {

            //                return;

            //            }

        }
        ui->m_lstwCABGResult->addItem(ui->m_lstwCABG->currentItem()->text()+"-"+ui->m_lstwCABGRight->currentItem()->text());
        m_sCABGstartblood.append(ui->m_lstwCABG->currentItem()->text());
        m_sCABGendblood.append(ui->m_lstwCABGRight->currentItem()->text());
    }

    UpdateZDJG();
}

void CWidgetAngiography::on_m_lstwCZXHRight_itemDoubleClicked(QListWidgetItem *item)
{
    QString addItemXL="";
    auto alistXL=ui->m_grpXL->children();
    for(int i=0;i<alistXL.length();i++)
    {
        if( alistXL.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(alistXL.at(i));
            QString sControl=aControl->text();
            if(aControl->isChecked()){
                addItemXL="血流等级"+aControl->text();
                m_sCZXHTIMI.append(aControl->text());
            }

        }
    }


    if(ui->m_lstwCZXHLeft->currentItem()->text()==ui->m_lstwCZXHRight->currentItem()->text()){

    }else{


        QString addItemResult = "由"+ui->m_lstwCZXHLeft->currentItem()->text()+"至"+ui->m_lstwCZXHRight->currentItem()->text()+"形成侧枝循环,"+addItemXL;

        ui->m_lstwCZXHResult->addItem(addItemResult);
        m_sCZXHstartblood.append(ui->m_lstwCZXHLeft->currentItem()->text());
        m_sCZXHendblood.append(ui->m_lstwCZXHRight->currentItem()->text());
        UpdateZDJG();

    }
}




/**
 * @brief 点击X按钮的删除事件
 */
void CWidgetAngiography::on_m_btnDeleteCABG_clicked()
{
    int iRemoveItem = ui->m_lstwCABGResult->currentRow();
    ui->m_lstwCABGResult->removeItemWidget(ui->m_lstwCABGResult->currentItem());
    m_sCABGstartblood.removeAt(iRemoveItem);
    m_sCABGendblood.removeAt(iRemoveItem);
    delete ui->m_lstwCABGResult->currentItem();
    UpdateZDJG();
}

void CWidgetAngiography::on_m_btnDeleteCZXH_clicked()
{
    int iRemoveItem = ui->m_lstwCZXHResult->currentRow();
    ui->m_lstwCZXHResult->removeItemWidget(ui->m_lstwCZXHResult->currentItem());
    m_sCZXHstartblood.removeAt(iRemoveItem);
    m_sCZXHendblood.removeAt(iRemoveItem);
    delete ui->m_lstwCZXHResult->currentItem();
    UpdateZDJG();
}

void CWidgetAngiography::on_m_btnDeleteGHY_clicked()
{
    int iRemoveItem = ui->m_lstwGHXResult->currentRow();
    ui->m_lstwGHXResult->removeItemWidget(ui->m_lstwGHXResult->currentItem());
    m_sGHYghblood.removeAt(iRemoveItem);
    m_sGHYghType.removeAt(iRemoveItem);
    delete ui->m_lstwGHXResult->currentItem();
    UpdateZDJG();
}

void CWidgetAngiography::on_m_ckbZYMJL_DZBB_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbDZBB->setEnabled(1);
    }
    else
    {
        ui->m_cmbDZBB->setEnabled(0);
        ui->m_cmbDZBB->setCurrentIndex(0);
    }
}




void CWidgetAngiography::on_m_radGZ_clicked()
{

}

void CWidgetAngiography::on_m_radDPZ_clicked()
{
//    ui->m_ckbWZ_RCA->setChecked(false);
//    ui->m_ckbWZ_LAD->setChecked(false);
//    ui->m_ckbWZ_LCA->setChecked(false);
//    ui->m_ckbWZ_LCX->setChecked(false);
}

void CWidgetAngiography::on_m_ckbZYMJL_SZBB_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbSZBBFirst->setEnabled(1);
        ui->m_cmbSZBBSecond->setEnabled(1);
    }
    else
    {
        ui->m_cmbSZBBFirst->setEnabled(0);
        ui->m_cmbSZBBSecond->setEnabled(0);

        ui->m_cmbSZBBFirst->setCurrentIndex(0);
        ui->m_cmbSZBBSecond->setCurrentIndex(0);
    }
}

void CWidgetAngiography::on_m_ckbZYMJL_LeftDouble_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbLeftDoubleFirst->setEnabled(1);
        ui->m_cmbLeftDoubleSecond->setEnabled(1);
    }
    else
    {
        ui->m_cmbLeftDoubleFirst->setEnabled(0);
        ui->m_cmbLeftDoubleSecond->setEnabled(0);

        ui->m_cmbLeftDoubleFirst->setCurrentIndex(0);
        ui->m_cmbLeftDoubleSecond->setCurrentIndex(0);
    }
}

void CWidgetAngiography::on_m_ckbZYMJL_LeftThree_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbLeftThreefirst->setEnabled(1);
        ui->m_cmbLeftThreeSecond->setEnabled(1);
        ui->m_cmbLeftThreeThird->setEnabled(1);
    }
    else
    {
        ui->m_cmbLeftThreefirst->setEnabled(0);
        ui->m_cmbLeftThreeSecond->setEnabled(0);
        ui->m_cmbLeftThreeThird->setEnabled(0);

        ui->m_cmbLeftThreefirst->setCurrentIndex(0);
        ui->m_cmbLeftThreeSecond->setCurrentIndex(0);
        ui->m_cmbLeftThreeThird->setCurrentIndex(0);
    }
}

void CWidgetAngiography::on_m_radGZ_toggled(bool checked)
{
    if(checked){
        ui->m_ckbWZ_RCA->setChecked(false);
        ui->m_ckbWZ_LAD->setChecked(false);
        ui->m_ckbWZ_LCA->setChecked(false);
        ui->m_ckbWZ_LCX->setChecked(false);
    }else{
        ui->m_ckbWZ_RCA->setChecked(false);
        ui->m_ckbWZ_LAD->setChecked(false);
        ui->m_ckbWZ_LCA->setChecked(false);
        ui->m_ckbWZ_LCX->setChecked(false);
    }
}

