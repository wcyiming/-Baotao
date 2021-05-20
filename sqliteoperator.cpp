#include "sqliteoperator.h"

SqliteOperator::SqliteOperator()
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
            database.setDatabaseName("AccountDataBase.db");
        }
}

    // 打开数据库
bool SqliteOperator::openDb()
{
        if (!database.open())
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        }
        else
        {
            QString tableName = "Account" ;
            if (!isTableExist((tableName)))
            {
                createTable();
            }
        }
        return true;
}

    // 创建数据表
void SqliteOperator::createTable()
{
        // 用于执行sql语句的对象
        QSqlQuery sqlQuery;
        // 构建创建数据库的sql语句字符串
        QString createSql = QString("CREATE TABLE Account (\
                              ID INT PRIMARY KEY NOT NULL,\
                              Name TEXT NOT NULL,\
                              Password TEXT NOT NULL,\
                              Purse INT NOT NULL,\
                              Type INT NOT NULL)");
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
bool SqliteOperator::isTableExist(QString& tableName)
{
        QSqlDatabase database = QSqlDatabase::database();
        if(database.tables().contains(tableName))
        {
            return true;
        }

        return false;
}

    // 查询数据
int SqliteOperator::ifquery(QString Name)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("SELECT * FROM Account WHERE Name = '%1'").arg(Name));
        if(!sqlQuery.next()){
                qDebug() << "The Account doesn't exist." ;
                return 0;
            }
            else{
                qDebug() << "The Account exists." ;
                int TYPE = sqlQuery.value(4).toInt();
                return TYPE;
            }
}

Account_user SqliteOperator::searchUserQuery (QString username)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("SELECT * FROM Account WHERE Name = '%1'").arg(username));
        sqlQuery.next();
        Account_user nowUser ;
        nowUser.ID = sqlQuery.value(0).toInt();
        nowUser.Name = sqlQuery.value(1).toString();
        nowUser.Password = sqlQuery.value(2).toString();
        nowUser.Purse = sqlQuery.value(3).toInt();
        nowUser.Type = sqlQuery.value(4).toInt();
        return nowUser;
}

Account_user SqliteOperator::searchUserIDQuery (int ID)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("SELECT * FROM Account WHERE ID = '%1'").arg(ID));
        sqlQuery.next();
        Account_user nowUser ;
        nowUser.ID = sqlQuery.value(0).toInt();
        nowUser.Name = sqlQuery.value(1).toString();
        nowUser.Password = sqlQuery.value(2).toString();
        nowUser.Purse = sqlQuery.value(3).toInt();
        nowUser.Type = sqlQuery.value(4).toInt();
        return nowUser;
}

Account_sailer SqliteOperator::searchSailerQuery(QString username)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("SELECT * FROM Account WHERE Name = '%1'").arg(username));
    Account_sailer nowUser ;
    sqlQuery.next();
    nowUser.ID = sqlQuery.value(0).toInt();
    nowUser.Name = sqlQuery.value(1).toString();
    nowUser.Password = sqlQuery.value(2).toString();
    nowUser.Purse = sqlQuery.value(3).toInt();
    nowUser.Type = sqlQuery.value(4).toInt();
    return nowUser;
}
//找最大id、建立管理员账号
int SqliteOperator::searchMaxID()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM Account WHERE ID = '0' ");
    if(!sqlQuery.next()){
        Account_user Data ;
        Data.ID = 0;
        Data.Name = "admin";
        Data.Password = "114514";
        Data.Purse = 0;
        Data.Type = 2;
        QSqlQuery nowSql;
        nowSql.prepare("INSERT INTO Account VALUES(:ID,:Name,:Password,:Purse,:Type)");
        nowSql.bindValue(":ID", Data.ID);
        nowSql.bindValue(":Name", Data.Name);
        nowSql.bindValue(":Password", Data.Password);
        nowSql.bindValue(":Purse", Data.Purse);
       nowSql.bindValue(":Type", Data.Type);
       if(!nowSql.exec())
       {
           qDebug() << "Error: Fail to insert 2data. " << sqlQuery.lastError();
       }
       else
       {
           qDebug() << "success to insert sb data! ";
       }
       nowSql.finish();
    }
    sqlQuery.exec("SELECT max(ID) FROM Account");
    sqlQuery.next();
    int nowID =sqlQuery.value(0).toInt();
     qDebug("maxid %d",nowID);
    sqlQuery.finish();
    return nowID + 1;

}
    // 插入数据
bool SqliteOperator::userInsertData(Account_user &Data)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("INSERT INTO Account VALUES(:ID,:Name,:Password,:Purse,:Type)");
        sqlQuery.bindValue(":ID", Data.ID);
        sqlQuery.bindValue(":Name", Data.Name);
        sqlQuery.bindValue(":Password", Data.Password);
        sqlQuery.bindValue(":Purse", Data.Purse);
        sqlQuery.bindValue(":Type", Data.getUserType());
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
bool SqliteOperator::modifyUserData(Account_user & Data)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("UPDATE Account SET Name=?,Password=?,Purse=? WHERE ID = ?");
        sqlQuery.addBindValue(Data.Name);
        sqlQuery.addBindValue(Data.Password);
        sqlQuery.addBindValue(Data.Purse);
        sqlQuery.addBindValue(Data.ID);
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

bool SqliteOperator::modifySailerData(Account_sailer & Data)
{
        QSqlQuery sqlQuery;
        sqlQuery.prepare("UPDATE Account SET Name=?,Password=?,Purse=? WHERE ID = ?");
        sqlQuery.addBindValue(Data.Name);
        sqlQuery.addBindValue(Data.Password);
        sqlQuery.addBindValue(Data.Purse);
        sqlQuery.addBindValue(Data.ID);
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
bool SqliteOperator::deleteData(int id)
{
        QSqlQuery sqlQuery;
        sqlQuery.exec(QString("DELETE FROM Account WHERE id = %1").arg(id));
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
