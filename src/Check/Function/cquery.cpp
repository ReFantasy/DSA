#include "cquery.h"
#include "ui_check.h"
#include <chrono>

CQuery &CQuery::SetTableName(const QString &table_name)
{
    _table_name = table_name;
    return *this;
}

CQuery &CQuery::SetField(const QStringList &fields)
{
    _fields = fields;
    return *this;
}

CQuery &CQuery::AddField(const QString &field)
{
    _fields.push_back(field);
    return *this;
}

CQuery &CQuery::SetCondition(const QStringList &conditons)
{
    _conditons = conditons;
    return *this;
}

CQuery &CQuery::AddCondition(const QString &conditon)
{
    _conditons.push_back(conditon);
    return *this;
}

int CQuery::Query(QSqlDatabase db)const
{
    // 如果查询条件为空， 清空查询模型上次查询的结果
    if(_conditons.isEmpty())
    {
        _query_model->clear();
        return 0;
    }

    // 生成查询语句
    QString query = CreateQueryStatement(_table_name, _fields, _conditons);
    LOG(INFO)<<"check module query: "<<query;
    // 查询
#ifdef _DEBUG
    auto t1 = std::chrono::steady_clock::now();
#endif
    _query_model->query().setForwardOnly(true);
    _query_model->setQuery(query,db);

#ifdef _DEBUG
    auto t2 = std::chrono::steady_clock::now();
    qDebug()<<"query time : "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<"ms";
#endif
    while(_query_model->canFetchMore())_query_model->fetchMore();  // sqlquerymodel 默认缓存256条查询结果 因此需要手动获取所有的查询结果
    return _query_model->rowCount();
}

QString CQuery::CreateQueryStatement(const QString &table_name, const QStringList &fields, const QStringList &conditon)const
{
    QString qs("SELECT ");

    // 连接查询字段
    qs += fields.at(0);
    for(int i=1;i<fields.size();i++)
    {
        qs += ",";
        qs += fields.at(i);
    }

    // 连接查询表
    qs += QString(" FROM ");
    qs += table_name;

    // 连接查询条件
    qs += QString(" ");
    if(conditon.size()>0)
    {
        qs += QString("WHERE ");
        qs += conditon.at(0);
        for(int i = 1;i<conditon.size();i++)
        {
            qs += QString(" AND ");
            qs += conditon.at(i);
        }
    }

    return qs;
}


