#include "cwidgetmedicine.h"
#include "ui_cwidgetmedicine.h"

CWidgetMedicine::CWidgetMedicine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetMedicine)
{
    ui->setupUi(this);
    //设置表格不可编辑
    ui->m_tblwYPKCLB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表的最后一列左对齐
    ui->m_tblwYPKCLB->horizontalHeaderItem(ui->m_tblwYPKCLB->columnCount() - 1)->setTextAlignment(Qt::AlignLeft);
    //设置表选中整行
    ui->m_tblwYPKCLB->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblwYPKCLB->setSelectionBehavior(QAbstractItemView::SelectRows);
    /******** 初始化药品树表 ********/
    QSqlQuery* sqlStorge = new QSqlQuery(SQLDB::GetCathLabStock());
    QString sSqlPciQC="select Tv_Name,Tv_Parent from LeeTree_T";
    sqlStorge->exec(sSqlPciQC);
    while (sqlStorge->next())
    {
        QString sAnsName=sqlStorge->value(0).toString();
        int nAnsParent=sqlStorge->value(1).toInt();
        STreeNode sNode={sAnsName,nAnsParent};
        m_vNameMedicine.push_back(sNode);
    }
    QStringList sHeaderQC;
    sHeaderQC.append("药品类别名称");
    m_modelYP= new QStandardItemModel();
    m_modelYP->setHorizontalHeaderLabels(sHeaderQC);
    //载入模型
    ui->m_treevYPYP->setModel(m_modelYP);
    ui->m_treevYPYP->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_treevYPYP->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_treevYPYP->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_treevYPYP->show();
    // 初始化药品
    this->InitTreeView(ui->m_treevYPYP);
}

CWidgetMedicine::~CWidgetMedicine()
{
    delete ui;
}

/**
 * @brief 显示从数据库中查询到的记录至表格中
 */
void CWidgetMedicine::ShowInfoAtTable(QString sSqlSelect)
{
    //从数据库中读取信息
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    QString sOneQCRecord = "";
    QStringList lQCRecord;
    sqlStorage->exec(sSqlSelect);
    while(sqlStorage->next())
    {
        for(int i = 0;i < ui->m_tblwYPKCLB->columnCount();i++)
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
    ui->m_tblwYPKCLB->setRowCount(0);
    ui->m_tblwYPKCLB->horizontalHeader()->setStretchLastSection(true);
    foreach(QString str, lQCRecord)
    {
        ui->m_tblwYPKCLB->setRowCount(ui->m_tblwYPKCLB->rowCount() + 1);
        lTemp = str.split("///");
        foreach(QString subStr, lTemp)
        {
            ui->m_tblwYPKCLB->setItem(nRow, nColumn, new QTableWidgetItem(subStr));
            ui->m_tblwYPKCLB->horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
            nColumn++;
        }
        nRow++;
        nColumn = 0;
    }
    //可视化管线更新
    ui->m_tblwYPKCLB->viewport()->update();
}

/**
 * @brief 层次遍历构造树
 * @param pRoot
 */
void CWidgetMedicine::InitTreeNode(int pRoot)
{

    QList<QStandardItem*> lstRootNode1;
    QStandardItem* itemNode1 = new QStandardItem(m_vNameMedicine[pRoot].sName);
    lstRootNode1.append(itemNode1);
    m_modelYP->appendRow(lstRootNode1);

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

        for (int j=0;j<m_vNameMedicine.size();j++)
        {
            if(m_vNameMedicine[j].nParent==nIdTemp)
            {
                qLevel1.push(j);

                QList<QStandardItem*> items2;
                QStandardItem* item2 = new QStandardItem(m_vNameMedicine[j].sName);
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
void CWidgetMedicine::InitTreeView(QTreeView *pTreeView)
{
    std::vector<int>vRootNode;
    for (int i=0;i<m_vNameMedicine.size();i++)
    {
        if(m_vNameMedicine[i].nParent==-1)
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
 * @brief 单击药品树中的某一项
 * @param index 被单击的项的索引号
 */
void CWidgetMedicine::on_m_treevYPYP_clicked(const QModelIndex &index)
{
    /********* 遍历选中项的父节点，以生成类别名称 *********/
    QModelIndex curNode = index;
    QString sTypeName = m_modelYP->itemData(curNode).values()[0].toString();
    while(curNode.parent().row() != -1)
    {
        curNode = curNode.parent();
        sTypeName = m_modelYP->itemData(curNode).values()[0].toString() + "->" + sTypeName;
    }
    ui->m_lineYPLBMC->setText(sTypeName);

    /********* 生成类别编码 *********/
    //有待完善
    int nTvID;
    int nTvParent;
    int nCount = 0;
    QStringList lIDNumber;
    QString sTypeCode = "";
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("select Tv_ID,Tv_Parent from LeeTree_T where Tv_Name='" + m_modelYP->itemData(index).values()[0].toString() + "'");
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
    ui->m_lineYPLBBM->setText(sTypeCode);   
    //显示该类别的药品信息至表格中
    ShowInfoAtTable("select LeeName,Unit,Style,HelpSign,Stock_Num from Lee_StockIndex where LeeType like '" + ui->m_lineYPLBMC->text() + "%'");
}

/**
 * @brief 各个控件状态复位
 */
void CWidgetMedicine::on_m_btnYPFW_clicked()
{
    ui->m_lineYPLBMC->setText("");
    ui->m_lineYPLBBM->setText("");
    ui->m_lineYPYPMC->setText("");
    ui->m_lineYPGG->setText("");
    ui->m_lineYPZJF->setText("");
    ui->m_cmbYPDW->setCurrentIndex(-1);
    ui->m_treevYPYP->setEnabled(1);
    ui->m_tblwYPKCLB->clearContents();
    ui->m_tblwYPKCLB->setRowCount(0);
    ui->m_lineYPYPMCRK->setText("");
    ui->m_dspdYPJL->setValue(0.00);
}

/**
 * @brief 添加药品配置信息
 */
void CWidgetMedicine::on_m_btnYPTJ_clicked()
{
    /********* 判断将要添加的信息是否合法 *********/
    // 判断是否漏填或漏选
    if(ui->m_lineYPLBBM->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请在药品分类中选择药品类别！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineYPLBMC->text() == "")
    {
        QMessageBox::warning(NULL, "警告", "请在药品分类中选择药品类别！", QMessageBox::Ok);
        return;
    }
    if(ui->m_lineYPYPMC->text() == "")
    {
       QMessageBox::warning(NULL, "警告", "请填写药品名称！", QMessageBox::Ok);
       return;
    }
    if(ui->m_lineYPGG->text() == "")
    {
       QMessageBox::warning(NULL, "警告", "请填写药品规格！", QMessageBox::Ok);
       return;
    }
    if(ui->m_lineYPZJF->text() == "")
    {
       QMessageBox::warning(NULL, "警告", "请填写助记符！", QMessageBox::Ok);
       return;
    }
    if(ui->m_cmbYPDW->currentText() == "")
    {
       QMessageBox::warning(NULL, "警告", "请选择或填写药品单位！", QMessageBox::Ok);
       return;
    }
    //判断是否包含非法字符串
    if(ui->m_lineYPLBBM->text().contains("///")
            || ui->m_lineYPLBMC->text().contains("///")
            || ui->m_lineYPYPMC->text().contains("///")
            || ui->m_lineYPGG->text().contains("///")
            || ui->m_lineYPZJF->text().contains("///")
            || ui->m_cmbYPDW->currentText().contains("///")
            )
    {
        QMessageBox::warning(NULL, "警告", "信息中不能包含'///'！", QMessageBox::Ok);
        return;
    }

    /********* 添加新的药品配置信息至数据库中 *********/
    //查询药品是否已存在于数据库中，如果不存在则添加
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    sqlStorage->exec("select * from Lee_StockIndex where LeeName='" + ui->m_lineYPYPMC->text() + "'");
    if(sqlStorage->last())
    {
        QMessageBox::warning(NULL, "警告", "该药品名称已存在！", QMessageBox::Ok);
        return;
    }
    else
    {
        sqlStorage->exec("insert into Lee_StockIndex(LeeName,Unit,Style,HelpSign,Stock_Num,LeeType,LeeCode) "
                         "values('" + ui->m_lineYPYPMC->text() +
                         "','" + ui->m_cmbYPDW->currentText() +
                         "','" + ui->m_lineYPGG->text() +
                         "','" + ui->m_lineYPZJF->text() +
                         "'," + QString::number(0) +
                         ",'" + ui->m_lineYPLBMC->text() +
                         "'," +  ui->m_lineYPLBBM->text() +
                         ")");
    }
    ShowInfoAtTable("select LeeName,Unit,Style,HelpSign,Stock_Num from Lee_StockIndex where LeeName='" + ui->m_lineYPYPMC->text() + "'");
    QMessageBox::information(NULL, "提示", "添加成功！", QMessageBox::Ok);
    //初始化控件状态
    ui->m_lineYPLBMC->setText("");
    ui->m_lineYPLBBM->setText("");
    ui->m_lineYPYPMC->setText("");
    ui->m_lineYPGG->setText("");
    ui->m_lineYPZJF->setText("");
    ui->m_cmbYPDW->setCurrentIndex(-1);
}

/**
 * @brief 双击填写入库信息
 * @param item
 */
void CWidgetMedicine::on_m_tblwYPKCLB_itemDoubleClicked(QTableWidgetItem *item)
{
    ui->m_lineYPYPMCRK->setText(ui->m_tblwYPKCLB->item(item->row(), 0)->text());
    ui->m_dspdYPJL->setFocus();
}

/**
 * @brief 药品入库
 */
void CWidgetMedicine::on_m_lineYPRK_clicked()
{
    //判断漏填
    if(ui->m_lineYPYPMCRK->text() == "")
    {
       QMessageBox::warning(NULL, "警告", "请双击表格中的药品或填写药品名称！", QMessageBox::Ok);
       return;
    }
    if(ui->m_dspdYPJL->text().toFloat() == 0)
    {
       QMessageBox::warning(NULL, "警告", "入库剂量应大于0！", QMessageBox::Ok);
       return;
    }
    //判断库中是否存在该药品，如果存在则更新入库信息
    QSqlQuery* sqlStorage = new QSqlQuery(SQLDB::GetCathLabStock());
    float fStockNum = 0;
    sqlStorage->exec("select Stock_Num from Lee_StockIndex where LeeName='" + ui->m_lineYPYPMCRK->text() + "'");
    if(sqlStorage->last())
    {
        fStockNum = sqlStorage->value(0).toFloat();
        fStockNum += ui->m_dspdYPJL->value();
        sqlStorage->exec("update Lee_StockIndex set Stock_Num=" + QString::number(fStockNum) + " where LeeName='" + ui->m_lineYPYPMCRK->text() + "'");
        QMessageBox::information(NULL, "提示", "入库成功！", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(NULL, "警告", "库中没有该药品，请添加后再进行入库操作！", QMessageBox::Ok);
        return;
    }
    ShowInfoAtTable("select LeeName,Unit,Style,HelpSign,Stock_Num from Lee_StockIndex where LeeName='" + ui->m_lineYPYPMCRK->text() + "'");
}


/**
 * @brief 入库时药品名称完成输入时
 */
void CWidgetMedicine::on_m_lineYPYPMCRK_editingFinished()
{
    ShowInfoAtTable("select LeeName,Unit,Style,HelpSign,Stock_Num from Lee_StockIndex where LeeName='" + ui->m_lineYPYPMCRK->text() + "'");
}
