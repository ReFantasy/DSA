#include "check.h"
#include "ui_check.h"
#include "singletondb.h"
#include <QDebug>
#include "dcm2mat.h"
#include <string>
#include <opencv2/opencv.hpp>
#include "singletondb.h"
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QHeaderView>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include "query.h"
#include "flowlayout.h"
#include "opencv2/opencv.hpp"
#include <QImage>
#include <QPixmap>
#include "dcmimagewidget.h"

#define ELPP_QT_LOGGING

#include "easyloggingpp/easylogging++.h"


Check::Check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Check)
{
    ui->setupUi(this);

    // 初始化
    _query_model = new QSqlQueryModel(this);
    _table_model = new TableModel(this);

    ui->pati_list->setHeaderLabel("影像");
    ui->pati_table->setModel(_table_model);
    ui->begin_study_date->setDate(QDateTime::currentDateTime().date());
    ui->end_study_date->setDate(QDateTime::currentDateTime().date());
    ui->begin_study_date->setEnabled(false);
    ui->end_study_date->setEnabled(false);
    ui->pati_table->setSelectionBehavior(QAbstractItemView::SelectRows); // 每次选中一行
    ui->pati_table->setSelectionMode(QAbstractItemView::SingleSelection);// 不能多行选中

    //ui->splitter_2->setStretchFactor(0,1);
    ui->splitter_2->setStretchFactor(1,4);



    // 设置风格
    SetStyle();

    /***************************  信号槽设置  ***************************/
    // 影像柜和病人表格
    connect(ui->pati_list, &QTreeWidget::itemChanged, this, &Check::UpdateStudyTable);



}

Check::~Check()
{
    delete ui;
}

QStringList Check::GenerateCheckCondition()
{
    QStringList cc;
    // 检查号
    if(!ui->PatientID->text().isEmpty())
    {
        QString PatientID = QString("PatientID = '%1'").arg(ui->PatientID->text());
        cc.push_back(PatientID);
    }

    // 姓名
    if(!ui->PatientNam->text().isEmpty())
    {
        QString PatientNam = QString("PatientNam = '%1'").arg(ui->PatientNam->text());
        cc.push_back(PatientNam);
    }

    // 开始日期
    if(ui->begin_study_date->isEnabled())
    {
        QString begin_study_date = QString("StudyDate >= '%1'").arg(ui->begin_study_date->date().toString("yyyyMMdd"));
        cc.push_back(begin_study_date);
    }
    // 截至日期
    if(ui->end_study_date->isEnabled())
    {
        QString end_study_date = QString("StudyDate <= '%1'").arg(ui->end_study_date->date().toString("yyyyMMdd"));
        cc.push_back(end_study_date);
    }

    return cc;
}

void Check::SetStyle()
{
    ui->pati_list->setStyle(QStyleFactory::create("Fusion"));

    // 表头居左
    auto hori_header = ui->pati_table->horizontalHeader();
    hori_header->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

}

void Check::on_checkButton_clicked()
{
    try
    {
        // 创建数据库连接
        auto db = SingletonDB("127.0.0.1");
        if(!db.open())
        {
            LOG(ERROR)<<"DataBase connect fail.";
            return;
        }

        // 主控界面数据库 EvertopDB
        db.exec("use EvertopDB");

        // 查询数据库
        QStringList check_condition_list = GenerateCheckCondition();
        Query(db, "DICOMStudies", check_condition_list);

        // 刷新查询结果
        RefreshUserInterface();
    }
    catch(const std::exception &e)
    {
        LOG(ERROR)<<e.what();
    }
    catch(...)
    {
        LOG(ERROR)<<"Unknow error while querying";
    }

}

int Check::Query(const QSqlDatabase &db, const QString &table, const QStringList &check_condition_list)
{
    // 如果查询条件为空 则清空上次查询结果
    if(check_condition_list.size()==0)
    {
        _query_model->clear();  // 更新查询模型
        return 0;
    }

    // 创建查询字段
    QStringList fields;
    fields<<"PatientID"<<"PatientNam"<<"PatientBir"<<"PatientSex"<<"StudyDate"<<"StudyTime"<<"AccessionN"
         << "ReferPhysi"<<"StudyID"<<"StudyDescr";

    // 生成查询语句
    QString query = CreateQueryStatement(table, fields, check_condition_list);
    qDebug()<<query;

    // 查询
    _query_model->setQuery(query,db);
    while(_query_model->canFetchMore())_query_model->fetchMore();  // sqlquerymodel 默认缓存256条查询结果 因此需要手动获取所有的查询结果
    return _query_model->rowCount();
}

void Check::RefreshUserInterface()
{
    // 清空病人列表和 Study Table
    ui->pati_list->clear();
    _table_model->ClearAll();

    // 添加检索结果到影像柜
    QTreeWidgetItem *root_item = new QTreeWidgetItem();
    root_item->setText(0,"影像");

    root_item->setCheckState(0,Qt::Unchecked);  // 影像柜设置为未选中状态

    int rows = _query_model->rowCount();

    for(int i = 0;i<rows;i++)
    {
        // 从数据库检索结果中找到每个病例的姓名和检查号
        // 其中，姓名信息显示在列表控件上
        // 检查号唯一标志一个病例，添加在列表控件上但不显示
        QModelIndex index_id = _query_model->index(i, 0);
        QVariant PatientID = _query_model->data(index_id, Qt::DisplayRole);

        QModelIndex index_name = _query_model->index(i, 1);
        QVariant PatientNam = _query_model->data(index_name, Qt::DisplayRole);

        // 挂到列表控件上
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0,PatientNam.toString());
        item->setCheckState(0,Qt::Unchecked);        // 影像柜设置为未选中状态
        item->setText(1,PatientID.toString());       // 检查号
        item->setText(2, QString::number(i));        // 查询结果中的序号
        root_item->addChild(item);
    }
    if(root_item->childCount()<=0)
        return;
    ui->pati_list->addTopLevelItem(root_item);
    ui->pati_list->expandAll();
}


void Check::UpdateStudyTable(QTreeWidgetItem *item, int column)
{
    // 如果是病人列表根项发生改变则忽略
    if(item->parent()==nullptr)
        return;

    if(item->checkState(column) == Qt::Unchecked)
    {
        auto index = item->data(2,Qt::DisplayRole);
        _table_model->RemoveRecord(_query_model->record(index.toInt()));
    }
    else
    {
        auto index = item->data(2,Qt::DisplayRole);
        _table_model->InsertRecord(_query_model->record(index.toInt()));
    }
}

void Check::on_begin_study_date_on_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->begin_study_date->setEnabled(false);
    }
    else
    {
        ui->begin_study_date->setEnabled(true);
    }
}

void Check::on_end_study_date_on_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->end_study_date->setEnabled(false);
    }
    else
    {
        ui->end_study_date->setEnabled(true);
    }
}

void Check::on_pati_table_clicked(const QModelIndex &index)
{

    // 删除幕布上所有对象包括图像widget和layout
    auto children_list = ui->dcmScrollAreaWidgetContents->children();
    for(auto e:children_list){
        delete e;
    }

    // TODO

    // 添加新的图像并设置流布局管理器
    auto flowlayout = new FlowLayout;

    for(int i = 0;i<100;i++)
    {
        auto image_widget = new DcmImageWidget(this);
        //auto image_widget = new QWidget;
        image_widget->setMinimumSize({120,120});

        image_widget->setStyleSheet("background-color: rgb(255, 170, 0)");

        flowlayout->addWidget(image_widget);

    }

    ui->dcmScrollAreaWidgetContents->setLayout(flowlayout);
}
