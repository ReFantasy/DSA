/************************************************************************
*
* 文件名：cwidgetpci.h
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
#ifndef CWIDGETREPORT_H
#define CWIDGETREPORT_H
//#pragma execution_character_set("utf-8")
#include <QWidget>
#include <qdebug.h>
#include <QString>
#include <QTime>
#include <QTime>

#include "cwidgetpatientinfo.h"
#include "cwidgetangiography.h"
#include "cwidgetpathologyinfo.h"
#include "cwidgetpci.h"
#include "cwidgetpatientstate.h"
#include "cwidgetreportpic.h"
#include "cwidgetadditionalinfo.h"
#include "cwidgetlabexamination.h"
#include "imageviewer.h"

#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>

#include <qmessagebox.h>
#include "printpreviewdialog.h"

#include "SQLDB.h"

namespace Ui {
class CWidgetReport;
}

class CWidgetReport : public QWidget
{
    Q_OBJECT

public:
    explicit CWidgetReport(QWidget *parent = nullptr);
    ~CWidgetReport();

private:
    Ui::CWidgetReport *ui;
    const QString sDateTimeStyle="yyyy-MM-dd hh:mm:ss.zzz";
    const QString sDateStyle="yyyy-MM-dd";
    const QString sTimeStyle="hh:mm:ss.zzz";

    // 各个子界面
    CWidgetPatientInfo *m_wgtPatientInfo;
    CWidgetAngiography *m_wgtAngiography;
    CWidgetPathologyInfo *m_wgtPathologyInfo;
    CWidgetPCI *m_wgtPCI;
    CWidgetPatientState *m_wgtPatientState;
    CWidgetReportPic *m_wgtReportPic;
    CWidgetAdditionalInfo *m_wgtAdditionalInfo;
    CWidgetLabExamination *m_wgtLabExamination;

    // 报告打印
    PrintPreviewDialog*m_wgtReportPrint;

    // 图像浏览器
    ImageViewer *m_wgtimageviewer;

    // 数据库
    QSqlDatabase m_dbStorage;
    QSqlDatabase m_dbReport;


    QString m_sIdPatient;

    int m_nPrePageId;

    enum EPageId{PatiInfoPage=0,AngiographyPage,PathologyInfoPage,PCIPage,PatiStatePage,ReportPicPage,AddInfoPage,LabExamPage};
public:

    void SetIdPatient(const QString pPatientId);
    void AddVideo(std::vector<std::vector<QPixmap>> videos);
    void SetViewerToReportPic();
    QString m_sSysCaseId;

    virtual void resizeEvent(QResizeEvent *event) override;
protected:
    void IsHavePatient(const QString pPatientId);
    void UpdateSubPage();

    void UpdateUIFromDB(int pPageId);
    void UpdateDBFromUI(int pPageId);

    void UpdateReport();

    QString DeleteRearLetter(QString pStr);
signals:
    void ExitReportWindow();
private slots:
    void on_m_btnWriteReport_clicked();
    void on_m_tbwReportPage_tabBarClicked(int index);



protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CWIDGETREPORT_H
