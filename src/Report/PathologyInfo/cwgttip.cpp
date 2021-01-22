#include "cwgttip.h"
#include "ui_cwgttip.h"

#include "cwidgetpathologyinfo.h"

CWgtTip::CWgtTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWgtTip)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    QString sBalance={"第一钝缘支/第二钝缘支/第三钝缘支/第一左左室后支/第二左左室后支/第三左左室后支/左后降支/中间支/"
                    "第一间隔支/第二间隔支/第三间隔支/第四间隔支/第一对角支/第二对角支/第三对角支/左前降支/"
                    "第一锐缘支"};

    QString sLeft={};

    m_slstBalance=sBalance.split('/');


    QString sBSCD="/无完全闭塞/<=3个月完全闭塞/>3个月完全闭塞";
    QStringList slstBSCD=sBSCD.split('/');
    this->InitComboBox(ui->m_cmbBSCD,slstBSCD);
    m_lstBBInfo.append(ui->m_cmbBSCD);
    QString sBBFW="/无/局限/节段/弥漫";
    QStringList slstBBFW=sBBFW.split('/');
    this->InitComboBox(ui->m_cmbBBFW,slstBBFW);
    m_lstBBInfo.append(ui->m_cmbBBFW);
    QString sBBLX="/再狭窄/原支架内再狭窄";
    QStringList slstBBLX=sBBLX.split('/');
    this->InitComboBox(ui->m_cmbBBLX,slstBBLX);
    m_lstBBInfo.append(ui->m_cmbBBLX);
    QString sBBXT="/同心/偏心";
    QStringList slstBBXT=sBBXT.split('/');
    this->InitComboBox(ui->m_cmbBBXT,slstBBXT);
    m_lstBBInfo.append(ui->m_cmbBBXT);
    QString sGHCD="/无/轻度/重度";
    QStringList slstGHCD=sGHCD.split('/');
    this->InitComboBox(ui->m_cmbGHCD,slstGHCD);
    m_lstBBInfo.append(ui->m_cmbGHCD);
    QString sTIMI="/0级/Ⅰ级/Ⅱ级/Ⅲ级";
    QStringList slstTIMI=sTIMI.split('/');
    this->InitComboBox(ui->m_cmbTIMI,slstTIMI);
    m_lstBBInfo.append(ui->m_cmbTIMI);
    this->CleanBBINfo();




    //connect(this, SIGNAL(UpdateTipSignal(QString)), parent, SLOT(UpdateTipSlot(QString)));

}

CWgtTip::~CWgtTip()
{
    delete ui;

    delete  m_lblTip;
    m_lblTip=NULL;
}

/**
 * @brief CWgtTip::SetVesselName
 * @param pName
 */
void CWgtTip::SetVesselName(QString pName)
{
    ui->m_cmbVessel->setCurrentText(pName);
}

void CWgtTip::SetVesselType(int pType)
{
    if(pType==CWidgetPathologyInfo::Right)
    {
        this->InitComboBox(ui->m_cmbVessel,m_slstBalance);
    }
    else if(pType==CWidgetPathologyInfo::Left)
    {
        this->InitComboBox(ui->m_cmbVessel,m_slstBalance);
    }
    else if(pType==CWidgetPathologyInfo::Balance)
    {
        this->InitComboBox(ui->m_cmbVessel,m_slstBalance);
    }
}

/**
 * @brief 设置当前要编辑的标签
 * @param pTip
 */
void CWgtTip::SetVesselLabel(QLabel *pTip)
{
    this->m_lblTip=pTip;
    this->m_lblTip->setStyleSheet("QLabel{background-color:rgb(0,120,220);color:white}");
    this->CleanBBINfo();
}

void CWgtTip::closeEvent(QCloseEvent *event)
{
    this->m_lblTip->setStyleSheet("QLabel{background-color:rgb(255,250,165);color:black}");
}

void CWgtTip::InitComboBox(QComboBox *pComboBox, QStringList pString)
{
    pComboBox->clear();
    for (int i=0;i<pString.size();i++)
    {
        pComboBox->addItem(pString[i]);
    }
}

/**
 * @brief CWgtTip::GetBBInfo
 * @return
 */
QString CWgtTip::GetBBInfo()
{
    QString sInfo=ui->m_cmbVessel->currentText()+":";

    if(ui->m_cmbBSCD->currentText()!="")
    {
        sInfo+=ui->m_cmbBSCD->currentText()+",";
    }
    if(ui->m_cmbBBFW->currentText()!="")
    {
        sInfo+=ui->m_cmbBBFW->currentText()+"病变,";
    }
    if(ui->m_cmbBBLX->currentText()!="")
    {
        sInfo+=ui->m_cmbBBLX->currentText()+"类型,";
    }
    if(ui->m_cmbBBXT->currentText()!="")
    {
        sInfo+=ui->m_cmbBBXT->currentText()+"形态,";
    }
    if(ui->m_cmbGHCD->currentText()!="")
    {
        sInfo+=ui->m_cmbGHCD->currentText()+"钙化,";
    }
    if(ui->m_cmbTIMI->currentText()!="")
    {
        sInfo+=ui->m_cmbTIMI->currentText()+"TIMI,";
    }

    sInfo.chop(1);
    return sInfo;
}

/**
 * @brief CWgtTip::on_m_cmbVessel_activated
 * @param index
 */
void CWgtTip::on_m_cmbVessel_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}

/**
 * @brief CWgtTip::UpdateVesselTip
 * @param pTip
 */
void CWgtTip::UpdateVesselTip(QString pTip)
{
    if(this->m_lblTip!=NULL)
    {
        this->m_lblTip->setText(pTip);
        this->m_lblTip->setWordWrap(1);
        this->m_lblTip->adjustSize();
    }
}

void CWgtTip::CleanBBINfo()
{
    ui->m_cmbBSCD->setCurrentIndex(0);
    ui->m_cmbBBFW->setCurrentIndex(0);
    ui->m_cmbBBLX->setCurrentIndex(0);
    ui->m_cmbBBXT->setCurrentIndex(0);
    ui->m_cmbGHCD->setCurrentIndex(0);
    ui->m_cmbTIMI->setCurrentIndex(0);
}

void CWgtTip::on_m_cmbBSCD_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}

void CWgtTip::on_m_cmbBBFW_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}

void CWgtTip::on_m_cmbBBLX_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}

void CWgtTip::on_m_cmbBBXT_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}

void CWgtTip::on_m_cmbGHCD_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}

void CWgtTip::on_m_cmbTIMI_activated(int index)
{
    this->UpdateVesselTip(this->GetBBInfo());
}
