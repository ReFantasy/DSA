#include "FlowImagesWidget.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QDir>
#include <QMouseEvent>
#include <chrono>
#include <QProgressBar>
#include <QProgressDialog>
#include <QApplication>
#include "flowlayout.h"
#include "SingleImageWidget.h"
#include "cvframestovideo.h"
#include "dcm2mat.h"
#include "SQLDB.h"
#include "dsaconfig.h"
#include "acquiredcmfile.h"
#include <QAction>
#include <QProcess>

FlowImagesWidget::FlowImagesWidget(QWidget *parent) : QWidget(parent)
{
    // 创建并设置布局管理器
    flowlayout = new FlowLayout(this);
    setLayout(flowlayout);


    // 图像处理弹出菜单
    _pop_menu = new QMenu;
    _img_process_action = new QAction(this);
    _img_process_action->setText(("处理图像"));
    _pop_menu->addAction(_img_process_action);
    connect(_img_process_action, &QAction::triggered, this, &FlowImagesWidget::CallDSAImg);

    // 光盘刻录
    auto _burncd_process_action = new QAction(this);
    _burncd_process_action->setText(("刻录图像"));
    _pop_menu->addAction(_burncd_process_action);
    connect(_burncd_process_action, &QAction::triggered, this,
            [](){QProcess process;process.execute("BurnCD.exe");process.waitForFinished();});

}

FlowImagesWidget::~FlowImagesWidget()
{
}

void FlowImagesWidget::Reset(const QString patient_id, const QString study_insta)
{
    _patient_id = patient_id;
    emit SendPatientID(patient_id);
    _study_insta = study_insta;
    QList<cv::Mat> mats;

    // 从共享文件夹读取图像
    QStringList filenames;
    auto pixmaps = AcquireDcmFile(patient_id.toStdString(), filenames);

    std::vector<QPixmap> first_frame_of_per_dcm;
    // 从多帧dcm图像提取单帧图像，并将第一张设置为缩略影
#ifdef _DEBUG
    auto t1 = std::chrono::high_resolution_clock::now();
#endif
    for(unsigned int i = 0;i<pixmaps.size();i++)
    {

        first_frame_of_per_dcm.push_back(pixmaps[i].at(0));


    }
#ifdef _DEBUG
    auto t2 = std::chrono::high_resolution_clock::now();
    qDebug()<<"generate "<<pixmaps.size()<<" dcm:"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<"ms";
#endif

    for(unsigned int i = 0;i<first_frame_of_per_dcm.size();i++)
    {
        auto wid_img = CreateSingleImageWidgetFromQPixmap(first_frame_of_per_dcm[i]);
        wid_img->setParent(this);
        wid_img->SetFileName(filenames[i]);
        flowlayout->addWidget(wid_img);
    }

}

void FlowImagesWidget::mousePressEvent(QMouseEvent *event)
{

    this->setFocus();
    if(event->button()==Qt::LeftButton)
    {
        //FlowImagesWidget::mousePressEvent(event);

    }
    else if(event->button()==Qt::RightButton)
    {
        _pop_menu->exec(QCursor::pos());
    }

    QWidget::mousePressEvent(event);
}

void FlowImagesWidget::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    if(this->hasFocus())
    {
        // 选中所有图像
        if (event->key()==Qt::Key_A&&event->modifiers()==(Qt::ControlModifier))
        {
            //static int n = 0;
            //qDebug()<<n++;
            //this->SelectAllImage();
            QList<SingleImageWidget*> all_image = this->findChildren<SingleImageWidget*>();
            qDebug()<<all_image.size();
            for(auto img:all_image)
            {
                bool se = img->IsSelected();
                if(!se)
                {
                    img->SetSelected(true);
                }

            }
        }
    }
}

SingleImageWidget* FlowImagesWidget::CreateSingleImageWidgetFromQPixmap(const QPixmap &pix)
{
    auto image_widget = new SingleImageWidget;
    image_widget->SetImage(pix);
    return image_widget;
}

void FlowImagesWidget::CallDSAImg()
{
    QProcess pro;
    pro.startDetached("dsaimg.exe");
}

