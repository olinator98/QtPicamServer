#include "server.h"


Server::Server()
{

}

Server::~Server()
{

}

void Server::doConnect()
{
    clientSocket = new QTcpSocket(this);
    server = new QTcpServer();

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection())); //this signal is emmited every time a new connection is available

    qDebug()<<"connecting...";

    server->listen(QHostAddress::Any, 12345); //Let the server listening
}

void Server::newConnection()
{
    if(server->hasPendingConnections())
    {
        clientSocket = server->nextPendingConnection();

        //currently connected threads

        //Looks if theres a already a connected client
        if(connectedClients.size() == 0)
        {
            connectedClients.append(clientSocket);
        }
        else
        {
            //If theres already a connected client
            for(int i = 0; i<connectedClients.size(); i++)
            {
                //looks if client is already connected to the server
                if(connectedClients.at(i) == clientSocket)
                {
                    clientSocket = connectedClients.at(i);
                    //use the socket from the list, don't create a new one
                }
                else
                {
                    //create a new one and add it to the QList
                    connectedClients.append(clientSocket);
                }
            }
        }

        Client *client= new Client(clientSocket); //create new client
        connect(client, SIGNAL(signalDisconnected(QTcpSocket*)), this, SLOT(removeFromList(QTcpSocket*))); //Signal when socket disconnects

    }

}

void Server::removeFromList(QTcpSocket *clientSocket)
{
    //delete the disconnected socket from the list
    for(int i = 0; i<connectedClients.size(); i++)
    {
        if(connectedClients.at(i) == clientSocket)
        {
            connectedClients.removeAt(i);
        }
        else
        {
        }
    }
}




