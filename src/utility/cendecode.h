#ifndef CENDECODE_H
#define CENDECODE_H
#include <qobject.h>
#include <qstring.h>

#include <iostream>
using namespace std;

// 密匙
static QString sKey="dsaStationbyCUST";
static QString sPad="1122334455667788";

class CEnDeCode
{
public:
    CEnDeCode();
    ~CEnDeCode();

    // 加密
    static QString EnDeCode(QString pCode);

    static QString EnCode(QString pCode);
    static QString UnCode(QString pCode);
};

#endif // CENDECODE_H
