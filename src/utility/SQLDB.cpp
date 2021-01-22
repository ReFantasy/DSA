#include "SQLDB.h"
#include <QSqlError>
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <thread>
#include <QVBoxLayout>
#include "dsaconfig.h"

QString SQLDB::_host = "",SQLDB::_password = "",SQLDB::_username = "";
int SQLDB::_port = 0;

void SQLDB::init(QString host, int port, QString username, QString password){
    _host = host;
    _port = port;
    _password = password;
    _username = username;
}

void SQLDB::update(QString host, int port, QString username, QString password){
    _host = host;
    _port = port;
    _password = password;
    _username = username;
}

QSqlDatabase SQLDB::getDB(QString dbName){
    auto db = QSqlDatabase::addDatabase("QODBC",QUuid::createUuid().toString());
    db.setDatabaseName(QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;UID=%3;PWD=%4;")
                       .arg(_host)
                       .arg(dbName)
                       .arg(_username)
                       .arg(_password));
    //db.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=3");//SQL_ATTR_CONNECTION_TIMEOUT = 1 SQL_ATTR_LOGIN_TIMEOUT
    bool is_open = db.open();

    if(!is_open)
    {
        LOG(ERROR)<<db.lastError().databaseText();
    }

    return db;
}

void SQLDB::InitDB(){
    auto DBInfo = DsaConfig::GetDB();
    _host = DBInfo[0];
    _port = DBInfo[1].toInt();
    _username = DBInfo[2];
    _password= DBInfo[3];

    init(_host,_port,_username,_password);

    auto TestDB = []()
    {
        QDialog dlg;
        dlg.resize(400,200);
        dlg.setWindowTitle("Initialize Database");

        auto label = new QLabel(&dlg);
        label->setText("Trying to connect Microsoft SQL Server...");


        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(label);
        dlg.setLayout(layout);
        dlg.show();


        auto db = GetEvertopDB();
        bool is_open = db.open();


        if(!is_open)
        {
            label->setText("Database connect failed");
            dlg.exec();
        }
    };
    TestDB();

}


QSqlDatabase SQLDB::GetEvertopDB(){
    return getDB("EvertopDB");
}


QSqlDatabase SQLDB::GetDfytCathLab(){
    return getDB("DfytCathLab");
}

QSqlDatabase SQLDB::GetCathLabStock(){
    return getDB("CathLabStock");
}
