#ifndef SQLDB_H
#define SQLDB_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QUuid>

#define ELPP_QT_LOGGING
#include "easyloggingpp/easylogging++.h"



class SQLDB: public QObject{
    Q_OBJECT

public:
    static void InitDB();
    static void init(QString host,int port, QString username,QString password);
    static QSqlDatabase getDB(QString dbName);
    static void update(QString host,int port, QString username, QString password);
    static QSqlDatabase GetEvertopDB();
    static QSqlDatabase GetDfytCathLab();
    static QSqlDatabase GetCathLabStock();

private:
    static QString _host;
    static int _port;
    static QString _username;
    static QString _password;

};


#endif // SQLDB_H
