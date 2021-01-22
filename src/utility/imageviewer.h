/************************************************************************
*
* 文件名：imageviewer.h
*
* 文件描述：基于Qt的图像浏览器，界面
*
* 创建人：TDL
*
* 时  间：2020/10/10
*
* 版本号：1.0
*
* 修改记录：
*
************************************************************************/
#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QList>
#include <QTimer>
#include <QLabel>

// 前置声明
class ImageViewerImpl;

namespace Ui {
class ImageViewer;
}

/**
 * @brief 播放器界面类
 */
class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

    void AddVideo(std::vector<QPixmap> video);

    void AddVideo(std::vector<std::vector<QPixmap>> videos);

    QPixmap GetCurrentFrame()const;


private slots:


    void on_btn_play_toggled(bool checked);

    void on_btn_next_video_clicked();

    void on_btn_last_video_clicked();



private:
    Ui::ImageViewer *ui;
    ImageViewerImpl *_image_viewer;
};


#endif // IMAGEVIEWER_H
