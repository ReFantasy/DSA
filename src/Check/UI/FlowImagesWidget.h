/*
 * 类名：FlowImagesWidget
 * 描述：使用流布局管理器的Widget部件，用于展示选中病例的所有dcm图像
 * 作者：TDL
 * 时间：2020/08/22
 */
#ifndef FLOWIMAGESWIDGET_H
#define FLOWIMAGESWIDGET_H

#include <QWidget>
//#include <QMediaPlayer>
#include "opencv2/opencv.hpp"
#include <QMenu>

class SingleImageWidget;
class FlowLayout;

class FlowImagesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowImagesWidget(QWidget *parent = nullptr);
    virtual ~FlowImagesWidget()override;

    void Reset(const QString patient_id, const QString study_insta);

    // 右击鼠标弹出图像处理操作
    void mousePressEvent(QMouseEvent *event)override;

    // 键盘按键重载
    void keyPressEvent(QKeyEvent *event)override;

signals:
    void SendPatientID(QString);



private:
    SingleImageWidget* CreateSingleImageWidgetFromQPixmap(const QPixmap &pix);

    // 调用图像处理模块
    void CallDSAImg();

signals:

private:
    // 流布局管理器
    FlowLayout *flowlayout;

    QString _patient_id;

    QString _study_insta;

    QMenu *_pop_menu;

    QAction *_img_process_action;


};

#endif // FLOWIMAGESWIDGET_H
