#ifndef SQLITESHOP_H
#define SQLITESHOP_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDoubleValidator>
#include "Classes.h"
#include "tcpclient.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

using namespace std;

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
    //以用户名为关键字搜索商店
    std::vector<int> searchShopName(QString clientName);
    //以用户名和商品id搜索该订单商品数量
    int searchProjectNumber(QString clientName,int projectID);

    //寻找最大id
    int searchMaxID();
    // 插入订单
    bool projectInsertData(QString clientName,int projectID);
    // 修改订单
    bool modifyprojectData(QString clientName,int projectID,int projectNum);
    //删除订单
    bool deleteData(QString clientName,int projectID);
    //清空某账户购物车
    bool deleteClient(QString clientName);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif // SQLITESHOP_H
