#include "server.h"

Server::Server(QWidget *parent) : QWidget(parent)
{
    tcpServer = new QTcpServer();
       if(!tcpServer->listen(QHostAddress::Any, 11451))
       {
           qDebug()<<tcpServer->errorString();
           return;
       }
       connect(tcpServer,&QTcpServer::newConnection,this,&Server::server_New_Connect);
}



void Server::server_New_Connect()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Server::socket_Read_Data);
}


void Server::socket_Read_Data()
{
    QByteArray buffer;
    buffer = tcpSocket->readAll();
    while(this->tcpSocket->waitForReadyRead(30))
    {
        buffer.append(this->tcpSocket->readAll());
    }
    devide *deviding = new devide();
    QByteArray ans = deviding->RUN(buffer);
    tcpSocket->write(ans);


}


Server::~Server()
{
    tcpServer->close();
    delete tcpServer;
    tcpSocket->abort();
    delete tcpSocket;
}
