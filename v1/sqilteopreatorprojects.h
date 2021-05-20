#ifndef SQILTEOPREATORPROJECTS_H
#define SQILTEOPREATORPROJECTS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDoubleValidator>
#include "Classes.h"

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

    std::vector<int> searchProjectName(QString projectName);
    std::vector<int> searchProjectAll();
    std::vector<int> searchProjectFather(int projectFather);

    // 返回具体数据
    Projects_books searchProjectInfo(int projectID);
    int searchMaxID();
    // 插入数据
    bool projectInsertData(Projects_books &Data);
    // 修改数据
    bool modifyprojectData(Projects_books &Data);
    bool modifyprojectDiscount(Projects_books &Data);
    bool deleteData(int id);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};



#endif // SQILTEOPREATORPROJECTS_H
