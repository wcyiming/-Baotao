#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "Classes.h"

class SqliteOperator
{
public:
    SqliteOperator();

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 查询数据
    int ifquery(QString username);
    // 返回具体数据
    Account_user searchUserQuery(QString username);
    Account_user searchUserIDQuery(int ID);
    Account_sailer searchSailerQuery(QString username);
    int searchMaxID();
    // 插入数据
    bool userInsertData(Account_user &Data);
    // 修改数据
    bool modifyUserData(Account_user &Data);
    bool modifySailerData(Account_sailer &Data);
    // 删除数据
    bool deleteData(int id);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif //  SQLITEOPERATOR_H
