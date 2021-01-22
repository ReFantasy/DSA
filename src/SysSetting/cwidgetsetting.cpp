#include "cwidgetsetting.h"
#include "ui_cwidgetsetting.h"

CWidgetSetting::CWidgetSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetSetting)
{
    ui->setupUi(this);

    /*********** 初始化服务器配置 ************/
    ui->m_lineServer->setText(DsaConfig::GetDB()[0]);
    ui->m_linePort->setText(DsaConfig::GetDB()[1]);
    ui->m_lineDicomPos->setText(DsaConfig::GetImagePath());
    ui->m_lineDBUsername->setText(DsaConfig::GetDB()[2]);
    ui->m_lineDBPassword->setText(DsaConfig::GetDB()[3]);


    QStringList sHeaderUser = QString("Id,用户类别,用户名").simplified().split(",");
    m_modelSysUser= new QStandardItemModel();
    m_modelSysUser->setHorizontalHeaderLabels(sHeaderUser);
    //载入模型
    ui->m_tblvSysUser->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->m_tblvSysUser->setModel(m_modelSysUser);
    ui->m_tblvSysUser->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tblvSysUser->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_tblvSysUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tblvSysUser->horizontalHeader()->setStretchLastSection(1);
    ui->m_tblvSysUser->show();

    ui->m_lineUserPassword->setEchoMode(QLineEdit::Password);
    ui->m_lineDBPassword->setEchoMode(QLineEdit::Password);

    /******** 初始化用户名和密码提示 ********/
    ui->m_lblUserNameTip->clear();
    ui->m_lblUserPasswordTip->clear();
    m_bIsPassName=false;
    m_bIsPassCode=false;
}

CWidgetSetting::~CWidgetSetting()
{
    delete ui;
}



void CWidgetSetting::on_BtnMedTool_clicked()
{

}

/**
 * @brief 查看用户
 */
void CWidgetSetting::on_m_btnFind_clicked()
{

    this->FindSysUser();
}

/**
 * @brief CWidgetSetting::on_m_btnAddUser_clicked
 */
void CWidgetSetting::on_m_btnAddUser_clicked()
{
    if(!m_bIsPassName||!m_bIsPassCode)
    {
        QMessageBox::information(NULL,"提示","用户名或密码不正确",QMessageBox::Ok);
        return;
    }

    QString sUserType=ui->m_cmbUserType->currentText();
    QString sUserName=ui->m_lineUserName->text();
    QString sUserPassWord=ui->m_lineUserPassword->text();

    sUserPassWord=this->GetPassword(sUserPassWord);

    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sSqlUser="insert into User_T(Usertype,Username,Password) values('"+sUserType+"','"+sUserName+"','"+sUserPassWord+"')";
    sqlReport->exec(sSqlUser);

    this->FindSysUser();
}

void CWidgetSetting::on_m_btnDelUser_clicked()
{
    int nCurrId=ui->m_tblvSysUser->currentIndex().row();
    if(nCurrId>-1)
    {
        QString sUserId=m_lstSysUser[nCurrId].sId;

        QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
        QString sSqlUser="delete from User_T where ID='"+sUserId+"'";
        sqlReport->exec(sSqlUser);

        this->FindSysUser();
    }
}

/**
 * @brief CWidgetSetting::FindSysUser
 */
void CWidgetSetting::FindSysUser()
{
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    // 用户类型
    QString sUserType=ui->m_cmbFindType->currentText();
    // 用户名
    QString sUserName=ui->m_lineFindName->text();

    QString sSqlUser="select ID,Usertype,Username,Password from User_T";

    if(sUserType!=""||sUserName!="")
    {
        sSqlUser+=" where";
    }

    if(sUserType!="")
    {
        sSqlUser+=" Usertype='"+sUserType+"'";
    }

    if(sUserName!="")
    {
        if(sUserType!="")
        {
            sSqlUser+=" and Username like '%"+sUserName+"%'";
        }
        else
        {
            sSqlUser+=" Username like '%"+sUserName+"%'";
        }
    }

    m_lstSysUser.clear();
    sqlReport->exec(sSqlUser);
    while(sqlReport->next())
    {
        SSysUser sUser;
        sUser.sId=sqlReport->value(0).toString();
        sUser.sType=sqlReport->value(1).toString();
        sUser.sName=sqlReport->value(2).toString();
        sUser.sPassword=sqlReport->value(2).toString();
        m_lstSysUser.append(sUser);
    }

    delete sqlReport;
    sqlReport=NULL;

    InitModel(m_modelSysUser,m_lstSysUser);
}

/**
 * @brief CWidgetSetting::on_m_tblvSysUser_doubleClicked
 * @param index
 */
void CWidgetSetting::on_m_tblvSysUser_doubleClicked(const QModelIndex &index)
{
    QString sUserID=m_lstSysUser[index.row()].sId;
    QString sUserType=m_lstSysUser[index.row()].sType;
    QString sUserName=m_lstSysUser[index.row()].sName;
    QString sUserPassWord=m_lstSysUser[index.row()].sPassword;

    ui->m_lineUserID->setText(sUserID);
    ui->m_cmbUserType->setCurrentText(sUserType);
    ui->m_lineUserName->setText(sUserName);
    ui->m_lineUserPassword->setText(sUserPassWord);
}

/**
 * @brief CWidgetSetting::on_m_lineFindName_editingFinished
 */
void CWidgetSetting::on_m_lineFindName_editingFinished()
{
    this->FindSysUser();
}

void CWidgetSetting::InitModel(QStandardItemModel *pModel, QList<SSysUser> plstUser)
{
    // 清空
    for (int i=0;i<pModel->rowCount();i++)
    {
        pModel->removeRow(i);
    }
    pModel->setColumnCount(0);
    // 刷新
    for (int i=0;i<plstUser.size();i++)
    {
        pModel->setItem(i,0,new QStandardItem(plstUser[i].sId));
        pModel->setItem(i,1,new QStandardItem(plstUser[i].sType));
        pModel->setItem(i,2,new QStandardItem(plstUser[i].sName));
    }
}

/**
 * @brief CWidgetSetting::on_m_cmbFindType_activated
 * @param index
 */
void CWidgetSetting::on_m_cmbFindType_activated(int index)
{

}

void CWidgetSetting::on_m_btnReset_clicked()
{
    ui->m_lineServer->clear();
    ui->m_linePort->clear();
    ui->m_lineDicomPos->clear();
    ui->m_lineDBUsername->clear();
    ui->m_lineDBPassword->clear();
}

void CWidgetSetting::on_m_btnOk_clicked()
{
    QString sServer="";
    QString sPort="";
    QString sDicomPos="";
    QString sDBUsername="";
    QString sDBPassword="";
    sServer=ui->m_lineServer->text();
    sPort=ui->m_linePort->text();
    sDicomPos=ui->m_lineDicomPos->text();
    sDBUsername=ui->m_lineDBUsername->text();
    sDBPassword=ui->m_lineDBPassword->text();

    if(sServer==""||sPort==""||sDicomPos==""||sDBUsername==""||
            sDBPassword=="")
    {
        QMessageBox::information(NULL,"提示","信息不完整",QMessageBox::Ok);
        return;
    }
    DsaConfig::SetDB(sServer,sPort.toInt(),sDBUsername,sDBPassword);
    DsaConfig::SetSharedDcmFolder(sDicomPos);
}



/**
 * @brief CWidgetSetting::GetPassword
 * @param pCode
 * @return
 */
QString CWidgetSetting::GetPassword(QString pCode)
{
    QString sCode="";
    QByteArray byte_array;
    byte_array.clear();
    byte_array.append(pCode);
    QByteArray hash_byte_array = QCryptographicHash::hash(byte_array, QCryptographicHash::Md5);
    sCode = hash_byte_array.toHex();
    return sCode;
}

/**
 * @brief CWidgetSetting::on_m_lineUserName_textChanged
 * @param arg1
 */
void CWidgetSetting::on_m_lineUserName_textChanged(const QString &arg1)
{
    ui->m_lblUserNameTip->setText(m_sUserNameTipT);
    ui->m_lblUserNameTip->setStyleSheet("QLabel{color:black}");
}

/**
 * @brief CWidgetSetting::on_m_lineUserPassword_textChanged
 * @param arg1
 */
void CWidgetSetting::on_m_lineUserPassword_textChanged(const QString &arg1)
{
    ui->m_lblUserPasswordTip->setText(m_sUserPasswordTipT);
    ui->m_lblUserPasswordTip->setStyleSheet("QLabel{color:black}");
}

/**
 * @brief CWidgetSetting::mousePressEvent
 * @param event
 */
void CWidgetSetting::mousePressEvent(QMouseEvent *event)
{
    return QWidget::mousePressEvent(event);
}

/**
 * @brief CWidgetSetting::on_m_lineUserName_editingFinished
 */
void CWidgetSetting::on_m_lineUserName_editingFinished()
{
    QString sCode=ui->m_lineUserName->text();
    int nLengthCode=sCode.length();
    if(nLengthCode<4||nLengthCode>16)
    {
        ui->m_lblUserNameTip->setText(m_sUserNameTipF);
        ui->m_lblUserNameTip->setStyleSheet("QLabel{color:red}");
        m_bIsPassName=false;
        return;
    }
    int nFlag=0;
    for(int i=0;i<nLengthCode;i++)
    {
        if(sCode[i]>='0'&&sCode[i]<='9')
        {
            nFlag++;
        }
        if(sCode[i]>='a'&&sCode[i]<='z')
        {
            nFlag++;
        }
        if(sCode[i]>='A'&&sCode[i]<='Z')
        {
            nFlag++;
        }
        if(sCode[i]=='_')
        {
            nFlag++;
        }
    }
    if(nFlag==nLengthCode)
    {
        // 在这里查看数据表中有没有该用户
        QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

        QString sSqlUser="select count(*) from User_T where Username='"+sCode+"'";
        sqlReport->exec(sSqlUser);
        int nCount=0;
        while(sqlReport->next())
        {
            nCount=sqlReport->value(0).toInt();
        }
        delete sqlReport;
        sqlReport=NULL;
        if(nCount!=0)
        {
            QMessageBox::information(NULL,"提示","存在该用户",QMessageBox::Ok);
            m_bIsPassName=false;
            ui->m_lblUserNameTip->setText(m_sUserNameTipT);
            ui->m_lblUserNameTip->setStyleSheet("QLabel{color:black}");
            ui->m_lineUserName->clear();
        }
        else
        {
            ui->m_lblUserNameTip->clear();
            m_bIsPassName=true;
        }
    }
    else
    {
        ui->m_lblUserNameTip->setText(m_sUserNameTipF);
        ui->m_lblUserNameTip->setStyleSheet("QLabel{color:red}");
        m_bIsPassName=false;
    }
}

/**
 * @brief CWidgetSetting::on_m_lineUserPassword_editingFinished
 */
void CWidgetSetting::on_m_lineUserPassword_editingFinished()
{
    QString sCode=ui->m_lineUserPassword->text();
    int nLengthCode=sCode.length();
    if(nLengthCode<4||nLengthCode>16)
    {
        ui->m_lblUserPasswordTip->setText(m_sUserPasswordTipF);
        ui->m_lblUserPasswordTip->setStyleSheet("QLabel{color:red}");
        m_bIsPassCode=false;
        return;
    }
    ui->m_lblUserPasswordTip->clear();
    m_bIsPassCode=true;
}

/**
 * @brief CWidgetSetting::on_m_btnShowPassword_pressed
 */
void CWidgetSetting::on_m_btnShowPassword_pressed()
{
    ui->m_lineUserPassword->setEchoMode(QLineEdit::Normal);
}

/**
 * @brief CWidgetSetting::on_m_btnShowPassword_released
 */
void CWidgetSetting::on_m_btnShowPassword_released()
{
    ui->m_lineUserPassword->setEchoMode(QLineEdit::Password);
}

void CWidgetSetting::on_m_btnShowDBPassword_pressed()
{
    ui->m_lineDBPassword->setEchoMode(QLineEdit::Normal);
}

void CWidgetSetting::on_m_btnShowDBPassword_released()
{
    ui->m_lineDBPassword->setEchoMode(QLineEdit::Password);
}
