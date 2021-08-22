#include "devide.h"

devide::devide()
{

}

QByteArray devide::RUN(QByteArray ask)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(ask, &jsonError);
    QJsonObject askobject = doucment.object();

    int types = askobject.value("messageType").toInt();
    qDebug()<<QString("%1").arg(types);
    switch(types)
    {
        case 1:
        return op1(askobject);
        break;

        case 2:
        return op2(askobject);
        break;
        case 3:
        return op3(askobject);
        break;
        case 4:
        return op4(askobject);
        break;
        case 5:
        return op5(askobject);
        break;
        case 6:
        return op6(askobject);
        break;
        case 7:
        return op7(askobject);
        break;
        case 8:
        return op8(askobject);
        break;
        case 9:
        return op9(askobject);
        break;
        case 10:
        return op10(askobject);
        break;
        case 11:
        return op11(askobject);
        break;
        case 12:
        return op12(askobject);
        break;
        case 13:
        return op13(askobject);
        break;
        case 14:
        return op14(askobject);
        break;
        case 15:
        return op15(askobject);
        break;
        case 16:
        return op16(askobject);
        break;
        case 17:
        return op17(askobject);
        break;
        case 18:
        return op18(askobject);
        break;
        case 19:
        return op19(askobject);
        break;
        case 20:
        return op20(askobject);
        break;
        case 21:
        return op21(askobject);
        break;
        case 22:
        return op22(askobject);
        break;
        case 23:
        return op23(askobject);
        break;
        case 24:
        return op24(askobject);
        break;
        case 25:
        return op25(askobject);
        break;
        case 26:
        return op26(askobject);
        break;
        case 27:
        return op27(askobject);
        break;

        default :
        return 0;
    }
}

bool devide::check(QJsonObject nowJson, QString nowName)
{
    if(nowJson.contains("JWT"))
    {
        QString nowJWT = nowJson.value("JWT").toString();
        QByteArray JWTArray = nowJWT.toUtf8();
        jwt W ;

        if(!W.verify_jwt(JWTArray ,jwt_secret))
        {
            return true;
        }
    }

    QString nowJWT = nowJson.value("JWT").toString();
    QByteArray JWTArray = nowJWT.toUtf8();
    jwt W;
    QJsonObject nowObject = W.decode_jwt(JWTArray);
    QString nowNameStr = nowObject.value("Name").toString();
    if(nowName.compare(nowNameStr))
    {
        return true;
    }
   qDebug()<<QString("%1  %2").arg(nowName).arg(nowNameStr);
    return false;

}

bool devide::checkid(QJsonObject nowJson, int nowID)
{
    if(nowJson.contains("JWT"))
    {
        QString nowJWT = nowJson.value("JWT").toString();
        QByteArray JWTArray = nowJWT.toUtf8();
        jwt W ;

        if(!W.verify_jwt(JWTArray ,jwt_secret))
        {
            return false;
        }
    }
    QString nowJWT = nowJson.value("JWT").toString();
    QByteArray JWTArray = nowJWT.toUtf8();
    jwt W;
    QJsonObject nowObject = W.decode_jwt(JWTArray);
    int nowid = nowObject.value("id").toInt();
    qDebug()<<QString("%1  %2").arg(nowid).arg(nowID);
    if(nowid == nowID)
    {
        return true;
    }
    return false;
}

QByteArray devide::op1(QJsonObject askob)
{
    QString nowName = askob.value("name").toString();
    if(check(askob,nowName)) return 0;


    qDebug()<<QString("%1 cao").arg(nowName);
    sqliteShop nowCar;
    nowCar.openDb();
    QString projectName = askob.value("name").toString();
    std::vector<int> w_list;
    w_list = nowCar.searchShopName(projectName);
    QJsonArray listArray;
    for(int i = 0;i <(int)w_list.size() ; i++)
    {
        QJsonObject roam;
        roam.insert("id",w_list[i]);
        listArray.append(roam);
    }

    QJsonObject ansob;
    ansob.insert("anslist",listArray);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op2(QJsonObject askob)
{
    QString nowName = askob.value("name").toString();
    if(check(askob,nowName)) return 0;

    sqliteShop nowCar;
    nowCar.openDb();
    QString projectName = askob.value("name").toString();
    int projectID = askob.value("projectID").toInt();
    int ans;
    ans = nowCar.searchProjectNumber(projectName,projectID);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op3(QJsonObject askob)
{
    sqliteShop nowCar;
    nowCar.openDb();

    int ans;
    ans = nowCar.searchMaxID();

    QJsonObject ansob;
    ansob.insert("maxID",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op4(QJsonObject askob)
{
    QString nowName = askob.value("name").toString();
    if(check(askob,nowName)) return 0;

    sqliteShop nowCar;
    nowCar.openDb();
    QString projectName = askob.value("name").toString();
    int projectID = askob.value("projectID").toInt();
    bool ans;
    ans = nowCar.projectInsertData(projectName,projectID);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op5(QJsonObject askob)
{
    QString nowName = askob.value("name").toString();
    if(check(askob,nowName)) return 0;

    sqliteShop nowCar;
    nowCar.openDb();
    QString projectName = askob.value("name").toString();
    int projectID = askob.value("projectID").toInt();
    int projectNum = askob.value("projectNum").toInt();
    bool ans;
    ans = nowCar.modifyprojectData(projectName,projectID,projectNum);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op6(QJsonObject askob)
{
    sqliteShop nowCar;
    nowCar.openDb();
    QString projectName = askob.value("name").toString();
    int projectID = askob.value("projectID").toInt();
    bool ans;
    ans = nowCar.deleteData(projectName,projectID);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op7(QJsonObject askob)
{
    QString nowName = askob.value("name").toString();
    if(check(askob,nowName)) return 0;

    sqliteShop nowCar;
    nowCar.openDb();
    QString projectName = askob.value("name").toString();
    bool ans;
    ans = nowCar.deleteClient(projectName);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op8(QJsonObject askob)
{

    SqliteOperator Account_db;
    Account_db.openDb();
    QString userName = askob.value("name").toString();

    int ans;
    ans = Account_db.ifquery(userName);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op9(QJsonObject askob)
{
    QString nowName = askob.value("name").toString();
    if(check(askob,nowName)) return 0;

    SqliteOperator Account_db;
    Account_db.openDb();
    QString userName = askob.value("name").toString();

    Account_user ans;
    ans = Account_db.searchUserQuery(userName);

    QJsonObject ansob;
    ansob.insert("ID",ans.ID);
    ansob.insert("Name",ans.Name.toStdString().c_str());
    ansob.insert("Password",ans.Password.toStdString().c_str());
    ansob.insert("Purse",ans.Purse);
    ansob.insert("Type",ans.Type);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op10(QJsonObject askob)
{
//    int nowID = askob.value("ID").toInt();
//    if(!checkid(askob,nowID)) return 0;

    SqliteOperator Account_db;
    Account_db.openDb();
    int askid = askob.value("ID").toInt();

    Account_user ans;
    ans = Account_db.searchUserIDQuery(askid);

    QJsonObject ansob;
    ansob.insert("ID",ans.ID);
    ansob.insert("Name",ans.Name.toStdString().c_str());
    ansob.insert("Password",ans.Password.toStdString().c_str());
    ansob.insert("Purse",ans.Purse);
    ansob.insert("Type",ans.Type);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op11(QJsonObject askob)
{
    SqliteOperator Account_db;
    Account_db.openDb();
    QString userName = askob.value("name").toString();

    Account_sailer ans;
    ans = Account_db.searchSailerQuery(userName);

    QJsonObject ansob;
    ansob.insert("ID",ans.ID);
    ansob.insert("Name",ans.Name.toStdString().c_str());
    ansob.insert("Password",ans.Password.toStdString().c_str());
    ansob.insert("Purse",ans.Purse);
    ansob.insert("Type",ans.Type);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op12(QJsonObject askob)
{

    SqliteOperator Account_db;
    Account_db.openDb();

    int ans;
    ans = Account_db.searchMaxID();
    qDebug("maxid %d",ans);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op13(QJsonObject askob)
{
    SqliteOperator Account_db;
    Account_db.openDb();
    Account_user nowUser;
    nowUser.ID = askob.value("ID").toInt();
    nowUser.Name = askob.value("Name").toString();
    nowUser.Password = askob.value("Password").toString();
    nowUser.Purse = askob.value("Purse").toInt();
    nowUser.Type = askob.value("Type").toInt();

    bool ans;
    ans = Account_db.userInsertData(nowUser);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op14(QJsonObject askob)
{
//    QString nowName = askob.value("Name").toString();
//    if(check(askob,nowName)) return 0;

    SqliteOperator Account_db;
    Account_db.openDb();
    Account_user nowUser;
    nowUser.ID = askob.value("ID").toInt();
    nowUser.Name = askob.value("Name").toString();
    nowUser.Password = askob.value("Password").toString();
    nowUser.Purse = askob.value("Purse").toInt();
    nowUser.Type = askob.value("Type").toInt();

    bool ans;
    ans = Account_db.modifyUserData(nowUser);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op15(QJsonObject askob)
{
        qDebug()<<QString("cao ");
    QString nowName = askob.value("Name").toString();
    if(check(askob,nowName)) return 0;

    SqliteOperator Account_db;
    Account_db.openDb();
    Account_sailer nowUser;
    nowUser.ID = askob.value("ID").toInt();
    nowUser.Name = askob.value("Name").toString();
    nowUser.Password = askob.value("Password").toString();
    nowUser.Purse = askob.value("Purse").toInt();
    nowUser.Type = askob.value("Type").toInt();

    qDebug()<<QString("cao %1").arg(nowUser.Password);


    bool ans;
    ans = Account_db.modifySailerData(nowUser);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op16(QJsonObject askob)
{
    int nowID = askob.value("id").toInt();
    if(!checkid(askob,nowID)) return 0;

    SqliteOperator Account_db;
    Account_db.openDb();
    int userID = askob.value("id").toInt();

    bool ans;
    ans = Account_db.deleteData(userID);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op17(QJsonObject askob)
{
    SqliteOperator Account_db;
    Account_db.openDb();
    QString userName = askob.value("name").toString();
    QString userPass = askob.value("password").toString();
    Account_user nowUser;
    nowUser = Account_db.searchUserQuery(userName);

    QJsonObject ansob;

    bool ans = 0 ;
    if(nowUser.Password.compare(userPass))
    {
        ans = 1;
    }
    else
    {
        jwt *W = new jwt();
        QByteArray JWT;
        QJsonObject payload;
        payload.insert("id",nowUser.ID);
        payload.insert("Name",nowUser.Name.toStdString().c_str());
        JWT = W->encode_jwt(payload , jwt_secret);
        QString jwtStr = QString(JWT);
        ansob.insert("JWT",jwtStr);
    }
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}



QByteArray devide::op18(QJsonObject askob)
{
    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    QString projectName = askob.value("name").toString();
    std::vector<int> w_list;
    w_list = Project_db.searchProjectName(projectName);

    QJsonArray listArray;
    for(int i = 0;i <(int)w_list.size() ; i++)
    {
        QJsonObject roam;
        roam.insert("id",w_list[i]);
        listArray.append(roam);
    }

    QJsonObject ansob;
    ansob.insert("anslist",listArray);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op19(QJsonObject askob)
{
    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    std::vector<int> w_list;
    w_list = Project_db.searchProjectAll();

    QJsonArray listArray;
    for(int i = 0;i <(int)w_list.size() ; i++)
    {
        QJsonObject roam;
        roam.insert("id",w_list[i]);
        listArray.append(roam);
    }

    QJsonObject ansob;
    ansob.insert("anslist",listArray);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op20(QJsonObject askob)
{
    int nowID = askob.value("projectFather").toInt();
    if(!checkid(askob,nowID)) return 0;


    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    int projectFather = askob.value("projectFather").toInt();
    std::vector<int> w_list;
    w_list = Project_db.searchProjectFather(projectFather);


    QJsonArray listArray;
    for(int i = 0;i <(int)w_list.size() ; i++)
    {
        QJsonObject roam;
        roam.insert("id",w_list[i]);
        listArray.append(roam);
    }

    QJsonObject ansob;
    ansob.insert("anslist",listArray);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op21(QJsonObject askob)
{
    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    int projectID = askob.value("projectID").toInt();

    Projects_books ans;
    ans = Project_db.searchProjectInfo(projectID);

    QJsonObject ansob;
    ansob.insert("id",ans.id);
    ansob.insert("Name",ans.Name.toStdString().c_str());
    ansob.insert("infor",ans.infor.toStdString().c_str());
    ansob.insert("prise",ans.prise);
    ansob.insert("type",ans.type);
    ansob.insert("number",ans.number);
    ansob.insert("discount",ans.discount);
    ansob.insert("father",ans.father);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op22(QJsonObject askob)
{
    sqilteOpreatorProjects Project_db;
    Project_db.openDb();

    int ans;
    ans = Project_db.searchMaxID();

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}


QByteArray devide::op23(QJsonObject askob)
{
    int nowID = askob.value("father").toInt();
    if(!checkid(askob,nowID)) return 0;


    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    Projects_books nowBook;
    nowBook.id = askob.value("id").toInt();
    nowBook.Name = askob.value("Name").toString();
    nowBook.infor = askob.value("infor").toString();
    nowBook.prise = askob.value("prise").toInt();
    nowBook.type = askob.value("type").toInt();
    nowBook.number = askob.value("number").toInt();
    nowBook.discount = askob.value("discount").toInt();
    nowBook.father = askob.value("father").toInt();

    bool ans;
    ans = Project_db.projectInsertData(nowBook);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op24(QJsonObject askob)
{
    int nowID = askob.value("father").toInt();
    if(!checkid(askob,nowID)) return 0;


    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    Projects_books nowBook;
    nowBook.id = askob.value("id").toInt();
    nowBook.Name = askob.value("Name").toString();
    nowBook.infor = askob.value("infor").toString();
    nowBook.prise = askob.value("prise").toInt();
    nowBook.type = askob.value("type").toInt();
    nowBook.number = askob.value("number").toInt();
    nowBook.discount = askob.value("discount").toInt();
    nowBook.father = askob.value("father").toInt();
    qDebug()<<QString("cao %1").arg(nowBook.discount);

    bool ans;
    ans = Project_db.modifyprojectData(nowBook);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op25(QJsonObject askob)
{
    int nowID = askob.value("father").toInt();
    if(!checkid(askob,nowID)) return 0;


    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    Projects_books nowBook;
    nowBook.id = askob.value("id").toInt();
    nowBook.Name = askob.value("Name").toString();
    nowBook.infor = askob.value("infor").toString();
    nowBook.prise = askob.value("prise").toInt();
    nowBook.type = askob.value("type").toInt();
    nowBook.number = askob.value("number").toInt();
    nowBook.discount = askob.value("discount").toInt();
    qDebug()<<QString("cao %1").arg(nowBook.discount);
    nowBook.father = askob.value("father").toInt();

    bool ans;
    ans = Project_db.modifyprojectDiscount(nowBook);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray devide::op26(QJsonObject askob)
{
    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    int projectID = askob.value("id").toInt();
    int number = askob.value("number").toInt();

    bool ans;
    ans = Project_db.modifyprojectNumber(projectID,number);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}



QByteArray devide::op27(QJsonObject askob)
{
    sqilteOpreatorProjects Project_db;
    Project_db.openDb();
    int projectID = askob.value("id").toInt();

    bool ans;
    ans = Project_db.deleteData(projectID);

    QJsonObject ansob;
    ansob.insert("number",ans);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(ansob);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    return data;
}






