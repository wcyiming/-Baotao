#ifndef DEVIDE_H
#define DEVIDE_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDoubleValidator>
#include "Classes.h"
#include "sqliteshop.h"
#include "sqliteoperator.h"
#include "sqilteopreatorprojects.h"
#include "jwt.h"

const QByteArray jwt_secret = "19j114e514sa9";

class devide
{
public:
    devide();
    bool check(QJsonObject nowJson, QString nowName);       //检查JWT存储的用户名字是否合法
    bool checkid(QJsonObject nowJson, int nowID);           //检查JWT存储的用户ID是否合法

    QByteArray RUN(QByteArray ask);                         //将报文转换为QJsonObject，并解析操作类型

    QByteArray op1(QJsonObject askob);
    QByteArray op2(QJsonObject askob);
    QByteArray op3(QJsonObject askob);
    QByteArray op4(QJsonObject askob);
    QByteArray op5(QJsonObject askob);
    QByteArray op6(QJsonObject askob);
    QByteArray op7(QJsonObject askob);
    QByteArray op8(QJsonObject askob);
    QByteArray op9(QJsonObject askob);
    QByteArray op10(QJsonObject askob);
    QByteArray op11(QJsonObject askob);
    QByteArray op12(QJsonObject askob);
    QByteArray op13(QJsonObject askob);
    QByteArray op14(QJsonObject askob);
    QByteArray op15(QJsonObject askob);
    QByteArray op16(QJsonObject askob);
    QByteArray op17(QJsonObject askob);
    QByteArray op18(QJsonObject askob);
    QByteArray op19(QJsonObject askob);
    QByteArray op20(QJsonObject askob);
    QByteArray op21(QJsonObject askob);
    QByteArray op22(QJsonObject askob);
    QByteArray op23(QJsonObject askob);
    QByteArray op24(QJsonObject askob);
    QByteArray op25(QJsonObject askob);
    QByteArray op26(QJsonObject askob);
    QByteArray op27(QJsonObject askob);
};

#endif // DEVIDE_H
