#include <QSqlRecord>
#include <QDebug>
#include <QObject>
#include <QButtonGroup>
#include "utility.h"
#include "cwidgetpatientinfo.h"
#include "ui_cwidgetpatientinfo.h"
#include "QSqlQuery"
#include "SQLDB.h"
//#include "easyloggingpp/easylogging++.h"
#include <QMessageBox>
#include <QModelIndex>
#include <QTextCodec>
#include <QListWidget>
#include "utility.h"


/**
 * @brief 构造并初始化
 */
CWidgetPatientInfo::CWidgetPatientInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetPatientInfo)
{
    ui->setupUi(this);

    // 设置按钮组

    bg_brlx = new QButtonGroup(this);
    bg_brlx->addButton(ui->mz);
    bg_brlx->addButton(ui->jz);
    bg_brlx->addButton(ui->zhuyuan);
    bg_brlx->addButton(ui->zhuanyuan);
    bg_brlx->setExclusive(true);  // 互斥

    bg_mzff = new QButtonGroup(this);
    bg_mzff->addButton(ui->MZJ_ldky);
    bg_mzff->addButton(ui->MZJ_nsky);
    bg_mzff->setExclusive(true);  // 互斥

    bg_qgxh = new QButtonGroup(this);
    bg_qgxh->addButton(ui->QGXH_4F);
    bg_qgxh->addButton(ui->QGXH_5F);
    bg_qgxh->addButton(ui->QGXH_6F);
    bg_qgxh->addButton(ui->QGXH_7F);
    bg_qgxh->addButton(ui->QGXH_8F);
    bg_qgxh->setExclusive(false); // 不互斥


    ui->CGLJ->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->CGLJ->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->CGLJ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bg_cgfx = new QButtonGroup(this);  // 插管方向
    bg_cgfx->addButton(ui->cgfx_left);
    bg_cgfx->addButton(ui->cgfx_right);
    bg_cgfx->setExclusive(true);  // 互斥

    bg_cgbw =  new QButtonGroup(this);  // 插管部位
    bg_cgbw->addButton(ui->cgbw_gdm);
    bg_cgbw->addButton(ui->cgbw_rdm);
    bg_cgbw->setExclusive(true);  // 互斥


    bg_cgjg =  new QButtonGroup(this);  // 插管结果
    bg_cgjg->addButton(ui->cgjg_suc);
    bg_cgjg->addButton(ui->cgjg_fail);
    bg_cgjg->setExclusive(true);  // 互斥





    // 造影部位
    bg_zybw = new QButtonGroup(this);
    bg_zybw->addButton(ui->ZYBW_ldm);
    bg_zybw->addButton(ui->ZYBW_sdm);
    bg_zybw->addButton(ui->ZYBW_zdm);
    bg_zybw->addButton(ui->ZYBW_zxs);
    bg_zybw->addButton(ui->ZYBW_lrgm);
    bg_zybw->setExclusive(false);

    // 造影规格
    bg_zygg = new QButtonGroup(this);
    bg_zygg->addButton(ui->Fr4);
    bg_zygg->addButton(ui->Fr5);
    bg_zygg->addButton(ui->Fr6);
    bg_zygg->addButton(ui->Fr7);
    bg_zygg->addButton(ui->Fr8);
    bg_zygg->setExclusive(true);  // 互斥

    // 造影形式
    bg_zyxs = new QButtonGroup(this);
    bg_zyxs->addButton(ui->zydg_jl, 0);
    bg_zyxs->addButton(ui->zydg_jr, 1);
    bg_zyxs->addButton(ui->zydg_al, 2);
    bg_zyxs->addButton(ui->zydg_ar, 3);
    bg_zyxs->addButton(ui->zydg_zw, 4);
    bg_zyxs->addButton(ui->zydg_myliti, 5);
    bg_zyxs->setExclusive(true);  // 互斥
    connect(bg_zyxs, QOverload<int>::of(&QButtonGroup::buttonPressed),
            [=](int id){
        ui->stackedWidget->setCurrentIndex(id);
    });

    // 造影尺寸
    for(int i = 0;i<4;i++)
        bgs_zycc.push_back(new QButtonGroup(this));
    bgs_zycc[0]->addButton(ui->acc30);
    bgs_zycc[0]->addButton(ui->acc35);
    bgs_zycc[0]->addButton(ui->acc40);
    bgs_zycc[0]->addButton(ui->acc45);
    bgs_zycc[0]->addButton(ui->acc50);
    bgs_zycc[0]->addButton(ui->acc60);

    bgs_zycc[1]->addButton(ui->bcc30);
    bgs_zycc[1]->addButton(ui->bcc35);
    bgs_zycc[1]->addButton(ui->bcc40);
    bgs_zycc[1]->addButton(ui->bcc45);
    bgs_zycc[1]->addButton(ui->bcc50);
    bgs_zycc[1]->addButton(ui->bcc60);

    bgs_zycc[2]->addButton(ui->ccc1);
    bgs_zycc[2]->addButton(ui->ccc2);
    bgs_zycc[2]->addButton(ui->ccc3);
    bgs_zycc[2]->addButton(ui->ccc4);

    bgs_zycc[3]->addButton(ui->dcc1);
    bgs_zycc[3]->addButton(ui->dcc2);
    bgs_zycc[3]->addButton(ui->dcc3);
    bgs_zycc[3]->addButton(ui->dcc4);


    // 手术类型
    _surg_type = new CSurType;
    connect(_surg_type, &CSurType::SendSelectedTypes, this, &CWidgetPatientInfo::UpdateSelectedTypes);



    // 从数据库读取控件所需的数据
    InitWidData();
}

/**
 * @brief 析构
 */
CWidgetPatientInfo::~CWidgetPatientInfo()
{
    delete ui;

    if(_surg_type)
    {
        delete _surg_type;
    }
}

void CWidgetPatientInfo::SetSysCaseId(const QString sys_case_id)
{
    _sys_case_id = sys_case_id;
    UpdateUIFromDatabase(_sys_case_id);
}

void CWidgetPatientInfo::UpdateUIFromDatabase()
{
    UpdateUIFromDatabase(_sys_case_id);
}

void CWidgetPatientInfo::UpdateDatabaseFromUI()
{
    UpdateDatabaseFromUI(_sys_case_id);
}

QString CWidgetPatientInfo::GenerateOutput() const
{
    QString out("患者取平卧位，常规消毒，铺巾");
    if(!_patient_info.MZJ.isEmpty())
    {
        out +=( QString("，以%1%%2局部麻醉。").arg(_patient_info.MZJJL, _patient_info.MZJ) );
    }
    else
    {
        out +="。";
    }

    if(!_patient_info.CGLJ.isEmpty())
    {
        out += "穿刺";
         for(auto str:_patient_info.CGLJ)
         {
             QString tmp_str;
             for(auto e:str)
             {
                 tmp_str +=e;
             }
             out+=tmp_str;
             out+="，";
         }
    }

    if(!_patient_info.QGXH.isEmpty())
    {
        out += "置入 ";
        for(auto e:_patient_info.QGXH)
        {
            out += (e+" ");
        }

        out += "导管鞘。";

    }

    if(!_patient_info.YYJL.isEmpty())
    {
        out += "经鞘管注入";
        for(auto e:_patient_info.YYJL)
        {
            out += (" "+e);
        }
        out+="。";
    }

    if(!_patient_info.ZYDG.isEmpty())
    {
        out += "选用 ";
        for(auto e:_patient_info.ZYDG)
        {
            out += (e+" ");
        }
        out+="号导管";
    }

    if(!_patient_info.ZYBW.isEmpty())
    {
        out += ",行 ";
        for(auto e:_patient_info.ZYBW)
        {
            out += (e+" ");
        }
        out+="造影。";
    }

    return out;
}

void CWidgetPatientInfo::UpdateTextEdit()
{
    ui->textEdit->clear();
    ui->textEdit->insertPlainText(GenerateOutput());
}

/**
 * @brief 如果已有报告记录则直接返回，否则创建新的报告记录
 */
void CWidgetPatientInfo::CreateReport(const QString patient_id)
{
    // 创建数据库查询对象
    //auto cathlab_db = SQLDB::GetDfytCathLab();
    //QSqlQuery cathlab_query(cathlab_db);

    /** 只读数据 没有则先生成 **/
    // [SysCaseID]  [PatiChName] [PatiDate] ,[PatiSex],[PatiDOB] ,[PatiAge]

    //cathlab_query.exec("select * from PatiInfo_T");

    //qDebug()<<cathlab_query.size();

}

void CWidgetPatientInfo::InitWidData()
{
    // 创建数据库查询对象
    auto cathlab_db = SQLDB::GetDfytCathLab();
    QSqlQuery cathlab_query(cathlab_db);

    cathlab_query.exec("select * from CathLab_T");

    // 导管室
    ui->Room->clear();
    cathlab_query.exec("select * from CathLab_T");
    while(cathlab_query.next())
    {
        auto record = cathlab_query.record();

        if(record.value("DelState").toString()!= "0")
        {
            ui->Room->addItem(record.value("CathLabName").toString());
        }
    }


    // 民族 ？？？
    ui->minzu->addItem("汉族");
    ui->minzu->addItem("其它民族");


    // 保险类型 DfytCathLab  InsuType
    cathlab_query.exec("select * from InsuType_T");
    ui->InsurType->clear();
    while(cathlab_query.next())
    {
        auto record = cathlab_query.record();
        ui->InsurType->addItem(record.value("InsuType").toString());
    }

    // 术者 & 外请专家 & Assis1 & Assis2
    cathlab_query.exec("select * from Staff_T");
    ui->SurName->clear();
    ui->InsductorName->clear();
    ui->Assis1->clear();
    ui->Assis2->clear();
    ui->Nursury1->clear();
    ui->Nursury2->clear();
    ui->Techno->clear();

    // 添加空选项
    ui->SurName->addItem("");
    ui->InsductorName->addItem("");
    ui->Assis1->addItem("");
    ui->Assis2->addItem("");
    ui->Nursury1->addItem("");
    ui->Nursury2->addItem("");
    ui->Techno->addItem("");

    while(cathlab_query.next())
    {
        auto record = cathlab_query.record();
        auto pos = record.value("StaffPosi").toString();

        if((record.value("StaffPosi").toString() != QString("护士")) && (record.value("StaffPosi").toString() != QString("技师")))
        {
            ui->SurName->addItem(record.value("StaffName").toString());
            ui->InsductorName->addItem(record.value("StaffName").toString());
            ui->Assis1->addItem(record.value("StaffName").toString());
            ui->Assis2->addItem(record.value("StaffName").toString());
        }


        if(record.value("StaffPosi").toString() == QString("护士"))
        {
            ui->Nursury1->addItem(record.value("StaffName").toString());
            ui->Nursury2->addItem(record.value("StaffName").toString());
        }
        if(record.value("StaffPosi").toString() == QString("技师"))
        {
            ui->Techno->addItem(record.value("StaffName").toString());
        }

    }

    // 初始化手术类型
    cathlab_query.exec("select * from SurgType_T");
    QStringList surg_types;
    while(cathlab_query.next())
    {
        auto record = cathlab_query.record();
        auto type = record.value("SurgTypeName").toString();
        surg_types.push_back(type);
    }
    _surg_type->SetSurgType(surg_types);

    // 临床诊断
    cathlab_query.exec("select * from CathBook_T");
    while(cathlab_query.next())
    {
        auto record = cathlab_query.record();
        if(record.value("LCZD").toString()!=QString{})
        {
            ui->LCZD->addItem(record.value("LCZD").toString());
        }
    }

    // 对比剂名称 类别编码9
    auto CathLabStock_db = SQLDB::GetCathLabStock();
    QSqlQuery CathLabStock_query(CathLabStock_db);
    CathLabStock_query.exec("select * from Lee_StockIndex");
    ui->ShadowType1->clear();
    while(CathLabStock_query.next())
    {
        auto record = CathLabStock_query.record();
        if(record.value("LeeCode").toString()=="9")
        {
            ui->ShadowType1->addItem(record.value("LeeName").toString());
        }
    }

    //对比剂类型 ？？？
    ui->ShadowLeixing->addItem("非离子型等渗");
    ui->ShadowLeixing->addItem("非离子型低渗");
    ui->ShadowLeixing->addItem("离子型");
}



void CWidgetPatientInfo::UpdateUIFromDatabase(const QString sys_case_id)
{
    /** 从dcm数据库读取数据 **/
    // [SysCaseID]  [PatiChName] [PatiDate] ,[PatiSex],[PatiDOB] ,[PatiAge]
    //    auto dcm_db = SQLDB::GetEvertopDB();
    //    QSqlQuery dcm_query(dcm_db);
    //    dcm_query.prepare("select * from DICOMStudies where PatientID = :id");
    //    dcm_query.bindValue(":id", patient_id);
    //    dcm_query.exec();
    //    dcm_query.next();
    //    auto dcm_record = dcm_query.record();




    // 从数据库读取病人信息
    auto db = SQLDB::GetDfytCathLab();
    QSqlQuery query(db);
    query.prepare("select * from PatiInfo_T where SysCaseID = :id");
    query.bindValue(":id", sys_case_id);
    query.exec();
    query.next();
    auto record = query.record();

    /*******************************************************************
     *
     * 更新界面用户信息
     *
     ******************************************************************/
    // 姓名
    ui->PatiChName->setText(record.value("PatiChName").toString());
    _patient_info.PatiChName = record.value("PatiChName").toString();
    // 住院号
    ui->CaseID->setText(record.value("CaseID").toString());
    _patient_info.CaseID = record.value("CaseID").toString();
    // 医保号
    ui->InsurNum->setText(record.value("InsurNum").toString());
    _patient_info.InsurNum = record.value("InsurNum").toString();
    // 门诊号
    ui->CaseNum->setText(record.value("CaseNum").toString());
    _patient_info.CaseNum = record.value("CaseNum").toString();
    // 手术日期
    ui->PatiDate->setDateTime(record.value("PatiDate").toDateTime());
    _patient_info.PatiDate = record.value("PatiDate").toDateTime();
    // 导管室
    ui->Room->setCurrentIndex(ui->Room->findText(record.value("Room").toString()));
    _patient_info.Room = record.value("Room").toString();
    // 保险类型
    ui->InsurType->setCurrentIndex(ui->InsurType->findText(record.value("InsurType").toString()));
    _patient_info.InsurType = record.value("InsurType").toString();
    // 手术编号
    ui->SysCaseID->setText(record.value("SysCaseID").toString());
    _patient_info.SysCaseID = record.value("SysCaseID").toString();
    // 性别
    ui->PatiSex->setCurrentIndex(ui->PatiSex->findText(record.value("PatiSex").toString()));
    _patient_info.PatiSex = record.value("PatiSex").toString();
    // 临床诊断
    ui->LCZD->setCurrentIndex(ui->LCZD->findText(record.value("LinChuang").toString()));
    _patient_info.LCZD = record.value("LinChuang").toString();
    // 对比剂类型
    ui->ShadowLeixing->setCurrentIndex(ui->ShadowLeixing->findText(record.value("ShadowType2").toString()));
    _patient_info.ShadowLeixing = record.value("ShadowType2").toString();
    // 年龄
    ui->PatiAge->setText(record.value("PatiAge").toString());
    _patient_info.PatiAge = record.value("PatiAge").toString();
    // 出生日期
    ui->PatiDOB->setDateTime(record.value("PatiDOB").toDateTime());
    _patient_info.PatiDOB = record.value("PatiDOB").toDateTime();
    // 身高
    ui->PatiHeig->setText(record.value("PatiHeig").toString());
    _patient_info.PatiHeig = record.value("PatiHeig").toString();
    // 体重
    ui->PatiWeig->setText(record.value("PatiWeig").toString());
    _patient_info.PatiWeig = record.value("PatiWeig").toString();
    // 电话
    ui->TelNum->setText(record.value("TelNum").toString());
    _patient_info.TelNum = record.value("TelNum").toString();
    // 地址
    ui->Address->setText(record.value("Address").toString());
    _patient_info.Address = record.value("Address").toString();
    // 邮编
    ui->ZipCodeP->setText(record.value("ZipCode").toString());
    _patient_info.ZipCode = record.value("ZipCode").toString();
    // 对比剂名称
    ui->ShadowType1->setCurrentIndex(ui->ShadowType1->findText(record.value("ShadowType1").toString()));
    _patient_info.ShadowType1 = record.value("ShadowType1").toString();
    // 对比剂用量
    ui->ShadowNum1->setText(record.value("ShadowNum1").toString());
    _patient_info.ShadowNum1 = record.value("ShadowNum1").toString();
    // 进导管室时间
    ui->InRoomTime->setDateTime(QStringToDateTime(record.value("InRoomTime").toString()));
    _patient_info.InRoomTime = record.value("InRoomTime").toDateTime();
    // 出导管室时间
    ui->OutRoomTime->setDateTime(QStringToDateTime(record.value("OutRoomTime").toString()));
    _patient_info.OutRoomTime = record.value("OutRoomTime").toDateTime();
    // 手术开始时间
    ui->BeginTime->setDateTime(QStringToDateTime(record.value("BeginTime").toString()));
    _patient_info.BeginTime = record.value("BeginTime").toDateTime();
    // 手术结束时间
    ui->EndTime->setDateTime(QStringToDateTime(record.value("EndTime").toString()));
    _patient_info.EndTime = record.value("EndTime").toDateTime();

    // 病人类型
    _patient_info.PatiStatus = record.value("PatiStatus").toString();
    if(_patient_info.PatiStatus == "住院") ui->zhuyuan->setChecked(true);
    if(_patient_info.PatiStatus == "转院") ui->zhuanyuan->setChecked(true);
    if(_patient_info.PatiStatus == "门诊") ui->mz->setChecked(true);
    if(_patient_info.PatiStatus == "急诊") ui->jz->setChecked(true);
    // X光照射时间
    ui->XTime->setText(record.value("XTime").toString());
    _patient_info.XTime = record.value("XTime").toString();

    // 造影号
    ui->zyhao->setText(record.value("CaseID").toString());

    ui->SurName->setCurrentIndex(ui->SurName->findText(record.value("SurName").toString()));
    _patient_info.SurName = record.value("SurName").toString();

    ui->InsductorName->setCurrentIndex(ui->InsductorName->findText(record.value("InsductorName").toString()));
    _patient_info.InsductorName = record.value("InsductorName").toString();

    ui->Assis1->setCurrentIndex(ui->Assis1->findText(record.value("Assis1").toString()));
    _patient_info.Assis1 = record.value("Assis1").toString();

    ui->Assis2->setCurrentIndex(ui->Assis2->findText(record.value("Assis2").toString()));
    _patient_info.Assis2 = record.value("Assis2").toString();

    ui->Nursury1->setCurrentIndex(ui->Nursury1->findText(record.value("Nursury1").toString()));
    _patient_info.Nursury1 = record.value("Nursury1").toString();

    ui->Nursury2->setCurrentIndex(ui->Nursury2->findText(record.value("Nursury2").toString()));
    _patient_info.Nursury2 = record.value("Nursury2").toString();

    ui->Techno->setCurrentIndex(ui->Techno->findText(record.value("Techno").toString()));
    _patient_info.Techno = record.value("Techno").toString();

    // 手术类型
    ui->SurType->clear();
    auto SSLX = record.value("SurType").toString();
    auto SSLXs = Split(SSLX, '#'); //
    for(auto e:SSLXs)
    {
        if(SSLXs.isEmpty())break;
        e = e.simplified();
        ui->SurType->setText(ui->SurType->text()+"\\"+e);
        _patient_info.SurType.push_back(e);
    }


    // 获取手术编号 SysCaseID
    QString syscaseid = record.value("SysCaseID").toString();
    query.prepare("select * from BB_ZYSJ where SysCaseID = :syscaseid");
    query.bindValue(":syscaseid", syscaseid);
    query.exec();
    query.next();
    record = query.record();

    // 麻醉方法
    auto MZJ = record.value("MZJ").toString();
    _patient_info.MZJ = MZJ;
    for(auto &e:bg_mzff->buttons())
    {
        if(e->text()==MZJ)
        {
            e->setChecked(true);
            break;
        }
    }

    auto MZJJL = record.value("MZJJL").toString();
    _patient_info.MZJJL = MZJJL;
    ui->MZJJL->setValue(MZJJL.toInt());

    // 设置鞘管型号
    auto QGXH = record.value("QGXH").toString();
    auto QGXHs = QGXH.split('#'); // '\\'
    for(auto e:QGXHs)
    {
        e = e.simplified();
        for(auto &f:bg_qgxh->buttons())
        {
            if(f->text()==e)
            {
                f->setChecked(true);
                _patient_info.QGXH.push_back(f->text());
            }
        }
    }



    // 插管
    auto CGLJ = record.value("CGLJ").toString();
    auto CGLJs = Split(CGLJ,'#'); // '\\'
    for(auto e:CGLJs)
    {
        if(e.isEmpty())continue;

        //添加新行
        ui->CGLJ->insertRow(ui->CGLJ->rowCount());
        int rowIdx = ui->CGLJ->rowCount()-1;

        auto cglj = Split(e,'\\');
        cglj.removeDuplicates();

        _patient_info.CGLJ.push_back(cglj);
        QTableWidgetItem *item0 = new QTableWidgetItem(cglj[0]+cglj[1]);
        QTableWidgetItem *item1 = new QTableWidgetItem(cglj[2]);
        QTableWidgetItem *item2 = new QTableWidgetItem();
        if(cglj.size()==4)
            item2->setData(Qt::DisplayRole, cglj[3]);
        ui->CGLJ->setItem(rowIdx,0,item0);
        ui->CGLJ->setItem(rowIdx,1,item1);
        ui->CGLJ->setItem(rowIdx,2,item2);
    }

    // 用药记录
    auto YYJL = record.value("YYJL").toString();
    auto YYJLs = Split(YYJL,'#'); // '\\'
    for(auto e:YYJLs)
    {
        _patient_info.YYJL.push_back(e);
        ui->YYJL_result->addItem(e);
    }

    // 造影手术
    auto ZYBW = record.value("ZYBW").toString();
    auto ZYBWs = Split(ZYBW,'#'); // '\\'
    if(!ZYBWs.isEmpty()){
        ui->ZYBW_yes->setChecked(true);
    }
    else{
        ui->ZYBW_no->setChecked(true);
    }

    _patient_info.ZYBW.clear();
    for(auto e:ZYBWs)
    {
        e = e.simplified();
        for(auto &f:bg_zybw->buttons())
        {
            if(f->text()==e)
            {
                f->setChecked(true);
                //_patient_info.ZYBW.push_back('#'+f->text());
            }
        }
    }

    // 造影导管
    auto ZYDG = record.value("ZYDG").toString();
    auto ZYDGs = Split(ZYDG,'#'); // '\\'
    for(auto e:ZYDGs)
    {
        _patient_info.ZYDG.push_back(e);
        ui->ZYDG_name->addItem(e);
    }

    UpdateTextEdit();

}

void CWidgetPatientInfo::UpdateDatabaseFromUI(const QString sys_case_id)
{
    // 从数据库读取病人信息
    auto db = SQLDB::GetDfytCathLab();
    QSqlQuery query_base_info(db);

    // 创建更新语句
    auto statement = QString("UPDATE PatiInfo_T Set "
                             "InsurNum = :InsurNum,"               // 医保号
                             "CaseNum = :CaseNum,"                 // 门诊号
                             "PatiDate = :PatiDate,"                // 手术日期
                             "Room = :Room,"                        // 导管室
                             "InsurType = :InsurType,"               // 保险类型
                             "PatiSex = :PatiSex,"               // 性别
                             "PatiHeig = :PatiHeig,"
                             "PatiAge = :PatiAge,"
                             "PatiDOB = :PatiDOB,"
                             "PatiWeig = :PatiWeig,"
                             "PatiBSA = :PatiBSA,"
                             "TelNum = :TelNum,"
                             "Address = :Address,"
                             "ZipCode = :ZipCode,"
                             "ShadowType1 = :ShadowType1,"
                             "ShadowNum1 = :ShadowNum1,"
                             "InRoomTime = :InRoomTime,"
                             "OutRoomTime = :OutRoomTime,"
                             "BeginTime = :BeginTime,"
                             "EndTime = :EndTime,"
                             "XTime = :XTime,"
                             "SurName = :SurName,"
                             "InsductorName = :InsductorName,"
                             "Assis1 = :Assis1,"
                             "Assis2 = :Assis2,"
                             "Nursury1 = :Nursury1,"
                             "Nursury2 = :Nursury2,"
                             "Techno = :Techno,"
                             "SurType = :SurType,"
                             "LinChuang = :LinChuang,"
                             "ShadowType2 = :ShadowType2,"
                             "PatiStatus = :PatiStatus"
                             " where SysCaseID = :id");
    query_base_info.prepare(statement);

    // 绑定更新参数
    query_base_info.bindValue(":id", sys_case_id);
    query_base_info.bindValue(":InsurNum", _patient_info.InsurNum);
    query_base_info.bindValue(":CaseNum", _patient_info.CaseNum);
    query_base_info.bindValue(":PatiDate", _patient_info.PatiDate);
    query_base_info.bindValue(":Room", _patient_info.Room);
    query_base_info.bindValue(":InsurType", _patient_info.InsurType);
    query_base_info.bindValue(":PatiSex", _patient_info.PatiSex);
    query_base_info.bindValue(":PatiHeig", _patient_info.PatiHeig);
    query_base_info.bindValue(":PatiAge", _patient_info.PatiAge);
    query_base_info.bindValue(":PatiDOB", _patient_info.PatiDOB);
    query_base_info.bindValue(":PatiWeig", _patient_info.PatiWeig);
    query_base_info.bindValue(":PatiBSA", _patient_info.PatiBSA);
    query_base_info.bindValue(":TelNum", _patient_info.TelNum);
    query_base_info.bindValue(":Address", _patient_info.Address);
    query_base_info.bindValue(":ZipCode", _patient_info.ZipCode);
    query_base_info.bindValue(":ShadowType1", _patient_info.ShadowType1);
    query_base_info.bindValue(":ShadowNum1", _patient_info.ShadowNum1);
    query_base_info.bindValue(":InRoomTime", _patient_info.InRoomTime);
    query_base_info.bindValue(":OutRoomTime", _patient_info.OutRoomTime);
    query_base_info.bindValue(":BeginTime", _patient_info.BeginTime);
    query_base_info.bindValue(":EndTime", _patient_info.EndTime);
    query_base_info.bindValue(":XTime", _patient_info.XTime); //
    query_base_info.bindValue(":PatiStatus", _patient_info.PatiStatus);
    query_base_info.bindValue(":SurName", _patient_info.SurName);
    query_base_info.bindValue(":InsductorName", _patient_info.InsductorName);
    query_base_info.bindValue(":Assis1", _patient_info.Assis1);
    query_base_info.bindValue(":Assis2", _patient_info.Assis2);
    query_base_info.bindValue(":Nursury1", _patient_info.Nursury1);
    query_base_info.bindValue(":Nursury2", _patient_info.Nursury2);
    query_base_info.bindValue(":Techno", _patient_info.Techno);
    query_base_info.bindValue(":LinChuang", _patient_info.LCZD);
    query_base_info.bindValue(":ShadowType2", _patient_info.ShadowLeixing);

    QString tmp_sur_type;
    for(auto e:_patient_info.SurType)tmp_sur_type+=("#"+e);
    query_base_info.bindValue(":SurType", tmp_sur_type);
    // 执行更新
    query_base_info.exec();






    // 获取SysCaseID
//    query_base_info.exec(QString("select * from PatiInfo_T where CaseID = '%1'").arg(sys_case_id));
//    query_base_info.next();
//    auto record = query_base_info.record();
//    auto SysCaseID = record.value("SysCaseID").toString();


    QSqlQuery query_sur(db);

    // 获取记录是否存在，不存在则创建
    query_sur.exec(QString("select * from BB_ZYSJ where SysCaseID = '%1'").arg(sys_case_id));
    bool is_exist = query_sur.first();
    if(!is_exist)
    {
        // TODO LOG
        query_sur.exec(QString("insert into BB_ZYSJ(SysCaseID) values('%1')").arg(sys_case_id));
        query_sur.exec(QString("select * from BB_ZYSJ where SysCaseID = '%1'").arg(sys_case_id));
        query_sur.first();
    }


    // 创建更新语句
    statement = QString("UPDATE BB_ZYSJ Set "
                        "MZJ = :MZJ,"
                        "MZJJL = :MZJJL,"
                        "QGXH = :QGXH,"
                        "CGLJ = :CGLJ,"
                        "YYJL = :YYJL,"
                        "ZYBW = :ZYBW,"
                        "ZYDG = :ZYDG"
                        " where SysCaseID = :SysCaseID");
    query_sur.prepare(statement);

    // 绑定更新参数
    query_sur.bindValue(":SysCaseID", sys_case_id);
    query_sur.bindValue(":MZJ", _patient_info.MZJ);
    query_sur.bindValue(":MZJJL", _patient_info.MZJJL);

    // 更新鞘管型号
    QString QGXH;
    for(auto e:_patient_info.QGXH)
    {
        QGXH +=('#'+e);
    }
    query_sur.bindValue(":QGXH", QGXH);

    // 更新插管结果
    QString CGLJ;
    for(auto e:_patient_info.CGLJ)
    {
        QString t;
        for(auto i:e)
        {
            t+=(QString('\\')+i);  // 反斜杠分隔字段 #分隔每一条结果
        }
        CGLJ +=('#'+t);
    }
    query_sur.bindValue(":CGLJ", CGLJ);

    // 更新用药记录
    QString YYJL;
    for(auto e:_patient_info.YYJL)
    {
        YYJL +=(QString('#')+e);
    }
    query_sur.bindValue(":YYJL", YYJL);


    // 更新造影手术
    QString ZYBW;
    for(auto e:_patient_info.ZYBW)
    {
        ZYBW +=(QString('#')+e);
    }
    query_sur.bindValue(":ZYBW", ZYBW);

    // 更新造影导管
    QString ZYDG;
    for(auto e:_patient_info.ZYDG)
    {
        ZYDG +=(QString('#')+e);
    }
    query_sur.bindValue(":ZYDG", ZYDG);


    // 执行更新
    query_sur.exec();

}


void CWidgetPatientInfo::on_radioButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_radioButton_24_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_radioButton_23_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_radioButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void CWidgetPatientInfo::on_radioButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_radioButton_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_ZYBW_yes_toggled(bool checked)
{
    if(checked)
    {
        ui->ZYSH_position->show();
        ui->groupBox_ZYDG->show();
    }
    else
    {
        ui->ZYSH_position->hide();
        ui->groupBox_ZYDG->hide();
    }
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_PatiChName_textChanged(const QString &arg1)
{
    _patient_info.PatiChName = arg1;
}

void CWidgetPatientInfo::on_CaseID_textChanged(const QString &arg1)
{
    _patient_info.CaseID = arg1;
}

void CWidgetPatientInfo::on_InsurNum_textChanged(const QString &arg1)
{
    _patient_info.InsurNum = arg1;
}

void CWidgetPatientInfo::on_CaseNum_textChanged(const QString &arg1)
{
    _patient_info.CaseNum = arg1;
}

void CWidgetPatientInfo::on_PatiDate_dateTimeChanged(const QDateTime &dateTime)
{
    _patient_info.PatiDate = dateTime;
}

void CWidgetPatientInfo::on_Room_currentIndexChanged(const QString &arg1)
{
    _patient_info.Room = arg1;
}

void CWidgetPatientInfo::on_InsurType_currentIndexChanged(const QString &arg1)
{
    _patient_info.InsurType = arg1;
}

void CWidgetPatientInfo::on_minzu_currentIndexChanged(const QString &arg1)
{
    _patient_info.minzu = arg1;
}

void CWidgetPatientInfo::on_PatiSex_currentIndexChanged(const QString &arg1)
{
    _patient_info.PatiSex = arg1;
}

void CWidgetPatientInfo::on_PatiAge_textChanged(const QString &arg1)
{
    _patient_info.PatiAge = arg1;
}

void CWidgetPatientInfo::on_PatiDOB_dateTimeChanged(const QDateTime &dateTime)
{
    _patient_info.PatiDOB = dateTime;
}



void CWidgetPatientInfo::on_radioButton_32_clicked()
{
    _patient_info.PatiType = "门诊";
}

void CWidgetPatientInfo::on_radioButton_34_clicked()
{
    _patient_info.PatiType = "急诊";

}

void CWidgetPatientInfo::on_radioButton_33_clicked()
{
    _patient_info.PatiType = "住院";
}

void CWidgetPatientInfo::on_radioButton_35_clicked()
{
    _patient_info.PatiType = "转院";
}

void CWidgetPatientInfo::on_PatiHeig_textChanged(const QString &arg1)
{
    _patient_info.PatiHeig = arg1;
}

void CWidgetPatientInfo::on_PatiWeig_textChanged(const QString &arg1)
{
    _patient_info.PatiWeig = arg1;
    // TODO 设置体表面积
}

void CWidgetPatientInfo::on_TelNum_textChanged(const QString &arg1)
{
    _patient_info.TelNum = arg1;
}

void CWidgetPatientInfo::on_Address_textChanged(const QString &arg1)
{
    _patient_info.Address = arg1;
}

void CWidgetPatientInfo::on_ZipCodeP_textChanged(const QString &arg1)
{
    _patient_info.ZipCode = arg1;
}

void CWidgetPatientInfo::on_ShadowType1_currentIndexChanged(const QString &arg1)
{
    _patient_info.ShadowType1 = arg1;
}

void CWidgetPatientInfo::on_ShadowNum1_textChanged(const QString &arg1)
{
    _patient_info.ShadowNum1 = arg1;
}

void CWidgetPatientInfo::on_InRoomTime_dateTimeChanged(const QDateTime &dateTime)
{
    _patient_info.InRoomTime = dateTime;
}

void CWidgetPatientInfo::on_ShadowLeixing_currentIndexChanged(const QString &arg1)
{
    _patient_info.ShadowLeixing = arg1;
}

void CWidgetPatientInfo::on_XTime_textChanged(const QString &arg1)
{
    _patient_info.XTime = arg1;
}

void CWidgetPatientInfo::on_OutRoomTime_dateTimeChanged(const QDateTime &dateTime)
{
    _patient_info.OutRoomTime = dateTime;
}

void CWidgetPatientInfo::on_BeginTime_dateTimeChanged(const QDateTime &dateTime)
{
    _patient_info.BeginTime = dateTime;
}




void CWidgetPatientInfo::on_EndTime_dateTimeChanged(const QDateTime &dateTime)
{
    _patient_info.EndTime = dateTime;
}

void CWidgetPatientInfo::on_SurName_currentIndexChanged(const QString &arg1)
{
    _patient_info.SurName = arg1;
}

void CWidgetPatientInfo::on_InsductorName_currentIndexChanged(const QString &arg1)
{
    _patient_info.InsductorName = arg1;
}

void CWidgetPatientInfo::on_Assis1_currentIndexChanged(const QString &arg1)
{
    _patient_info.Assis1 = arg1;
}

void CWidgetPatientInfo::on_Assis2_currentIndexChanged(const QString &arg1)
{
    _patient_info.Assis2 = arg1;
}

void CWidgetPatientInfo::on_Nursury1_currentIndexChanged(const QString &arg1)
{
    _patient_info.Nursury1 = arg1;
}

void CWidgetPatientInfo::on_Nursury2_currentIndexChanged(const QString &arg1)
{
    _patient_info.Nursury2 = arg1;
}

void CWidgetPatientInfo::on_Techno_currentIndexChanged(const QString &arg1)
{
    _patient_info.Techno = arg1;
}



void CWidgetPatientInfo::on_MZJ_ldky_clicked()
{
    _patient_info.MZJ = "利多卡因";
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_MZJ_nsky_clicked()
{
    _patient_info.MZJ = "那塞卡因";
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_MZJJL_valueChanged(int arg1)
{
    _patient_info.MZJJL = QString::number(arg1);
    qDebug()<<_patient_info.MZJJL;
    UpdateTextEdit();
}


void CWidgetPatientInfo::on_QGXH_4F_clicked(bool checked)
{
    if(checked)
    {
        if(!_patient_info.QGXH.contains("4F"))
        {
            _patient_info.QGXH.append("4F");
        }
    }
    else
    {
        _patient_info.QGXH.removeOne("4F");
    }
    _patient_info.QGXH.sort();
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_QGXH_5F_clicked(bool checked)
{
    if(checked)
    {
        if(!_patient_info.QGXH.contains("5F"))
        {
            _patient_info.QGXH.append("5F");
        }
    }
    else
    {
        _patient_info.QGXH.removeOne("5F");
    }
    _patient_info.QGXH.sort();
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_QGXH_6F_clicked(bool checked)
{
    if(checked)
    {
        if(!_patient_info.QGXH.contains("6F"))
        {
            _patient_info.QGXH.append("6F");
        }
    }
    else
    {
        _patient_info.QGXH.removeOne("6F");
    }
    _patient_info.QGXH.sort();
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_QGXH_7F_clicked(bool checked)
{
    if(checked)
    {
        if(!_patient_info.QGXH.contains("7F"))
        {
            _patient_info.QGXH.append("7F");
        }
    }
    else
    {
        _patient_info.QGXH.removeOne("7F");
    }
    _patient_info.QGXH.sort();
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_QGXH_8F_clicked(bool checked)
{
    if(checked)
    {
        if(!_patient_info.QGXH.contains("8F"))
        {
            _patient_info.QGXH.append("8F");
        }
    }
    else
    {
        _patient_info.QGXH.removeOne("8F");
    }
    _patient_info.QGXH.sort();
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_cgjg_suc_toggled(bool checked)
{
    if(checked)
    {
        ui->grpcgyy->hide();
    }
    else
    {
        ui->grpcgyy->show();
    }
    UpdateTextEdit();
}

// 添加插管结果
void CWidgetPatientInfo::on_pushButton_clicked()
{
    // 插管结果保存到结构体对象
    QList<QString> cur_cg;
    cur_cg<<bg_cgfx->checkedButton()->text();
    cur_cg<<bg_cgbw->checkedButton()->text();
    cur_cg<<bg_cgjg->checkedButton()->text();
    cur_cg<<ui->cgyy->toPlainText();

    if(_patient_info.CGLJ.indexOf(cur_cg)!= -1)
    {
        // 已存在
        QMessageBox::information(NULL, QStringLiteral("插管"), QStringLiteral("重复插入"));
    }
    else
    {
        _patient_info.CGLJ.push_back(cur_cg);
        // 处理界面显示
        int row = ui->CGLJ->rowCount();
        ui->CGLJ->insertRow(row);

        int cols = ui->CGLJ->columnCount();
        for(int i = 0;i<cols;i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem;
            if(i==0)
            {
                newItem->setData(Qt::DisplayRole, cur_cg[0]+cur_cg[1]);
            }
            else
            {
                newItem->setData(Qt::DisplayRole, cur_cg[i+1]);
            }

            ui->CGLJ->setItem(row, i, newItem);
        }
    }
    UpdateTextEdit();

}






void CWidgetPatientInfo::on_CGLJ_cellDoubleClicked(int row, int column)
{
    // 双击删除一行
    int rowIndex = ui->CGLJ->currentRow();
    qDebug()<<rowIndex;
    if (rowIndex != -1)
        ui->CGLJ->removeRow(rowIndex);

    // 同步删除结构体内信息
    _patient_info.CGLJ.removeAt(rowIndex);
    UpdateTextEdit();
}


// 添加用药记录
void CWidgetPatientInfo::on_pushButton_2_clicked()
{
    if((ui->ypm->currentRow() == -1)||(ui->jl->currentRow() == -1)||
            (ui->dw->currentRow() == -1))
    {
        QMessageBox::information(NULL, QString("用药"),
                                 QString("未选中用药信息"));
        return ;
    }
    // 用药记录保存到结构体对象
    QList<QString> cur_yy;
    auto row = ui->ypm->currentRow();
    cur_yy<<ui->ypm->item(row)->data(Qt::DisplayRole).toString();
    row = ui->jl->currentRow();
    cur_yy<<ui->jl->item(row)->data(Qt::DisplayRole).toString();
    row = ui->dw->currentRow();
    cur_yy<<ui->dw->item(row)->data(Qt::DisplayRole).toString();



    // 新纪录更新到界面
    QString tmp;
    for(auto e:cur_yy) tmp+=e;
    _patient_info.YYJL.push_back(tmp);
    ui->YYJL_result->addItem(tmp);
    UpdateTextEdit();

}



void CWidgetPatientInfo::on_YYJL_result_itemDoubleClicked(QListWidgetItem *item)
{
    // 双击删除一行
    int rowIndex = ui->YYJL_result->currentRow();
    qDebug()<<rowIndex;
    if (rowIndex != -1)
    {
        auto item = ui->YYJL_result->takeItem(rowIndex);
        delete item;
    }

    // 同步删除结构体内信息
    _patient_info.YYJL.removeAt(rowIndex);
    qDebug()<<_patient_info.YYJL;
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_ZYBW_lrgm_toggled(bool checked)
{
    if(checked)
    {
        if(_patient_info.ZYBW.indexOf(ui->ZYBW_lrgm->text()) == -1)
        {
            _patient_info.ZYBW.push_back(ui->ZYBW_lrgm->text());
        }
    }
    else
    {
        _patient_info.ZYBW.removeOne(ui->ZYBW_lrgm->text());
    }
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_ZYBW_zxs_toggled(bool checked)
{
    if(checked)
    {
        if(_patient_info.ZYBW.indexOf(ui->ZYBW_zxs->text()) == -1)
        {
            _patient_info.ZYBW.push_back(ui->ZYBW_zxs->text());
        }
    }
    else
    {
        _patient_info.ZYBW.removeOne(ui->ZYBW_zxs->text());
    }
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_ZYBW_sdm_toggled(bool checked)
{
    if(checked)
    {
        if(_patient_info.ZYBW.indexOf(ui->ZYBW_sdm->text()) == -1)
        {
            _patient_info.ZYBW.push_back(ui->ZYBW_sdm->text());
        }
    }
    else
    {
        _patient_info.ZYBW.removeOne(ui->ZYBW_sdm->text());
    }
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_ZYBW_zdm_toggled(bool checked)
{
    if(checked)
    {
        if(_patient_info.ZYBW.indexOf(ui->ZYBW_zdm->text()) == -1)
        {
            _patient_info.ZYBW.push_back(ui->ZYBW_zdm->text());
        }
    }
    else
    {
        _patient_info.ZYBW.removeOne(ui->ZYBW_zdm->text());
    }
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_ZYBW_ldm_toggled(bool checked)
{
    if(checked)
    {
        if(_patient_info.ZYBW.indexOf(ui->ZYBW_ldm->text()) == -1)
        {
            _patient_info.ZYBW.push_back(ui->ZYBW_ldm->text());
        }
    }
    else
    {
        _patient_info.ZYBW.removeOne(ui->ZYBW_ldm->text());
    }
    //qDebug()<<_patient_info.ZYBW;
    UpdateTextEdit();
}


// 造影导管
void CWidgetPatientInfo::on_pushButton_3_clicked()
{
    bool error = false;
    if((bg_zygg->checkedId()== -1)||
            (bg_zyxs->checkedId()== -1))error = true;
    auto index = ui->stackedWidget->currentIndex();
    if(index<4)
    {
        if(bgs_zycc[index]->checkedId()==-1) error = true;
    }
    if(error)
    {
        QMessageBox::information(NULL, QString("造影导管"), QString("未选中信息"));
        return;
    }

    QList<QString> cur_dg;
    cur_dg<<bg_zygg->checkedButton()->text();

    cur_dg<<bg_zyxs->checkedButton()->text();

    if(index<4)
    {
        cur_dg<<bgs_zycc[index]->checkedButton()->text();
    }
    else
    {
        cur_dg<<QString{};
    }



    // 更新界面
    QString tmp;
    for(auto e:cur_dg) tmp+=e;
    ui->ZYDG_name->addItem(tmp);

    _patient_info.ZYDG.push_back(tmp);
    UpdateTextEdit();


}

void CWidgetPatientInfo::on_ZYDG_name_itemDoubleClicked(QListWidgetItem *item)
{
    // 双击删除一行
    int rowIndex = ui->ZYDG_name->currentRow();
    qDebug()<<rowIndex;
    if (rowIndex != -1)
    {
        auto item = ui->ZYDG_name->takeItem(rowIndex);
        delete item;
    }

    // 同步删除结构体内信息
    _patient_info.ZYDG.removeAt(rowIndex);
    qDebug()<<_patient_info.ZYDG;
    UpdateTextEdit();
}

void CWidgetPatientInfo::on_mz_toggled(bool checked)
{
    if(checked)
    {
        _patient_info.PatiStatus = "门诊";
    }
    UpdateTextEdit();

}

void CWidgetPatientInfo::on_jz_toggled(bool checked)
{
    if(checked)
    {
        _patient_info.PatiStatus = "急诊";
    }

}

void CWidgetPatientInfo::on_zhuyuan_toggled(bool checked)
{
    if(checked)
    {
        _patient_info.PatiStatus = "住院";
    }
}

void CWidgetPatientInfo::on_zhuanyuan_toggled(bool checked)
{
    if(checked)
    {
        _patient_info.PatiStatus = "转院";
    }
}





void CWidgetPatientInfo::on_ZYBW_no_clicked(bool checked)
{
    if(checked)
    {
//        auto list = bg_zybw->findChildren<QCheckBox*>();
//        qDebug()<<"list:"<<list.size();
//        for(int i = 0;i<list.size();i++)
//        {
//            list[i]->setChecked(false);
//        }
        ui->ZYBW_ldm->setChecked(false);
        ui->ZYBW_sdm->setChecked(false);
        ui->ZYBW_zdm->setChecked(false);
        ui->ZYBW_zxs->setChecked(false);
        ui->ZYBW_lrgm->setChecked(false);

    }
    UpdateTextEdit();
}


void CWidgetPatientInfo::on_LCZD_currentIndexChanged(const QString &arg1)
{
    _patient_info.LCZD = arg1;
}


// 选择手术类型
void CWidgetPatientInfo::on_add_surtype_clicked()
{
    _surg_type->setWindowModality(Qt::WindowModal);
    _surg_type->show();
}

void CWidgetPatientInfo::UpdateSelectedTypes(QStringList _selected_types)
{
    this->setWindowModality(Qt::WindowModal);

    _patient_info.SurType = _selected_types;

    // 更新界面
    ui->SurType->clear();
    for(auto e:_selected_types)ui->SurType->setText(ui->SurType->text()+"\\"+e);
}
