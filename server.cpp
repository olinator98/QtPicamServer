#include "server.h"


Server::Server()
{

}

Server::~Server()
{

}

void Server::doConnect()
{
    clientConnection = new QTcpSocket(this);
    server = new QTcpServer();

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection())); //this signal is emmited every time a new connection is available

    qDebug()<<"connecting...";

    server->listen(QHostAddress::Any, 12345); //Let the server listening
}



void Server::newConnection()
{
    if(server->hasPendingConnections())
    {
        qDebug()<<"Pending connection";
        qDebug()<<"Checking Permissions...";

        clientConnection = server->nextPendingConnection();

        connectedClients.push_back(clientConnection->peerAddress()); //Add a connected client to the list
        //currently connected threads
        for(std::vector<QHostAddress>::iterator it = connectedClients.begin(); it != connectedClients.end(); it++)
        {
            qDebug()<<*it;
            qDebug()<<"\n";
        }
        Client *client= new Client(clientConnection); //create new client


   }

}




