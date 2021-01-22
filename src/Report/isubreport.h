/************************************************************************
*
* 文件名：isubreport.h
*
* 文件描述：报告主模块和子模块的接口类
*
* 创建人：TDL
*
* 时  间：2020/10/19
*
* 版本号：1.0
*
* 修改记录：
*
************************************************************************/

#ifndef ISUBREPORT_H
#define ISUBREPORT_H

#include <QString>

class ISubReport
{
public:

    /**
     * @brief 设置病例ID
     */
    virtual void SetSysCaseId(const QString) = 0;

    /**
     * @brief 从数据库请求数据更新界面信息
     */
    virtual void UpdateUIFromDatabase() = 0;

    /**
     * @brief 将界面修改信息写回数据库
     */
    virtual void UpdateDatabaseFromUI() = 0;

};

#endif // ISUBREPORT_H
