#ifndef CWIDGETSETTING_H
#define CWIDGETSETTING_H

#include <QWidget>
#include <qstring.h>
#include <qdebug.h>
#include <qsqlquery.h>
#include <QStandardItemModel>
#include <QDateTime>
#include <QCryptographicHash>
#include <qmessagebox.h>

#include "SQLDB.h"
#include "cendecode.h"
#include "dsaconfig.h"

struct SSysUser
{
    QString sId,sType,sName,sPassword;
};

namespace Ui {
class CWidgetSetting;
}

class CWidgetSetting : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetSetting(QWidget *parent = nullptr);
    ~CWidgetSetting();

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_BtnMedTool_clicked();

    void on_m_btnFind_clicked();

    void on_m_btnAddUser_clicked();

    void on_m_btnDelUser_clicked();

    void on_m_tblvSysUser_doubleClicked(const QModelIndex &index);

    void on_m_lineFindName_editingFinished();

    void on_m_cmbFindType_activated(int index);

    void on_m_btnReset_clicked();

    void on_m_btnOk_clicked();

    void on_m_lineUserName_editingFinished();
    void on_m_lineUserName_textChanged(const QString &arg1);

    void on_m_lineUserPassword_editingFinished();
    void on_m_lineUserPassword_textChanged(const QString &arg1);

    // 密码明文显示时间
    void on_m_btnShowPassword_pressed();
    void on_m_btnShowPassword_released();

    void on_m_btnShowDBPassword_pressed();

    void on_m_btnShowDBPassword_released();

private:
    Ui::CWidgetSetting *ui;
    // 用户统计结果
    QStandardItemModel* m_modelSysUser;
    QList<SSysUser>m_lstSysUser;
    QString GetPassword(QString pCode);

    // 用户名输入正确
    bool m_bIsPassName;
    // 密码输入正确
    bool m_bIsPassCode;

    // 用户名提示
    const QString m_sUserNameTipT="请输入4-16位字符，支持字母、数字及“_”";
    const QString m_sUserNameTipF="用户名格式不正确，请重新输入";
    // 密码提示
    const QString m_sUserPasswordTipT="请输入4-16位字符，支持字母、数字及常用符号";
    const QString m_sUserPasswordTipF="密码格式不正确，请重新输入";
protected:
    void InitModel(QStandardItemModel* pModel,QList<SSysUser>plstUser);
    // 查找系统用户
    void FindSysUser();
};

#endif // CWIDGETSETTING_H
