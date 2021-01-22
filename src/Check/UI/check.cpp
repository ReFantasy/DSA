#include "check.h"
#include "ui_check.h"
#include "SQLDB.h"
#include <QDebug>
#include "dcm2mat.h"
#include <string>
#include "SQLDB.h"
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QHeaderView>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QProcess>

#include "TreeWidgetWithCheckBox.h"
#include "FlowImagesWidget.h"
#include "TableWidget.h"
#include "cstatistical.h"
#include <cquery.h>


#include "cwidgetsetting.h"
#include "cwidgetmedtool.h"
#include "cwidgetdiscburner.h"
#include "cwidgetstatistical.h"
//#include "cwidgetreportprint.h"
#include "printpreviewdialog.h"
#include "cdlglogin.h"


Check::Check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Check)
{
    ui->setupUi(this);


    // 初始化
    cquery = new CQuery;
    ui->begin_study_date->setDate(QDateTime::currentDateTime().date());
    ui->end_study_date->setDate(QDateTime::currentDateTime().date());
    ui->begin_study_date->setEnabled(false);
    ui->end_study_date->setEnabled(false);

    fields<<"PatientID"<<"PatientNam"<<"PatientBir"<<"PatientSex"<<"StudyDate"<<"StudyTime"<<"AccessionN"
         << "ReferPhysi"<<"StudyID"<<"StudyDescr"<<"StudyInsta";

    QStringList pati_table;
    pati_table<<"造影号"<<"姓名"<<"出生日期"<<"性别"<<"检查日期"<<"检查时间"<<"住院号"
             << "术者"<<"检查号"<<"描述"<<"StudyInsta";

    // 设置表格
    ui->pati_table->setColumnCount(fields.size());
    ui->pati_table->setHorizontalHeaderLabels(pati_table);
    ui->pati_table->setSelectionBehavior(QAbstractItemView::SelectRows); // 每次选中一行
    ui->pati_table->setSelectionMode(QAbstractItemView::SingleSelection);// 不能多行选中
    ui->pati_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pati_table->hideColumn(10);

    // 布局设置
    ui->splitter_2->setStretchFactor(0,1);
    ui->splitter_2->setStretchFactor(1,4);

    // 查询更新时发送信号给影像柜和病例表格
    connect(this, &Check::NewQuery, ui->pati_list, &TreeWidgetWithCheckBox::QueryUpdate);
    connect(this, &Check::NewQuery, ui->pati_table, &TableWidget::QueryUpdate);


    // 病人列表复选框选中状态发生变化，发送信号给病人表格
    connect(ui->pati_list, &QTreeWidget::itemChanged, ui->pati_table, &TableWidget::UpdateTable);
    connect(ui->pati_table,&TableWidget::SendCurrentSelectedModelIndex,this,&Check::UpdateDicomImagesWidget);

    // 设置病人列表弹出菜单动作
    auto _pati_table_menu = ui->pati_table->GetMenu();
    _pati_table_menu->setStyleSheet("QMenu{border: 1px solid gray;background-color: white;}"
                                    "QMenu::item:selected {background-color: rgb(165, 224, 255);}");
    auto _report_action = new QAction;
    _report_action->setText(("撰写报告"));
    _pati_table_menu->addAction(_report_action);
    connect(_report_action, &QAction::triggered, this, &Check::ShowReport);

    //connect(flow_image_widget, &FlowImagesWidget::SendPatientID,this, &Check::GetSelectedPatientID);

    // TODO 发送视频文件
}

Check::~Check()
{
    delete ui;
    delete cquery;
}

void Check::SetUserAuthority(int auth)
{
    switch (auth)
    {
    case CDlgLogin::SysManage: // 系统管理员
        break;

    case CDlgLogin::DepManage: // 科室管理员
        ui->btn_sys_setting->setEnabled(false);
        break;

    case CDlgLogin::User: // 普通股用户
        ui->btn_report_sys->setEnabled(false);   // 禁用报告系统
        ui->btn_sys_setting->setEnabled(false);  // 禁用系统设置
        ui->btn_statistics->setEnabled(false);   // 禁止统计操作
        break;

    default:
        ui->btn_report_sys->setEnabled(false);
        ui->btn_sys_setting->setEnabled(false);
        break;
    }
}


void Check::ShowReport()
{
    auto row = ui->pati_table->currentRow();
    if(row>=0)
    {
        auto id = ui->pati_table->item(row, 0)->text();
        emit ShowReportUI(id);
    }
}


void Check::on_checkButton_clicked()
{
    PCheck({});
}


void Check::on_begin_study_date_on_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->begin_study_date->setEnabled(false);
    }
    else
    {
        ui->begin_study_date->setEnabled(true);
    }
}

void Check::on_end_study_date_on_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->end_study_date->setEnabled(false);
    }
    else
    {
        ui->end_study_date->setEnabled(true);
    }
}

void Check::UpdateDicomImagesWidget(QModelIndex index)
{
    // 删除幕布上所有对象包括图像widget和layout
    delete  ui->scrollAreaWidgetContents;

    // 创建图像显示部件
    auto wid = new FlowImagesWidget;
    flow_image_widget = wid;

    // 根据索引信息添加图像
    auto query = ((QSqlQueryModel*)index.model())->query();
    query.seek(index.row());
    wid->Reset(query.value("PatientID").toString(), query.value("StudyInsta").toString());
    PatientID = query.value("PatientID").toString();
    // 添加到可滚动区域
    ui->scrollAreaWidgetContents = wid;
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setFocus();
}

QStringList Check::GenerateCheckCondition(QStringList con_list)
{
    QStringList cc;
    // 检查号
    if(!ui->PatientID->text().isEmpty())
    {
        QString PatientID = QString("PatientID = '%1'").arg(ui->PatientID->text());
        cc.push_back(PatientID);
    }

    // 姓名
    if(!ui->PatientNam->text().isEmpty())
    {
        QString PatientNam = QString("PatientNam like '%%1%'").arg(( ui->PatientNam->text() ));
        cc.push_back(PatientNam);
    }

    // 开始日期
    if(ui->begin_study_date->isEnabled())
    {
        QString begin_study_date = QString("StudyDate >= '%1'").arg(ui->begin_study_date->date().toString("yyyyMMdd"));
        cc.push_back(begin_study_date);
    }
    // 截至日期
    if(ui->end_study_date->isEnabled())
    {
        QString end_study_date = QString("StudyDate <= '%1'").arg(ui->end_study_date->date().toString("yyyyMMdd"));
        cc.push_back(end_study_date);
    }

    // 住院号
    if(!ui->edt_accessionN->text().isEmpty())
    {
        QString accessionN = QString("AccessionN = '%1'").arg(ui->edt_accessionN->text());
        cc.push_back(accessionN);
    }

    for(auto e:con_list)
    {
        cc.push_back(e);
    }

    return cc;
}

void Check::PCheck(QStringList con_list)
{
    try
    {
        // 查询数据库
        QStringList check_condition_list = GenerateCheckCondition(con_list);
        cquery->SetTableName("DICOMStudies").SetField(fields).SetCondition(check_condition_list);
        cquery->Query(SQLDB::GetEvertopDB());

        // 发送查询结果索引
        QList<QModelIndex> index_list;
        for(int i = 0;i<cquery->GetQueryModel()->rowCount();i++)
        {
            index_list.push_back(cquery->GetQueryModel()->index(i,1, QModelIndex{}));
        }
        emit NewQuery(index_list);
    }
    catch(...)
    {
        LOG(ERROR)<<"Unknow error while querying";
    }
}

/**
 * @brief 清除界面查找信息
 */
void Check::on_btn_clear_query_condition_clicked()
{
    // 检查号
    ui->PatientID->clear();

    // 姓名
    ui->PatientNam->clear();


    // 开始日期
    ui->begin_study_date_on->setChecked(false);

    // 截至日期
    ui->end_study_date_on->setChecked(false);


    // 住院号
    ui->edt_accessionN->clear();


    // 医生
    //ui->edt_ReferPhysi->clear();


    // 患病种类
    //ui->edt_DiseaseType->clear();


    // Treatment
    // 治疗情况
    //ui->edt_Treatment->clear();

    on_checkButton_clicked();

}



void Check::GetSelectedPatientID(QString pid)
{
    _selected_patient_id = pid;
}


// 显示统计模块
void Check::on_btn_statistics_clicked()
{
    try
    {
        // 统计
        static CWidgetStatistical _statistical ;

        QDesktopWidget* wgtDesktop = QApplication::desktop();
        int nWidth = wgtDesktop->width() * 3 / 4;
        int nHeight = wgtDesktop->height() * 3 / 4;

        (&_statistical)->resize(nWidth,nHeight);
        (&_statistical)->setAttribute(Qt::WA_ShowModal, true);  // 模态窗口，阻塞父窗口
        (&_statistical)->show();
    }
    catch(...)
    {
        LOG(ERROR)<<"高级检索模块异常";
    }
}


// 物品管理
void Check::on_btn_report_sys_clicked()
{
    static CWidgetMedTool _med_tool;

    QDesktopWidget* wgtDesktop = QApplication::desktop();
    int nWidth = wgtDesktop->width() * 3 / 4;
    int nHeight = wgtDesktop->height() * 3 / 4;

    (&_med_tool)->resize(nWidth,nHeight);
    (&_med_tool)->setAttribute(Qt::WA_ShowModal, true);  // 模态窗口，阻塞父窗口
    (&_med_tool)->show();
}



// 光盘刻录
void Check::on_pushButton_4_clicked()
{
//    static CWidgetDiscBurner _disc_burner;
//    (&_disc_burner)->setAttribute(Qt::WA_ShowModal, true);  // 模态窗口，阻塞父窗口
//    (&_disc_burner)->show();


    QProcess process;
    process.execute("BurnCD.exe");
    process.waitForFinished();


}


// 系统设置
void Check::on_btn_sys_setting_clicked()
{
    static CWidgetSetting _system_setting_widget;

    (&_system_setting_widget)->setAttribute(Qt::WA_ShowModal, true);  // 模态窗口，阻塞父窗口
    (&_system_setting_widget)->show();
}



// 打印报告
void Check::on_pushButton_3_clicked()
{
    // 根据所选病人id查找病历号
    auto db = SQLDB::GetDfytCathLab();
    auto query_result = db.exec(QString("select * from PatiInfo_T where CaseID = '%1'").arg(PatientID));
    if(query_result.first())
    {
        auto sys_case_id = query_result.record().value("SysCaseID").toString();

        PrintPreviewDialog ppd;
        ppd.SetSysCaseId(sys_case_id);
        ppd.exec();
    }
}

// 查找今天病例信息
void Check::on_today_clicked()
{
    if(ui->begin_study_date_on->isChecked())
        ui->begin_study_date_on->setChecked(false);
    if(ui->end_study_date_on->isChecked())
        ui->end_study_date_on->setChecked(false);

    // 开始日期
    QString begin_study_date = QString("StudyDate >= '%1'").arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    QStringList cc;
    cc.push_back(begin_study_date);
    PCheck(cc);
}
// 查找昨天病例信息
void Check::on_yesterday_clicked()
{
    if(ui->begin_study_date_on->isChecked())
        ui->begin_study_date_on->setChecked(false);
    if(ui->end_study_date_on->isChecked())
        ui->end_study_date_on->setChecked(false);

    auto yesterday = QDateTime::currentDateTime().addDays(-1);
    // 开始日期
    QString begin_study_date = QString("StudyDate >= '%1'").arg(yesterday.toString("yyyyMMdd"));

    // 截至日期
    QString end_study_date = QString("StudyDate <= '%1'").arg(yesterday.toString("yyyyMMdd"));

    QStringList cc;
    cc.push_back(begin_study_date);
    cc.push_back(end_study_date);
    PCheck(cc);
}



