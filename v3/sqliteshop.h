#ifndef SQLITESHOP_H
#define SQLITESHOP_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDoubleValidator>
#include "Classes.h"

class sqliteShop
{
public:
    sqliteShop();

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);

    std::vector<int> searchShopName(QString clientName);
    int searchProjectNumber(QString clientName,int projectID);


    int searchMaxID();
    // 插入数据
    bool projectInsertData(QString clientName,int projectID);
    // 修改数据
    bool modifyprojectData(QString clientName,int projectID,int projectNum);
    bool deleteData(QString clientName,int projectID);
    bool deleteClient(QString clientName);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif // SQLITESHOP_H
