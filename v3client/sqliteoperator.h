#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "Classes.h"
#include "tcpclient.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
extern QString ClientJWT;

using namespace std;

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
    // 以名字为关键字返回具体数据
    Account_user searchUserQuery(QString username);
    // 以id为关键字返回具体数据
    Account_user searchUserIDQuery(int ID);
    // 以名字为关键字返回具体数据
    Account_sailer searchSailerQuery(QString username);
    //寻找最大id
    int searchMaxID();
    // 插入数据
    bool userInsertData(Account_user &Data);
    // 修改数据
    bool modifyUserData(Account_user &Data);
    bool modifySailerData(Account_sailer &Data);
    // 删除数据
    bool deleteData(int id);
    //登录检查
    bool login_check(QString nameString, QString passString);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif //  SQLITEOPERATOR_H
