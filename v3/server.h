#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "devide.h"

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

public slots:
    void server_New_Connect();        //新链接建立
    void socket_Read_Data();          //监听报文，并回复报文

};

#endif // SERVER_H
