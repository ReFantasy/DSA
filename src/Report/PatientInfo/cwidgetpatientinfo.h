/************************************************************************
*
* 文件名：cwidgetpatientinfo.h
*
* 文件描述：病人资料设计师界面类
*         UI界面可以显示和修改病人的基本信息和部分治疗信息。界面类的构造函数初始化类的
*         相关成员数据，并从数据库中读取界面组件需要的相关信息。比如民族下拉框的名族种类。
*         通过UpdateUiPatiInfo(const QString patient_id)函数传递病人ID，并从数据
*         库中读取病人信息更新界面。
*
* 创建人：TDL
*
* 时  间：2020/10/04
*
* 版本号：1.0
*
* 修改记录：
*
************************************************************************/
#ifndef CWIDGETPATIENTINFO_H
#define CWIDGETPATIENTINFO_H
#include <QWidget>
#include <QSqlDatabase>
#include <QButtonGroup>
#include "patientinfo.h"
#include <QListWidgetItem>
#include <QDebug>
#include "isubreport.h"
#include "csurtype.h"

namespace Ui {
class CWidgetPatientInfo;
}

class CWidgetPatientInfo : public QWidget, public ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetPatientInfo(QWidget *parent = nullptr);
    ~CWidgetPatientInfo();

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


private:
    /**
     * @brief 在数据库中创建报告记录
     */
    void CreateReport(const QString patient_id);

    /**
     * @brief 初始化界面控件的可选数据
     */
    void InitWidData();


    /**
     * @brief 从数据库读取病人信息到界面
     * @param patient_id 病人ID
     */
    void UpdateUIFromDatabase(const QString patient_id);

    /**
     * @brief 将界面数据写回数据库
     * @param patient_id 病人ID
     */
    void UpdateDatabaseFromUI(const QString patient_id);

    // 结果输出
    QString GenerateOutput()const;


    void UpdateTextEdit();

private:
    // 按钮组
    QButtonGroup *bg_brlx = nullptr;  // 病人类型
    QButtonGroup *bg_mzff = nullptr;  // 麻醉方法
    QButtonGroup *bg_qgxh = nullptr;  // 鞘管型号


    QButtonGroup *bg_cgfx = nullptr;  // 插管方向
    QButtonGroup *bg_cgbw = nullptr;  // 插管部位
    QButtonGroup *bg_cgjg = nullptr;  // 插管结果

    QButtonGroup *bg_zybw = nullptr;  // 造影部位
    QButtonGroup *bg_zygg = nullptr;  // 造影规格
    QButtonGroup *bg_zyxs = nullptr;  // 造影形式

    QList<QButtonGroup*> bgs_zycc;   // 造影尺寸

    // 手术类型widget
    CSurType *_surg_type;



private:
    Ui::CWidgetPatientInfo *ui;
    //QString _patient_id;
    QString _sys_case_id;
    PatientInfo _patient_info;


private slots:
    void on_radioButton_20_clicked();

    void on_radioButton_24_clicked();

    void on_radioButton_23_clicked();

    void on_radioButton_22_clicked();

    void on_radioButton_21_clicked();

    void on_radioButton_25_clicked();

    void on_ZYBW_yes_toggled(bool checked);

    void on_PatiChName_textChanged(const QString &arg1);

    void on_CaseID_textChanged(const QString &arg1);

    void on_InsurNum_textChanged(const QString &arg1);

    void on_CaseNum_textChanged(const QString &arg1);

    void on_PatiDate_dateTimeChanged(const QDateTime &dateTime);

    void on_Room_currentIndexChanged(const QString &arg1);

    void on_InsurType_currentIndexChanged(const QString &arg1);

    void on_minzu_currentIndexChanged(const QString &arg1);

    void on_PatiSex_currentIndexChanged(const QString &arg1);

    void on_PatiAge_textChanged(const QString &arg1);

    void on_PatiDOB_dateTimeChanged(const QDateTime &dateTime);


    void on_radioButton_32_clicked();

    void on_radioButton_34_clicked();

    void on_radioButton_33_clicked();

    void on_radioButton_35_clicked();

    void on_PatiHeig_textChanged(const QString &arg1);

    void on_PatiWeig_textChanged(const QString &arg1);

    void on_TelNum_textChanged(const QString &arg1);

    void on_Address_textChanged(const QString &arg1);

    void on_ZipCodeP_textChanged(const QString &arg1);

    void on_ShadowType1_currentIndexChanged(const QString &arg1);

    void on_ShadowNum1_textChanged(const QString &arg1);

    void on_InRoomTime_dateTimeChanged(const QDateTime &dateTime);

    void on_ShadowLeixing_currentIndexChanged(const QString &arg1);

    void on_XTime_textChanged(const QString &arg1);

    void on_OutRoomTime_dateTimeChanged(const QDateTime &dateTime);

    void on_BeginTime_dateTimeChanged(const QDateTime &dateTime);




    void on_EndTime_dateTimeChanged(const QDateTime &dateTime);

    void on_SurName_currentIndexChanged(const QString &arg1);

    void on_InsductorName_currentIndexChanged(const QString &arg1);

    void on_Assis1_currentIndexChanged(const QString &arg1);

    void on_Assis2_currentIndexChanged(const QString &arg1);

    void on_Nursury1_currentIndexChanged(const QString &arg1);

    void on_Nursury2_currentIndexChanged(const QString &arg1);

    void on_Techno_currentIndexChanged(const QString &arg1);

    void on_MZJ_ldky_clicked();

    void on_MZJ_nsky_clicked();

    void on_MZJJL_valueChanged(int arg1);



    void on_QGXH_4F_clicked(bool checked);

    void on_QGXH_5F_clicked(bool checked);

    void on_QGXH_6F_clicked(bool checked);

    void on_QGXH_7F_clicked(bool checked);

    void on_QGXH_8F_clicked(bool checked);

    void on_cgjg_suc_toggled(bool checked);

    void on_pushButton_clicked();






    void on_CGLJ_cellDoubleClicked(int row, int column);

    void on_pushButton_2_clicked();

    void on_YYJL_result_itemDoubleClicked(QListWidgetItem *item);

    void on_ZYBW_lrgm_toggled(bool checked);

    void on_ZYBW_zxs_toggled(bool checked);

    void on_ZYBW_sdm_toggled(bool checked);

    void on_ZYBW_zdm_toggled(bool checked);

    void on_ZYBW_ldm_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_ZYDG_name_itemDoubleClicked(QListWidgetItem *item);

    void on_mz_toggled(bool checked);

    void on_jz_toggled(bool checked);

    void on_zhuyuan_toggled(bool checked);

    void on_zhuanyuan_toggled(bool checked);

    void on_ZYBW_no_clicked(bool checked);




    void on_LCZD_currentIndexChanged(const QString &arg1);
    void on_add_surtype_clicked();

    void UpdateSelectedTypes(QStringList _selected_types);


};
#endif // CWIDGETPATIENTINFO_H
