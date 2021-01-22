#ifndef CQUERY_H
#define CQUERY_H
#include <QObject>
#include <QString>
#include <QStringList>
#include <QSqlQueryModel>


/**
 * Describe：CQuery类用于查询并保存数据库表的信息
 * Usage：你可以使用SetTableName、SetField、SetCondition三个成员函数
 *        分别设置要查询的表名、字段名、以及查询条件， 例如：
 *        SetTableName("EvertopDB")设置要查询的表EvertopDB
 *        SetField("PatientID")设置要查询的字段
 *        SetCondition("StudyDate >= 20200728")设置查询的条件
 *        CQuery对象最终将根据设置的查询日期生成SQL查询语句 "SELECT PatientID FROM EvertopDB WHERE StudyDate >= 20200728"
 *        然后通过调用Query成员函数进行数据库检索操作，Query使用默认数据库，你可以通过传递指定的数据库变量对象指定要在哪个数据库中执行查找操作
 *        检索的结果将保存在私有QSqlQueryModel对象内。
 *
 */
class CQuery:public QObject
{
    Q_OBJECT
public:
    CQuery()
    {
        _query_model = new QSqlQueryModel;
    }
    ~CQuery()
    {
        delete  _query_model;
    }

    /**
     * @brief 设置查询表
     * @param table_name 表的名称
     * @return 返回自身的引用
     */
    CQuery& SetTableName(const QString &table_name);

    /**
     * @brief 设置查询字段
     * @param fields 字段名称
     * @return 返回自身的引用
     */
    CQuery& SetField(const QStringList &fields);

    /**
     * @brief 添加字段
     * @param field 添加的字段名称
     * @return 返回自身的引用
     */
    CQuery& AddField(const QString &field);

    /**
     * @brief 设置查询条件
     * @param conditons 条件列表
     * @return 返回自身的引用
     */
    CQuery& SetCondition(const QStringList &conditons);

    /**
     * @brief 添加查询条件
     * @param conditon 查询条件字符串
     * @return 返回自身的引用
     */
    CQuery& AddCondition(const QString &conditon);

    /**
     * @brief 查询数据
     * @param db 要查询的数据库
     * @return 返回查询到的记录数
     */
    int Query(QSqlDatabase db = QSqlDatabase::database())const;

    /**
     * @brief 获取内部查询模型
     * @return 查询模型常量指针
     */
    const QSqlQueryModel * GetQueryModel()const
    {
        return  _query_model;
    }


private:
    /**
     * @brief 创建查询语句
     * @param table_name 查询的表名
     * @param fields 查询的字段
     * @param conditon 查询条件
     * @return 生成的SQL语句
     */
    QString CreateQueryStatement(const QString &table_name, const QStringList &fields, const QStringList &conditon)const;

private:
    QString _table_name;
    QStringList _fields;
    QStringList _conditons;

    // 查询模型,保存数据库查询结果
    QSqlQueryModel *_query_model;

};



#endif // CQUERY_H
