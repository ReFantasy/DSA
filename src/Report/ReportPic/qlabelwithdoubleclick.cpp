#include "qlabelwithdoubleclick.h"
#include <QDebug>
#include <QMouseEvent>
#include <QSizePolicy>

QLabelWithDoubleClick::QLabelWithDoubleClick(QWidget *parent)
    :QLabel(parent)
{

    // toolTip
    this->setToolTip(QString("双击鼠标左键（右键）添加（删除）图像"));

    this->setScaledContents(true);


    this->setMinimumSize(QSize(200,200));

    QSizePolicy sizePolicy = this->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
    sizePolicy.setVerticalPolicy(QSizePolicy::Minimum);
    this->setSizePolicy(sizePolicy);


}

void QLabelWithDoubleClick::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 左键双击添加图像
    if(event->button()==Qt::LeftButton)
    {
        emit UpdateLabel(this);
    }
    else if(event->button()==Qt::RightButton)
    {
        this->clear();
    }

}
