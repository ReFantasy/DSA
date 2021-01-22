#include "cendecode.h"

CEnDeCode::CEnDeCode()
{

}

CEnDeCode::~CEnDeCode()
{

}

QString CEnDeCode::EnDeCode(QString pCode)
{
    std::string Code = pCode.toStdString();
    QByteArray byteKey = sKey.toUtf8();
    for (unsigned int i = 0; i < Code.size(); i++)
    {
        Code[i] = Code[i] ^ byteKey[i % byteKey.size()];
    }
    return QString::fromStdString(Code).toUtf8();
}

/**
 * @brief 14位密码
 * @param pCode
 * @return
 */
QString CEnDeCode::EnCode(QString pCode)
{
    QString sCode=pCode;
    // 字符填充
    int nLength=sCode.length();
    int addnum=14-nLength;
    QString sAddNum=QString("%1").arg(nLength,2,10,QChar('0'));
    for(int i=0;i<addnum;i++)
    {
        sCode+=sPad[i];
    }
    for(int i=0;i<sAddNum.length();i++)
    {
        sCode+=sAddNum[i];
    }

    std::string Code = sCode.toStdString();
    QByteArray byteKey = sKey.toUtf8();
    for (unsigned int i = 0; i < Code.size(); i++)
    {
        Code[i] = Code[i] ^ byteKey[i % byteKey.size()];
    }
    return QString::fromStdString(Code).toUtf8();
}

/**
* @brief CEnDeCode::DeCode
* @param pCode
* @return
*/
QString CEnDeCode::UnCode(QString pCode)
{
    std::string Code = pCode.toStdString();
    QByteArray byteKey = sKey.toUtf8();
    for (unsigned int i = 0; i < Code.size(); i++)
    {
        Code[i] = Code[i] ^ byteKey[i % byteKey.size()];
    }

    QString sCode=QString::fromStdString(Code).toUtf8();
    // 计算长度
    QString sLenth=sCode.right(2);
    int nLength=sLenth.toInt();

    sCode=sCode.left(nLength);
    return sCode;
}
