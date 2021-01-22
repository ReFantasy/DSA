#include "cwidgetreportpic.h"
#include "ui_cwidgetreportpic.h"
#include "SQLDB.h"

const std::string DATABASE_IMAGE_TYPE("png");

CWidgetReportPic::CWidgetReportPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetReportPic)
{
    ui->setupUi(this);
    ui->image->setScaledContents(true);

    _label_list.clear();
    _label_list.push_back(ui->image1);
    _label_list.push_back(ui->image2);
    _label_list.push_back(ui->image3);
    _label_list.push_back(ui->image4);
    _label_list.push_back(ui->image5);
    _label_list.push_back(ui->image6);
    _label_list.push_back(ui->image7);
    _label_list.push_back(ui->image8);
    _label_list.push_back(ui->image9);
    _label_list.push_back(ui->image10);
    _label_list.push_back(ui->image11);
    _label_list.push_back(ui->image12);
    _label_list.push_back(ui->image13);
    _label_list.push_back(ui->image14);
    _label_list.push_back(ui->image15);

    // 图像更新信号槽
    connect(ui->image1, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image2, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image3, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image4, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image5, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image6, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image7, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image8, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image9, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image10, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image11, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image12, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image13, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image14, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
    connect(ui->image15, &QLabelWithDoubleClick::UpdateLabel, this, &CWidgetReportPic::UpdateLabel);
}

CWidgetReportPic::~CWidgetReportPic()
{
    delete ui;
}

void CWidgetReportPic::SetImageViewer(const ImageViewer *viewer)
{
    _image_viewer = viewer;
}

void CWidgetReportPic::UpdateLabel(QLabelWithDoubleClick *label)
{
    auto frame = _image_viewer->GetCurrentFrame().copy();
    if(!frame.isNull())
    {
        label->setPixmap(frame);
    }
}

void CWidgetReportPic::UpdateImageToDatabase()
{
    for(int i = 0;i<15;i++)
    {
        QByteArray byteArray = QByteArray();
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);


        // 从数据库读取图片信息 1047178
        auto cathlab_db = SQLDB::GetDfytCathLab();
        QSqlQuery cathlab_query(cathlab_db);
        const QPixmap* pixmap;

        cathlab_query.prepare(QString("update operateitem set image%1 = :imgdata where caseid = '%2'").arg(QString::number(i+1), _patient_id));
        //pixmap = ui->image1->pixmap();
        pixmap = _label_list[i]->pixmap();
        if(pixmap)
        {
            pixmap->save(&buffer,DATABASE_IMAGE_TYPE.c_str(),0);
            cathlab_query.bindValue (":imgdata",byteArray);
            cathlab_query.exec();
        }
        else
        {
            cathlab_query.bindValue (":imgdata",QByteArray{});
            cathlab_query.exec();
        }
    }

}

void CWidgetReportPic::UpdateImageFromDatabase()
{
    // 从数据库读取图片信息 1047178
    auto cathlab_db = SQLDB::GetDfytCathLab();
    QSqlQuery cathlab_query(cathlab_db);

    cathlab_query.exec(QString("select * from operateitem where caseid = '%1'").arg(_patient_id));
    cathlab_query.next();  // 唯一一条数据
    auto record = cathlab_query.record();

    QPixmap pix;


    // cathlab_query.prepare(QString("update operateitem set image%1 = :imgdata where caseid = '%2'").arg(QString::number(i+1), _patient_id));
    QByteArray byteArray;
    for(int i = 0;i<15;i++)
    {
        byteArray = record.value( QString("image%1").arg(QString::number(i+1)) ).toByteArray();
        if(pix.loadFromData(byteArray,DATABASE_IMAGE_TYPE.c_str()) ){
            pix.scaled(_label_list[i]->size(), Qt::KeepAspectRatio);
            //ui->image2->setPixmap(pix);
            _label_list[i]->setPixmap(pix);
        }
    }

    byteArray = record.value("image").toByteArray();
    if(pix.loadFromData(byteArray,DATABASE_IMAGE_TYPE.c_str()) ){
        ui->image->setPixmap(pix);
    }



}

void CWidgetReportPic::SetSysCaseId(const QString pSysCaseId)
{
    _patient_id = pSysCaseId;
    UpdateImageFromDatabase();
}

void CWidgetReportPic::UpdateUIFromDatabase()
{
    UpdateUIFromDatabase();
}

void CWidgetReportPic::UpdateDatabaseFromUI()
{
    UpdateImageToDatabase();
}


void CWidgetReportPic::on_pushButton_clicked()
{
    UpdateDatabaseFromUI();
}
