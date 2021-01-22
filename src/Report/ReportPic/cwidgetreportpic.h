/************************************************************************
*
* 文件名：cwidgetreportpic.h
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
#ifndef CWIDGETREPORTPIC_H
#define CWIDGETREPORTPIC_H
//#pragma execution_character_set("utf-8")
#include <QWidget>

#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include "imageviewer.h"
#include "qlabelwithdoubleclick.h"
#include "isubreport.h"

namespace Ui {
class CWidgetReportPic;
}

class CWidgetReportPic : public QWidget, public ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetReportPic(QWidget *parent = nullptr);
    ~CWidgetReportPic();

    void SetImageViewer(const ImageViewer *viewer);

    /**
     * @brief 设置病例ID
     */
    virtual void SetSysCaseId(const QString)override;

    /**
     * @brief 从数据库请求数据更新界面信息
     */
    virtual void UpdateUIFromDatabase()override;

    /**
     * @brief 将界面修改信息写回数据库
     */
    virtual void UpdateDatabaseFromUI()override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::CWidgetReportPic *ui;
    QList<QLabelWithDoubleClick*> _label_list;

    const ImageViewer *_image_viewer;

    QString _patient_id;

    void UpdateLabel(QLabelWithDoubleClick*);

    void UpdateImageToDatabase();
    void UpdateImageFromDatabase();

};

#endif // CWIDGETREPORTPIC_H
