#include "cwgttargetpathology.h"
#include "ui_cwgttargetpathology.h"
#include "SQLDB.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QStandardItem>
#include <QDebug>

/**
 * @brief CWgtTargetPathology::CWgtTargetPathology
 * @param parent
 */
CWgtTargetPathology::CWgtTargetPathology(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWgtTargetPathology)
{
    ui->setupUi(this);

    /******** 初始化术后 ********/
    ui->m_grpSHQCA->hide();
    ui->m_grpSHFFR->hide();
    ui->m_grpSHOCT->hide();
    ui->m_grpSHIVUS->hide();

    /******** 初始化术前 ********/
    ui->m_grpSQQCA->hide();
    ui->m_grpSQFFR->hide();
    ui->m_grpSQOCT->hide();
    ui->m_grpSQIVUS->hide();

    /******** 初始化病变属性 ********/
    ui->m_radBBCJT->setChecked(1);
    ui->m_radWQBST->setChecked(1);

    ui->m_grpSZBFZ->hide();
}

/**
 * @brief CWgtTargetPathology::~CWgtTargetPathology
 */
CWgtTargetPathology::~CWgtTargetPathology()
{
    delete ui;
}

/**
 * @brief CWgtTargetPathology::InitComboBox
 * @param pComboBox
 * @param pQuery
 */
void CWgtTargetPathology::InitComboBox(QComboBox *pComboBox, QString pQuery)
{
    for(int i=0;i<pComboBox->count();i++)
    {
        QString sControl=pComboBox->itemText(i);
        QString sAnsTemp=pQuery;
        if(sControl==sAnsTemp)
        {
            pComboBox->setCurrentIndex(i);
            break;
        }
    }
}

/**
 * @brief CWgtTargetPathology::InitWidgetRadBtn
 * @param pWidget
 * @param pQuery
 */
void CWgtTargetPathology::InitWidgetRadBtn(QWidget *pWidget, QString pQuery)
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
 * @brief CWgtTargetPathology::InitWidgetCkbBtn
 * @param pWidget
 * @param pQuery
 */
void CWgtTargetPathology::InitWidgetCkbBtn(QWidget *pWidget, QString pQuery)
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

/**
 * @brief CWgtTargetPathology::GetWidgetCkbBtn
 * @param pWidget
 * @return
 */
QString CWgtTargetPathology::GetWidgetCkbBtn(QWidget *pWidget)
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
 * @brief CWgtTargetPathology::SetNewPathology
 * @param pJrqInfo
 * @param pJrhInfo
 */
void CWgtTargetPathology::SetNewPathology(SJrqInfo pJrqInfo,SJrhInfo pJrhInfo)
{
    ui->m_lineBBMC->setText(pJrqInfo.sBBWZ);

    this->InitComboBox(ui->m_cmbBBXG,pJrqInfo.sBBWZ);
    this->InitComboBox(ui->m_cmbBBFW,pJrqInfo.sBBFW);
    this->InitComboBox(ui->m_cmbBBXT,pJrqInfo.sBBXT);

    if(pJrqInfo.sBBCJ=="否")
    {
        this->InitWidgetRadBtn(ui->m_wgtBBCJ,"否");
        ui->m_cmbBBCJ->setEnabled(0);
    }
    else
    {
        this->InitWidgetRadBtn(ui->m_wgtBBCJ,"是");
        ui->m_cmbBBCJ->setEnabled(1);
        this->InitComboBox(ui->m_cmbBBCJ,pJrqInfo.sBBCJ);
    }

    this->InitComboBox(ui->m_cmbBBWX,pJrqInfo.sBBWX);
    this->InitComboBox(ui->m_cmbBBGH,pJrqInfo.sGH);
    this->InitComboBox(ui->m_cmbTIMI,pJrqInfo.sTIMI);

    if(pJrqInfo.sWQBS=="否")
    {
        this->InitWidgetRadBtn(ui->m_wgtWQBS,"否");
        ui->m_cmbWQBS->setEnabled(0);
    }
    else
    {
        this->InitWidgetRadBtn(ui->m_wgtWQBS,"是");
        ui->m_cmbWQBS->setEnabled(1);
        this->InitComboBox(ui->m_cmbWQBS,pJrqInfo.sWQBS);
    }

    this->InitComboBox(ui->m_cmbBBTD,pJrqInfo.sBBTD);
    this->InitComboBox(ui->m_cmbBBLX,pJrqInfo.sBBLX);
    this->InitComboBox(ui->m_cmbJDXGWQD,pJrqInfo.sJDXGWQ);

    ui->m_lineSqCZXGZJ->setText(pJrqInfo.sSQMCXGZJ);
    ui->m_lineSqBBBCD->setText(pJrqInfo.sSQMCBBBCD);
    ui->m_lineSqZXGQZJ->setText(pJrqInfo.sSQMCZXGQ);
    ui->m_lineSqXZCD->setText(pJrqInfo.sSQMCXZCD);


    if(pJrqInfo.sSQQCA=="否")
    {
        ui->m_ckbSQQCA->setChecked(0);
        ui->m_grpSQQCA->hide();
    }
    else
    {
        ui->m_ckbSQQCA->setChecked(1);
        ui->m_grpSQQCA->show();
    }

    if(pJrqInfo.sSQOCT=="否")
    {
        ui->m_ckbSQOCT->setChecked(0);
        ui->m_grpSQOCT->hide();
    }
    else
    {
        ui->m_ckbSQOCT->setChecked(1);
        ui->m_grpSQOCT->show();
    }

    if(pJrqInfo.sSQIVUS=="否")
    {
        ui->m_ckbSQIVUS->setChecked(0);
        ui->m_grpSQIVUS->hide();
    }
    else
    {
        ui->m_ckbSQIVUS->setChecked(1);
        ui->m_grpSQIVUS->show();
    }


    ///////////////////////////////////////////////////////////////////////
    if(pJrqInfo.sSQFFR=="否")
    {
        ui->m_ckbSQFFR->setChecked(0);
        ui->m_grpSQFFR->hide();
    }
    else
    {
        ui->m_ckbSQFFR->setChecked(1);
        ui->m_grpSQFFR->show();
        ui->m_lineSqFFR->setText(pJrqInfo.sSQFFR);
    }

    if(pJrqInfo.sSZBFZ=="否")
    {
        ui->m_ckbSZBFZ->setChecked(0);
        ui->m_grpSZBFZ->hide();
    }
    else
    {
        ui->m_ckbSZBFZ->setChecked(1);
        ui->m_grpSZBFZ->show();
        QStringList slstBFZ=pJrqInfo.sSZBFZ.split('/');
        for (int i=0;i<slstBFZ.size();i++)
        {
            this->InitWidgetCkbBtn(ui->m_wgtSZBFZ,slstBFZ[i]);
        }
    }

    /////////////////////////////////////////////////////////


    ui->m_lineShMCCZXGZJ->setText(pJrhInfo.sSHMCXGZJ);
    ui->m_lineShMCCYXZCD->setText(pJrhInfo.sSHMCXZCD);
    ui->m_lineShMCZXGQZJ->setText(pJrhInfo.sSHMCZXGQ);


    if(pJrhInfo.sSHQCA=="否")
    {
        ui->m_ckbSHQCA->setChecked(0);
        ui->m_grpSHQCA->hide();
    }
    else
    {
        ui->m_ckbSHQCA->setChecked(1);
        ui->m_grpSHQCA->show();
    }

    if(pJrhInfo.sSHOCT=="否")
    {
        ui->m_ckbSHOCT->setChecked(0);
        ui->m_grpSHOCT->hide();
    }
    else
    {
        ui->m_ckbSHOCT->setChecked(1);
        ui->m_grpSHOCT->show();
    }

    if(pJrhInfo.sSHIVUS=="否")
    {
        ui->m_ckbSHIVUS->setChecked(0);
        ui->m_grpSHIVUS->hide();
    }
    else
    {
        ui->m_ckbSHIVUS->setChecked(1);
        ui->m_grpSHIVUS->show();
    }

    if(pJrhInfo.sSHFFR=="否")
    {
        ui->m_ckbSHFFR->setChecked(0);
        ui->m_grpSHFFR->hide();
    }
    else
    {
        ui->m_ckbSHFFR->setChecked(1);
        ui->m_grpSHFFR->show();
        ui->m_lineShFFR->setText(pJrhInfo.sSHFFR);
    }
}

/**
 * @brief CWgtTargetPathology::SetSqOCT
 * @param pSqOCT
 */
void CWgtTargetPathology::SetSqOCT(SOCT pSqOCT)
{
    ui->m_lineSqOctEEM_CSA->setText(pSqOCT.sEEM_CSA);
    ui->m_lineSqOctStent_CSA->setText(pSqOCT.sStent_CSA);
    ui->m_lineSqOctLumen_CSA->setText(pSqOCT.sLumen_CSA);
    ui->m_lineSqOctEEM_Dmax->setText(pSqOCT.sEEM_Dmax);
    ui->m_lineSqOctStent_Dmax->setText(pSqOCT.sStent_Dmax);
    ui->m_lineSqOctLumen_Dmax->setText(pSqOCT.sLumen_Dmax);
    ui->m_lineSqOctEEM_Dmin->setText(pSqOCT.sEEM_Dmin);
    ui->m_lineSqOctStent_Dmin->setText(pSqOCT.sStent_Dmin);
    ui->m_lineSqOctLumen_Dmin->setText(pSqOCT.sLumen_Dmin);
}

/**
 * @brief CWgtTargetPathology::SetSqIVUS
 * @param pSqIVUS
 */
void CWgtTargetPathology::SetSqIVUS(SIVUS pSqIVUS)
{
    ui->m_lineSqIvusEEM_CSA->setText(pSqIVUS.sEEM_CSA);
    ui->m_lineSqIvusStent_CSA->setText(pSqIVUS.sStent_CSA);
    ui->m_lineSqIvusLumen_CSA->setText(pSqIVUS.sLumen_CSA);
    ui->m_lineSqIvusEEM_Dmax->setText(pSqIVUS.sEEM_Dmax);
    ui->m_lineSqIvusStent_Dmax->setText(pSqIVUS.sStent_Dmax);
    ui->m_lineSqIvusLumen_Dmax->setText(pSqIVUS.sLumen_Dmax);
    ui->m_lineSqIvusEEM_Dmin->setText(pSqIVUS.sEEM_Dmin);
    ui->m_lineSqIvusStent_Dmin->setText(pSqIVUS.sStent_Dmin);
    ui->m_lineSqIvusLumen_Dmin->setText(pSqIVUS.sLumen_Dmin);
}

/**
 * @brief CWgtTargetPathology::SetSqQCA
 * @param pSqQCA
 */
void CWgtTargetPathology::SetSqQCA(SSqQCA pSqQCA)
{
    ui->m_lineSqQcaCZXGZJ->setText(pSqQCA.sCZXGZJ);
    ui->m_lineSqQcaBBCD->setText(pSqQCA.sBBCD);
    ui->m_lineSqQcaXZCD->setText(pSqQCA.sXZCD);
    ui->m_lineSqQcaZXGQZJ->setText(pSqQCA.sZXGQZJ);
    ui->m_lineSqQcaQNCLXZCD->setText(pSqQCA.sQNCLXZCD);
    ui->m_lineSqQcaQNCLZXGQ->setText(pSqQCA.sQNCLZXGQ);
}

/**
 * @brief CWgtTargetPathology::SetShOCT
 * @param pShOCT
 */
void CWgtTargetPathology::SetShOCT(SOCT pShOCT)
{
    ui->m_lineShOctEEM_CSA->setText(pShOCT.sEEM_CSA);
    ui->m_lineShOctStent_CSA->setText(pShOCT.sStent_CSA);
    ui->m_lineShOctLumen_CSA->setText(pShOCT.sLumen_CSA);
    ui->m_lineShOctEEM_Dmax->setText(pShOCT.sEEM_Dmax);
    ui->m_lineShOctStent_Dmax->setText(pShOCT.sStent_Dmax);
    ui->m_lineShOctLumen_Dmax->setText(pShOCT.sLumen_Dmax);
    ui->m_lineShOctEEM_Dmin->setText(pShOCT.sEEM_Dmin);
    ui->m_lineShOctStent_Dmin->setText(pShOCT.sStent_Dmin);
    ui->m_lineShOctLumen_Dmin->setText(pShOCT.sLumen_Dmin);
}

/**
 * @brief CWgtTargetPathology::SetShIVUS
 * @param pShIVUS
 */
void CWgtTargetPathology::SetShIVUS(SIVUS pShIVUS)
{
    ui->m_lineShIvusEEM_CSA->setText(pShIVUS.sEEM_CSA);
    ui->m_lineShIvusStent_CSA->setText(pShIVUS.sStent_CSA);
    ui->m_lineShIvusLumen_CSA->setText(pShIVUS.sLumen_CSA);
    ui->m_lineShIvusEEM_Dmax->setText(pShIVUS.sEEM_Dmax);
    ui->m_lineShIvusStent_Dmax->setText(pShIVUS.sStent_Dmax);
    ui->m_lineShIvusLumen_Dmax->setText(pShIVUS.sLumen_Dmax);
    ui->m_lineShIvusEEM_Dmin->setText(pShIVUS.sEEM_Dmin);
    ui->m_lineShIvusStent_Dmin->setText(pShIVUS.sStent_Dmin);
    ui->m_lineShIvusLumen_Dmin->setText(pShIVUS.sLumen_Dmin);
}

/**
 * @brief CWgtTargetPathology::SetShQCA
 * @param pShQCA
 */
void CWgtTargetPathology::SetShQCA(SShQCA pShQCA)
{
    ui->m_lineShCZXGZJ->setText(pShQCA.sCZXGZJ);
    ui->m_lineShZJZXGQ->setText(pShQCA.sZJZXGQ);
    ui->m_lineShQNCLXZCD->setText(pShQCA.sQNCLXZCD);
    ui->m_lineShZJCYXZ->setText(pShQCA.sZJCYXZ);
    ui->m_lineShBBZXGQZJ->setText(pShQCA.sBBZXGQZJ);
    ui->m_lineShZJZCD->setText(pShQCA.sZJZCD);
    ui->m_lineShBBCYXZ->setText(pShQCA.sBBCYXZ);
    ui->m_lineShQNZXGQZJ->setText(pShQCA.sQNZXGQZJ);
    ui->m_lineShZJCDCD->setText(pShQCA.sZJCDCD);
}

/**
 * @brief CWgtTargetPathology::GetJrqInfo
 * @return
 */
SJrqInfo CWgtTargetPathology::GetJrqInfo()
{
    SJrqInfo JrqInfo;
    JrqInfo.sBBWZ=ui->m_cmbBBXG->currentText();
    JrqInfo.sBBFW=ui->m_cmbBBFW->currentText();
    JrqInfo.sBBXT=ui->m_cmbBBXT->currentText();

    if(ui->m_radBBCJF->isChecked())
    {
        JrqInfo.sBBCJ="否";
    }
    else
    {
        JrqInfo.sBBCJ=ui->m_cmbBBCJ->currentText();
    }

    JrqInfo.sBBWX=ui->m_cmbBBWX->currentText();
    JrqInfo.sGH=ui->m_cmbBBGH->currentText();
    JrqInfo.sTIMI=ui->m_cmbTIMI->currentText();

    if(ui->m_radWQBSF->isChecked())
    {
        JrqInfo.sWQBS="否";
    }
    else
    {
        JrqInfo.sWQBS=ui->m_cmbWQBS->currentText();
    }

    JrqInfo.sBBTD=ui->m_cmbBBTD->currentText();
    JrqInfo.sBBLX=ui->m_cmbBBLX->currentText();
    JrqInfo.sJDXGWQ=ui->m_cmbJDXGWQD->currentText();

    JrqInfo.sSQMCXGZJ=ui->m_lineSqCZXGZJ->text();
    JrqInfo.sSQMCBBBCD=ui->m_lineSqBBBCD->text();
    JrqInfo.sSQMCZXGQ=ui->m_lineSqZXGQZJ->text();
    JrqInfo.sSQMCXZCD=ui->m_lineSqXZCD->text();


    if(ui->m_ckbSQQCA->isChecked())
    {
        JrqInfo.sSQQCA="是";
    }
    else
    {
        JrqInfo.sSQQCA="否";
    }

    if(ui->m_ckbSQOCT->isChecked())
    {
        JrqInfo.sSQOCT="是";
    }
    else
    {
        JrqInfo.sSQOCT="否";
    }

    if(ui->m_ckbSQIVUS->isChecked())
    {
        JrqInfo.sSQIVUS="是";
    }
    else
    {
        JrqInfo.sSQIVUS="否";
    }


    if(ui->m_ckbSQFFR->isChecked())
    {
        JrqInfo.sSQFFR=ui->m_lineSqFFR->text();
    }
    else
    {
        JrqInfo.sSQFFR="否";
    }

    if(ui->m_ckbSZBFZ->isChecked())
    {
        JrqInfo.sSZBFZ=GetWidgetCkbBtn(ui->m_wgtSZBFZ);
    }
    else
    {
        JrqInfo.sSZBFZ="否";
    }


    return JrqInfo;
}

/**
 * @brief CWgtTargetPathology::GetJrhInfo
 * @return
 */
SJrhInfo CWgtTargetPathology::GetJrhInfo()
{
    SJrhInfo JrhInfo;

    JrhInfo.sBBWZ=ui->m_cmbBBXG->currentText();

    JrhInfo.sSHMCXGZJ=ui->m_lineShMCCZXGZJ->text();
    JrhInfo.sSHMCXZCD=ui->m_lineShMCCYXZCD->text();
    JrhInfo.sSHMCZXGQ=ui->m_lineShMCZXGQZJ->text();


    if(ui->m_ckbSHQCA->isChecked())
    {
        JrhInfo.sSHQCA="是";
    }
    else
    {
        JrhInfo.sSHQCA="否";
    }

    if(ui->m_ckbSHOCT->isChecked())
    {
        JrhInfo.sSHOCT="是";
    }
    else
    {
        JrhInfo.sSHOCT="否";
    }

    if(ui->m_ckbSHIVUS->isChecked())
    {
        JrhInfo.sSHIVUS="是";
    }
    else
    {
        JrhInfo.sSHIVUS="否";
    }


    if(ui->m_ckbSHFFR->isChecked())
    {
         JrhInfo.sSHFFR=ui->m_lineShFFR->text();
    }
    else
    {
        JrhInfo.sSHFFR="否";
    }

    return JrhInfo;
}



/**
 * @brief CWgtTargetPathology::GetSqOCT
 * @return
 */
SOCT CWgtTargetPathology::GetSqOCT()
{
    SOCT SqOct;
    SqOct.sEEM_CSA=ui->m_lineSqOctEEM_CSA->text();
    SqOct.sStent_CSA=ui->m_lineSqOctStent_CSA->text();
    SqOct.sLumen_CSA=ui->m_lineSqOctLumen_CSA->text();
    SqOct.sEEM_Dmax=ui->m_lineSqOctEEM_Dmax->text();
    SqOct.sStent_Dmax=ui->m_lineSqOctStent_Dmax->text();
    SqOct.sLumen_Dmax=ui->m_lineSqOctLumen_Dmax->text();
    SqOct.sEEM_Dmin=ui->m_lineSqOctEEM_Dmin->text();
    SqOct.sStent_Dmin=ui->m_lineSqOctStent_Dmin->text();
    SqOct.sLumen_Dmin=ui->m_lineSqOctLumen_Dmin->text();
    return SqOct;
}

/**
 * @brief CWgtTargetPathology::GetSqIVUS
 * @return
 */
SIVUS CWgtTargetPathology::GetSqIVUS()
{
    SIVUS SqIvus;
    SqIvus.sEEM_CSA=ui->m_lineSqIvusEEM_CSA->text();
    SqIvus.sStent_CSA=ui->m_lineSqIvusStent_CSA->text();
    SqIvus.sLumen_CSA=ui->m_lineSqIvusLumen_CSA->text();
    SqIvus.sEEM_Dmax=ui->m_lineSqIvusEEM_Dmax->text();
    SqIvus.sStent_Dmax=ui->m_lineSqIvusStent_Dmax->text();
    SqIvus.sLumen_Dmax=ui->m_lineSqIvusLumen_Dmax->text();
    SqIvus.sEEM_Dmin=ui->m_lineSqIvusEEM_Dmin->text();
    SqIvus.sStent_Dmin=ui->m_lineSqIvusStent_Dmin->text();
    SqIvus.sLumen_Dmin=ui->m_lineSqIvusLumen_Dmin->text();
    return SqIvus;
}

/**
 * @brief CWgtTargetPathology::GetSqQCA
 * @return
 */
SSqQCA CWgtTargetPathology::GetSqQCA()
{
    SSqQCA SqQca;
    SqQca.sCZXGZJ=ui->m_lineSqQcaCZXGZJ->text();
    SqQca.sBBCD=ui->m_lineSqQcaBBCD->text();
    SqQca.sXZCD=ui->m_lineSqQcaXZCD->text();
    SqQca.sZXGQZJ=ui->m_lineSqQcaZXGQZJ->text();
    SqQca.sQNCLXZCD=ui->m_lineSqQcaQNCLXZCD->text();
    SqQca.sQNCLZXGQ=ui->m_lineSqQcaQNCLZXGQ->text();
    return SqQca;
}

/**
 * @brief CWgtTargetPathology::GetShOCT
 * @return
 */
SOCT CWgtTargetPathology::GetShOCT()
{
    SOCT ShOct;
    ShOct.sEEM_CSA=ui->m_lineShOctEEM_CSA->text();
    ShOct.sStent_CSA=ui->m_lineShOctStent_CSA->text();
    ShOct.sLumen_CSA=ui->m_lineShOctLumen_CSA->text();
    ShOct.sEEM_Dmax=ui->m_lineShOctEEM_Dmax->text();
    ShOct.sStent_Dmax=ui->m_lineShOctStent_Dmax->text();
    ShOct.sLumen_Dmax=ui->m_lineShOctLumen_Dmax->text();
    ShOct.sEEM_Dmin=ui->m_lineShOctEEM_Dmin->text();
    ShOct.sStent_Dmin=ui->m_lineShOctStent_Dmin->text();
    ShOct.sLumen_Dmin=ui->m_lineShOctLumen_Dmin->text();
    return ShOct;
}

/**
 * @brief CWgtTargetPathology::GetShIVUS
 * @return
 */
SIVUS CWgtTargetPathology::GetShIVUS()
{
    SIVUS ShIvus;
    ShIvus.sEEM_CSA=ui->m_lineShIvusEEM_CSA->text();
    ShIvus.sStent_CSA=ui->m_lineShIvusStent_CSA->text();
    ShIvus.sLumen_CSA=ui->m_lineShIvusLumen_CSA->text();
    ShIvus.sEEM_Dmax=ui->m_lineShIvusEEM_Dmax->text();
    ShIvus.sStent_Dmax=ui->m_lineShIvusStent_Dmax->text();
    ShIvus.sLumen_Dmax=ui->m_lineShIvusLumen_Dmax->text();
    ShIvus.sEEM_Dmin=ui->m_lineShIvusEEM_Dmin->text();
    ShIvus.sStent_Dmin=ui->m_lineShIvusStent_Dmin->text();
    ShIvus.sLumen_Dmin=ui->m_lineShIvusLumen_Dmin->text();
    return ShIvus;
}

/**
 * @brief CWgtTargetPathology::GetShQCA
 * @return
 */
SShQCA CWgtTargetPathology::GetShQCA()
{
    SShQCA ShQca;
    ShQca.sCZXGZJ=ui->m_lineShCZXGZJ->text();
    ShQca.sZJZXGQ=ui->m_lineShZJZXGQ->text();
    ShQca.sQNCLXZCD=ui->m_lineShQNCLXZCD->text();
    ShQca.sZJCYXZ=ui->m_lineShZJCYXZ->text();
    ShQca.sBBZXGQZJ=ui->m_lineShBBZXGQZJ->text();
    ShQca.sZJZCD=ui->m_lineShZJZCD->text();
    ShQca.sBBCYXZ=ui->m_lineShBBCYXZ->text();
    ShQca.sQNZXGQZJ=ui->m_lineShQNZXGQZJ->text();
    ShQca.sZJCDCD=ui->m_lineShZJCDCD->text();
    return ShQca;
}


/**
 * @brief CWgtTargetPathology::on_m_ckbSQQCA_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSQQCA_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSQQCA->show();
    }
    else
    {
        ui->m_grpSQQCA->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSQIVUS_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSQIVUS_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSQIVUS->show();
    }
    else
    {
        ui->m_grpSQIVUS->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSQOCT_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSQOCT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSQOCT->show();
    }
    else
    {
        ui->m_grpSQOCT->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSQFFR_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSQFFR_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSQFFR->show();
    }
    else
    {
        ui->m_grpSQFFR->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSZBFZ_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSZBFZ_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSZBFZ->show();
    }
    else
    {
        ui->m_grpSZBFZ->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSHOCT_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSHOCT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSHOCT->show();
    }
    else
    {
        ui->m_grpSHOCT->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSHQCA_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSHQCA_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSHQCA->show();
    }
    else
    {
        ui->m_grpSHQCA->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSHIVUS_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSHIVUS_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSHIVUS->show();
    }
    else
    {
        ui->m_grpSHIVUS->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_ckbSHFFR_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_ckbSHFFR_clicked(bool checked)
{
    if(checked)
    {
        ui->m_grpSHFFR->show();
    }
    else
    {
        ui->m_grpSHFFR->hide();
    }
}

/**
 * @brief CWgtTargetPathology::on_m_radBBCJT_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_radBBCJT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbBBCJ->setEnabled(1);
    }
}

/**
 * @brief CWgtTargetPathology::on_m_radBBCJF_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_radBBCJF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbBBCJ->setEnabled(0);
    }
}

/**
 * @brief CWgtTargetPathology::on_m_radWQBST_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_radWQBST_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbWQBS->setEnabled(1);
    }
}

/**
 * @brief CWgtTargetPathology::on_m_radWQBSF_clicked
 * @param checked
 */
void CWgtTargetPathology::on_m_radWQBSF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cmbWQBS->setEnabled(0);
    }
}
