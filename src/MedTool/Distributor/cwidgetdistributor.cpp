#include "cwidgetdistributor.h"
#include "ui_cwidgetdistributor.h"

CWidgetDistributor::CWidgetDistributor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetDistributor)
{
    ui->setupUi(this);
    ui->m_btnPSSGX->hide();
    //设置表格不可编辑
    ui->m_tblwPSSLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表的最后一列左对齐
    ui->m_tblwPSSLB->horizontalHeaderItem(ui->m_tblwPSSLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    //设置表选中整行
    ui->m_tblwPSSLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwPSSLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置手机号与邮编只能输入数字
    QRegExp rx("[0-9.]+$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->m_linePSSDH->setValidator(pReg);
    ui->m_linePSSYB->setValidator(new QIntValidator(100000, 999999));
    //隐藏第一列
    ui->m_tblwPSSLB->hideColumn(0);
}

CWidgetDistributor::~CWidgetDistributor()
{
    delete ui;
}

/**
 * @brief 显示查询到的信息至表格中
 * @param sSqlSelect
 */
void CWidgetDistributor::ShowInfoAtTable(QString sSqlSelect)
{
    //从数据库中读取信息
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sOneQCRecord = "";
    QStringList lQCRecord;
    sqlStorage->exec(sSqlSelect);
    while(sqlStorage->next())
    {
        for(int i = 0;i < ui->m_tblwPSSLB->columnCount();i++)
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
    ui->m_tblwPSSLB->setRowCount(0);
    ui->m_tblwPSSLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lQCRecord)
    {
        ui->m_tblwPSSLB->setRowCount(ui->m_tblwPSSLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            ui->m_tblwPSSLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            ui->m_tblwPSSLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //隐藏第一列
    ui->m_tblwPSSLB->hideColumn(0);
    //可视化管线更新
    ui->m_tblwPSSLB->viewport()->update();
}

/**
 * @brief 查询记录
 */
void CWidgetDistributor::on_m_btnPSSCX_clicked()
{
    if(ui->m_linePSSCX->text() == "")
    {
        ShowInfoAtTable("select ManuID,ManuName,LineMan,Phone,email,Address,Zip from Manufacturer_T order by ManuID");
    }
    else
    {
        ShowInfoAtTable("select ManuID,ManuName,LineMan,Phone,email,Address,Zip from Manufacturer_T where ManuName='" + ui->m_linePSSCX->text() + "' order by ManuID");
    }
}

/**
 * @brief 复位
 */
void CWidgetDistributor::on_m_btnPSSFW_clicked()
{
    ui->m_linePSSCX->setText("");
    ui->m_linePSSMC->setText("");
    ui->m_linePSSLXR->setText("");
    ui->m_linePSSDH->setText("");
    ui->m_linePSSEMAIL->setText("");
    ui->m_linePSSDZ->setText("");
    ui->m_linePSSYB->setText("");
    ui->m_tblwPSSLB->clearContents();
    ui->m_tblwPSSLB->setRowCount(0);
    ui->m_btnPSSTJ->show();
    ui->m_btnPSSGX->hide();
    ui->m_linePSSMC->setEnabled(1);
    m_nCurRecordID = -1;
}

/**
 * @brief 添加
 */
void CWidgetDistributor::on_m_btnPSSTJ_clicked()
{
    //判断必要信息是否漏填
    if(ui->m_linePSSMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写配送商名称！", QMessageBox::Ok);
        return;
    }
    if(ui->m_linePSSLXR->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写联系人！", QMessageBox::Ok);
        return;
    }
    if(ui->m_linePSSDH->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写电话！", QMessageBox::Ok);
        return;
    }
    //添加信息至数据库
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());

    sqlDfy->exec("insert into Manufacturer_T(ManuName,LineMan,Phone,email,Address,Zip) "
                 "values('" + ui->m_linePSSMC->text() +
                 "','" + ui->m_linePSSLXR->text() +
                 "','" + ui->m_linePSSDH->text() +
                 "','" + ui->m_linePSSEMAIL->text() +
                 "','" + ui->m_linePSSDZ->text() +
                 "','" + ui->m_linePSSYB->text() +
                 "')");
    ShowInfoAtTable("select ManuID,ManuName,LineMan,Phone,email,Address,Zip from Manufacturer_T where ManuName='" + ui->m_linePSSMC->text() + "' order by ManuID");
    ui->m_linePSSMC->setText("");
    ui->m_linePSSLXR->setText("");
    ui->m_linePSSDH->setText("");
    ui->m_linePSSEMAIL->setText("");
    ui->m_linePSSDZ->setText("");
    ui->m_linePSSYB->setText("");
}

/**
 * @brief 双击对表格中的信息进行编辑
 * @param item 选中的行
 */
void CWidgetDistributor::on_m_tblwPSSLB_itemDoubleClicked(QTableWidgetItem *item)
{
    //显示更新按钮，隐藏添加按钮
    ui->m_btnPSSTJ->hide();
    ui->m_btnPSSGX->show();
    //将信息显示在界面控件中
    ui->m_linePSSMC->setEnabled(1);
    m_nCurRecordID = ui->m_tblwPSSLB->item(item->row(), 0)->text().toInt();
    ui->m_linePSSMC->setText(ui->m_tblwPSSLB->item(item->row(), 1)->text());
    ui->m_linePSSLXR->setText(ui->m_tblwPSSLB->item(item->row(), 2)->text());
    ui->m_linePSSDH->setText(ui->m_tblwPSSLB->item(item->row(), 3)->text());
    ui->m_linePSSEMAIL->setText(ui->m_tblwPSSLB->item(item->row(), 4)->text());
    ui->m_linePSSDZ->setText(ui->m_tblwPSSLB->item(item->row(), 5)->text());
    ui->m_linePSSYB->setText(ui->m_tblwPSSLB->item(item->row(), 6)->text());
}

/**
 * @brief 更新
 */
void CWidgetDistributor::on_m_btnPSSGX_clicked()
{
    //判断必要信息是否漏填
    if(ui->m_linePSSMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写配送商名称！", QMessageBox::Ok);
        return;
    }
    if(ui->m_linePSSLXR->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写联系人！", QMessageBox::Ok);
        return;
    }
    if(ui->m_linePSSDH->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请填写电话！", QMessageBox::Ok);
        return;
    }
    //更新信息至数据库
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("update Manufacturer_T set ManuName='" + ui->m_linePSSMC->text() + "',LineMan='" + ui->m_linePSSLXR->text() + "',Phone='" + ui->m_linePSSDH->text() +
                 "',email='" + ui->m_linePSSEMAIL->text() + "',Address='" + ui->m_linePSSDZ->text() + "',Zip='" + ui->m_linePSSYB->text() + "' where ManuID=" + QString::number(m_nCurRecordID));
    ui->m_tblwPSSLB->clearContents();
    //显示更新的信息
    ShowInfoAtTable("select ManuID,ManuName,LineMan,Phone,email,Address,Zip from Manufacturer_T where ManuID=" + QString::number(m_nCurRecordID) + " order by ManuID");
    //初始化控件
    ui->m_linePSSCX->setText("");
    ui->m_linePSSMC->setText("");
    ui->m_linePSSLXR->setText("");
    ui->m_linePSSDH->setText("");
    ui->m_linePSSEMAIL->setText("");
    ui->m_linePSSDZ->setText("");
    ui->m_linePSSYB->setText("");
    ui->m_btnPSSTJ->show();
    ui->m_btnPSSGX->hide();
    //解锁配送商名称
    ui->m_linePSSMC->setEnabled(1);
}

/**
 * @brief 配送商名称完成编辑时
 */
void CWidgetDistributor::on_m_linePSSMC_editingFinished()
{
    //判断库中是否已有该配送商，没有则添加，有则更新
    QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
    sqlDfy->exec("select ManuID,ManuName,LineMan,Phone,email,Address,Zip from Manufacturer_T where ManuName='" + ui->m_linePSSMC->text() + "' order by ManuID");
    if(sqlDfy->last())
    {
        QMessageBox::warning(NULL, "警告", "此配送商已存在，其信息已显示在各个输入框中,请更新!", QMessageBox::Ok);
        m_nCurRecordID = sqlDfy->value(0).toInt();
        ui->m_linePSSLXR->setText(sqlDfy->value(2).toString());
        ui->m_linePSSDH->setText(sqlDfy->value(3).toString());
        ui->m_linePSSEMAIL->setText(sqlDfy->value(4).toString());
        ui->m_linePSSDZ->setText(sqlDfy->value(5).toString());
        ui->m_linePSSYB->setText(sqlDfy->value(6).toString());
        ui->m_btnPSSGX->show();
        ui->m_btnPSSTJ->hide();
        //锁定配送商名称
        ui->m_linePSSMC->setEnabled(0);
    }
}

/**
 * @brief 删除
 */
void CWidgetDistributor::on_m_btnPSSSC_clicked()
{
    if(ui->m_tblwPSSLB->selectedItems().count())
    {
        QSqlQuery* sqlDfy = new QSqlQuery(SQLDB::GetDfytCathLab());
        //获取选中项的ID
        int nCurSelectedID = ui->m_tblwPSSLB->item(ui->m_tblwPSSLB->selectedItems()[0]->row(), 0)->text().toInt();
        int bResult = QMessageBox::question(NULL, "提示", "确认删除吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(QMessageBox::Yes == bResult)
        {
            sqlDfy->exec("delete Manufacturer_T where ManuID=" + QString::number(nCurSelectedID));
        }
        ShowInfoAtTable("select ManuID,ManuName,LineMan,Phone,email,Address,Zip from Manufacturer_T order by ManuID");
    }
}
