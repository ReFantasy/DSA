/************************************************************************
*
* 文件名：cwidgetpathologyinfo.h
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
#ifndef CWIDGETPATHOLOGYINFO_H
#define CWIDGETPATHOLOGYINFO_H


#include <QWidget>
#include <qdebug.h>
#include <qstring.h>
#include <qdir.h>
#include <QTableWidget>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qlineedit.h>

#include <QtSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include<QGroupBox>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QListWidget>
#include<SQLDB.h>
#include<QCheckBox>
#include<QList>
#include<QStringList>
#include<vector>
#include<QMessageBox>


#include <iostream>
#include <vector>
#include "isubreport.h"
#include "cpaintboard.h"


using namespace std;
namespace Ui {
class CWidgetPathologyInfo;
}

class CWidgetPathologyInfo : public QWidget,public ISubReport
{
    Q_OBJECT

public:
    explicit CWidgetPathologyInfo(QWidget *parent = nullptr);
    ~CWidgetPathologyInfo();

signals:
    void stateChanged();

private slots:
    void on_m_ckbCZBB_toggled(bool checked);
    void on_m_btnGX_clicked();
    void on_m_radLYKZ_clicked();
    void on_m_radYBBB_clicked();
    void on_m_radJC_clicked();
    void on_m_radGQ_clicked();
    void on_m_radLJFZW_toggled(bool checked);
    void on_m_radBZW_toggled(bool checked);
    void on_m_radQXG_toggled(bool checked);
    QString on_m_cmbQXGZ_currentTextChanged(const QString &arg1);
    QString on_m_cmbQXGY_currentTextChanged(const QString &arg1);
    QString on_m_cmbLJXGZ_currentTextChanged(const QString &arg1);
    QString on_m_cmbLJFZ_currentTextChanged(const QString &arg1);
    QString on_m_cmbSFBS_currentTextChanged(const QString &arg1);
    void on_m_radZQZ_toggled(bool checked);
    int on_m_spbZQZ_valueChanged(int arg1);
    int on_m_spbFWZZ_valueChanged(int arg1);
    int on_m_spbFWZY_valueChanged(int arg1);
    void on_m_radFWZ_toggled(bool checked);
    QString GetLineEditText(const QLineEdit *linEdit);
    void on_m_radYG_toggled(bool checked);
    void on_m_radZG_toggled(bool checked);
    void on_m_radBSS_toggled(bool checked);

    void on_m_tblBBInfo_doubleClicked(const QModelIndex &index);
    void on_m_btnSCInfo_clicked();
    void on_m_cmbQXGZ_currentIndexChanged(const QString &arg1);

    void on_m_tblBBInfo_clicked(const QModelIndex &index);
    

private:
    Ui::CWidgetPathologyInfo *ui;
    QListWidget *m_lWidget;

    /// lyh
    CPaintBoard *m_wgtPaintBoard;

    ///YL
    QStringList m_lYGAndZG;
    QStringList m_slstQXG;
    QStringList m_lLJXGSLFZ;//病变累及血管与受累分支信息列表
    //**********数据库传进来的参数**********//
    QString m_sSysCaseId;//数据库接口的id
    QStringList m_lBBXX;//病变信息列表
    QString m_sOneItem;//选择病变信息的某一条的item初始化整个按钮界面
    int m_nIndexToId[1000];//存放listwidget和数据库Id转换的列表
    int m_nSQLItemCount=0;//存放数据库中信息的总条数
    int m_nNumListItem=0;//病变信息的条目数量
    int m_nCurrenItemID;//当前点击item对应数据库中的ID
    int m_nLastID;//最新的数据库中的ID
    
    int m_sDeleteIndex=-1;//要删除的Item的Index

    //**********从界面存到数据库中的数据********//
    QString m_sIdLast;//最新的ID，QString类型的
    QString m_sIsHaveBB;//对应isHaveBB
    QString m_sstrConclusion;//对应bbRecord
    QString m_sstrBBXZ;//病变性质
    QString m_sstrBBWZ;//对应bbgm
    QString m_sstrSFBS;//对应BS
    QString m_sstrFW;//对应FW
    QString m_sstrBBLX;//对应BType
    QString m_sstrXT;//对应XT
    QString m_sstrGH;//对应GH
    QString m_sstrXS;//对应XS
    QString m_sstrXL;//对应TIMI
    QString m_sstrLJFZ;//对应FZ
    QString m_sstrBZ;//对应BZ
    QString m_sstrQXGZ;//对应bbzywz
    QString m_sstrQXGY;//对应bbxxwz
    QString m_sstrLJXG;//对应bbljwz
    int m_nZQZ;//对应max=min
    int m_nFWZZ;//对应min
    int m_nFWZY;//对应max
    bool isExistError=false;//判断是否存在应选未选的按钮
    QStringList m_lShowInfo;//存储Tableview要展示的信息


    ////////////////////////////////////////////////////
    ///<lyh
    // 模板
    QStandardItemModel* m_modelBBInfo;

    int m_nGMType=0;

public:
    void SetSqDB();
    void UpdateSqDB();
    void UpdateReportTable();

    // 冠脉供血类型
    enum EGMType{Right=0,Left=1,Balance=2};
    //**********向数据库插入SysCaseID的信息**********//
    void InsertSQL_SysCaseID();

    //**********向数据库插入是否病变信息信息**********//
    void UpdateSQL_isHaveBB();
    //**********向数据库插入病变性质的信息**********//
    void UpdateSQL_BBXZ();
    //**********向数据库插入病变冠脉信息**********//
    void UpdateSQL_bbgm();
    //**********向数据库插入病变累及位置信息**********//
    void UpdateSQL_bbljwz();
    //**********向数据库插入是否闭塞信息**********//
    void UpdateSQL_BS();
    //**********向数据库插入范围信息**********//
    void UpdateSQL_FW();
    //**********向数据库插入病变类型信息**********//
    void UpdateSQL_BType();
    //**********向数据库插入形态信息**********//
    void UpdateSQL_XT();
    //**********向数据库插入钙化信息**********//
    void UpdateSQL_GH();
    //**********向数据库插入血栓信息**********//
    void UpdateSQL_XS();
    //**********向数据库插入TIMI血流信息**********//
    void UpdateSQL_TIMI();
    //**********向数据库插入累及分支信息**********//
    void UpdateSQL_FZ();
    //**********向数据库插入备注信息**********//
    void UpdateSQL_BZ();
    //**********向数据库插入桥血管左侧第一个框信息**********//
    void UpdateSQL_bbzywz();
    //**********向数据库插入桥血管左侧第二个框信息**********//
    void UpdateSQL_bbxxwz();
    //**********向数据库插入病变累计血管信息**********//
    void UpdateSQL_bbljxg();
    //**********向数据库插入狭窄率信息**********//
    void UpdateSQL_xzl();
    //**********向数据库插入病变记录信息**********//
    void UpdateSQL_bbRocord();
    //**********获取已选择的radiobutton的名称***********//
    QString GetButtonText(const QGroupBox *grp);
    //**********判断grp中是否有应选而未选的radiobutton***********//
    bool GetButtonStatus(const QGroupBox *grp);
    //**********判断整个界面中是否有应选而未选的radiobutton***********//
    int CheckAllButtonStatus();
    //**********获取combobox的内容*************//
    QString GetComboboxText(const QGroupBox *grp);
    //设置listwidget的内容
    void SetListWidgetText(QListWidget *litw,QString str);
    //**********获取病变性质的按钮信息**********//
    void GetBBXZ_ButtonFromSqDB(QString str);
    //**********从数据库获取是否病变的按钮信息**********//
    void GetisHaveBB_ButtonFromSqDB(QString str);
    //**********获取病变冠脉的按钮信息**********//
    void Getbbgm_ButtonFromSqDB(QString str);
    //**********获取病变桥血管左侧的按钮信息**********//
    void GetQxgz_ComboboxFromSqDB(QString str);
    //**********获取病变桥血管右侧的按钮信息**********//
    void GetQxgy_ComboboxFromSqDB(QString str);
    //**********获取病变桥血管右侧的按钮信息**********//
    void GetLJXG_ComboboxFromSqDB(QString str);
    //**********获取是否闭塞的按钮信息**********//
    void GetBS_ButtonFromSqDB(QString str1,QString str2);
    //**********获取是否狭窄率的按钮信息**********//
    void GetXZL_ButtonFromSqDB(int strmin,int strmax);
    //**********获取是否范围的按钮信息**********//
    void GetFW_ButtonFromSqDB(QString str);
    //**********获取是否病变类型的按钮信息**********//
    void GetBType_ButtonFromSqDB(QString str);
    //**********获取是否形态的按钮信息**********//
    void GetXT_ButtonFromSqDB(QString str);
    //**********获取是否钙化的按钮信息**********//
    void GetGH_ButtonFromSqDB(QString str);
    //**********获取是否血栓的按钮信息**********//
    void GetXS_ButtonFromSqDB(QString str);
    //**********获取是否TIMI血流的按钮信息**********//
    void GetTIMI_ButtonFromSqDB(QString str);
    //**********获取是否累及分支的按钮信息**********//
    void GetFZ_ButtonFromSqDB(QString str);
    //**********获取是否备注的按钮信息**********//
    void GetBZ_ButtonFromSqDB(QString str);
    //**********获取病变信息的按钮信息**********//
    void GetbbRecord_ButtonFromSqDB(QString str);
    //**********获取是否范围的按钮信息**********//

    //**********初始化累及血管&受累分支&病变血管(右冠左冠)下拉菜单的项**********//
    void InitializeCmbsItem();
    //**********初始化病变血管(桥血管)下拉菜单的项**********//
    void UpdateQXGItem();
    //**********获取累及分支与受累分支下拉菜单项**********//
    QStringList GetCmbItemList(QString sCondition);
    //**********添加项至累及分支与受累分支下拉菜单**********//
    void AddItemToList(QStringList lItemList);
    virtual void SetSysCaseId(const QString pSysCaseId)override;
    virtual void UpdateUIFromDatabase()override;
    virtual void UpdateDatabaseFromUI()override;


    void InitQXGComboBox(bool checked);
    void InitYGComboBox(bool checked);
    void InitZGComboBox(bool checked);

    //lyh
    int GetGMGXType();

protected:

};

#endif // CWIDGETPATHOLOGYINFO_H
