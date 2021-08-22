#include "sqilteopreatorprojects.h"

sqilteOpreatorProjects::sqilteOpreatorProjects()
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
            database.setDatabaseName("ProjectDataBase.db");
        }
}

    // 打开数据库
bool sqilteOpreatorProjects::openDb()
{
        if (!database.open())
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        }
        else
        {
            QString tableName = "Project" ;
            if (!isTableExist((tableName)))
            {
                createTable();
            }
        }
        return true;
}

    // 创建数据表
void sqilteOpreatorProjects::createTable()
{
        // 用于执行sql语句的对象
        QSqlQuery sqlQuery;
        // 构建创建数据库的sql语句字符串
        QString createSql = QString("CREATE TABLE Project (\
                              ID INT PRIMARY KEY NOT NULL,\
                              Name TEXT NOT NULL,\
                              infor TEXT NOT NULL,\
                              prise INT NOT NULL,\
                              type INT NOT NULL,\
                              number INT NOT NULL,\
                              discount INT NOT NULL,\
                              father INT NOT NULL)");
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
bool sqilteOpreatorProjects::isTableExist(QString& tableName)
{
        QSqlDatabase database = QSqlDatabase::database();
        if(database.tables().contains(tableName))
        {
            return true;
        }

        return false;
}

//    // 查询数据
//int sqilteOpreatorProjects::ifquery(int projectID)
//{
//        QSqlQuery sqlQuery;
//        sqlQuery.exec(QString("SELECT * FROM Projects WHERE ID = '%1'").arg(projectID));
//        if(!sqlQuery.next()){
//                qDebug() << "The Account doesn't exist." ;
//                return 0;
//            }
//            else{
//                qDebug() << "The Account exists." ;
//                int TYPE = sqlQuery.value(4).toInt();
//                return TYPE;
//            }
//}

//返回搜索结果
std::vector<int> sqilteOpreatorProjects::searchProjectName(QString projectName)
{
    QSqlQuery sqlQuery;
    qDebug("=%s=",qPrintable(projectName));
    sqlQuery.exec(QString("SELECT * FROM Project WHERE Name LIKE '%%1%'").arg(projectName));
    if(!sqlQuery.exec())
        {
            std::vector<int> list;
            list.push_back(-1);
            return list;
            qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
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
                project_list.push_back(sqlQuery.value(0).toInt());
                qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(0).toInt()).arg(sqlQuery.value(1).toString());
                while(sqlQuery.next())
                {
                    project_list.push_back(sqlQuery.value(0).toInt());
                    qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(0).toInt()).arg(sqlQuery.value(1).toString());
                }
            }

            return project_list;
        }
}
//返回所有
std::vector<int> sqilteOpreatorProjects::searchProjectAll()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM Project");
    if(!sqlQuery.exec())
        {
            std::vector<int> list;
            list.push_back(-1);
            return list;
            qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
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
                project_list.push_back(sqlQuery.value(0).toInt());
                qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(0).toInt()).arg(sqlQuery.value(1).toString());
                while(sqlQuery.next())
                {
                    project_list.push_back(sqlQuery.value(0).toInt());
                    qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(0).toInt()).arg(sqlQuery.value(1).toString());
                }
            }
            return project_list;
        }
}
//商家的儿子
std::vector<int> sqilteOpreatorProjects::searchProjectFather(int projectFather)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("SELECT * FROM Project WHERE father = '%1'").arg(projectFather));
    if(!sqlQuery.exec())
        {
            std::vector<int> list;
            list.push_back(-1);
            return list;
            qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
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
                project_list.push_back(sqlQuery.value(0).toInt());
                qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(0).toInt()).arg(sqlQuery.value(1).toString());
                while(sqlQuery.next())
                {
                    project_list.push_back(sqlQuery.value(0).toInt());
                    qDebug()<<QString("id:%1  ?  name:%2").arg(sqlQuery.value(0).toInt()).arg(sqlQuery.value(1).toString());
                }
            }
            return project_list;
        }
}
//具体数值
Projects_books sqilteOpreatorProjects::searchProjectInfo(int projectID)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("SELECT * FROM Project WHERE ID = '%1'").arg(projectID));
        sqlQuery.next();
        Projects_books nowProject ;
        nowProject.id = sqlQuery.value(0).toInt();
        nowProject.Name = sqlQuery.value(1).toString();
        nowProject.infor = sqlQuery.value(2).toString();
        nowProject.prise = sqlQuery.value(3).toInt();
        nowProject.type = sqlQuery.value(4).toInt();
        nowProject.number = sqlQuery.value(5).toInt();
        nowProject.discount = sqlQuery.value(6).toInt();
        nowProject.father = sqlQuery.value(7).toInt();
        return nowProject;
}


//找最大id、建立id1
int sqilteOpreatorProjects::searchMaxID()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM Project WHERE ID = '1' ");
    if(!sqlQuery.next()){
        return 1;
    }
    sqlQuery.exec("SELECT max(ID) FROM Project");
    sqlQuery.next();
    int nowID =sqlQuery.value(0).toInt();
     qDebug("maxid %d",nowID);
    sqlQuery.finish();
    return nowID + 1;

}
    // 插入数据
bool sqilteOpreatorProjects::projectInsertData(Projects_books &Data)
{
        QSqlQuery sqlQuery;
        qDebug("id = %d",Data.id);
        sqlQuery.prepare("INSERT INTO Project VALUES(:ID,:Name,:infor,:prise,:type,:number,:discount,:father)");
        sqlQuery.bindValue(":ID", Data.id );
        sqlQuery.bindValue(":Name", Data.Name);
        sqlQuery.bindValue(":infor", Data.infor);
        sqlQuery.bindValue(":prise", Data.getPrise());
        sqlQuery.bindValue(":type", Data.type);
        sqlQuery.bindValue(":number", Data.number);
        sqlQuery.bindValue(":discount", Data.discount);
        sqlQuery.bindValue(":father", Data.father);
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
    // 修改数据
bool sqilteOpreatorProjects::modifyprojectData(Projects_books &Data)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("UPDATE Project SET Name=?,infor=?,prise=?,number=?,discount=? WHERE ID = ?");
        sqlQuery.addBindValue(Data.Name);
        sqlQuery.addBindValue(Data.infor);
        sqlQuery.addBindValue(Data.prise);
        sqlQuery.addBindValue(Data.number);
        sqlQuery.addBindValue(Data.discount);
        sqlQuery.addBindValue(Data.id);
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
//打折（仅修改discount）
bool sqilteOpreatorProjects::modifyprojectDiscount(Projects_books &Data)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("UPDATE Project SET discount=? WHERE ID = ?");
        sqlQuery.addBindValue(Data.discount);
        sqlQuery.addBindValue(Data.id);
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

bool sqilteOpreatorProjects::modifyprojectNumber(int nowProjectID,int Number)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("UPDATE Project SET number = ? WHERE ID = ?");
        sqlQuery.addBindValue(Number);
        sqlQuery.addBindValue(nowProjectID);
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
bool sqilteOpreatorProjects::deleteData(int id)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("DELETE FROM Project WHERE id = %1").arg(id));
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


