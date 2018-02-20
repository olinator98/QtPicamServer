#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "client.h"


class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server();
    ~Server();
    void doConnect();

private:
    QTcpSocket *clientSocket;
    QTcpServer *server;
    QList<QTcpSocket*> connectedSockets;
    QList<Client*> connectedClients;
    Client *client;
    void createClient();
    bool checkClient(QTcpSocket *socket);
    Client* getConnectedInstance();
public slots:
    void newConnection();
    void removeFromList(QTcpSocket *clientSocket); //if signalDisconnected is true, remove the item from the QList
};

#endif // SERVER_H
