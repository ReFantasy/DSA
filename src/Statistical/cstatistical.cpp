#include "cstatistical.h"
#include "ui_cstatistical.h"
#include <QTime>
#include <QPushButton>

CStatistical::CStatistical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CStatistical)
{
    ui->setupUi(this);


    QTime time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    //int n = qrand() % 5;    //产生5以内的随机数

    // 填写表的信息
    QStringList xfields;
    xfields<<"医生"<<"球囊"<<"支架"<<"拱桥";

    // 设置表头
    ui->tableWidget->setColumnCount(xfields.size());
    ui->tableWidget->setHorizontalHeaderLabels(xfields);

    // 行列
    ui->tableWidget->setColumnCount(4);    //设置列数
    ui->tableWidget->setRowCount(3);        //设置行数/

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //去掉每行的行号
    QHeaderView *headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
    ui->tableWidget->setVerticalHeaderLabels({"周俊","李洋","张杰"});

    // 插入一条记录
    int rows = ui->tableWidget->rowCount();
    int cols = ui->tableWidget->columnCount();
    for(int row=0;row<rows;row++)
    {
        for(int i = 1;i<cols;i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem;
            newItem->setData(Qt::DisplayRole, qrand() % 15+2);
            ui->tableWidget->setItem(row, i, newItem);
        }
    }

    QTableWidgetItem *newItem = new QTableWidgetItem;
    newItem->setData(Qt::DisplayRole, "周俊");
    ui->tableWidget->setItem(0, 0, newItem);

    newItem = new QTableWidgetItem;
    newItem->setData(Qt::DisplayRole, "李洋");
    ui->tableWidget->setItem(1, 0, newItem);

    newItem = new QTableWidgetItem;
    newItem->setData(Qt::DisplayRole, "张杰");
    ui->tableWidget->setItem(2, 0, newItem);

    // 设置表格左上角



}

CStatistical::~CStatistical()
{
    delete ui;
}
