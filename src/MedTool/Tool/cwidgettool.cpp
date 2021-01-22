#include "cwidgettool.h"
#include "ui_cwidgettool.h"


CWidgetTool::CWidgetTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetTool)
{
    ui->setupUi(this);
    //设置表格不可编辑
    ui->m_tblwKCLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwCKLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwRKLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwRKKCLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwCXTJCK->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwCXTJKC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwCXTJRK->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwCXTJYXQ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblwQPKCLB->setEditTriggers(QAbstractItemView::NoEditTriggers);    
    //设置表格单击选择整行
    ui->m_tblwKCLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwKCLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblwCKLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwCKLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblwRKLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwRKLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblwRKKCLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwRKKCLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblwQPKCLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwQPKCLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表头最后一项对齐格式
    ui->m_tblwRKKCLB->horizontalHeaderItem(ui->m_tblwRKKCLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwKCLB->horizontalHeaderItem(ui->m_tblwKCLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwRKLB->horizontalHeaderItem(ui->m_tblwRKLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwCKLB->horizontalHeaderItem(ui->m_tblwCKLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwCXTJCK->horizontalHeaderItem(ui->m_tblwCXTJCK->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwCXTJKC->horizontalHeaderItem(ui->m_tblwCXTJKC->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwCXTJRK->horizontalHeaderItem(ui->m_tblwCXTJRK->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwCXTJYXQ->horizontalHeaderItem(ui->m_tblwCXTJYXQ->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    ui->m_tblwQPKCLB->horizontalHeaderItem(ui->m_tblwQPKCLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    //初始化变量
    m_sCurSelectedRecordRK = "";
    m_sCurSelectedRecordCK = "";
    m_sDateSelectWay = "";
    m_nCurBarQCTJ = 0;
    ui->m_dtmCKRQ->setDateTime(QDateTime::currentDateTime());
    ui->m_dtmRKRQ->setDateTime(QDateTime::currentDateTime());
    ui->m_dtmRKYXQ->setDateTime(QDateTime::currentDateTime());
    ui->m_dtJZSJ->setDate(QDate::currentDate());
    m_nIsNewQX = 0;
    m_nQPQCTMFlag = 0;
    m_nCurBarQCTJ = 0;
    int nCurBarIndex;
    nCurBarIndex = ui->m_tbwCXTJ->currentIndex();
    if(nCurBarIndex == 0 || nCurBarIndex == 3)
        ui->m_grpKJCX->setEnabled(0);
    else
        ui->m_grpKJCX->setEnabled(1);
    ui->m_btnQPGX->hide();
    //设置出库信息控件不可编辑
    ui->m_lineQCMC->setEnabled(0);
    ui->m_lineLOT->setEnabled(0);
    ui->m_lineQCTM->setEnabled(0);    
    ui->m_linePSS->setEnabled(0);
    ui->m_lineCKJG->setEnabled(0);
    ui->m_lineRKQCTM->setEnabled(0);
    ui->m_lineRKQCMC->setEnabled(0);
    ui->m_lineRKJG->setEnabled(0);
    ui->m_lineQPSBTM->setEnabled(0);
    ui->m_btnTJXQX->hide();
    /******** 初始化器材树表 ********/
    QSqlQuery* sqlStorge = new QSqlQuery(SQLDB::GetCathLabStock());
    QString sSqlPciQC="select Tv_Name,Tv_Parent from ToolTree_T";
    sqlStorge->exec(sSqlPciQC);
    while (sqlStorge->next())
    {
        QString sAnsName=sqlStorge->value(0).toString();
        int nAnsParent=sqlStorge->value(1).toInt();
        STreeNode sNode={sAnsName,nAnsParent};
        m_vNameTool.push_back(sNode);
    }
    QStringList sHeaderQC;
    sHeaderQC.append("器材类别名称");
    m_modelQC= new QStandardItemModel();
    m_modelQC->setHorizontalHeaderLabels(sHeaderQC);
    //载入模型
    ui->m_treevQPQC->setModel(m_modelQC);
    ui->m_treevQPQC->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_treevQPQC->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_treevQPQC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_treevQPQC->show();
    // 初始化器材
    this->InitTreeView(ui->m_treevQPQC);
    //设置价格输入框只能输入数字
    ui->m_lineQPJG->setValidator(new QDoubleValidator(0, 999999999, 2));
    ui->m_lineQPBJZ->setValidator(new QIntValidator(0, 999999999));
//    //恢复库存
//    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
//    sqlStorage->exec("update Warehouse_T set WH_RestNum=10");
//    qDebug() << "恢复成功";
}

CWidgetTool::~CWidgetTool()
{
    delete ui;
}

/********* 器材出库 *********/
/**
 * @brief 单击查询按钮，显示查询结果
 */
void CWidgetTool::on_m_btnCX_clicked()
{
    ui->m_tblwKCLB->clearContents();
    /********* 获取查询方式与查询关键字 *********/
    QString lSearchWay;
    QString sSearchWay = "条形码";
    QString sSearchKey = "";
    QStringList lRecord;
    sSearchWay = ui->m_cmbCXF->currentText();
    sSearchKey = ui->m_lineCXM->text();
    if(sSearchWay == "条形码")
        sSearchWay = "BarCd_Parse";
    else
    {
        if(sSearchWay == "助记符")
            sSearchWay = "HelpSign";
    }
    /********* 根据条件查询数据库中的库存信息 *********/
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    if(sSearchKey == "")
        sqlStorage->exec("select Full_Name,LotCode,BarCd_Parse,HelpSign,WH_RestNum,Unit,WH_Price,Provider from V_Query_WH");
    else
    {
        sqlStorage->exec("select Full_Name,LotCode,BarCd_Parse,HelpSign,WH_RestNum,Unit,WH_Price,Provider from V_Query_WH where " + sSearchWay + "='" + sSearchKey +"'");
    }
    QString sOneRecord = "";
    while(sqlStorage->next())
    {
        for(int i = 0;i < 8;i++)
        {
            sOneRecord += sqlStorage->value(i).toString() + "///";
        }
//        //测试，查询
//        qDebug() << "查询：";
//        qDebug() << sOneRecord;
        if(sOneRecord.split("///")[4] != "0")
            lRecord.append(sOneRecord.left(sOneRecord.length() - 3));
        sOneRecord = "";
    }

    /********* 将数据库中的库存信息显示出来 *********/
    int nRow = 0;
    int nColumn = 0;
    QStringList lTemp;
    ui->m_tblwKCLB->setRowCount(0);
    ui->m_tblwKCLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lRecord)
    {
        ui->m_tblwKCLB->setRowCount(ui->m_tblwKCLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            ui->m_tblwKCLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            ui->m_tblwKCLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //可视化管线更新
    ui->m_tblwKCLB->viewport()->update();
}

/**
 * @brief 双击库存列表中某行，将其值填入对应控件。
 * @param item 被双击的单元格
 */
void CWidgetTool::on_m_tblwKCLB_itemDoubleClicked(QTableWidgetItem *item)
{
    /********* 将当前选中行的信息添加至控件 *********/
    m_sCurSelectedRecordCK = "";
    int nCurRow = item->row();
    ui->m_lineQCTM->setText(ui->m_tblwKCLB->item(nCurRow, 2)->text());
    ui->m_lineLOT->setText(ui->m_tblwKCLB->item(nCurRow, 1)->text());
    ui->m_lineQCMC->setText(ui->m_tblwKCLB->item(nCurRow, 0)->text());
    ui->m_spbCKSL->setValue(1);
    ui->m_lineCKJG->setText(ui->m_tblwKCLB->item(nCurRow, 6)->text());
    ui->m_linePSS->setText(ui->m_tblwKCLB->item(nCurRow, 7)->text());
    ui->m_dtmCKRQ->setDateTime(QDateTime::currentDateTime());
    /********* 并将其加入缓存变量 *********/
    for(int i = 0;i < 8;i++)
        m_sCurSelectedRecordCK += ui->m_tblwKCLB->item(nCurRow, i)->text() + "///";
    m_sCurSelectedRecordCK = m_sCurSelectedRecordCK.left(m_sCurSelectedRecordCK.length() - 3);
}

/**
 * @brief 将控件中显示的出库信息添加进出库列表中
 */
void CWidgetTool::on_m_btnTJ_clicked()
{
    if(m_sCurSelectedRecordCK == "")
        return;
    //如果出库数量大于库存数量则报错
    if(m_sCurSelectedRecordCK.split("///").at(4).toInt() < ui->m_spbCKSL->value())
    {
        QMessageBox::warning(NULL, "warning", "出库数量应小于库存数量！", QMessageBox::Ok);
        return;
    }
    //将可变控件的内容添加进缓存
    int nCurFields = m_sCurSelectedRecordCK.split("///").length();
    if(nCurFields <= 8)
    {
        m_sCurSelectedRecordCK += "///" + ui->m_cmbCKLX->currentText() + "///";
        m_sCurSelectedRecordCK += ui->m_dtmCKRQ->text() + "///";
        m_sCurSelectedRecordCK += ui->m_spbCKSL->text();
    }
    //m_sCurSelectedRecordCK中存储信息的顺序：
    //器材名称、器材批次、条形码、助记符、单批剩余、单位、出库价格、配送商、出库类型、出库日期、出库数量
    //Full_Name,LotCode,BarCd_Parse,HelpSign,WH_RestNum,Unit,WH_Price,Provider,UH_Type,UH_Date,UH_Num
    m_lCXLBCK.append(m_sCurSelectedRecordCK);
    //m_sCurSelectedRecord = "";
    ui->m_tblwCKLB->setRowCount(ui->m_tblwCKLB->rowCount() + 1);
    int nRow = ui->m_tblwCKLB->rowCount() - 1;
    ui->m_tblwCKLB->setItem(nRow, 0, new QTableWidgetItem(ui->m_lineQCMC->text()));
    ui->m_tblwCKLB->setItem(nRow, 1, new QTableWidgetItem(ui->m_lineQCTM->text()));
    ui->m_tblwCKLB->setItem(nRow, 2, new QTableWidgetItem(ui->m_lineLOT->text()));
    ui->m_tblwCKLB->setItem(nRow, 3, new QTableWidgetItem(ui->m_spbCKSL->text()));
    ui->m_tblwCKLB->setItem(nRow, 4, new QTableWidgetItem(ui->m_dtmCKRQ->text()));
    ui->m_tblwCKLB->setItem(nRow, 5, new QTableWidgetItem(ui->m_cmbCKLX->currentText()));
    ui->m_tblwCKLB->setItem(nRow, 6, new QTableWidgetItem(ui->m_lineCKJG->text()));
    ui->m_tblwCKLB->setItem(nRow, 7, new QTableWidgetItem(ui->m_linePSS->text()));
    ui->m_tblwCKLB->viewport()->update();
    //设置列宽自适应
    ui->m_tblwCKLB->horizontalHeader()->setStretchLastSection(true);
    for(int i = 0;i < ui->m_tblwCKLB->columnCount() - 1;i++)
        ui->m_tblwCKLB->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    //测试，添加
    qDebug() << "添加" << m_lCXLBCK.count();
    foreach(QString str, m_lCXLBCK)
    {
        qDebug() << str;
    }
}

/**
 * @brief 完成出库操作，将出库信息更新至数据库
 */
void CWidgetTool::on_m_btnCK_clicked()
{
    //出库失败的条数、出库成功的条数
    int nFailureCount = 0;
    int nSuccessCount = 0;
    if(!(m_lCXLBCK.length()))
            return;
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    int nCurStockRest = 0;
    QStringList lCurRecord;
    QString sBarCodeID;
    for(int i = 0;i < m_lCXLBCK.length();i++)
    {
        lCurRecord = m_lCXLBCK.at(i).split("///");
        //如果库存为零，则出库失败；如果出库数量大于库存数量则出库失败
        sqlStorage->exec("select WH_RestNum from V_Query_WH where BarCd_Parse='" + lCurRecord.at(2) + "'and LotCode='" + lCurRecord.at(1) + "'");
        while(sqlStorage->next())
            nCurStockRest = sqlStorage->value(0).toInt();
        if(!nCurStockRest || nCurStockRest < lCurRecord.at(10).toInt())
        {
            nFailureCount++;
            continue;
        }
        //根据BarCd_Parse查询BarCode_ID
        sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + lCurRecord.at(2) + "'");
        while(sqlStorage->next())
            sBarCodeID = sqlStorage->value(0).toString();
        //将出库信息更新至数据库
        sqlStorage->exec("update V_Query_WH set WH_RestNum=" + QString::number(nCurStockRest - lCurRecord.at(10).toInt()) + "where BarCd_Parse='" + lCurRecord.at(2) + "'and LotCode='" + lCurRecord.at(1) + "'");
        sqlStorage->exec("insert into Unhouse_T(LotCode,BarCode_ID,UH_Price,UH_Type,UH_Date,UH_Num) values('"
                         + lCurRecord.at(1)
                         + "'," + sBarCodeID
                         + "," + lCurRecord.at(6)
                         + ",'" + lCurRecord.at(8)
                         + "','" + lCurRecord.at(9)
                         + "'," + lCurRecord.at(10) + ")");
        nSuccessCount++;
//        qDebug() << "insert into Unhouse_T(LotCode,BarCode_ID,UH_Price,UH_Type,UH_Date,UH_Num) values('"
//                    + lCurRecord.at(1)
//                    + "'," + sBarCodeID
//                    + "," + lCurRecord.at(6)
//                    + ",'" + lCurRecord.at(8)
//                    + "','" + lCurRecord.at(9)
//                    + "',1)";

    }
    if(nFailureCount)
        QMessageBox::warning(NULL, "出库失败条数统计", "出库成功条数:" + QString::number(nSuccessCount) + ",出库失败条数:" + QString::number(nFailureCount), QMessageBox::Ok);
    //清空缓存区
    ui->m_tblwCKLB->clearContents();
    m_lCXLBCK.clear();
//    //测试，出库是否成功
//    qDebug() << "测试，出库是否成功";
//    sqlStorage->exec("select UH_Date from Unhouse_T");
//    while(sqlStorage->next())
//    {
//        qDebug() << sqlStorage->value(0).toString();
//    }
    //更新查询列表
    on_m_btnCX_clicked();
    ui->m_tblwCKLB->setRowCount(0);
}

/**
 * @brief 双击删除出库列表中的项
 * @param item 被双击的单元格
 */
void CWidgetTool::on_m_tblwCKLB_itemDoubleClicked(QTableWidgetItem *item)
{
    m_lCXLBCK.removeAt(item->row());
    ui->m_tblwCKLB->removeRow(item->row());
//    //测试，删除
//    qDebug() << "删除";
//    foreach(QString str, m_lCXLBCK)
//    {
//        qDebug() << str;
//    }
}


/********* 器材入库 *********/
/**
 * @brief 入库界面的库存查询
 */
void CWidgetTool::on_m_btnRKCX_clicked()
{
    /********* 获取查询方式与查询关键字 *********/
    int nRecordCount = 0;
    QString sSearchKey = "";
    QStringList lRecord;
    sSearchKey = ui->m_lineKJTM->text();
    /********* 根据条件查询数据库中的库存信息 *********/
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    if(sSearchKey == "")
        sqlStorage->exec("select Full_Name,BarCd_Parse,LotCode,WH_RestNum,WH_Date,Valid_Date,WH_Type,WH_Price from V_Query_WH");
    else
    {
        sqlStorage->exec("select Full_Name,BarCd_Parse,LotCode,WH_RestNum,WH_Date,Valid_Date,WH_Type,WH_Price from V_Query_WH where BarCd_Parse='" + sSearchKey +"'");       
    }
    QString sOneRecord = "";
    while(sqlStorage->next())
    {
        for(int i = 0;i < 8;i++)
        {
            sOneRecord += sqlStorage->value(i).toString() + "///";
        }
//        //测试，查询
//        qDebug() << "查询：";
//        qDebug() << sOneRecord;
        lRecord.append(sOneRecord.left(sOneRecord.length() - 3));
        sOneRecord = "";
        nRecordCount++;
    }
    if(!nRecordCount)
    {
        QString sBarCdID = "";
        ui->m_lineRKQCTM->setText("");
        ui->m_lineRKQCMC->setText("");
        ui->m_lineRKJG->setText("");
        sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineKJTM->text() + "'");
        while(sqlStorage->next())
        {
            sBarCdID = sqlStorage->value(0).toString();
        }
        sqlStorage->exec("select Full_Name,DefaultPrice from StockIndex_T where BarCode_ID=" + sBarCdID);
        while(sqlStorage->next())
        {
            ui->m_lineRKQCTM->setText(sSearchKey);
            ui->m_lineRKQCMC->setText(sqlStorage->value(0).toString());
            ui->m_lineRKJG->setText(sqlStorage->value(1).toString());
        }
        m_sCurSelectedRecordRK = "///";
        ui->m_tblwRKKCLB->clearContents();
        ui->m_tblwRKKCLB->setRowCount(0);
        return;
    }
    /********* 将数据库中的库存信息显示出来 *********/
    int nRow = 0;
    int nColumn = 0;
    QStringList lTemp;
    ui->m_tblwRKKCLB->setRowCount(0);
    ui->m_tblwRKKCLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lRecord)
    {
        ui->m_tblwRKKCLB->setRowCount(ui->m_tblwRKKCLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            ui->m_tblwRKKCLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            ui->m_tblwRKKCLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //可视化管线更新
    ui->m_tblwRKKCLB->viewport()->update();
}

/**
 * @brief 将库存列表中的选中项的信息放入各个控件中
 * @param item 选中的项
 */
void CWidgetTool::on_m_tblwRKKCLB_itemDoubleClicked(QTableWidgetItem *item)
{
    /********* 将当前选中行的信息添加至控件 *********/
    m_sCurSelectedRecordRK = "";
    int nCurRow = item->row();
    ui->m_lineRKQCTM->setText(ui->m_tblwRKKCLB->item(nCurRow, 1)->text());
    ui->m_lineRKLOT->setText(ui->m_tblwRKKCLB->item(nCurRow, 2)->text());
    ui->m_lineRKQCMC->setText(ui->m_tblwRKKCLB->item(nCurRow, 0)->text());
    ui->m_lineRKJG->setText(ui->m_tblwRKKCLB->item(nCurRow, 7)->text());
    ui->m_cmbRKLX->setCurrentText(ui->m_tblwRKKCLB->item(nCurRow, 6)->text());
    ui->m_dtmRKRQ->setDateTime(QDateTime::currentDateTime());
    ui->m_dtmRKYXQ->setDateTime(QDateTime::currentDateTime());
    /********* 写入字符到当前选中项缓存，以判断当前是否有选中项 *********/
    m_sCurSelectedRecordRK = "///";

    //改变控件的可编辑性
    ui->m_lineRKQCTM->setEnabled(0);
    ui->m_lineRKQCMC->setEnabled(0);
    ui->m_lineRKJG->setEnabled(0);
}

/**
 * @brief 入库器材条码输入完毕
 */
void CWidgetTool::on_m_lineRKQCTM_editingFinished()
{
    QString sBarCdID;
    QString sFullName;
    QString sPrice;
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineRKQCTM->text() + "'");
    while(sqlStorage->next())
        sBarCdID = sqlStorage->value(0).toString();
    sqlStorage->exec("select Full_Name,DefaultPrice from StockIndex_T where BarCode_ID='" + sBarCdID + "'");
    while(sqlStorage->next())
    {
        sFullName = sqlStorage->value(0).toString();
        sPrice = sqlStorage->value(1).toString();
    }
    ui->m_lineRKQCMC->setText(sFullName);
    ui->m_lineRKJG->setText(sPrice);
}

/**
 * @brief 将控件中的信息添加到待入库列表中
 */
void CWidgetTool::on_m_btnRKTJ_clicked()
{
    /********* 判断将要添加进待入库列表的信息是否合法 *********/
    //添加方式，‘new’为新器械，‘//’为库存中已有的器械
    QString sAddWay = "///";
    //m_sCurSelectedRecordRK = "///",该表达式用于允许执行添加操作
    //判断空操作
    if(m_sCurSelectedRecordRK == "")
        return;
    if(m_sCurSelectedRecordRK == "new")
    {
        m_nIsNewQX = 1;
        sAddWay = "new";
    }
    m_sCurSelectedRecordRK = "";
    //判断漏填操作
    if(ui->m_spbRKSL->text() == "0")
    {
        QMessageBox::warning(NULL, "warning", "入库数量应大于0！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    if(ui->m_lineRKQCTM->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "器械条码没有填写！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    if(ui->m_lineRKQCMC->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "器械名称没有填写！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    if(ui->m_dtmRKYXQ->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "有效期没有填写！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    if(ui->m_lineRKJG->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "入库价格没有填写！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    if(ui->m_lineRKLOT->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "LOT号没有填写！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    //判断是否包含非法字符
    if(ui->m_lineRKQCTM->text().contains("///")
            || ui->m_lineRKQCMC->text().contains("///")
            || ui->m_lineRKLOT->text().contains("///")
            || ui->m_lineRKJG->text().contains("///")
            )
    {
        QMessageBox::warning(NULL, "warning", "信息中不能包含'///'！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    //判断有效期是否大于入库时间
    int nYearYXQ;
    int nMouthYXQ;
    int nDayYXQ;
    int nYearRKRQ;
    int nMouthRKRQ;
    int nDayRKRQ;
    nYearYXQ = ui->m_dtmRKYXQ->text().split("-")[0].toInt();;
    nMouthYXQ = ui->m_dtmRKYXQ->text().split("-")[1].toInt();
    nDayYXQ = ui->m_dtmRKYXQ->text().split("-")[2].split("T")[0].toInt();
    nYearRKRQ = ui->m_dtmRKRQ->text().split("-")[0].toInt();
    nMouthRKRQ = ui->m_dtmRKRQ->text().split("-")[1].toInt();
    nDayRKRQ = ui->m_dtmRKRQ->text().split("-")[2].split("T")[0].toInt();
//    qDebug() << nYearYXQ << " " << nMouthYXQ << " " << nDayYXQ;
//    qDebug() << nYearRKRQ << " " << nMouthRKRQ << " " << nDayRKRQ;
    if(nYearYXQ < nYearRKRQ )
    {
        QMessageBox::warning(NULL, "warning", "有效期应大于入库日期！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }

    if(nYearYXQ == nYearRKRQ && nMouthYXQ < nMouthRKRQ)
    {
        QMessageBox::warning(NULL, "warning", "有效期应大于入库日期！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }

    if(nMouthYXQ == nMouthRKRQ && nDayYXQ < nDayRKRQ)
    {
        QMessageBox::warning(NULL, "warning", "有效期应大于入库日期！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }

//    //新品判断条形码是否存在,非新品判断批次号是否存在
//    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
//    QStringList lBarCdParse;
//    QStringList lLotCode;
//    QString sBarCdID;
//    if(m_nIsNewQX)
//    {
//        sqlStorage->exec("select BarCd_Parse from BarCdManage_T");
//        while(sqlStorage->next())
//        {
//            lBarCdParse.append(sqlStorage->value(0).toString());
//        }
//        if(!lBarCdParse.contains(ui->m_lineRKQCTM->text()))
//        {
//            QMessageBox::warning(NULL, "warning", "该器材未配置，请配置后再进行入库操作！", QMessageBox::Ok);
//            m_sCurSelectedRecordRK = sAddWay;
//            return;
//        }
//        m_nIsNewQX = 0;
//    }
//    //批次号重复的判断
//    else
//    {
//        sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineRKQCTM->text() + "'");
//        while(sqlStorage->next())
//        {
//            sBarCdID = sqlStorage->value(0).toString();
//        }
//        sqlStorage->exec("select LotCode from Warehouse_T where BarCode_ID=" + sBarCdID);
//        while(sqlStorage->next())
//        {
//            lLotCode.append(sqlStorage->value(0).toString());
//        }
//        if(lLotCode.contains(ui->m_lineRKLOT->text()))
//        {
//            QMessageBox::warning(NULL, "warning", "该Lot号已存在！", QMessageBox::Ok);
//            m_sCurSelectedRecordRK = sAddWay;
//            return;
//        }
//    }

    //判断在该器材中，当前批次号是否存在
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    QString sBarCodeID = "";
    //根据BarCd_Parse查询BarCode_ID
    sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineRKQCTM->text() + "'");
    while(sqlStorage->next())
        sBarCodeID = sqlStorage->value(0).toString();
    sqlStorage->exec("select * from Warehouse_T where BarCode_ID=" + sBarCodeID + " and LotCode='" + ui->m_lineRKLOT->text() + "'");
    if(sqlStorage->last())
    {
        QMessageBox::warning(NULL, "warning", "在该器材的记录中该批次号已存在，请更换批次号！", QMessageBox::Ok);
        m_sCurSelectedRecordRK = sAddWay;
        return;
    }
    /********* 将控件信息添加进待入库列表 *********/
    //将可变控件的内容添加进缓存
    m_sCurSelectedRecordRK += ui->m_lineRKQCMC->text() + "///";
    m_sCurSelectedRecordRK += ui->m_lineRKQCTM->text() + "///";
    m_sCurSelectedRecordRK += ui->m_lineRKLOT->text() + "///";
    m_sCurSelectedRecordRK += ui->m_spbRKSL->text() + "///";
    m_sCurSelectedRecordRK += ui->m_dtmRKRQ->text() + "///";
    m_sCurSelectedRecordRK += ui->m_dtmRKYXQ->text() + "///";
    m_sCurSelectedRecordRK += ui->m_cmbRKLX->currentText() + "///";
    m_sCurSelectedRecordRK += ui->m_lineRKJG->text() + "///";
    //m_sCurSelectedRecordRK中存储信息的顺序：
    //器材名称、条形码、LOT号、数量、入库日期、有效期、入库类型、入库价格
    //Full_Name,BarCd_Parse,LotCode,WH_Num,WH_Date,Valid_Date,WH_Type,WH_Price
    m_lCXLBRK.append(m_sCurSelectedRecordRK);
    //m_sCurSelectedRecordRK = "";
    ui->m_tblwRKLB->setRowCount(ui->m_tblwRKLB->rowCount() + 1);
    int nRow = ui->m_tblwRKLB->rowCount() - 1;
    //ui->m_tblwRKLB->setItem(nRow, 0, new QTableWidgetItem(QString::number(ui->m_tblwRKLB->rowCount())));
    QStringList lTemp;
    lTemp = m_sCurSelectedRecordRK.split("///");
    for(int i = 0;i < 8;i++)
        ui->m_tblwRKLB->setItem(nRow, i, new QTableWidgetItem(lTemp.at(i)));
    ui->m_tblwRKLB->viewport()->update();
    //设置列宽自适应
    ui->m_tblwRKLB->horizontalHeader()->setStretchLastSection(true);
    for(int i = 0;i < ui->m_tblwRKLB->columnCount() - 1;i++)
        ui->m_tblwRKLB->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
//    //测试，添加
//    qDebug() << "添加" << m_lCXLBRK.count();
//    foreach(QString str, m_lCXLBRK)
//    {
//        qDebug() << str;
//    }
}

/**
 * @brief 将各个控件复位到初始值
 */
void CWidgetTool::on_m_btnRKFW_clicked()
{
    ui->m_lineRKQCTM->setText("");
    ui->m_lineRKLOT->setText("");
    ui->m_lineRKQCMC->setText("");
    ui->m_spbRKSL->setValue(0);
    ui->m_lineRKJG->setText("");
    ui->m_cmbRKLX->setCurrentIndex(0);
    ui->m_dtmRKRQ->setDateTime(QDateTime::currentDateTime());
    ui->m_dtmRKYXQ->setDateTime(QDateTime::currentDateTime());
    m_sCurSelectedRecordRK = "";
    ui->m_lineRKQCTM->setEnabled(0);
    ui->m_lineRKQCMC->setEnabled(0);
    ui->m_lineRKJG->setEnabled(0);
}

/**
 * @brief 删除待入库列表中的项
 * @param item 将要删除的项
 */
void CWidgetTool::on_m_tblwRKLB_itemDoubleClicked(QTableWidgetItem *item)
{
    m_lCXLBRK.removeAt(item->row());
    ui->m_tblwRKLB->removeRow(item->row());
//    //测试，删除
//    qDebug() << "删除";
//    foreach(QString str, m_lCXLBRK)
//    {
//        qDebug() << str;
//    }
}

/**
 * @brief 添加新器械
 */
void CWidgetTool::on_m_btnTJXQX_clicked()
{
    //初始化器械信息
    ui->m_lineRKQCTM->setText("");
    ui->m_lineRKLOT->setText("");
    ui->m_lineRKQCMC->setText("");
    ui->m_spbRKSL->setValue(0);
    ui->m_lineRKJG->setText("");
    ui->m_cmbRKLX->setCurrentIndex(0);
    ui->m_dtmRKRQ->setDateTime(QDateTime::currentDateTime());
    ui->m_dtmRKYXQ->setDateTime(QDateTime::currentDateTime());
    m_sCurSelectedRecordRK = "new";
    ui->m_lineRKQCTM->setEnabled(1);
    ui->m_lineRKQCMC->setEnabled(1);
    ui->m_lineRKJG->setEnabled(1);
    ui->m_lineRKQCTM->setFocus();
    ui->m_lineRKQCMC->setEnabled(0);
}

/**
 * @brief 入库
 */
void CWidgetTool::on_m_btnRKRK_clicked()
{
    if(!(m_lCXLBRK.length()))
            return;
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    QStringList lCurRecord;
    QString sBarCodeID = "";
    for(int i = 0;i < m_lCXLBRK.length();i++)
    {
        lCurRecord = m_lCXLBRK.at(i).split("///");       
        //根据BarCd_Parse查询BarCode_ID
        sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + lCurRecord.at(1) + "'");
        while(sqlStorage->next())
            sBarCodeID = sqlStorage->value(0).toString();
        //将入库信息更新至Warehouse_T
        sqlStorage->exec("insert into Warehouse_T(BarCode_ID,LotCode,WH_Num,WH_Date,Valid_Date,WH_Type,WH_Price,BarCode_Original,WH_RestNum) values("
                         + sBarCodeID
                         + ",'" + lCurRecord.at(2)
                         +"'," + lCurRecord.at(3)
                         +",'" + lCurRecord.at(4)
                         + "','" + lCurRecord.at(5)
                         + "','" + lCurRecord.at(6)
                         + "'," + lCurRecord.at(7)
                         + ",'" + lCurRecord.at(1) + lCurRecord.at(2)
                         + "'," + lCurRecord.at(3) + ")");
        //将入库信息更新至StockInfo_T
        //根据BarCode_ID查询StockInfo_T的ID
        QString sStockInfoID = "";
        int nStockNum = 0;
        int nStcokInfoCount = 0;
        sqlStorage->exec("select ID,Stock_Num from StockInfo_T where BarCode_ID=" + sBarCodeID);
        while(sqlStorage->next())
        {
             sStockInfoID = sqlStorage->value(0).toString();
             nStockNum = sqlStorage->value(1).toInt();
             nStcokInfoCount++;
        }
        if(nStcokInfoCount)
        {
            nStockNum += ui->m_spbRKSL->text().toInt();
            sqlStorage->exec("update StockInfo_T set Stock_Num=" + QString::number(nStockNum));
        }
        else
        {
            nStockNum = ui->m_spbRKSL->text().toInt();
            sqlStorage->exec("insert into StockInfo_T(BarCode_ID,Stock_Num) values(" + sBarCodeID + "," + QString::number(nStockNum) + ")");

        }
        //测试，StockInfo_T
        sqlStorage->exec("select * from StockInfo_T where BarCode_ID=" + sBarCodeID);
        while(sqlStorage->next())
        {
             qDebug() << sqlStorage->value(0).toString() << "  "
                      << sqlStorage->value(1).toString() << "  "
                      << sqlStorage->value(2).toString();
        }
//        qDebug() << "insert into Warehouse_T(BarCode_ID,LotCode,WH_Num,WH_Date,Valid_Date,WH_Type,WH_Price,BarCode_Original,WH_RestNum) values("
//                    + sBarCodeID
//                    + ",'" + lCurRecord.at(2)
//                    +"'," + lCurRecord.at(3)
//                    +",'" + lCurRecord.at(4)
//                    + "','" + lCurRecord.at(5)
//                    + "','" + lCurRecord.at(6)
//                    + "'," + lCurRecord.at(7)
//                    + ",'" + lCurRecord.at(1) + lCurRecord.at(2)
//                    + "'," +  + ")";

    }
    //清空缓存区
    ui->m_tblwRKLB->clearContents();
    m_lCXLBRK.clear();
//    //测试，入库是否成功
//    qDebug() << "测试，出库是否成功";
//    sqlStorage->exec("select WH_Date from Warehouse_T");
//    while(sqlStorage->next())
//    {
//        qDebug() << sqlStorage->value(0).toString();
//    }
    //更新查询列表
    on_m_btnRKCX_clicked();
    ui->m_tblwRKLB->setRowCount(0);
}

/********* 器材查询统计 *********/
/**
 * @brief 单击器械查询统计选项卡
 * @param 选项卡索引号
 */
void CWidgetTool::on_m_tbwCXTJ_tabBarClicked(int index)
{
    m_nCurBarQCTJ = index;
    ui->m_lineCXTJCXM->setText("");
    ui->m_lineCXTJPSS->setText("");
    ui->m_ckbSJDCX->setChecked(0);
    if(index == 0 || index == 3)
    {
        ui->m_grpKJCX->setEnabled(0);
        ui->m_ckbSJDCX->setChecked(0);
    }
    else
        ui->m_grpKJCX->setEnabled(1);  
}

/**
 * @brief 器械查询
 */
void CWidgetTool::on_m_btnCXTJCX_clicked()
{
    /********* 判断查询条件 *********/
    //lCondition,记录查询条件
    QStringList lCondition;
    //如果是有条件查询，则在条件字符串中添加where
    QString sConditions = "";
    if(ui->m_lineCXTJCXM->text() != "")
    {
        if(ui->m_cmbCXTJCXF->currentText() == "条形码")
            lCondition.append(" BarCd_Parse='" + ui->m_lineCXTJCXM->text() + "'");
        if(ui->m_cmbCXTJCXF->currentText() == "助记符")
            lCondition.append(" HelpSign='" + ui->m_lineCXTJCXM->text() + "'");
        sConditions = " where";
    }
    if(ui->m_lineCXTJPSS->text() != "")
    {
        lCondition.append(" Provider='" + ui->m_lineCXTJPSS->text() + "'");
        sConditions = " where";
    }
    if(ui->m_ckbSJDCX->isChecked())
    {
        if(m_nCurBarQCTJ == 1)
            lCondition.append(" UH_Date>='" + ui->m_dtQSSJ->text() + "' and " + "UH_Date<='" + ui->m_dtJZSJ->text() + "'");
        if(m_nCurBarQCTJ == 2)
            lCondition.append(" WH_Date>='" + ui->m_dtQSSJ->text() + "' and " + "WH_Date<='" + ui->m_dtJZSJ->text() + "'");
        sConditions = " where";
    }
    if(m_sDateSelectWay == "今天")
    {
        if(m_nCurBarQCTJ == 1)
            lCondition.append(" UH_Date>='" + QDate::currentDate().toString("yyyy-MM-dd")+ "'");
        if(m_nCurBarQCTJ == 2)
            lCondition.append(" WH_Date>='" + QDate::currentDate().toString("yyyy-MM-dd")+ "'");
        sConditions = " where";
    }
    if(m_sDateSelectWay == "本月")
    {
        if(m_nCurBarQCTJ == 1)
            lCondition.append(" UH_Date>='" + QDate::currentDate().toString("yyyy-MM-01")+ "'");
        if(m_nCurBarQCTJ == 2)
            lCondition.append(" WH_Date>='" + QDate::currentDate().toString("yyyy-MM-01")+ "'");
        sConditions = " where";
    }
    if(m_sDateSelectWay == "上月")
    {
        QString sCurDate = QDate::currentDate().toString("yyyy-MM-dd");
        int nCurMouth = sCurDate.split("-").at(1).toInt();
        if(m_nCurBarQCTJ == 1)
            lCondition.append(" UH_Date<='" + QDate::currentDate().toString("yyyy-MM-01") + "' and UH_Date>='" + QDate::currentDate().toString("yyyy-" + QString::number(nCurMouth - 1) + "-01") + "'");
        if(m_nCurBarQCTJ == 2)
            lCondition.append(" WH_Date<='" + QDate::currentDate().toString("yyyy-MM-01") + "' and WH_Date>='" + QDate::currentDate().toString("yyyy-" + QString::number(nCurMouth - 1) + "-01") + "'");
        sConditions = " where";
    }
    /********* 根据记录生成查询条件 *********/
    if(sConditions != "")
    {
        foreach(QString str, lCondition)
        {
            sConditions += " " + str + " and";
        }
        sConditions = sConditions.left(sConditions.length() - 4);
    }

    /********* 根据条件查询记录,并存入缓存中 *********/
    //查询语句
    QString sSqlSelect = "";
    QString sOneRecord = "";
    QStringList lBarcdParse;
    QStringList lTemp;
    QStringList lWHRestNum;
    QStringList lResult;
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    QTableWidget* tblwResult;
    int nCurRestNum;
    int nRestNumIndex;
    m_nCurBarQCTJ = ui->m_tbwCXTJ->currentIndex();
    if(m_nCurBarQCTJ == 0)
    {
        tblwResult = ui->m_tblwCXTJKC;
        sqlStorage->exec("select Full_Name,WH_RestNum,Alarm,Provider,BarCd_Parse,HelpSign from V_Query_WH" + sConditions);
        while(sqlStorage->next())
        {
            for(int i = 0;i < 6;i++)
            {
                sOneRecord += sqlStorage->value(i).toString() + "///";
            }
            //将条形码加入列表中，并保证其唯一性
            if(!(lBarcdParse.contains(sqlStorage->value(4).toString())))
            {
                lBarcdParse.append(sqlStorage->value(4).toString());
                lWHRestNum.append(sqlStorage->value(1).toString());
                lResult.append(sOneRecord.left(sOneRecord.length() - 3));
            }
            else
            {
                //对列表中已经有的条形码进行库存剩余量的累加
                nRestNumIndex = lBarcdParse.indexOf(sqlStorage->value(4).toString());
                nCurRestNum = lWHRestNum.at(nRestNumIndex).toInt();
                nCurRestNum += sqlStorage->value(1).toString().toInt();
                lWHRestNum[nRestNumIndex] = QString::number(nCurRestNum);
            }
            sOneRecord = "";
        }
        //将合计出的库存总量更新至结果列表
        QString sTemp = "";
        for(int i = 0;i < lResult.length();i++)
        {
            lTemp = lResult[i].split("///");
            lTemp[1] = lWHRestNum[i];
            foreach(QString str1, lTemp)
            {
                sTemp += str1 + "///";
            }
            lResult[i] = sTemp.left(sTemp.length() - 3);
            sTemp = "";
        }
        //测试，器械查询统计查询
        qDebug() << "select Full_Name,WH_RestNum,Alarm,Provider,BarCd_Parse,HelpSign from V_Query_WH" + sConditions;
    }
    //列的数量
    int nFieldCount = 0;
    QString sOrderWay = "";
    if(m_nCurBarQCTJ == 1 || m_nCurBarQCTJ == 2 || m_nCurBarQCTJ == 3)
    {
        if(m_nCurBarQCTJ == 1)
        {
            nFieldCount = 9;
            sSqlSelect = "select UH_Date,Full_Name,UH_Num,Unit,UH_Price,UH_Num*UH_Price,Provider,UH_Type,BarCd_Parse from V_Query_UH";
            sOrderWay = " order by UH_Date";
            tblwResult = ui->m_tblwCXTJCK;
        }
        if(m_nCurBarQCTJ == 3)
        {
            nFieldCount = 6;
            sSqlSelect = "select WH_Date,Full_Name,Valid_Date,Provider,BarCd_Parse,LotCode from V_Query_WH";
            sOrderWay = " order by WH_Date";
            tblwResult = ui->m_tblwCXTJYXQ;
        }
        if(m_nCurBarQCTJ == 2)
        {
            nFieldCount = 9;
            sSqlSelect = "select WH_Date,Full_Name,WH_Num,Unit,WH_Price,WH_Num*WH_Price,Valid_Date,Provider,WH_Type from V_Query_WH";
            sOrderWay = " order by WH_Date";
            tblwResult = ui->m_tblwCXTJRK;
        }
        sqlStorage->exec(sSqlSelect + sConditions + sOrderWay);
        while(sqlStorage->next())
        {
            for(int i = 0;i < nFieldCount;i++)
                sOneRecord += sqlStorage->value(i).toString() + "///";
            lResult.append(sOneRecord.left(sOneRecord.length() - 3));
            sOneRecord = "";
        }

        //测试，器械查询统计查询
        qDebug() << sSqlSelect + sConditions + sOrderWay;
    }
    /********* 将查询的结果存入表格中 *********/
    int nRow = 0;
    int nColumn = 0;
    lTemp.clear();
    tblwResult->setRowCount(0);
    tblwResult->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lResult)
    {
        tblwResult->setRowCount(tblwResult->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            tblwResult->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            tblwResult->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //可视化管线更新
    tblwResult->viewport()->update();
}

/**
 * @brief 当天记录查询
 */
void CWidgetTool::on_m_btnCXTJJT_clicked()
{
    m_sDateSelectWay = "今天";
    on_m_btnCXTJCX_clicked();
    m_sDateSelectWay = "";
}

/**
 * @brief 本月记录查询
 */
void CWidgetTool::on_m_btnCXTJBY_clicked()
{
    m_sDateSelectWay = "本月";
    on_m_btnCXTJCX_clicked();
    m_sDateSelectWay = "";
}

/**
 * @brief 上月记录查询
 */
void CWidgetTool::on_m_btnCXTJSY_clicked()
{
    m_sDateSelectWay = "上月";
    on_m_btnCXTJCX_clicked();
    m_sDateSelectWay = "";
}

/**
 * @brief 保存表格中的信息到CSV文件
 * @param tblwResult 表对象
 * @param sFilePath
 * @return 保存是否成功
 */
bool CWidgetTool::ExportExecl(QTableWidget *tblwResult, QString sFilePath)
{
    QStringList lTemp = sFilePath.split("/");
    QString fileName = sFilePath.split("/")[lTemp.length() - 1];
    QString dirName = sFilePath.left(sFilePath.length() - fileName.length() - 1);
    qDebug() << fileName << " " << dirName << " " << sFilePath;
    QDir dir(dirName);
    if (!dir.exists())
    {
        dir.mkdir(dirName);
    }
    QFile file(sFilePath);
    bool ret = file.open(QIODevice::Truncate | QIODevice::ReadWrite);
    if(!ret)
    {
        qDebug() << "open failure";
        return ret;
    }

    QTextStream stream(&file);
    QString conTents;
    // 写入头
    QHeaderView * header = tblwResult->horizontalHeader() ;
    if (NULL != header)
    {
        for (int i = 0; i < header->count(); i++)
        {
            QTableWidgetItem *item = tblwResult->horizontalHeaderItem(i);
            if (NULL != item)
            {
                conTents += item->text() + ",";
            }
        }
        conTents += "\n";
    }

    // 写内容
    for (int row = 0; row < tblwResult->rowCount(); row++)
    {
        for (int column = 0; column < tblwResult->columnCount(); column++)
        {
            QTableWidgetItem* item = tblwResult->item(row, column);
            if (NULL != item )
            {
                QString str;
                str = item->text();
                str.replace(","," ");
                conTents += str + ",";
            }
        }
        conTents += "\n";
    }
    stream << conTents;

    file.close();
    return true;
}

/**
 * @brief 保存当前表的信息为CSV文件
 */
void CWidgetTool::on_m_btnCXTJBCWJ_clicked()
{
    QTableWidget* tblwResult;
    QString sFilePath = "./";
    const char* cFilePath;
    if(m_nCurBarQCTJ == 0)
    {
        sFilePath += "QCKC" + QDateTime::currentDateTime().toString("yyyyMMddhhmmssss");
        tblwResult = ui->m_tblwCXTJKC;
    }
    if(m_nCurBarQCTJ == 1)
    {
        sFilePath += "QCCK" + QDateTime::currentDateTime().toString("yyyyMMddhhmmssss");
        tblwResult = ui->m_tblwCXTJCK;
    }
    if(m_nCurBarQCTJ == 2)
    {
        sFilePath += "QCRK" + QDateTime::currentDateTime().toString("yyyyMMddhhmmssss");
        tblwResult = ui->m_tblwCXTJRK;
    }
    if(m_nCurBarQCTJ == 3)
    {
        sFilePath += "QCYXQ" + QDateTime::currentDateTime().toString("yyyyMMddhhmmssss");
        tblwResult = ui->m_tblwCXTJYXQ;
    }
    QByteArray bFilepath = sFilePath.toLatin1();
    cFilePath = bFilepath.data();
    QString sSaveName = QFileDialog::getSaveFileName(this,tr("保存文件"),tr(cFilePath),tr("CSV files(*.CSV)"));
    ExportExecl(tblwResult, sSaveName);
}

/********* 器材配置 *********/
/**
 * @brief 层次遍历构造树
 * @param pRoot
 */
void CWidgetTool::InitTreeNode(int pRoot)
{

    QList<QStandardItem*> lstRootNode1;
    QStandardItem* itemNode1 = new QStandardItem(m_vNameTool[pRoot].sName);
    lstRootNode1.append(itemNode1);
    m_modelQC->appendRow(lstRootNode1);

    std::queue<int>qLevel1;
    qLevel1.push(pRoot);

    std::queue<QStandardItem*>qItemNode;
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
void CWidgetTool::InitTreeView(QTreeView *pTreeView)
{
    std::vector<int>vRootNode;
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
}

/**
 * @brief 单击器材列表
 * @param index 节点的索引
 */
void CWidgetTool::on_m_treevQPQC_clicked(const QModelIndex &index)
{
    /********* 遍历选中项的父节点，以生成类别名称 *********/
    QModelIndex curNode = index;
    QString sTypeName = m_modelQC->itemData(curNode).values()[0].toString();
    while(curNode.parent().row() != -1)
    {
        curNode = curNode.parent();
        sTypeName = m_modelQC->itemData(curNode).values()[0].toString() + "->" + sTypeName;
    }
    ui->m_lineQPLBMC->setText(sTypeName);

    /********* 生成类别编码 *********/
    //有待完善
    int nTvID;
    int nTvParent;
    int nCount = 0;
    QStringList lIDNumber;
    QString sTypeCode = "";
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("select Tv_ID,Tv_Parent from ToolTree_T where Tv_Name='" + m_modelQC->itemData(index).values()[0].toString() + "'");
    while(sqlStorage->next())
    {
        if(nCount == 1)
            break;
        nTvID = sqlStorage->value(0).toInt();
        lIDNumber.append(QString::number(nTvID));
        nTvParent = sqlStorage->value(1).toInt();
        nCount++;
    }
    while(nTvParent != -1)
    {
        lIDNumber.append(QString::number(nTvParent));
        sqlStorage->exec("select Tv_Parent from ToolTree_T where Tv_ID=" + QString::number(nTvParent));
        while(sqlStorage->next())
        {
            nTvParent = sqlStorage->value(0).toInt();
        }
    }
    foreach(QString str, lIDNumber)
    {
        sTypeCode = str + "-" + sTypeCode;
    }
    sTypeCode = sTypeCode.left(sTypeCode.length() - 1);
    ui->m_lineQPLBBM->setText(sTypeCode);

    /********* 根据类别名称检索器材配置信息 *********/
    //数据库待完善，价格
    QString sOneQCRecord = "";
    QStringList lQCRecord;
    sqlStorage->exec("select Full_Name,BarCode_ID,HelpSign,Alarm,Unit,Provider,Short_Name,Std1,Std2,Std3,Full_Name,DefaultPrice,IsUse from StockIndex_T where Std3 like '" + ui->m_lineQPLBMC->text() + "%'");
    while(sqlStorage->next())
    {
        for(int i = 0;i < ui->m_tblwQPKCLB->columnCount();i++)
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
    ui->m_tblwQPKCLB->setRowCount(0);
    ui->m_tblwQPKCLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lQCRecord)
    {
        ui->m_tblwQPKCLB->setRowCount(ui->m_tblwQPKCLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            ui->m_tblwQPKCLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            ui->m_tblwQPKCLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //搜索BarCdManage_T表中的信息,填写StockIndex表中没有的项目
    //获取条形码ID列表
    QStringList lBarCdID;
    QStringList lRestRecordInfo;
    foreach(QString str, lQCRecord)
    {
        lBarCdID.append(str.split("///")[1]);
    }
    sOneQCRecord = "";
    lQCRecord.clear();
    foreach(QString str, lBarCdID)
    {
        sqlStorage->exec("select BarCd_Parse,BarCd_Self from BarCdManage_T where ID=" + str);
        while(sqlStorage->next())
        {
            sOneQCRecord += sqlStorage->value(0).toString() + "///";
            sOneQCRecord += sqlStorage->value(1).toString();
        }
        lQCRecord.append(sOneQCRecord);
        sOneQCRecord = "";
    }
    //将信息填入表格中
    nRow = 0;
    lTemp.clear();
    foreach(QString str, lQCRecord)
    {
        lTemp = str.split("///");
        ui->m_tblwQPKCLB->setItem(nRow, 1, new QTableWidgetItem(lTemp[0]));
        ui->m_tblwQPKCLB->setItem(nRow, 10, new QTableWidgetItem(lTemp[1]));
        nRow++;
    }
    //可视化管线更新
    ui->m_tblwQPKCLB->viewport()->update();
}

/**
 * @brief 双击器材配置列表的某一项
 * @param item
 */
void CWidgetTool::on_m_tblwQPKCLB_itemDoubleClicked(QTableWidgetItem *item)
{
    //设置控件的显示，隐藏，可用性
    ui->m_btnQPTJ->hide();
    ui->m_btnQPGX->show();
    ui->m_treevQPQC->setEnabled(0);
    ui->m_lineQPQCTM->setEnabled(0);
    ui->m_lineQPQCTM->setText(ui->m_tblwQPKCLB->item(item->row(),1)->text());
    ui->m_lineQPSBTM->setText(ui->m_tblwQPKCLB->item(item->row(),1)->text());
    ui->m_lineQPQCJC->setText(ui->m_tblwQPKCLB->item(item->row(),6)->text());
    ui->m_lineQPQCMC->setText(ui->m_tblwQPKCLB->item(item->row(),0)->text());
    ui->m_lineQPGG->setText(ui->m_tblwQPKCLB->item(item->row(),7)->text());
    ui->m_lineQPZJF->setText(ui->m_tblwQPKCLB->item(item->row(),2)->text());    
    //防止重复向下拉菜单中添加相同内容的项
    QStringList lQPDW;
    for(int i = 0;i < ui->m_cmbQPDW->count();i++)
    {
        lQPDW.append(ui->m_cmbQPDW->itemText(i));
    }
    if(!lQPDW.contains(ui->m_tblwQPKCLB->item(item->row(),4)->text()))
    {
        ui->m_cmbQPDW->addItem(ui->m_tblwQPKCLB->item(item->row(),4)->text());
    }
    ui->m_cmbQPDW->setCurrentText(ui->m_tblwQPKCLB->item(item->row(),4)->text());
    ui->m_lineQPXH->setText(ui->m_tblwQPKCLB->item(item->row(),8)->text());
    ui->m_lineQPBJZ->setText(ui->m_tblwQPKCLB->item(item->row(),3)->text());
    ui->m_lineQPJG->setText(ui->m_tblwQPKCLB->item(item->row(),11)->text());
    //防止重复向下拉菜单中添加相同内容的项
    QStringList lQPPSS;
    for(int i = 0;i < ui->m_cmbQPPSS->count();i++)
    {
        lQPPSS.append(ui->m_cmbQPPSS->itemText(i));
    }
    if(!lQPPSS.contains(ui->m_tblwQPKCLB->item(item->row(),5)->text()))
    {
        ui->m_cmbQPPSS->addItem(ui->m_tblwQPKCLB->item(item->row(),5)->text());
    }
    ui->m_cmbQPPSS->setCurrentText(ui->m_tblwQPKCLB->item(item->row(),5)->text());
    if(ui->m_tblwQPKCLB->item(item->row(),12)->text() == "是")
        ui->m_radQPSHI->setChecked(1);
    else if(ui->m_tblwQPKCLB->item(item->row(),12)->text() == "否")
        ui->m_radQPFOU->setChecked(1);
}

/**
 * @brief 器材配置界面器材条码完成编辑时
 */
void CWidgetTool::on_m_lineQPQCTM_textChanged(const QString &arg1)
{
    ui->m_lineQPSBTM->setText(ui->m_lineQPQCTM->text());
}

/**
 * @brief 将各个控件信息初始化
 */
void CWidgetTool::on_m_btnQPFW_clicked()
{
    ui->m_lineQPQCTM->setText("");
    ui->m_lineQPSBTM->setText("");
    ui->m_lineQPQCJC->setText("");
    ui->m_lineQPQCMC->setText("");
    ui->m_lineQPGG->setText("");
    ui->m_lineQPZJF->setText("");
    ui->m_cmbQPDW->setCurrentText("");
    ui->m_lineQPXH->setText("");
    ui->m_lineQPBJZ->setText("");
    ui->m_lineQPJG->setText("");
    ui->m_cmbQPPSS->setCurrentText("");
    ui->m_radQPSHI->setCheckable(0);
    ui->m_radQPFOU->setCheckable(0);
    ui->m_radQPSHI->setCheckable(1);
    ui->m_radQPFOU->setCheckable(1);
    ui->m_tblwQPKCLB->clearContents();
    ui->m_tblwQPKCLB->setRowCount(0);
    ui->m_treevQPQC->setEnabled(1);
    ui->m_lineQPQCTM->setEnabled(1);
    ui->m_lineQPLBBM->setText("");
    ui->m_lineQPLBMC->setText("");
    ui->m_btnQPGX->hide();
    ui->m_btnQPTJ->show();
}

/**
 * @brief 更新器材配置信息
 */
void CWidgetTool::on_m_btnQPGX_clicked()
{
    /********* 将修改的内容更新至数据库 *********/
    QString sIsUse = "是";
    if(ui->m_radQPSHI->isChecked())
        sIsUse = "是";
    else if(ui->m_radQPFOU->isChecked())
        sIsUse = "否";
    QString sBarCdID = "";
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineQPQCTM->text() + "'");
    //测试
    qDebug() << "select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineQPQCTM->text() + "'";
    while(sqlStorage->next())
    {
        sBarCdID = sqlStorage->value(0).toString();
    }
    sqlStorage->exec("update StockIndex_T set "
                     "Short_Name='" + ui->m_lineQPQCJC->text() + "',Full_Name='" + ui->m_lineQPQCMC->text() + "',"
                     "Std1='" + ui->m_lineQPGG->text() + "',HelpSign='" + ui->m_lineQPZJF->text() + "',"
                     "Unit='" + ui->m_cmbQPDW->currentText() + "',Std2='" + ui->m_lineQPXH->text() + "',"
                     "Alarm='" + ui->m_lineQPBJZ->text() + "',DefaultPrice='" + ui->m_lineQPJG->text() + "',"
                     "Provider='" + ui->m_cmbQPPSS->currentText() + "',IsUse='" + sIsUse + "'"
                     " where BarCode_ID='" + sBarCdID + "'");
    //测试
    qDebug() << "update StockIndex_T set "
                "Short_Name='" + ui->m_lineQPQCJC->text() + "',Full_Name='" + ui->m_lineQPQCMC->text() + "',"
                "Std1='" + ui->m_lineQPGG->text() + "',HelpSign='" + ui->m_lineQPZJF->text() + "',"
                "Unit='" + ui->m_cmbQPDW->currentText() + "',Std2='" + ui->m_lineQPXH->text() + "',"
                "Alarm='" + ui->m_lineQPBJZ->text() + "',DefaultPrice='" + ui->m_lineQPJG->text() + "',"
                "Provider='" + ui->m_cmbQPPSS->currentText() + "',IsUse='" + sIsUse + "'"
                " where BarCode_ID='" + sBarCdID + "'";
    /********* 刷新器材信息表的内容 *********/
    //数据库待完善，价格
    QString sOneQCRecord = "";
    QStringList lQCRecord;
    sqlStorage->exec("select Full_Name,BarCode_ID,HelpSign,Alarm,Unit,Provider,Short_Name,Std1,Std2,Std3,Full_Name,DefaultPrice,IsUse from StockIndex_T where Std3 like '" + ui->m_lineQPLBMC->text() + "%'");
    while(sqlStorage->next())
    {
        for(int i = 0;i < ui->m_tblwQPKCLB->columnCount();i++)
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
    ui->m_tblwQPKCLB->setRowCount(0);
    ui->m_tblwQPKCLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lQCRecord)
    {
        ui->m_tblwQPKCLB->setRowCount(ui->m_tblwQPKCLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            ui->m_tblwQPKCLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            ui->m_tblwQPKCLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //搜索BarCdManage_T表中的信息,填写StockIndex表中没有的项目
    //获取条形码ID列表
    QStringList lBarCdID;
    QStringList lRestRecordInfo;
    foreach(QString str, lQCRecord)
    {
        lBarCdID.append(str.split("///")[1]);
    }
    sOneQCRecord = "";
    lQCRecord.clear();
    foreach(QString str, lBarCdID)
    {
        sqlStorage->exec("select BarCd_Parse,BarCd_Self from BarCdManage_T where ID=" + str);
        while(sqlStorage->next())
        {
            sOneQCRecord += sqlStorage->value(0).toString() + "///";
            sOneQCRecord += sqlStorage->value(1).toString();
        }
        lQCRecord.append(sOneQCRecord);
        sOneQCRecord = "";
    }
    //将信息填入表格中
    nRow = 0;
    lTemp.clear();
    foreach(QString str, lQCRecord)
    {
        lTemp = str.split("///");
        ui->m_tblwQPKCLB->setItem(nRow, 1, new QTableWidgetItem(lTemp[0]));
        ui->m_tblwQPKCLB->setItem(nRow, 10, new QTableWidgetItem(lTemp[1]));
        nRow++;
    }
    //可视化管线更新
    ui->m_tblwQPKCLB->viewport()->update();
    ui->m_lineQPQCTM->setText("");
    ui->m_lineQPSBTM->setText("");
    ui->m_lineQPQCJC->setText("");
    ui->m_lineQPQCMC->setText("");
    ui->m_lineQPGG->setText("");
    ui->m_lineQPZJF->setText("");
    ui->m_cmbQPDW->setCurrentText("");
    ui->m_lineQPXH->setText("");
    ui->m_lineQPBJZ->setText("");
    ui->m_lineQPJG->setText("");
    ui->m_cmbQPPSS->setCurrentText("");
    ui->m_radQPSHI->setCheckable(0);
    ui->m_radQPFOU->setCheckable(0);
    ui->m_radQPSHI->setCheckable(1);
    ui->m_radQPFOU->setCheckable(1);
    ui->m_treevQPQC->setEnabled(1);
    ui->m_lineQPQCTM->setEnabled(1);
    ui->m_btnQPGX->hide();
    ui->m_btnQPTJ->show();
}

/**
 * @brief 添加新的器材配置信息
 */
void CWidgetTool::on_m_btnQPTJ_clicked()
{
    /********* 判断是否有漏填 *********/
    if(ui->m_lineQPLBMC->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请在器材分类中选择器材类别！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPQCTM->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写器材条码！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPQCJC->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写器材简称！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPQCMC->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写器材名称！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPGG->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写规格！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPZJF->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写助记符！", QMessageBox::Ok);
        return;
    }
    if(ui->m_cmbQPDW->currentText() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写或选择单位！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPXH->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写型号！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPBJZ->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写报警值！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineQPJG->text() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写价格！", QMessageBox::Ok);
        return;
    }
    if(ui->m_cmbQPPSS->currentText() == "")
    {
        QMessageBox::warning(NULL, "warning", "请填写或选择配送商！", QMessageBox::Ok);
        return;
    }
    if(!(ui->m_radQPFOU->isChecked() || ui->m_radQPSHI->isChecked()))
    {
        QMessageBox::warning(NULL, "warning", "请选择是否在用！", QMessageBox::Ok);
        return;
    }

    /********* 判断是否包含非法字符 *********/
    if(ui->m_lineQPLBMC->text().contains("///")
        || ui->m_lineQPQCJC->text().contains("///")
        || ui->m_lineQPQCMC->text().contains("///")
        || ui->m_lineQPGG->text().contains("///")
        || ui->m_lineQPZJF->text().contains("///")
        || ui->m_cmbQPDW->currentText().contains("///")
        || ui->m_lineQPXH->text().contains("///")
        || ui->m_lineQPBJZ->text().contains("///")
        || ui->m_cmbQPPSS->currentText().contains("///")
    )
    {
        QMessageBox::warning(NULL, "warning", "信息中含有非法字符'///'", QMessageBox::Ok);
        return;
    }

    /********* 向数据库中添加新的器械配置信息 *********/
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("insert into BarCdManage_T(BarCd_Parse,BarCd_Self) values('" + ui->m_lineQPQCTM->text() + "','" + ui->m_lineQPLBBM->text() + "')");
    QString sSHIFOU = "";
    if(ui->m_radQPSHI->isChecked())
        sSHIFOU = "是";
    else if(ui->m_radQPFOU->isChecked())
        sSHIFOU = "否";
    sqlStorage->exec("select ID from BarCdManage_T where BarCd_Parse='" + ui->m_lineQPQCTM->text() + "'");
    QString sBarCdID = "";
    while(sqlStorage->next())
    {
        sBarCdID = sqlStorage->value(0).toString();
    }
    sqlStorage->exec("insert into StockIndex_T(BarCode_ID,Type_ID,Full_Name,Short_Name,Std1,Std2,Std3,Alarm,HelpSign,Provider,Unit,DefaultPrice,IsUse) "
                     "values(" + sBarCdID
                     + ",'" + QString::number(0)
                     + "','" + ui->m_lineQPQCMC->text()
                     + "','" + ui->m_lineQPQCJC->text()
                     + "','" + ui->m_lineQPGG->text()
                     + "','" + ui->m_lineQPXH->text()
                     + "','" + ui->m_lineQPLBMC->text()
                     + "'," + ui->m_lineQPBJZ->text()
                     + ",'" + ui->m_lineQPZJF->text()
                     + "','" + ui->m_cmbQPPSS->currentText()
                     + "','" + ui->m_cmbQPDW->currentText()
                     + "'," + ui->m_lineQPJG->text()
                     + ",'" + sSHIFOU
                     + "')");
//    //测试,测试插入到条形码管理表中
//    sqlStorage->exec("select * from BarCdManage_T where BarCd_Parse='" + ui->m_lineQPQCTM->text() + "' order by ID");
//    QString sTemp = "";
//    while(sqlStorage->next())
//    {
//        sTemp = "";
//        sTemp += sqlStorage->value(0).toString() + "//";
//        sTemp += sqlStorage->value(1).toString() + "//";
//        sTemp += sqlStorage->value(2).toString();
//    }
//    qDebug() << sTemp;
//    sqlStorage->exec("select * from StockIndex_T where BarCode_ID=" + sTemp.split("//")[0] + " order by ID");
//    sTemp = "";
//    while(sqlStorage->next())
//    {
//        sTemp = "";
//        for(int i = 0;i < 18;i++)
//        {
//            sTemp += sqlStorage->value(i).toString() + "//";
//        }
//    }
//    qDebug() << sTemp;
//    sqlStorage->exec("select Full_Name,BarCd_Parse,HelpSign,Alarm,Unit,Provider,Short_Name,Std1,Std2,Std3,BarCd_Self,DefaultPrice,IsUse from V_Query_Stock where Std3 like '其他%'");
//    sTemp = "";
//    while(sqlStorage->next())
//    {
//        sTemp = "";
//        for(int i = 0;i < 18;i++)
//        {
//            sTemp += sqlStorage->value(i).toString() + "//";
//        }
//    }
//    qDebug() << sTemp;
    QMessageBox::information(NULL, "Ttp", "添加成功！", QMessageBox::Ok);
    on_m_btnQPFW_clicked();
}


/**
 * @brief 检测条形码是否已存在与数据库中，如果已存在则将其信息填写到对应框中
 */
void CWidgetTool::on_m_lineQPQCTM_editingFinished()
{
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("select ID,BarCd_Self from BarCdManage_T where BarCd_Parse='" + ui->m_lineQPQCTM->text() + "'");
    int nRecordCount = 0;
    QString sBarID = "";
    QString sBarSelf = "";
    while(sqlStorage->next())
    {
        sBarID = sqlStorage->value(0).toString();
        sBarSelf = sqlStorage->value(1).toString();
        nRecordCount++;
    }
    if(nRecordCount)
    {

        sqlStorage->exec("select Full_Name,Full_Name,HelpSign,Alarm,Unit,Provider,Short_Name,Std1,Std2,Std3,Full_Name,DefaultPrice,IsUse from StockIndex_T where BarCode_ID=" + sBarID);
        while(sqlStorage->next())
        {
            ui->m_lineQPQCJC->setText(sqlStorage->value(6).toString());
            ui->m_lineQPQCMC->setText(sqlStorage->value(0).toString());
            ui->m_lineQPGG->setText(sqlStorage->value(7).toString());
            ui->m_lineQPZJF->setText(sqlStorage->value(2).toString());
            QStringList lQPDW;
            for(int i = 0;i < ui->m_cmbQPDW->count();i++)
            {
                lQPDW.append(ui->m_cmbQPDW->itemText(i));
            }
            if(!lQPDW.contains(sqlStorage->value(4).toString()))
            {
                ui->m_cmbQPDW->addItem(sqlStorage->value(4).toString());
            }
            ui->m_cmbQPDW->setCurrentText(sqlStorage->value(4).toString());
            ui->m_lineQPXH->setText(sqlStorage->value(8).toString());
            ui->m_lineQPBJZ->setText(sqlStorage->value(3).toString());
            ui->m_lineQPJG->setText(sqlStorage->value(11).toString());
            QStringList lQPPSS;
            for(int i = 0;i < ui->m_cmbQPPSS->count();i++)
            {
                lQPPSS.append(ui->m_cmbQPPSS->itemText(i));
            }
            if(!lQPPSS.contains(sqlStorage->value(5).toString()))
            {
                ui->m_cmbQPPSS->addItem(sqlStorage->value(5).toString());
            }
            ui->m_cmbQPPSS->setCurrentText(sqlStorage->value(5).toString());
            if(sqlStorage->value(12).toString() == "是")
                ui->m_radQPSHI->setChecked(1);
            else if(sqlStorage->value(12).toString() == "否")
                ui->m_radQPFOU->setChecked(1);
            ui->m_lineQPLBMC->setText(sqlStorage->value(9).toString());
            ui->m_lineQPLBBM->setText(sBarSelf);
        }
        m_nQPQCTMFlag = 1;
        ui->m_btnQPGX->show();
        ui->m_btnQPTJ->hide();
        QMessageBox::warning(NULL, "warning", "该器材条码已存在，其信息已显示在各个信息框中！", QMessageBox::Ok);    
        return;
    }
    //判断之前是否发生过器材条码已存在的警告
    if(m_nQPQCTMFlag)
    {
        ui->m_lineQPQCJC->setText("");
        ui->m_lineQPQCMC->setText("");
        ui->m_lineQPGG->setText("");
        ui->m_lineQPZJF->setText("");
        ui->m_cmbQPDW->setCurrentText("");
        ui->m_lineQPXH->setText("");
        ui->m_lineQPBJZ->setText("");
        ui->m_lineQPJG->setText("");
        ui->m_cmbQPPSS->setCurrentText("");
        ui->m_radQPSHI->setChecked(0);
        ui->m_radQPFOU->setChecked(0);
        ui->m_tblwQPKCLB->clearContents();
        ui->m_tblwQPKCLB->setRowCount(0);
        ui->m_treevQPQC->setEnabled(1);
        ui->m_lineQPQCTM->setEnabled(1);
        ui->m_lineQPLBBM->setText("");
        ui->m_lineQPLBMC->setText("");
        ui->m_btnQPGX->hide();
        ui->m_btnQPTJ->show();
        m_nQPQCTMFlag = 0;
    }
}


