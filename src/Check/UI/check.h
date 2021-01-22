/*
 * DB  数据库 一个病人可以有多个study 一个study对应多个series 一个series对应多个Image
 * 一次study 唯一对应ID（PatienID）
 * 每个报告的唯一ID也是PatienID
 *
 */
#ifndef CHECK_H
#define CHECK_H
#include <QWidget>
#include <QSqlQueryModel>
#include <QTreeWidget>
#include <QTableView>
#include <QStringList>
#include <QDate>
#include <QModelIndex>
#include <QList>
#include <QDebug>
#include <QDesktopWidget>

// 前置声明
class FlowImagesWidget;
namespace Ui {
class Check;
}

class CQuery;

class Check : public QWidget
{
    Q_OBJECT
    friend class CheckTest;  //友元类，用于测试

    friend class MainWindow;
public:
    explicit Check(QWidget *parent = nullptr);
    ~Check();

    void SetUserAuthority(int);



private slots:
    /**
     * @brief 查询操作
     */
    void on_checkButton_clicked();

    /**
     * @brief 开启和关闭 起始日期控件
     * @param arg1
     */
    void on_begin_study_date_on_stateChanged(int arg1);

    /**
     * @brief 开启和关闭 截至日期控件
     * @param arg1
     */
    void on_end_study_date_on_stateChanged(int arg1);

    void UpdateDicomImagesWidget(QModelIndex index);

    void on_btn_clear_query_condition_clicked();



    void GetSelectedPatientID(QString);

    void on_pushButton_4_clicked();

    void on_btn_sys_setting_clicked();

    void on_pushButton_3_clicked();

    void on_today_clicked();

    void on_yesterday_clicked();




    void on_btn_statistics_clicked();

    void on_btn_report_sys_clicked();

signals:
    // 查询结果信号
    void NewQuery(QList<QModelIndex>);
    void ShowReportUI(QString);

private:
    /**
     * @brief 读取检索输入信息
     * @return 检索条件列表
     */
    QStringList GenerateCheckCondition(QStringList con_list= {});

    void PCheck(QStringList con_list= {});

     void ShowReport();

private:
    Ui::Check *ui;
    CQuery *cquery;
    QStringList fields; //查询字段
    FlowImagesWidget *flow_image_widget = nullptr;

    QString _selected_patient_id;
    QString PatientID;

};

#endif // CHECK_H
