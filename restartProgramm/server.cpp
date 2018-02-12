#include "server.h"

Server::Server()
{

}

void Server::doConnect()
{
    clientSocket = new QTcpSocket(this);
    server = new QTcpServer();

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection())); //this signal is emmited every time a new connection is available

    qDebug()<<"waiting for command to go steil";

    server->listen(QHostAddress::Any, 55555); //Let the server listening
    parent = nullptr;
}

void Server::newConnection()
{
    qDebug()<<"New connection";
    if(server->hasPendingConnections())
    {
        QProcess *restartProcess = new QProcess(parent);
        qDebug()<<"Restarting server";
        clientSocket->write("restarting");
        (restartProcess->start("sudo reboot now"));

    }
}

