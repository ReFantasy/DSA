#include "utility.h"

QDateTime QStringToDateTime(const QString &str)
{
    return QDateTime::fromString(str.mid(0,10)+" "+str.mid(11,8), "yyyy-MM-dd hh:mm:ss");
}

QStringList Split(QString str, QChar c)
{
    auto str_list = str.split(c);

    for(auto b = str_list.begin();b!= str_list.end();)
    {
        if(b->isEmpty())
        {
            b = str_list.erase(b);
        }
        else
        {
            b++;
        }
    }

    return str_list;
}
