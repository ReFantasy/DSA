#ifndef DSACONFIG_H
#define DSACONFIG_H
#include <QString>
#include <QPair>
#include <QSettings>
#include <vector>

#define ELPP_QT_LOGGING
#include "easyloggingpp/easylogging++.h"

class DsaConfig
{
public:
    DsaConfig();
    static void Init();
    /**
     * @brief 设置共享文件夹路径
     * @param path 路径
     * @return
     */
    static QString SetSharedDcmFolder(QString path);

    /**
     * @brief 获取共享文件夹路径
     * @return 路径
     */
    static QString GetSharedDcmFolder();

    /**
     * @brief 设置数据库信息
     * @param host ip
     * @param port 端口
     * @param username 用户名
     * @param password 密码
     */
    static void SetDB(QString host,int port, QString username,QString password);

    /**
     * @brief 返回数据库信息
     * @return 返回向量顺序 ip,port,username,password
     */
    static std::vector<QString> GetDB();

    // 范围共享文件夹名称
    static QString GetImagePath();

    static void LogConfig();
    static QString GetImageProcessIniName();
    static QString GetReportTemplatePath();

    static void SetDatabase(QString host,int port, QString username,QString password);
    static std::tuple<QString> GetDatabase();

    // 报告模板图片的尺寸 单位：像素
    static QPair<int,int> GetReportTemplatePicSize();

    static QSettings *settings;

};



#endif // DSACONFIG_H
