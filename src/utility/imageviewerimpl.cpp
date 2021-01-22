#include "imageviewerimpl.h"
#include <QDebug>

ImageViewerImpl::ImageViewerImpl(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);

    _cur_video_index = 0;
    _cur_frame_index = 0;
    _fps = 25;

    connect(timer, &QTimer::timeout, this, &ImageViewerImpl::DrawQPixmap);
}

void ImageViewerImpl::Start()
{
    if(_cur_video_index>=_video.size())
        return;

    // 设置计时器
    if(timer->isActive())
        timer->stop();
    timer->start(1000.0/_fps);
}

void ImageViewerImpl::Stop()
{
    timer->stop();
}

void ImageViewerImpl::SetLabel(QLabel *label)
{
    _label = label;
}

void ImageViewerImpl::SetFps(double fps)
{
    timer->stop();
    _fps = fps;
    timer->start(1.0/fps);
}

void ImageViewerImpl::NextVideo()
{
    if(_cur_video_index <_video.size()-1)
    {

        _cur_video_index++;
        _cur_frame_index = 0;
    }
}

void ImageViewerImpl::LastVideo()
{
    if(_cur_video_index>0)
    {
        _cur_video_index--;
        _cur_frame_index = 0;
    }
}

void ImageViewerImpl::AddVideo(std::vector<QPixmap> video)
{
    // 若之前没有视频文件，则将新加入的视频的第一帧显示到界面
    if(_video.empty())
    {
        auto pix = video[0];
        auto sz = _label->size();
        pix = pix.scaled({sz.width()-2, sz.height()-2}, Qt::KeepAspectRatio).copy();
        _label->setPixmap(pix);
    }


    _video.push_back(video);
}


void ImageViewerImpl::DrawQPixmap()
{
    // 图片播放完则重新开始
    if(_cur_frame_index>=_video[_cur_video_index].size())
    {
        _cur_frame_index = 0;
        return;
    }

    // 显示一帧图像
    auto pix = _video[_cur_video_index][_cur_frame_index++].copy();

    // pixmap适应label尺寸
    auto sz = _label->size();
    pix = pix.scaled({sz.width()-2, sz.height()-2}, Qt::KeepAspectRatio).copy();

    _label->setPixmap(pix);
}
