#include "sqliteshop.h"

sqliteShop::sqliteShop()
{

    return;
}

    // 打开数据库
bool sqliteShop::openDb()
{

        return true;
}

    // 创建数据表
void sqliteShop::createTable()
{
        return;
}

    // 判断数据库中某个数据表是否存在
bool sqliteShop::isTableExist(QString& tableName)
{
    return true;


    /*    QSqlDatabase database = QSqlDatabase::database();
        if(database.tables().contains(tableName))
        {
            return true;
        }

        return false; */
}


std::vector<int> sqliteShop::searchShopName(QString projectName)
{

    QJsonObject nowObject;
    nowObject.insert("messageType", 1);
    nowObject.insert("name" ,projectName.toStdString().c_str());

    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    QJsonObject ansobject = doucment.object();
    QJsonArray productArrayList = ansobject.value("anslist").toArray();
    std::vector<int> w_list;
    for(int i = 0;i < productArrayList.size() ; i++)
    {
        QJsonObject ansob = productArrayList[i].toObject();
        int nowAns = ansob.value("id").toInt();
        w_list.push_back(nowAns);
    }
    return w_list;

/*    QSqlQuery sqlQuery;
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
        } */
}

int sqliteShop::searchProjectNumber(QString clientName,int projectID)
{
    QJsonObject nowObject;
    nowObject.insert("messageType", 2);
    nowObject.insert("name" ,clientName.toStdString().c_str());
    nowObject.insert("projectID" ,projectID);


    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject ansobject = doucment.object();
        int ans = ansobject.value("number").toInt();
        return ans;
    }
    else
    {
        return -1;
    }



    /*
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
        }*/
}
//具体数值

//找最大id、建立id1
int sqliteShop::searchMaxID()
{
    QJsonObject nowObject;
    nowObject.insert("messageType", 3);

    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject ansobject = doucment.object();
        int ans = ansobject.value("maxID").toInt();
        return ans;
    }
    else
    {
        return -1;
    }

    /*
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
    */


}
    // 插入数据
bool sqliteShop::projectInsertData(QString clientName,int projectID)
{

    QJsonObject nowObject;
    nowObject.insert("messageType", 4);
    nowObject.insert("name" ,clientName.toStdString().c_str());
    nowObject.insert("projectID" ,projectID);


    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject ansobject = doucment.object();
        bool ans = ansobject.value("number").toBool();
        return ans;
    }
    else
    {
        return 1;
    }


    /*
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
        */
}
    // 修改数据
bool sqliteShop::modifyprojectData(QString clientName,int projectID,int projectNum)
{
    QJsonObject nowObject;
    nowObject.insert("messageType", 5);
    nowObject.insert("name" ,clientName.toStdString().c_str());
    nowObject.insert("projectID" ,projectID);
    nowObject.insert("projectNum" ,projectNum);


    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject ansobject = doucment.object();
        bool ans = ansobject.value("number").toBool();
        return ans;
    }
    else
    {
        return 1;
    }



    /*
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
        }*/
}
    // 删除数据
bool sqliteShop::deleteData(QString clientName,int projectID)
{
    QJsonObject nowObject;
    nowObject.insert("messageType", 6);
    nowObject.insert("name" ,clientName.toStdString().c_str());
    nowObject.insert("projectID" ,projectID);


    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject ansobject = doucment.object();
        bool ans = ansobject.value("number").toBool();
        return ans;
    }
    else
    {
        return 1;
    }


    /*
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
        }*/
}

bool sqliteShop::deleteClient(QString clientName)
{
    QJsonObject nowObject;
    nowObject.insert("messageType", 7);
    nowObject.insert("name" ,clientName.toStdString().c_str());


    TcpClient *nowTCP = new TcpClient();
    QByteArray ansArray;
    ansArray = nowTCP->recvData(nowObject);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ansArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject ansobject = doucment.object();
        bool ans = ansobject.value("number").toBool();
        return ans;
    }
    else
    {
        return 1;
    }


    /*
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
        }*/
}
