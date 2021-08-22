#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

}

int TcpClient::connectServer()
{
    tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost(HOST, PORT);
    if(!tcpSocket->waitForConnected(1000))
    {
        qDebug() << "Connection failed!" ;
        return 1;
    }
    qDebug() << "Connect successfully!";
    return 0;
}

void TcpClient::sendData(QJsonObject nowObject)
{
    if (tcpSocket==nullptr)
    {
        connectServer();
    }
    nowObject.insert("JWT",jwtStr);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(nowObject);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    tcpSocket->write(data);
}

void TcpClient::disconnectServer()
{
    if (tcpSocket != nullptr)
    {
        tcpSocket->disconnectFromHost();
        delete tcpSocket;
    }
}

QByteArray TcpClient::recvData(QJsonObject nowObject) // while true, if false
{
    if (tcpSocket==nullptr)
    {
        connectServer();
    }
    nowObject.insert("JWT",ClientJWT);
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(nowObject);    
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    tcpSocket->write(data);
    QByteArray buffer;
    if (tcpSocket->waitForReadyRead(50))
    {
        //读取缓冲区数据
        buffer.append(tcpSocket->readAll());
    }
    return buffer;
}

QByteArray TcpClient::recvJWT(QJsonObject nowObject) // while true, if false
{
    if (tcpSocket==nullptr)
    {
        connectServer();
    }
    QJsonDocument rectJsonDoc;
    rectJsonDoc.setObject(nowObject);
    QByteArray data = rectJsonDoc.toJson(QJsonDocument::Compact);
    tcpSocket->write(data);
    QByteArray buffer;
    if (tcpSocket->waitForReadyRead(50))
    {
        //读取缓冲区数据
        buffer.append(tcpSocket->readAll());
    }
    return buffer;
}


