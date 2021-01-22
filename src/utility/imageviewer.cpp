#include "imageviewer.h"
#include "ui_imageviewer.h"
#include "imageviewerimpl.h"
#include <QDebug>

ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    _image_viewer = new ImageViewerImpl(this);
    _image_viewer->SetLabel(ui->label);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::AddVideo(std::vector<QPixmap> video)
{
    _image_viewer->AddVideo(video);
}

void ImageViewer::AddVideo(std::vector<std::vector<QPixmap> > videos)
{
    for(auto v:videos)
    {
        AddVideo(v);
    }
}

QPixmap ImageViewer::GetCurrentFrame() const
{
    if(_image_viewer->_video.size()>0)
    {
        return _image_viewer->_video[_image_viewer->_cur_video_index][_image_viewer->_cur_frame_index];
    }
    else
    {
        return QPixmap{};
    }

}


void ImageViewer::on_btn_play_toggled(bool checked)
{
    if(checked)
    {
        _image_viewer->Start();
        ui->btn_play->setText(QString("暂停"));
    }
    else if(!checked)
    {
        _image_viewer->Stop();
        ui->btn_play->setText(QString("播放"));
    }
}

void ImageViewer::on_btn_next_video_clicked()
{
    _image_viewer->NextVideo();
    // 将画面显示为新视频的第一帧
    auto pix = _image_viewer->_video[_image_viewer->_cur_video_index][_image_viewer->_cur_frame_index++];
    auto sz = ui->label->size();
    pix = pix.scaled({sz.width()-2, sz.height()-2}, Qt::KeepAspectRatio).copy();
    _image_viewer->_label->setPixmap(pix);

}

void ImageViewer::on_btn_last_video_clicked()
{
    _image_viewer->LastVideo();
    // 将画面显示为新视频的第一帧
    auto pix = _image_viewer->_video[_image_viewer->_cur_video_index][_image_viewer->_cur_frame_index++];
    auto sz = ui->label->size();
    pix = pix.scaled({sz.width()-2, sz.height()-2}, Qt::KeepAspectRatio).copy();
    _image_viewer->_label->setPixmap(pix);
}


