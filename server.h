#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include "client.h";

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server();
    ~Server();
    void doConnect();

private:
    QTcpSocket *clientConnection;
    QTcpServer *server;

    QList<QTcpSocket*> connectedClients;


signals:


public slots:
    void newConnection();

};

#endif // SERVER_H
