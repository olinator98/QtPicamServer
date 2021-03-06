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
    found = false;

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection())); //this signal is emmited every time a new connection is available

    qDebug()<<"connecting...";

    server->listen(QHostAddress::Any, 12345); //Let the server listening
}

void Server::createClient()
{
    qDebug()<<"\n\n-------------checking sucessfull-----------";
    qDebug()<<"IP-Address: "<<clientSocket->peerAddress();
    Client *client= new Client(); //create new client
    connect(client, SIGNAL(signalDisconnected(QTcpSocket*)), this, SLOT(removeFromList(QTcpSocket*))); //Signal when socket disconnects

    client->init(clientSocket);

    //connectedSockets.append(clientSocket); //add the socket to a list

    connectedClients.append(client); //add the client to a list
}

bool Server::checkClient(QTcpSocket *socket)
{
    QHostAddress peerAddressClient = clientSocket->peerAddress();

    if(socket->peerAddress() == peerAddressClient)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Client *Server::getConnectedInstance()
{
    for(int i = 0; i < connectedClients.size(); i++)
    {
        if(connectedClients.at(i)->getClientSocket()->peerAddress() == clientSocket->peerAddress())
        {
            qDebug()<<"return old connection";
            return connectedClients.at(i);
        }
     }
}

void Server::newConnection()
{
    if(server->hasPendingConnections())
    {
        clientSocket = server->nextPendingConnection();

        //Looks if theres a already a connected client
        if(connectedClients.size() == 0)
        {
            createClient();
        }
        else
        {
            //If theres already a connected client
            for(int i = 0; i<connectedClients.size(); i++)
            {
                if(!checkClient(connectedClients.at(i)->getClientSocket()))
                {
                    qDebug()<<"Host found";
                    client = getConnectedInstance();
                    client->init(clientSocket);
                    found = true;
                }
             }
            if(!found)
            {
                createClient();
            }
        }
    }
}

void Server::removeFromList(QTcpSocket *clientSocket)
{
    //delete the disconnected socket from the list
    for(int i = 0; i<connectedClients.size(); i++)
    {
        if(connectedClients.at(i)->getClientSocket()->peerAddress() == clientSocket->peerAddress())
        {
            qDebug()<<"removing";
            connectedClients.removeAt(i);
        }
        else
        {
            qDebug()<<"Not found";
        }
    }
}




