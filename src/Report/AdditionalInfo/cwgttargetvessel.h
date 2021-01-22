/************************************************************************
*
* cwgttargetvessel.h
*
* 文件描述：
*
* 创建人：LYH
*
* 时  间：2020-10-
*
* 版本号 1.0
*
************************************************************************/
#ifndef CWGTTARGETVESSEL_H
#define CWGTTARGETVESSEL_H

#include <QWidget>

struct STargetVessel
{
    QString sXGMC;
    QString sSQXZCD;
    QString sBBTD;
    QString sSQTIMI;
    QString sDSTGBB;
    QString sBBCYXZ;
    QString sSHTIMI;
    QString sXGNCS;
    QString sMJXZ;
    QString sZXGQ;
    QString sXLCBFS;
    QString sSZBFZ;
    QString sTSQC;
};

namespace Ui {
class CWgtTargetVessel;
}

class CWgtTargetVessel : public QWidget
{
    Q_OBJECT

public:
    explicit CWgtTargetVessel(QWidget *parent = nullptr);
    ~CWgtTargetVessel();

    void SetTagetVessel(STargetVessel pBXG);
     STargetVessel GetTagetVessel();
private slots:

     void on_m_radXGNCST_clicked(bool checked);
     void on_m_radXGNCSF_clicked(bool checked);

     void on_m_radXLCBT_clicked(bool checked);
     void on_m_radXLCBF_clicked(bool checked);

     void on_m_radUSESpecailT_clicked(bool checked);
     void on_m_radUSESpecailF_clicked(bool checked);

     void on_m_radSZBFZT_clicked(bool checked);
     void on_m_radSZBFZF_clicked(bool checked);

private:
    Ui::CWgtTargetVessel *ui;

    void InitWidgetRadBtn(QWidget *pWidget, QString pQuery);
    void InitWidgetCkbBtn(QWidget *pWidget, QString pQuery);
    QString GetWidgetCkbBtn(QWidget *pWidget);
};

#endif // CWGTTARGETVESSEL_H
