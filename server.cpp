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

QList<QTcpSocket *> Server::getConnectedClients() const
{
    return connectedClients;
}

void Server::setConnectedClients(const QList<QTcpSocket *> &value)
{
    connectedClients = value;
}




void Server::newConnection()
{
    if(server->hasPendingConnections())
    {
        qDebug()<<"Pending connection";

        clientSocket = server->nextPendingConnection();

        //connectedClients.append(clientSocket); //Add a connected client to the list
        //currently connected threads

        //Looks if theres a already a connected client
        if(connectedClients.size() == 0)
        {
            qDebug()<<("You're my first one");
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
                    qDebug()<<"multiple times connected";
                    clientSocket = connectedClients.at(i);
                    //use the socket from the list, don't create a new one
                }
                else
                {
                    //create a new one and add it to the QList
                    qDebug()<<"First time connected";
                    connectedClients.append(clientSocket);
                }
            }
        }

            Client *client= new Client(clientSocket); //create new client
            connect(client, SIGNAL(signalDisconnected(QTcpSocket*)), this, SLOT(removeFromList(QTcpSocket*)));

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
            qDebug()<<"Client removed from list";
            qDebug()<<connectedClients.size();
        }
        else
        {
            qDebug()<<"Not found";
        }
    }
}




