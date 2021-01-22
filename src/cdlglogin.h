/************************************************************************
*
* cdlglogin.h
*
* 文件描述：登录页面
*
* 创建人：LYH
*
* 时  间：2020-10-
*
* 版本号 1.0
*
************************************************************************/
#ifndef CDLGLOGIN_H
#define CDLGLOGIN_H

#include <iostream>
#include <string>
using namespace std;

#include <QDialog>
#include <qmessagebox.h>
#include <qstring.h>
#include <QSqlQuery>
#include <qdebug.h>
#include <qcryptographichash.h>

#include "SQLDB.h"
#include "cendecode.h"

namespace Ui {
class CDlgLogin;
}

class CDlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgLogin(QWidget *parent = nullptr);
    ~CDlgLogin();

    // 用户类型
    enum EUserType{SysManage=0,DepManage,User};
    // 获取当前用户的类型ID
    int GetUserType();

signals:
    void ShowSignal(int pType);
private slots:
    // 登录
    void on_m_btnLogin_clicked();
    // 取消
    void on_m_btnConsel_clicked();

    // 用户类型
    void on_m_radSysManage_clicked(bool checked);
    void on_m_radDepManage_clicked(bool checked);
    void on_m_radUser_clicked(bool checked);

    // 获取密码
    QString GetPassword(QString pCode);
private:
    // 获取身份
    int GetUserType(QString pType);
private:
    Ui::CDlgLogin *ui;
    // 登录失败次数
    int m_nLoginFailure;
    // 用户类别
    QString m_sUserType;
};

#endif // CDLGLOGIN_H
