/************************************************************************
*
* 文件名：imageviewerimpl.h
*
* 文件描述：图像浏览器实现，多个图像为一组，可视为一个视频。
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
#ifndef IMAGEVIEWERIMPL_H
#define IMAGEVIEWERIMPL_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <vector>
#include <atomic>

class ImageViewerImpl : public QObject
{
    Q_OBJECT


    friend class ImageViewer;

public:
    explicit ImageViewerImpl(QObject *parent = nullptr);

    /**
     * @brief 循环播放当前视频
     */
    void Start();

    /**
     * @brief 停止播放
     */
    void Stop();

    /**
     * @brief 设置显示视频图像的控件
     * @param label
     */
    void SetLabel(QLabel *label);

    // 设置帧率
    void SetFps(double fps);

    /**
     * @brief 播放下一个视频
     */
    void NextVideo();

    /**
     * @brief 播放上一个视频
     */
    void LastVideo();

    /**
     * @brief 添加一个视频
     * @param video QPixmap数组
     */
    void AddVideo(std::vector<QPixmap> video);

private:
    /**
     * @brief 绘制视频图像到可绘制控件
     */
    void DrawQPixmap();

    QLabel *_label = nullptr;

private:
    // 视频文件
    std::vector<std::vector<QPixmap>> _video;

    // 当前视频索引
    std::atomic<int> _cur_video_index;

    // 当前帧索引
    std::atomic<int> _cur_frame_index;

    // 帧率
    std::atomic<int> _fps;

    // 计时器
    QTimer *timer;

};

#endif // IMAGEVIEWERIMPL_H
