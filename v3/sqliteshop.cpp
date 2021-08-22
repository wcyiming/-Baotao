#include "sqliteshop.h"

sqliteShop::sqliteShop()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
        {
            database = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
            // 建立和SQlite数据库的连接
            database = QSqlDatabase::addDatabase("QSQLITE");
            // 设置数据库文件的名字
            database.setDatabaseName("ShopDataBase.db");
        }
}

    // 打开数据库
bool sqliteShop::openDb()
{
        if (!database.open())
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        }
        else
        {
            QString tableName = "shopList" ;
            if (!isTableExist((tableName)))
            {
                createTable();
            }
        }
        return true;
}

    // 创建数据表
void sqliteShop::createTable()
{
        // 用于执行sql语句的对象
        QSqlQuery sqlQuery;
        // 构建创建数据库的sql语句字符串
        QString createSql = QString("CREATE TABLE shopList (\
                              ID INT PRIMARY KEY NOT NULL,\
                              Name TEXT NOT NULL,\
                              projectID INT NOT NULL,\
                              number INT NOT NULL)");
        sqlQuery.prepare(createSql);
        // 执行sql语句
        if(!sqlQuery.exec())
        {
            qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
}

    // 判断数据库中某个数据表是否存在
bool sqliteShop::isTableExist(QString& tableName)
{
        QSqlDatabase database = QSqlDatabase::database();
        if(database.tables().contains(tableName))
        {
            return true;
        }

        return false;
}


std::vector<int> sqliteShop::searchShopName(QString projectName)
{
    QSqlQuery sqlQuery;
    qDebug("=%s=",qPrintable(projectName));
    sqlQuery.exec(QString("SELECT * FROM shopList WHERE Name = '%1'").arg(projectName));
    if(!sqlQuery.exec())
        {
            std::vector<int> list;
            list.push_back(-1);
            qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
            return list;            
        }
        else
        {
            std::vector<int> project_list;
            if(!sqlQuery.next())
            {
                project_list.push_back(-1);
            }
            else
            {
                project_list.push_back(sqlQuery.value(2).toInt());
                qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(2).toInt()).arg(sqlQuery.value(1).toString());
                while(sqlQuery.next())
                {
                    project_list.push_back(sqlQuery.value(2).toInt());
                    qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(2).toInt()).arg(sqlQuery.value(1).toString());
                }
            }

            return project_list;
        }
}

int sqliteShop::searchProjectNumber(QString clientName,int projectID)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("SELECT * FROM shopList WHERE Name = '%1' AND projectID = '%2'").arg(clientName).arg(projectID));
    if(!sqlQuery.exec())
        {
            return -1;
            qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
        }
        else
        {
            if(!sqlQuery.next())
            {
                return -1;
            }
            else
            {
                int projectNumber = sqlQuery.value(3).toInt();
                qDebug()<<QString("id:%1  ?  name:%2  number:%3").arg(sqlQuery.value(2).toInt()).arg(sqlQuery.value(1).toString()).arg(sqlQuery.value(2).toInt());
                return projectNumber;
            }
        }
}
//具体数值

//找最大id、建立id1
int sqliteShop::searchMaxID()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM shopList WHERE ID = '1' ");
    if(!sqlQuery.next()){
        return 1;
    }
    sqlQuery.exec("SELECT max(ID) FROM shopList");
    sqlQuery.next();
    int nowID =sqlQuery.value(0).toInt();
     qDebug("maxid %d",nowID);
    sqlQuery.finish();
    return nowID + 1;
}
    // 插入数据
bool sqliteShop::projectInsertData(QString clientName,int projectID)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("SELECT * FROM shopList WHERE Name = '%1' AND projectID = '%2'").arg(clientName).arg(projectID));

        if(!sqlQuery.next())
        {
            int nowID = searchMaxID();
            int number = 1;
            qDebug("id = %d",nowID);
            sqlQuery.prepare("INSERT INTO shopList VALUES(:ID,:Name,:projectID,:number)");
            sqlQuery.bindValue(":ID", nowID );
            sqlQuery.bindValue(":Name", clientName);
            sqlQuery.bindValue(":projectID", projectID);
            sqlQuery.bindValue(":number", number);
            if(!sqlQuery.exec())
            {
                qDebug() << "Error: Fail to insert 1data. " << sqlQuery.lastError();
                return 1;
            }
            else
            {
                qDebug() << "success to insert data! ";
                return 0;
            }
        }
        else
        {
            int projectNumber = sqlQuery.value(3).toInt();
            projectNumber++;
            qDebug()<<QString("id:%1  ?  name:%2  number:%3").arg(sqlQuery.value(2).toInt()).arg(sqlQuery.value(1).toString()).arg(sqlQuery.value(2).toInt());
            sqlQuery.prepare("UPDATE shopList SET number=? WHERE  Name = ? AND projectID = ?");
            sqlQuery.addBindValue(projectNumber);
            sqlQuery.addBindValue(clientName);
            sqlQuery.addBindValue(projectID);
            if(!sqlQuery.exec())
            {
                qDebug() << sqlQuery.lastError();
                return 1;
            }
            else
            {
                qDebug() << "updated data success!";
                return 0;
            }
        }

}
    // 修改数据
bool sqliteShop::modifyprojectData(QString clientName,int projectID,int projectNum)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("UPDATE shopList SET number = ? WHERE  Name = ? AND projectID = ?");
        sqlQuery.addBindValue(projectNum);
        sqlQuery.addBindValue(clientName);
        sqlQuery.addBindValue(projectID);
        if(!sqlQuery.exec())
        {
            qDebug() << sqlQuery.lastError();
            return 1;
        }
        else
        {
            qDebug() << "updated data success!";
            return 0;
        }
}
    // 删除数据
bool sqliteShop::deleteData(QString clientName,int projectID)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("DELETE FROM shopList WHERE Name = '%1' AND projectID = '%2'").arg(clientName).arg(projectID));
        if(!sqlQuery.exec())
        {
            qDebug()<<sqlQuery.lastError();
            return 1;
        }
        else
        {
            qDebug()<<"deleted data success!";
            return 0;
        }
}

bool sqliteShop::deleteClient(QString clientName)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("DELETE FROM shopList WHERE Name = '%1'").arg(clientName));
        if(!sqlQuery.exec())
        {
            qDebug()<<sqlQuery.lastError();
            return 1;
        }
        else
        {
            qDebug()<<"deleted data success!";
            return 0;
        }
}
