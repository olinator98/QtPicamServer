#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include "client.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server();
    ~Server();
    void doConnect();


    QList<QTcpSocket *> getConnectedClients() const;
    void setConnectedClients(const QList<QTcpSocket *> &value);

private:
    QTcpSocket *clientSocket;
    QTcpServer *server;

    QList<QTcpSocket*> connectedClients;


public slots:
    void newConnection();
    void removeFromList(QTcpSocket *clientSocket); //if signalDisconnected is true, remove the item from the QList

};

#endif // SERVER_H
