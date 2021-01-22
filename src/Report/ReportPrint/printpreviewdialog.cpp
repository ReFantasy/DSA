#include "printpreviewdialog.h"
#include <QTextDocument>
#include <QDebug>
#include "SQLDB.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include "dsaconfig.h"
#include <QFile>
#include <fstream>


const std::string DATABASE_IMAGE_TYPE("png");

PrintPreviewDialog::PrintPreviewDialog(QWidget *parent)
    : QPrintPreviewDialog(parent)
{
    connect(this, &QPrintPreviewDialog::paintRequested,
            this, &PrintPreviewDialog::printPreview);

    // 初始化
    resize(1500,1080);
}

PrintPreviewDialog::~PrintPreviewDialog()
{

}

void PrintPreviewDialog::SetSysCaseId(const QString sys_case_id)
{
    specified = GenerateHtml(sys_case_id);
}

QString PrintPreviewDialog::GenerateHtml(const QString sys_case_id)
{   

    auto db = SQLDB::GetDfytCathLab();
    QSqlQuery query(db);
    query.prepare("select * from PatiInfo_T where SysCaseID = :id");
    query.bindValue(":id",sys_case_id);
    query.exec();
    query.next();
    auto record = query.record();


    QString html_title = ("吉林大学第二医院");  //title显示在网页的标题栏 pdf中没有
    QString hospital = ("吉林大学第二医院");
    QString report_name = ("PCI报告");
    QString patient_name = record.value("PatiChName").toString();//姓名
    QString patient_gender = record.value("PatiSex").toString();//性别
    QString patient_age = record.value("PatiAge").toString();//年龄
    QString patient_num = record.value("CaseID").toString();//住院号
    QString image_num = record.value("CaseID").toString();//造影号
    QString surgery_date = record.value("PatiDate").toDateTime().toString("yyyy年MM月dd日");//手术日期
    QString doctor = record.value("SurName").toString();//医生
    QString assistant_1 = record.value("Assis1").toString();//助手1
    QString assistant_2 = record.value("Assis2").toString();//助手1
    QString nurse_1 = record.value("Nursury1").toString();//护士1
    QString nurse_2 = record.value("Nursury2").toString();//护士1
    QString technician = record.value("Techno").toString();//技师
    QString surgery_type = record.value("SurType").toString();//手术类型
    QString patient_diag = record.value("LinChuang").toString();//临床诊断
    QString outside_doctor = record.value("InsductorName").toString();//外请专家
    QString patient_state = record.value("PatiStatus").toString();//病人状态

    query.prepare("select * from BB_JLYZ where SysCaseID = :id");
    query.bindValue(":id", sys_case_id);
    query.exec();
    query.next();
    record = query.record();
    QString proposal = record.value("jyb").toString();//进一步处理建议
    QString zyjl = record.value("zyjl").toString();//造影结论
    QString medical_advice = record.value("shyz").toString();//医嘱
    QString status_in_sur = record.value("ssqk").toString();//术中状态
    QString status_after_sur = record.value("jsy").toString();//术后状态
    QString status_in_after = status_in_sur + " " + status_after_sur;//术中及术后状态
     QString zyms = record.value("gyxg").toString();//造影描述


    // 读取图片
    // 先删除已有文件
    for(int i = 0;i<15;i++)
    {
        auto filename = QString("%1.png").arg(i);
        QFile fileTemp(filename);
        fileTemp.remove();
    }

    query.prepare("select * from operateitem where SysCaseID = :id");
    query.bindValue(":id",sys_case_id);
    query.exec();
    query.next();
    record = query.record();

    // 冠脉造影图像
    QStringList gmzy_pictures;
    QStringList pci_pictures;
    auto picture_size = DsaConfig::GetReportTemplatePicSize();
    for(int i = 0;i<9;i++)
    {
        auto image_name = QString("image%1").arg(QString::number(i+1));
        auto byteArray = record.value(image_name).toByteArray();
        if(byteArray.isNull()||byteArray.isEmpty())continue;
        QPixmap pix;
        if(pix.loadFromData(byteArray),DATABASE_IMAGE_TYPE.c_str() )
        {
            if(pix.save(QString("%1.png").arg(i)))
            {
                auto picture_html = QString("<img src=\"%1.png\" width=\"%2\" height=\"%3\" > ")
                        .arg(QString::number(i),QString::number(picture_size.first),QString::number(picture_size.second));
                gmzy_pictures.push_back(picture_html);
            }

        }
    }
    for(int i = 9;i<15;i++)
    {
        auto image_name = QString("image%1").arg(QString::number(i+1));
        auto byteArray = record.value(image_name).toByteArray();
        if(byteArray.isNull()||byteArray.isEmpty())continue;
        QPixmap pix;
        if(pix.loadFromData(byteArray),DATABASE_IMAGE_TYPE.c_str() )
        {
            if(pix.save(QString("%1.png").arg(i)))
            {
                auto picture_html = QString("<img src=\"%1.png\" width=\"%2\" height=\"%3\" > ")
                        .arg(QString::number(i),QString::number(picture_size.first),QString::number(picture_size.second));
                pci_pictures.push_back(picture_html);
            }

        }
    }
    QString gm_pics;
    QString pci_pics;
    for(auto e:gmzy_pictures)gm_pics+=e;
    for(auto e:pci_pictures)pci_pics+=e;


    //手术经过
    query.prepare("select * from SurgProc_new_T where SysCaseID = :id");
    query.bindValue(":id",sys_case_id);
    query.exec();
    QString surgery_pro;
    while(query.next()){
        record = query.record();
        QString tmp = record.value("Rec").toString();
        surgery_pro = surgery_pro + tmp;
    }

    // TODO

    QString recorder = ("TDL");//记录医师



    // 读取模板文件
    auto filename = DsaConfig::GetReportTemplatePath();

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        LOG(ERROR)<<"Report template Read fail.";
        return {};
    }

    auto report_html = QString(file.readAll());
    file.close();


    QString tmp;
//    auto tmp = report_html.arg(patient_name,patient_gender, patient_age,patient_num,image_num,
//                               patient_diag, surgery_date,patient_state, surgery_type.remove('#'),doctor,
//                               assistant_1,nurse_1,technician,outside_doctor, assistant_2,nurse_2,
//                               gm_pics,pci_pics,proposal,zyjl,surgery_pro,zyms,status_in_after,medical_advice,recorder);

    tmp = report_html.arg(patient_name,patient_gender, patient_age,patient_num,image_num)
            .arg(patient_diag, surgery_date,patient_state, surgery_type.remove('#'),doctor)
            .arg(assistant_1,nurse_1,technician,outside_doctor, assistant_2,nurse_2)
            .arg(gm_pics,pci_pics,proposal,zyjl,surgery_pro,zyms,status_in_after)
            .arg(medical_advice,recorder);

    return  tmp;
}

void PrintPreviewDialog::printPreview(QPrinter *printer)
{
    QTextDocument textDocument;
    textDocument.setHtml(specified);
    textDocument.print(printer);
}




