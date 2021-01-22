#include "cwgttargetvessel.h"
#include "ui_cwgttargetvessel.h"

CWgtTargetVessel::CWgtTargetVessel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWgtTargetVessel)
{
    ui->setupUi(this);
}

CWgtTargetVessel::~CWgtTargetVessel()
{
    delete ui;
}

/**
 * @brief CWgtTargetVessel::InitWidgetRadio
 * @param pWidget
 * @param pQuery
 */
void CWgtTargetVessel::InitWidgetRadBtn(QWidget *pWidget, QString pQuery)
{
    QObjectList lstObject=pWidget->children();
    for(int i=0;i<lstObject.length();i++)
    {
        if(lstObject.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(lstObject.at(i));
            QString sControl=aControl->text();
            if(sControl==pQuery)
            {
                aControl->setChecked(1);
                break;
            }
        }
    }
}

/**
 * @brief CWgtTargetVessel::InitWidgetCkbBtn
 * @param pWidget
 * @param pQuery
 */
void CWgtTargetVessel::InitWidgetCkbBtn(QWidget *pWidget, QString pQuery)
{
    QObjectList lstObject=pWidget->children();
    for(int i=0;i<lstObject.length();i++)
    {
        if(lstObject.at(i)->inherits("QCheckBox"))
        {
            auto aControl=qobject_cast<QCheckBox*>(lstObject.at(i));
            QString sControl=aControl->text();
            if(sControl==pQuery)
            {
                aControl->setChecked(1);
                break;
            }
        }
    }
}

QString CWgtTargetVessel::GetWidgetCkbBtn(QWidget *pWidget)
{
    QString sTemp="";
    QObjectList lstObject=pWidget->children();
    for(int i=0;i<lstObject.length();i++)
    {
        if(lstObject.at(i)->inherits("QCheckBox"))
        {
            auto aControl=qobject_cast<QCheckBox*>(lstObject.at(i));
            QString sControl=aControl->text();
            if(aControl->isChecked())
            {
                sTemp+=sControl+"/";
            }
        }
    }
    sTemp=sTemp.left(sTemp.length()-1);
    return sTemp;
}

/**
 * @brief CWgtTargetVessel::SetTagetVessel
 * @param pBXG
 */
void CWgtTargetVessel::SetTagetVessel(STargetVessel pBXG)
{
    ui->m_grpVesselName->setTitle(pBXG.sXGMC);
    ui->m_lineSQXZCD->setText(pBXG.sSQXZCD);
    ui->m_lineBBTD->setText(pBXG.sBBTD);
    ui->m_lineSQTIMI->setText(pBXG.sSQTIMI);
    ui->m_lineDSTGBB->setText(pBXG.sDSTGBB);
    ui->m_lineBBCYXZ->setText(pBXG.sBBCYXZ);
    ui->m_lineSHTIMI->setText(pBXG.sSHTIMI);

    if(pBXG.sXGNCS=="否")
    {
        this->InitWidgetRadBtn(ui->m_wgtXGNCSTF,"否");
        ui->m_wgtXGNCS->setEnabled(0);
    }
    else
    {
        this->InitWidgetRadBtn(ui->m_wgtXGNCSTF,"是");
        ui->m_wgtXGNCS->setEnabled(1);
        ui->m_lineMJXZ->setText(pBXG.sMJXZ);
        ui->m_lineZXGQ->setText(pBXG.sZXGQ);
    }

    if(pBXG.sXLCBFS=="否")
    {
        this->InitWidgetRadBtn(ui->m_wgtXLCBTF,"否");
        ui->m_wgtXLCB->setEnabled(0);

    }
    else
    {
        this->InitWidgetRadBtn(ui->m_wgtXLCBTF,"是");
        ui->m_wgtXLCB->setEnabled(1);
        ui->m_lineFFR->setText(pBXG.sXLCBFS);
    }


    if(pBXG.sSZBFZ=="否")
    {
        this->InitWidgetRadBtn(ui->m_wgtSZBFZTF,"否");
        ui->m_wgtSZBFZ->setEnabled(0);

    }
    else
    {
        this->InitWidgetRadBtn(ui->m_wgtSZBFZTF,"是");
        ui->m_wgtSZBFZ->setEnabled(1);
        QStringList slstBFZ=pBXG.sSZBFZ.split('/');
        for(int j=0;j<slstBFZ.size();j++)
        {
            this->InitWidgetCkbBtn(ui->m_wgtSZBFZ,slstBFZ[j]);
        }
    }


    if(pBXG.sTSQC=="否")
    {
        this->InitWidgetRadBtn(ui->m_wgtTSQCTF,"否");
        ui->m_wgtTSQC->setEnabled(0);

    }
    else
    {
        this->InitWidgetRadBtn(ui->m_wgtTSQCTF,"是");
        ui->m_wgtTSQC->setEnabled(1);
        QStringList slstTSQC=pBXG.sTSQC.split('/');
        for(int j=0;j<slstTSQC.size();j++)
        {
            this->InitWidgetCkbBtn(ui->m_wgtTSQC,slstTSQC[j]);
        }
    }
}

/**
 * @brief CWgtTargetVessel::GetTagetVessel
 * @return
 */
STargetVessel CWgtTargetVessel::GetTagetVessel()
{
    STargetVessel TargetVessel;

    if(ui->m_radXGNCSF->isChecked())
    {
        TargetVessel.sXGNCS="否";
    }
    else
    {
        TargetVessel.sXGNCS="是";
        TargetVessel.sMJXZ=ui->m_lineMJXZ->text();
        TargetVessel.sZXGQ=ui->m_lineZXGQ->text();
    }

    if(ui->m_radXLCBF->isChecked())
    {
        TargetVessel.sXLCBFS="否";
    }
    else
    {
        TargetVessel.sXLCBFS=ui->m_lineFFR->text();
    }

    if(ui->m_radSZBFZF->isChecked())
    {
        TargetVessel.sXLCBFS="否";
    }
    else
    {
        TargetVessel.sSZBFZ=this->GetWidgetCkbBtn(ui->m_wgtSZBFZ);
    }

    if(ui->m_radUSESpecailF->isChecked())
    {
        TargetVessel.sTSQC="否";
    }
    else
    {
        TargetVessel.sTSQC=this->GetWidgetCkbBtn(ui->m_wgtTSQC);
    }

    return TargetVessel;
}



void CWgtTargetVessel::on_m_radXGNCST_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtXGNCS->setEnabled(1);
    }
}

void CWgtTargetVessel::on_m_radXGNCSF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtXGNCS->setEnabled(0);
    }
}

void CWgtTargetVessel::on_m_radXLCBT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtXLCB->setEnabled(1);
    }
}

void CWgtTargetVessel::on_m_radXLCBF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtXLCB->setEnabled(0);
    }
}

void CWgtTargetVessel::on_m_radUSESpecailT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtTSQC->setEnabled(1);
    }
}

void CWgtTargetVessel::on_m_radUSESpecailF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtTSQC->setEnabled(0);
    }
}

void CWgtTargetVessel::on_m_radSZBFZT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtSZBFZ->setEnabled(1);
    }
}

void CWgtTargetVessel::on_m_radSZBFZF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtSZBFZ->setEnabled(0);
    }
}
