#include "cwidgetmedtool.h"
#include "ui_cwidgetmedtool.h"

CWidgetMedTool::CWidgetMedTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetMedTool)
{
    ui->setupUi(this);
    m_wgtTool = new CWidgetTool();
    m_wgtMedicine = new CWidgetMedicine();
    m_wgtDistributor = new CWidgetDistributor();
    ui->m_tbTool->layout()->addWidget(m_wgtTool);
    ui->m_tbMed->layout()->addWidget(m_wgtMedicine);
    ui->m_tbDistributor->layout()->addWidget(m_wgtDistributor);

    /********* 人员管理  *********/
    ui->m_btnRYGX->hide();
    //设置表格不可编辑
    ui->m_tblwRYLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表的最后一列左对齐
    ui->m_tblwRYLB->horizontalHeaderItem(ui->m_tblwRYLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    //设置表选中整行
    ui->m_tblwRYLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwRYLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置手机号只能输入数字
    QRegExp rx("[0-9.]+$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->m_lineRYDH->setValidator(pReg);
    //隐藏第一列
    ui->m_tblwRYLB->hideColumn(0);

    /********* 保险类型管理  *********/
    ui->m_btnBXLXGX->hide();
    //设置表格不可编辑
    ui->m_tblwBXLXLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表的最后一列左对齐
    ui->m_tblwBXLXLB->horizontalHeaderItem(ui->m_tblwBXLXLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    //设置表选中整行
    ui->m_tblwBXLXLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwBXLXLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    //显示所有记录
    ShowInfoAtTable("select * from InsuType_T", ui->m_tblwBXLXLB);    

    /********* 手术类型管理  *********/
    ui->m_btnSSLXGX->hide();
    //设置表格不可编辑
    ui->m_tblwSSLXLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表的最后一列左对齐
    ui->m_tblwSSLXLB->horizontalHeaderItem(ui->m_tblwSSLXLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    //设置表选中整行
    ui->m_tblwSSLXLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwSSLXLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ShowInfoAtTable("select * from SurgType_T order by SurgTypeID", ui->m_tblwSSLXLB);
}

CWidgetMedTool::~CWidgetMedTool()
{
    delete ui;

    delete m_wgtTool;
    m_wgtTool=NULL;
    delete m_wgtMedicine;
    m_wgtMedicine=NULL;
    delete m_wgtDistributor;
    m_wgtDistributor=NULL;
}

/**
 * @brief 显示查询到的信息至表格中
 * @param sSqlSelect
 */
void CWidgetMedTool::ShowInfoAtTable(QString sSqlSelect, QTableWidget* tblwCurLB)
{
    //从数据库中读取信息
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sOneQCRecord = "";
    QStringList lQCRecord;
    sqlStorage->exec(sSqlSelect);
    while(sqlStorage->next())
    {
        for(int i = 0;i < tblwCurLB->columnCount();i++)
        {
            sOneQCRecord += sqlStorage->value(i).toString() + "///";
        }
        lQCRecord.append(sOneQCRecord.left(sOneQCRecord.length() - 3));
        sOneQCRecord = "";
    }
    //将信息填入表格中
    int nRow = 0;
    int nColumn = 0;
    QStringList lTemp;
    tblwCurLB->setRowCount(0);
    tblwCurLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lQCRecord)
    {
        tblwCurLB->setRowCount(tblwCurLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            tblwCurLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            tblwCurLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //隐藏第一列
    tblwCurLB->hideColumn(0);
    //可视化管线更新
    tblwCurLB->viewport()->update();
}

/****************** 人员管理操作  ******************/
/**
 * @brief 人员查询
 */
void CWidgetMedTool::on_m_btnRYCX_clicked()
{
    if(ui->m_lineRYCX->text() == "")
    {
        ShowInfoAtTable("select * from Staff_T order by StaffID", ui->m_tblwRYLB);
    }
    else
    {
        ShowInfoAtTable("select * from Staff_T where StaffName='" + ui->m_lineRYCX->text() + "' order by StaffID", ui->m_tblwRYLB);
    }
}

/**
 * @brief 人员管理复位
 */
void CWidgetMedTool::on_m_btnRYFW_clicked()
{
    ui->m_lineRYCX->setText("");
    ui->m_lineRYMC->setText("");
    ui->m_lineRYZC->setText("");
    ui->m_lineRYDH->setText("");
    ui->m_lineRYDZ->setText("");
    ui->m_tblwRYLB->clearContents();
    ui->m_tblwRYLB->setRowCount(0);
    ui->m_spbRYNL->setValue(0);
    ui->m_cmbRYXB->setCurrentIndex(-1);
    ui->m_btnRYTJ->show();
    ui->m_btnRYGX->hide();
}

/**
 * @brief 人员管理添加
 */
void CWidgetMedTool::on_m_btnRYTJ_clicked()
{
    //判断必要信息是否漏填
    if(ui->m_lineRYMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写姓名！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineRYZC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写职称！", QMessageBox::Ok);
        return;
    }
    //添加信息至数据库
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("insert into Staff_T(StaffName,StaffPosi,Age,Sex,Tel,Address) "
                 "values('" + ui->m_lineRYMC->text() +
                 "','" + ui->m_lineRYZC->text() +
                 "'," + ui->m_spbRYNL->text() +
                 ",'" + ui->m_cmbRYXB->currentText() +
                 "','" + ui->m_lineRYDH->text() +
                 "','" + ui->m_lineRYDZ->text() +
                 "')");
    ShowInfoAtTable("select * from Staff_T where StaffName='" + ui->m_lineRYMC->text() + "' order by StaffID", ui->m_tblwRYLB);
}


/**
 * @brief 双击对人员表格中的信息进行编辑
 * @param item
 */
void CWidgetMedTool::on_m_tblwRYLB_itemDoubleClicked(QTableWidgetItem *item)
{
    //显示更新按钮，隐藏添加按钮
    ui->m_btnRYTJ->hide();
    ui->m_btnRYGX->show();
    //将信息显示在界面控件中
    m_nCurRecordIDRY = ui->m_tblwRYLB->item(item->row(), 0)->text().toInt();
    ui->m_lineRYMC->setText(ui->m_tblwRYLB->item(item->row(), 1)->text());
    ui->m_lineRYZC->setText(ui->m_tblwRYLB->item(item->row(), 2)->text());
    ui->m_spbRYNL->setValue(ui->m_tblwRYLB->item(item->row(), 3)->text().toInt());
    ui->m_cmbRYXB->setCurrentText(ui->m_tblwRYLB->item(item->row(), 4)->text().remove(" "));
    ui->m_lineRYDH->setText(ui->m_tblwRYLB->item(item->row(), 5)->text());
    ui->m_lineRYDZ->setText(ui->m_tblwRYLB->item(item->row(), 6)->text());
}

/**
 * @brief 人员管理更新
 */
void CWidgetMedTool::on_m_btnRYGX_clicked()
{
    //判断必要信息是否漏填
    if(ui->m_lineRYMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写配送商名称！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineRYZC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写联系人！", QMessageBox::Ok);
        return;
    }
    //更新信息至数据库
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("update Staff_T set StaffName='" + ui->m_lineRYMC->text() + "',StaffPosi='" + ui->m_lineRYZC->text() + "',"
                 "Age=" + ui->m_spbRYNL->text() + ",Sex='" + ui->m_cmbRYXB->currentText() + "',Tel='" + ui->m_lineRYDH->text() +"',"
                 "Address='" + ui->m_lineRYDZ->text() + "' where StaffID=" + QString::number(m_nCurRecordIDRY));
    ui->m_tblwRYLB->clearContents();
    //显示更新的信息
    ShowInfoAtTable("select * from Staff_T where StaffID=" + QString::number(m_nCurRecordIDRY) + " order by StaffID", ui->m_tblwRYLB);
    //初始化控件
    ui->m_lineRYCX->setText("");
    ui->m_lineRYMC->setText("");
    ui->m_lineRYZC->setText("");
    ui->m_lineRYDH->setText("");
    ui->m_lineRYDZ->setText("");
    ui->m_spbRYNL->setValue(0);
    ui->m_cmbRYXB->setCurrentIndex(-1);
    ui->m_btnRYTJ->show();
    ui->m_btnRYGX->hide();

}

/**
 * @brief 人员管理删除
 */
void CWidgetMedTool::on_m_btnRYSC_clicked()
{
    if(ui->m_tblwRYLB->selectedItems().count())
    {
        QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
        //获取选中项的ID
        int nCurSelectedID = ui->m_tblwRYLB->item(ui->m_tblwRYLB->selectedItems()[0]->row(), 0)->text().toInt();
        int bResult = QMessageBox::question(NULL, "提示", "确认删除吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(QMessageBox::Yes == bResult)
        {
            sqlDfy->exec("delete Staff_T where StaffID=" + QString::number(nCurSelectedID));
        }
        ShowInfoAtTable("select * from Staff_T order by StaffID", ui->m_tblwRYLB);
    }
}

/****************** 保险类型管理操作  ******************/
/**
 * @brief 保险类型管理保险类型输入框完成编辑
 */
void CWidgetMedTool::on_m_lineBXLXMC_editingFinished()
{
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("select * from InsuType_T where InsuType='" + ui->m_lineBXLXMC->text() + "'");
    if(sqlDfy->last())
    {
        QMessageBox::warning(NULL, "警告", "此保险类型已存在，其信息已显示在各个输入框中,请更新!", QMessageBox::Ok);
        m_nCurRecordIDBXLX = sqlDfy->value(0).toInt();
        ui->m_lineBXLXMC->setText(sqlDfy->value(1).toString());
        ui->m_lineBXLXMS->setText(sqlDfy->value(2).toString());
        ui->m_btnBXLXGX->show();
        ui->m_btnBXLXTJ->hide();
    }
}


/**
 * @brief 保险类型管理添加
 */
void CWidgetMedTool::on_m_btnBXLXTJ_clicked()
{
    //判断必要信息是否漏填
    if(ui->m_lineBXLXMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写保险类型！", QMessageBox::Ok);
        return;
    }
    //添加信息至数据库
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("insert into InsuType_T(InsuType,Description) values('" + ui->m_lineBXLXMC->text() + "','" + ui->m_lineBXLXMS->text() + "')");
    ShowInfoAtTable("select * from InsuType_T", ui->m_tblwBXLXLB);
    ui->m_lineBXLXMC->setText("");
    ui->m_lineBXLXMS->setText("");
}

/**
 * @brief 保险类型管理复位
 */
void CWidgetMedTool::on_m_btnBXLXFW_clicked()
{
    ui->m_btnBXLXGX->hide();
    ui->m_btnBXLXTJ->show();
    ui->m_lineBXLXMC->setText("");
    ui->m_lineBXLXMS->setText("");
    ShowInfoAtTable("select * from InsuType_T", ui->m_tblwBXLXLB);
}

/**
 * @brief 保险类型管理更新
 */
void CWidgetMedTool::on_m_btnBXLXGX_clicked()
{
    //判断必要信息是否漏填
    if(ui->m_lineBXLXMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写保险类型名称！", QMessageBox::Ok);
        return;
    }
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("update InsuType_T set InsuType='" + ui->m_lineBXLXMC->text() + "',Description='" + ui->m_lineBXLXMS->text() + "' where InsuTypeID=" + QString::number(m_nCurRecordIDBXLX));
    ShowInfoAtTable("select * from InsuType_T", ui->m_tblwBXLXLB);
    ui->m_lineBXLXMC->setText("");
    ui->m_lineBXLXMS->setText("");
    ui->m_btnBXLXGX->hide();
    ui->m_btnBXLXTJ->show();
}

/**
 * @brief 双击对保险类型表格中的信息进行编辑
 * @param item
 */
void CWidgetMedTool::on_m_tblwBXLXLB_itemDoubleClicked(QTableWidgetItem *item)
{
    ui->m_btnBXLXGX->show();
    ui->m_btnBXLXTJ->hide();
    m_nCurRecordIDBXLX = ui->m_tblwBXLXLB->item(item->row(), 0)->text().toInt();
    ui->m_lineBXLXMC->setText(ui->m_tblwBXLXLB->item(item->row(), 1)->text());
    ui->m_lineBXLXMS->setText(ui->m_tblwBXLXLB->item(item->row(), 2)->text());
}

/**
 * @brief 保险类型删除
 */
void CWidgetMedTool::on_m_btnBXLXSC_clicked()
{
    if(ui->m_tblwBXLXLB->selectedItems().count())
    {
        QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
        //获取选中项的ID
        int nCurSelectedID = ui->m_tblwBXLXLB->item(ui->m_tblwBXLXLB->selectedItems()[0]->row(), 0)->text().toInt();
        int bResult = QMessageBox::question(NULL, "提示", "确认删除吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(QMessageBox::Yes == bResult)
        {
            sqlDfy->exec("delete InsuType_T where InsuTypeID=" + QString::number(nCurSelectedID));
        }
        ShowInfoAtTable("select * from InsuType_T", ui->m_tblwBXLXLB);
    }
}

/****************** 手术类型操作  ******************/
/**
 * @brief 手术类型复位
 */
void CWidgetMedTool::on_m_btnSSLXFW_clicked()
{
    ui->m_lineSSLXMC->setText("");
    ui->m_btnSSLXTJ->show();
    ui->m_btnSSLXGX->hide();
}

/**
 * @brief 手术类型添加
 */
void CWidgetMedTool::on_m_btnSSLXTJ_clicked()
{
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    //判断必要信息是否漏填
    if(ui->m_lineSSLXMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写手术类型！", QMessageBox::Ok);
        return;
    }
    sqlDfy->exec("select * from SurgType_T where SurgTypeName='" + ui->m_lineSSLXMC->text() + "' order by SurgTypeID");
    if(sqlDfy->last())
    {
        QMessageBox::warning(NULL, "警告", "该手术类型已存在！", QMessageBox::Ok);
        return;
    }
    else
    {
        //添加信息至数据库
        sqlDfy->exec("insert into SurgType_T(SurgTypeName) values('" + ui->m_lineSSLXMC->text() + "')");
        ShowInfoAtTable("select * from SurgType_T order by SurgTypeID", ui->m_tblwSSLXLB);
        ui->m_lineSSLXMC->setText("");
    }
}

/**
 * @brief 双击对手术类型表格中的信息进行编辑
 * @param item
 */
void CWidgetMedTool::on_m_tblwSSLXLB_itemDoubleClicked(QTableWidgetItem *item)
{
    //显示更新按钮，隐藏添加按钮
    ui->m_btnSSLXTJ->hide();
    ui->m_btnSSLXGX->show();
    //将信息显示在界面控件中
    m_nCurRecordIDSSLX = ui->m_tblwSSLXLB->item(item->row(), 0)->text().toInt();
    ui->m_lineSSLXMC->setText(ui->m_tblwSSLXLB->item(item->row(), 1)->text());
}

/**
 * @brief 手术类型更新
 */
void CWidgetMedTool::on_m_btnSSLXGX_clicked()
{
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    //判断必要信息是否漏填
    if(ui->m_lineSSLXMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写手术类型！", QMessageBox::Ok);
        return;
    }
    sqlDfy->exec("select * from SurgType_T where SurgTypeName='" + ui->m_lineSSLXMC->text() + "' order by SurgTypeID");
    if(sqlDfy->last())
    {
        QMessageBox::warning(NULL, "警告", "该手术类型已存在！", QMessageBox::Ok);
        return;
    }
    else
    {
        //添加信息至数据库
        sqlDfy->exec("update SurgType_T set SurgTypeName='" + ui->m_lineSSLXMC->text() + "' where SurgTypeID=" + QString::number(m_nCurRecordIDSSLX));
        ShowInfoAtTable("select * from SurgType_T order by SurgTypeID", ui->m_tblwSSLXLB);
        ui->m_lineSSLXMC->setText("");
    }
    ui->m_btnSSLXTJ->show();
    ui->m_btnSSLXGX->hide();
}

/**
 * @brief 手术类型删除
 */
void CWidgetMedTool::on_m_btnSSLXSC_clicked()
{
    if(ui->m_tblwSSLXLB->selectedItems().count())
    {
        QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
        //获取选中项的ID
        int nCurSelectedID = ui->m_tblwSSLXLB->item(ui->m_tblwSSLXLB->selectedItems()[0]->row(), 0)->text().toInt();
        int bResult = QMessageBox::question(NULL, "提示", "确认删除吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(QMessageBox::Yes == bResult)
        {
            sqlDfy->exec("delete SurgType_T where SurgTypeID=" + QString::number(nCurSelectedID));
        }
        ShowInfoAtTable("select * from SurgType_T order by SurgTypeID", ui->m_tblwSSLXLB);
    }
}
