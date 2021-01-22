/************************************************************************
*
* cpaintboard.h
*
* 文件描述：这里进行虚拟搭桥
*
* 创建人：LYH
*
* 时  间：2020-10-
*
* 版本号 1.0
*
************************************************************************/
#ifndef CPAINTBOARD_H
#define CPAINTBOARD_H

#include <iostream>
#include <vector>
using namespace std;

#include <QWidget>
#include <qpen.h>
#include <qbrush.h>
#include <qpainter.h>
#include <QMouseEvent>
#include <qfiledialog.h>
#include <QList>
#include <qlabel.h>

#include "cwgttip.h"

namespace Ui {
class CPaintBoard;
}

class CPaintBoard : public QWidget
{
    Q_OBJECT

public:
    explicit CPaintBoard(QWidget *parent = nullptr);
    ~CPaintBoard();
    enum Shape{Bridge,Line};

    void setShape(Shape);       //设置形状
    void setPen(QPen);          //设置画笔
    void setBrush(QBrush);      //设置画刷
    void setFillRule(Qt::FillRule);//设置填充模式

    //void paintEvent(QPaintEvent *event);//重画事件
    void mousePressEvent(QMouseEvent *event);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *event);//重写鼠标移动事件

    bool eventFilter(QObject *obj, QEvent *event);

    void labelPaintEvent();


    // 设置冠脉树图
    void SetVesselTree(int pType);

private slots:
    void on_m_btnCleanTip_clicked();
    //void UpdateTipSlot(QString pInfo);
    void on_m_btnCancelQ_clicked();

    void on_m_btnCleanQ_clicked();

    void on_m_btnCancelTip_clicked();

private:
    Ui::CPaintBoard *ui;

    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;

    bool m_bLIsPressed;
    bool m_bRIsPressed;
    bool m_bMIsPressed;

    QPixmap m_pixmapPci;//画布图片

    // 线条集合
    vector<vector<QPoint>> m_vLines;

    // 原图
    QImage *m_imgHash;

    // 均衡型颜色映射表
    QHash <QString,QString> m_hashColorBalance;

    QHash <QString,QString> m_hashColorRight;

    QHash <QString,QString> m_hashColorLeft;

    // 标签集
    QList<QLabel*>m_lstTip;

    // 标签对话框
    CWgtTip *m_wgtTip;
    QString m_sCurrVessel="";

    QLabel * IsExistTip(QString pColor);
    void UpDateTip();
};

#endif // CPaintBoard_H
