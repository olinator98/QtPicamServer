#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include "client.h"

class Client;

class Server : public QObject
{

    Q_OBJECT


public:
    explicit Server();
    ~Server();
    void doConnect();
    void removeFromList(QHostAddress addr);

    QList<QTcpSocket *> getConnectedClients() const;
    void setConnectedClients(const QList<QTcpSocket *> &value);

private:
    Client *client;
    QTcpServer *server;
    QTcpSocket *clientConnection;
    QList<QTcpSocket *> connectedClients;

    int counterOfConn;




signals:


public slots:
    void newConnection();

};

#endif // SERVER_H
