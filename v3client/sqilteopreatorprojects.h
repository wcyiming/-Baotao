#ifndef SQILTEOPREATORPROJECTS_H
#define SQILTEOPREATORPROJECTS_H

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


class sqilteOpreatorProjects
{
public:
    sqilteOpreatorProjects();
    ~sqilteOpreatorProjects(){}

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);    
    // 以商品名字搜索
    std::vector<int> searchProjectName(QString projectName);
    // 搜索全部
    std::vector<int> searchProjectAll();
    // 以商家名字搜索
    std::vector<int> searchProjectFather(int projectFather);

    // 返回具体数据
    Projects_books searchProjectInfo(int projectID);
    //寻找最大商品id
    int searchMaxID();
    // 插入数据
    bool projectInsertData(Projects_books &Data);
    // 修改数据
    bool modifyprojectData(Projects_books &Data);
    // 只修改折扣
    bool modifyprojectDiscount(Projects_books &Data);
    // 只修改数量
    bool modifyprojectNumber(int nowProjectID,int Number);
    // 删除商品
    bool deleteData(int id);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};



#endif // SQILTEOPREATORPROJECTS_H
