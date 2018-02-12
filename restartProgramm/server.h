#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QProcess>


class Server : public QObject
{
    Q_OBJECT

public:
    Server();
    void doConnect();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
    QObject *parent;

public slots:
    void newConnection();
};

#endif // SERVER_H
