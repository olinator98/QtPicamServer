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

        clientConnection = server->nextPendingConnection();

        //connectedClients.append(clientConnection); //Add a connected client to the list
        //currently connected threads
        if(connectedClients.size() == 0)
        {
            qDebug()<<("You're my first one");
            connectedClients.append(clientConnection);
        }
        else
        {
            for(int i = 0; i<connectedClients.size(); i++)
            {
                if(connectedClients.at(i) == clientConnection)
                {
                    qDebug()<<"multiple times connected";
                    clientConnection = connectedClients.at(i);
                }
                else
                {
                    qDebug()<<"First time connected";
                    connectedClients.append(clientConnection);

                }
            }
        }

            Client *client= new Client(clientConnection); //create new client
   }

}




