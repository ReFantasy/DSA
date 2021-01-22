/************************************************************************
*
* 文件名：cwidgetlabexamination.h
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
#ifndef CWIDGETLABEXAMINATION_H
#define CWIDGETLABEXAMINATION_H
//#pragma execution_character_set("utf-8")
#include <QWidget>

#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>

namespace Ui {
class CWidgetLabExamination;
}

class CWidgetLabExamination : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetLabExamination(QWidget *parent = nullptr);
    ~CWidgetLabExamination();

private:
    Ui::CWidgetLabExamination *ui;
public:
    void SetSqDB();
    void UpdateSqDB();
     void SetIdPatient(const QString pIdPatient);
private slots:
    void on_checkBox_xcg_toggled(bool checked);
    void on_checkBox_ncg_toggled(bool checked);
    void on_checkBox_xysh_toggled(bool checked);
    void on_checkBox_xzgn_toggled(bool checked);
    void on_checkBox_xdt_toggled(bool checked);
};

#endif // CWIDGETLABEXAMINATION_H
