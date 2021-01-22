#ifndef QLABELWITHDOUBLECLICK_H
#define QLABELWITHDOUBLECLICK_H

#include <QObject>
#include <QLabel>

class QLabelWithDoubleClick : public QLabel
{
    Q_OBJECT
public:
    QLabelWithDoubleClick(QWidget *parent = 0);

    // 重载双击事件 发送添加和删除图像信号
    void mouseDoubleClickEvent(QMouseEvent *event)override;

signals:
    void UpdateLabel(QLabelWithDoubleClick*);

};

#endif // QLABELWITHDOUBLECLICK_H
