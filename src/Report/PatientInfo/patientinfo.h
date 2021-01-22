/************************************************************************
*
* 文件名：patientinfo.h
*
* 文件描述：病人资料界面所用数据结构体
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
#ifndef PATIENTINFO_H
#define PATIENTINFO_H
#include <QString>
#include <QDateTime>

class PatientInfo
{
public:
    PatientInfo();


public:
    QString PatiChName;       //姓名
    QString CaseID;           // 住院号
    QString InsurNum;         // 医保号
    QString CaseNum;          //门诊号
    QDateTime PatiDate;         //手术日期
    QString Room;             //导管室
    QString InsurType;        //保险类型
    QString SysCaseID;        //手术编号
    QString PatiSex;          //性别
    QString PatiAge;          //年龄
    QDateTime PatiDOB;          //出生日期
    QString minzu;            // ???名族
    QString PatiHeig;         //身高
    QString PatiWeig;         //体重
    QString PatiType;         // 病人类型
    QString PatiBSA;          //体表面积
    QString TelNum;           //联系电话
    QString Address;          //联系地址
    QString ZipCode;         //邮编

    QString ShadowType1;      //对比剂名称
    QString ShadowNum1;       //对比剂用量
    QDateTime InRoomTime;       //进导管室时间
    QDateTime BeginTime;        //手术开始时间
    QDateTime EndTime;        //手术结束时间
    QString PatiStatus;       // 病人类型
    // ？？造影号
    QString LCZD;          // 临床诊断
    QString ShadowLeixing;    // ???对比剂类型
    QString XTime;            //X光照射时间
    QDateTime OutRoomTime;      //出导管室时间
    QString time1;            // ???症状发作距手术时间
    QString time2;            // ???医院就诊距手术时间
    QString SurName;          //术者
    QString InsductorName;    //外请专家
    QString Assis1;           //助手1
    QString Assis2;           //助手2
    QString Nursury1;         //护士1
    QString Nursury2;         //护士2
    QString Techno;           //技师
    QStringList SurType;           //手术类型

    QString MZJ;              //麻醉方法
    QString MZJJL;            //计量
    QList<QString> QGXH;             //鞘管型号
    QList<QList<QString>> CGLJ;             //插管结果
    QStringList YYJL;             //用药记录结果

    QList<QString> ZYBW;             //造影手术

    QList<QString> ZYDG;             //造影导管
};

#endif // PATIENTINFO_H
