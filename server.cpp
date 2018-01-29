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
        connectedClients.append(clientConnection); //Add the connected client to the Qlist

        //Check if a client is already connected.
        for(int i = 0; i<connectedClients.size(); i++)
        {
                if(connectedClients.at(i) == clientConnection)
                {
                   counterOfConn = counterOfConn+1;
                   qDebug()<<"Times connected: "<<counterOfConn;

                       if(counterOfConn ==1)
                       {
                           qDebug()<<"First time connected";
                           client = new Client(clientConnection);
                       }
                       else
                       {
                           qDebug()<<"Already connected. Getting stored connection";
                           clientConnection = connectedClients.at(i);
                           client = new Client(clientConnection);
                       }
                }
        }

   }
}
void Server::removeFromList(QHostAddress addr)
{
//    for(it = connectedClients.begin(); it != connectedClients.end(); it++)
//    {
//        if(*it == addr)
//        {
//            connectedClients.erase(it);
//       }
//    }
}

QList<QTcpSocket *> Server::getConnectedClients() const
{
    return connectedClients;
}

void Server::setConnectedClients(const QList<QTcpSocket *> &value)
{
    connectedClients = value;
}




