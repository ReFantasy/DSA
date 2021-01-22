#include "csurtype.h"
#include "ui_csurtype.h"
#include <QDebug>

CSurType::CSurType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSurType)
{
    ui->setupUi(this);

    setWindowTitle("手术类型");

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &CSurType::UpdateSelected);
}

CSurType::~CSurType()
{
    delete ui;
}

void CSurType::SetSurgType(QStringList surg_types)
{

    _surg_types = surg_types;
    for(auto e:_surg_types)
    {
        ui->listWidget->addItem(e);
    }

}

void CSurType::UpdateSelected(QListWidgetItem *item)
{
    bool is_exit = false;
    for (int j = 0; j < ui->selected_surtype->count(); j++)
    {
        QString type = ui->selected_surtype->item(j)->text();
        if(type == item->data(Qt::DisplayRole).toString())
        {
            is_exit = true;
            break;
        }

    }

    // 如果不存在则添加
    if(!is_exit)
    {
        ui->selected_surtype->addItem(item->data(Qt::DisplayRole).toString());
        _selected_types.push_back(item->data(Qt::DisplayRole).toString());
    }


}

void CSurType::on_clear_selected_clicked()
{
    ui->selected_surtype->clear();
    _selected_types.clear();
}


// 确定按钮 发送已选信号
void CSurType::on_pushButton_clicked()
{
    emit SendSelectedTypes(_selected_types);
    hide();
}
