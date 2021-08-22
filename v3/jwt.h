#ifndef JWT_H
#define JWT_H
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
#include <QMessageAuthenticationCode>
#include <QString>
#include <QList>
#include "Classes.h"

class jwt
{
public:
    jwt();

    QByteArray encode_jwt(const QJsonObject &payload, const QByteArray &secret);

    bool verify_jwt(const QByteArray &jwt, const QByteArray &secret);

    QJsonObject decode_jwt(const QByteArray &jwt);
};

#endif // JWT_H
