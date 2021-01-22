/************************************************************************
*
* cwgttip.h
*
* 文件描述：鼠标点击的时候弹出对话框，编辑
*
* 创建人：LYH
*
* 时  间：2020-10-
*
* 版本号 1.0
*
************************************************************************/
#ifndef CWGTTIP_H
#define CWGTTIP_H

#include <QWidget>
#include <qcombobox.h>
#include <qlabel.h>

namespace Ui {
class CWgtTip;
}

class CWgtTip : public QWidget
{
    Q_OBJECT

public:
    explicit CWgtTip(QWidget *parent = nullptr);
    ~CWgtTip();

    void SetVesselName(QString pName);
    void SetVesselType(int pType);
    void SetVesselLabel(QLabel *pTip);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    //void UpdateTipSignal(QString pInfo);
private slots:
    void on_m_cmbVessel_activated(int index);

    void on_m_cmbBSCD_activated(int index);

    void on_m_cmbBBFW_activated(int index);

    void on_m_cmbBBLX_activated(int index);

    void on_m_cmbBBXT_activated(int index);

    void on_m_cmbGHCD_activated(int index);

    void on_m_cmbTIMI_activated(int index);

private:
    Ui::CWgtTip *ui;
    QStringList m_slstRight;
    QStringList m_slstLeft;
    QStringList m_slstBalance;

    QLabel *m_lblTip=NULL;
    QList<QComboBox*>m_lstBBInfo;


    void UpdateVesselTip(QString pTip);
    void CleanBBINfo();
    void InitComboBox(QComboBox *pComboBox,QStringList pString);

    QString GetBBInfo();

};

#endif // CWGTTIP_H
