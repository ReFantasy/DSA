#include "dsaconfig.h"
#include <QCoreApplication>
#include <tuple>
#include <QString>
#include <QtDebug>

QSettings *DsaConfig::settings = nullptr;

DsaConfig::DsaConfig()
{

}

void DsaConfig::Init()
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+QString("/dsa.conf"), QSettings::IniFormat);

    // IP地址配置
    auto DB = GetDB();
    SetDB(DB[0],DB[1].toInt(),DB[2],DB[3]);

    // 设置共享文件夹路径
    auto dcm_folder = GetSharedDcmFolder();
    SetSharedDcmFolder(dcm_folder);
//    if(settings->value("SharedDcmDir", "").toString() == QString{})
//    {
//        settings->setValue("SharedDcmDir", "\\\\WIN-5307K1TI0MH\\Storage\\");
//    }


//    if(settings->value("DB/ip", "").toString() == QString{})
//    {
//        settings->setValue("DB/ip", "192.168.97.16");
//    }
//    if(settings->value("DB/port", "").toString() == QString{})
//    {
//        settings->setValue("DB/port", "1433");
//    }
//    if(settings->value("DB/username", "").toString() == QString{})
//    {
//        settings->setValue("DB/username", "sa");
//    }
//    if(settings->value("DB/password", "").toString() == QString{})
//    {
//        settings->setValue("DB/password", "Evertop1301");
//    }

    // 日志配置文件目录
    if(settings->value("LOG", "").toString() == QString{})
    {
#ifdef _DEBUG
        settings->setValue("LOG", "../../src/3rdparty/easyloggingpp/log.conf");
#else
        settings->setValue("LOG", "log.conf");
#endif

    }

    // 图像处理配置
    if(settings->value("ImageProcess", "").toString() == QString{})
    {
        settings->setValue("ImageProcess", "cal.ini");
    }

    // 报告模板配置
    if(settings->value("ReportTempalte", "").toString() == QString{})
    {
        settings->setValue("ReportTempalte", "report.html");//QString("../../dsa/src/Report/ReportPrint/report.html")
    }

    // 报告图像尺寸
    if(settings->value("ReportImg/width", "").toString() == QString{})
    {
        settings->setValue("ReportImg/width", 199);
    }
    if(settings->value("ReportImg/height", "").toString() == QString{})
    {
        settings->setValue("ReportImg/height", 199);
    }



}

QString DsaConfig::SetSharedDcmFolder(QString path)
{
    settings->setValue("SharedDcmDir", path);
    return path;
}

QString DsaConfig::GetSharedDcmFolder()
{
    return settings->value("SharedDcmDir", "Storage").toString();
}

void DsaConfig::SetDB(QString host, int port, QString username, QString password)
{
    settings->setValue("DB/ip", host);


    settings->setValue("DB/port", port);


    settings->setValue("DB/username", username);


    settings->setValue("DB/password", password);

}

std::vector<QString> DsaConfig::GetDB()
{
    auto host = settings->value("DB/ip","192.168.97.16").toString();
    auto port = settings->value("DB/port", "1433").toString();
    auto username = settings->value("DB/username", "sa").toString();
    auto password = settings->value("DB/password", "Evertop1301").toString();

    return {host, port, username, password};
}

QString DsaConfig::GetImagePath()
{
    auto aImagePath = settings->value("General/SharedDcmDir","Storage").toString();
    return aImagePath;
}

void DsaConfig::LogConfig()
{
    /*
     * 必须设置标记 LoggingFlag::StrictLogFileSizeCheck
     * 否则,配置文件中MAX_LOG_FILE_SIZE = 1048576不生效
     */
    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);

    el::Configurations conf(settings->value("LOG").toString().toStdString());

    // 设置全部logger的配置
    el::Loggers::reconfigureAllLoggers(conf);
}

QString DsaConfig::GetImageProcessIniName()
{
    return settings->value("ImageProcess").toString();
}

QString DsaConfig::GetReportTemplatePath()
{
    return settings->value("ReportTempalte").toString();
}

QPair<int,int> DsaConfig::GetReportTemplatePicSize()
{
    return QPair<int, int>{settings->value("ReportImg/width").toInt(),
                settings->value("ReportImg/height").toInt()};
}
