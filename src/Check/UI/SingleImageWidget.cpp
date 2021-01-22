#include "SingleImageWidget.h"
#include "ui_singleimagewidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QRect>
#include <QSettings>
#include "dsaconfig.h"
#include <QMouseEvent>

SingleImageWidget::SingleImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleImageWidget)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("CUST");
    QCoreApplication::setOrganizationDomain("www.cust.edu.cn");
    QCoreApplication::setApplicationName("DSA");

    _ini_config_name = DsaConfig::GetImageProcessIniName();

    settings = new QSettings(_ini_config_name, QSettings::IniFormat);
    settings->setParent(this);
    settings->clear();
    settings->sync();

}

SingleImageWidget::~SingleImageWidget()
{
    delete ui;
}

void SingleImageWidget::SetImage(const QPixmap &pix)
{
    ui->widget->resize(pix.size());
    ui->widget->setMinimumSize(pix.size());


    //ui->image_label->setMinimumSize(pix.size());
    ui->image_label->resize(pix.size());
    ui->image_label->setPixmap(pix);
    ui->image_label->move(0,0);

    ui->checkBox->move(0,0);

}

void SingleImageWidget::SetFileName(QString filename)
{
    _filename = filename;
}

bool SingleImageWidget::IsSelected() const
{
    return this->ui->checkBox->isChecked();
}

void SingleImageWidget::SetSelected(bool check)
{
    if(check)
    {
        on_checkBox_clicked(check);
        this->ui->checkBox->setChecked(check);
    }
    else
    {
        on_checkBox_clicked(!check);
        this->ui->checkBox->setChecked(!check);
    }
}

void SingleImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //FlowImagesWidget::mousePressEvent(event);
        bool checked = this->ui->checkBox->isChecked();
        on_checkBox_clicked(!checked);
        this->ui->checkBox->setChecked(!checked);

    }
    else if(event->button()==Qt::RightButton)
    {

    }
    QWidget::mousePressEvent(event);
}

void SingleImageWidget::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        auto count = settings->value("SERIES/count", 0).toInt();
        settings->setValue("SERIES/count", count+1);
        settings->setValue(QString("SERIES/f%1").arg(count+1), _filename);
    }
    else
    {
        auto count = settings->value("SERIES/count", 0).toInt();
        // 找到此文件的记录
        int this_img_index = 0;
        auto keys = settings->allKeys();
        for(int i = 1;i<=keys.size();i++)
        {
            if(settings->value(QString("SERIES/f%1").arg(i)).toString() == _filename)
            {
                this_img_index = i;
                break;
            }
        }

        if(this_img_index>0)
        {
            settings->setValue(QString("SERIES/f%1").arg(this_img_index), settings->value(QString("SERIES/f%1").arg(count)).toString());
            settings->setValue("SERIES/count", count-1);
            settings->remove(QString("SERIES/f%1").arg(count));
        }
    }
    settings->sync();
}
