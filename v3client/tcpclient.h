#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
extern QString ClientJWT;

#define HOST "localhost"
#define PORT 11451

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    QTcpSocket *tcpSocket = nullptr;
    int connectServer();
    void disconnectServer();
    void sendData(QJsonObject nowObject);
    QByteArray recvData(QJsonObject nowObject);
    QByteArray recvJWT(QJsonObject nowObject);


    QString jwtStr;



};


#endif // TCPCLIENT_H
