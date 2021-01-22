#include "cdlglogin.h"
#include "ui_cdlglogin.h"

/**
 * @brief CDlgLogin::CDlgLogin
 * @param parent
 */
CDlgLogin::CDlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgLogin),
    m_nLoginFailure(0)
{
    ui->setupUi(this);
    // 打开密码模式
    ui->m_lineUserPassword->setEchoMode(QLineEdit::Password);
    // 默认身份
    ui->m_radUser->setChecked(1);
    m_sUserType=ui->m_radUser->text();
}

CDlgLogin::~CDlgLogin()
{
    delete ui;
}

/**
 * @brief 获取用户类型Id
 * @return
 */
int CDlgLogin::GetUserType()
{
    return this->GetUserType(m_sUserType);
}

/**
 * @brief CDlgLogin::这里首先判断是不是超级用户，然后设置完成数据库之后
 */
void CDlgLogin::on_m_btnLogin_clicked()
{
    // 登录超过限制次数
    if(m_nLoginFailure>4)
    {
        QMessageBox::information(NULL,"提示","尝试次数超过限制",QMessageBox::Ok);
        this->close();
        return;
    }

    // 读取用户登录信息
    QString sUsername=ui->m_lineUserName->text();
    QString sUserPassword=ui->m_lineUserPassword->text();
    QString sUserType=this->m_sUserType;
    sUserPassword=this->GetPassword(sUserPassword);
    // 获取用户类型索引
    int nUserType=this->GetUserType(sUserType);
    ///lyh
    accept();
    emit ShowSignal(nUserType);

    if(sUsername=="")
    {
        m_nLoginFailure++;
        QMessageBox::information(NULL,"提示","请输入用户名",QMessageBox::Ok);
        return;
    }
    if(sUserPassword=="")
    {
        m_nLoginFailure++;
        QMessageBox::information(NULL,"提示","请输入用户密码",QMessageBox::Ok);
        return;
    }

    // 这里进行判断
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());
    QString sPassword="";
    QString sSqlUser="select Password from User_T where Username='"+sUsername+"' and Usertype='"+sUserType+"'";
    sqlReport->exec(sSqlUser);
    while (sqlReport->next())
    {
        sPassword=sqlReport->value(0).toString();
    }
    delete sqlReport;
    sqlReport=NULL;


    if(sUserPassword==sPassword)
    {
        accept();
        emit ShowSignal(nUserType);
    }
    else
    {
        m_nLoginFailure++;
        QMessageBox::information(NULL,"提示","用户名或密码错误",QMessageBox::Ok);
    }
}

/**
 * @brief CDlgLogin::on_m_btnConsel_clicked
 */
void CDlgLogin::on_m_btnConsel_clicked()
{
    this->close();
}

/**
 * @brief CDlgLogin::GetUserType
 * @param pType
 * @return
 */
int CDlgLogin::GetUserType(QString pType)
{
    if(pType=="系统管理员")
    {
        return SysManage;
    }
    else if(pType=="科室管理员")
    {
     return DepManage;
    }
    else if(pType=="普通用户")
    {
        return User;
    }
    return -1;
}

/**
 * @brief CDlgLogin::on_m_radSysManage_clicked
 * @param checked
 */
void CDlgLogin::on_m_radSysManage_clicked(bool checked)
{
    if(checked)
    {
        m_sUserType=ui->m_radSysManage->text();
    }
}

/**
 * @brief CDlgLogin::on_m_radDepManage_clicked
 * @param checked
 */
void CDlgLogin::on_m_radDepManage_clicked(bool checked)
{
    if(checked)
    {
        m_sUserType=ui->m_radDepManage->text();
    }
}

/**
 * @brief CDlgLogin::on_m_radUser_clicked
 * @param checked
 */
void CDlgLogin::on_m_radUser_clicked(bool checked)
{
    if(checked)
    {
        m_sUserType=ui->m_radUser->text();
    }
}

/**
 * @brief CDlgLogin::GetPassword
 * @param pCode
 * @return
 */
QString CDlgLogin::GetPassword(QString pCode)
{
    QString sCode="";
    QByteArray byte_array;
    byte_array.clear();
    byte_array.append(pCode);
    QByteArray hash_byte_array = QCryptographicHash::hash(byte_array, QCryptographicHash::Md5);
    sCode = hash_byte_array.toHex();
    return sCode;
}
