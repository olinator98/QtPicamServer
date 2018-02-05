#include "client.h"

Client::Client(QTcpSocket *conn)
{
    clientSocket = conn;
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug()<<"new socket created";
    verificationRequired == true;
    password = '3'; //User verificational password


}

void Client::bytesWritten(qint64 bytes)
{
    qDebug()<<"Bytes written";
}

void Client::readyRead()
{
    //qDebug()<<clientSocket->readAll();

    if(verificationRequired == true) //First login
    {
        QByteArray arr;
        arr = clientSocket->readAll();
        char *data = arr.data();
        //qDebug()<<*data;
            if(*data == password) //check if password is correct
            {
                qDebug()<<"Connection ethablished";
                selectOperation();
                verificationRequired = false;
            }
            else
            {
               qDebug()<<"wrongPassword";
               //clientSocket->write("Wrong password");
            }
    }
    else
    {
        qDebug()<<"Here you are again";
        selectOperation();
    }

}

void Client::selectOperation()
{
    clientSocket->write("Please choose one of the points: Camera setting 2. Close connection");
    QByteArray operation;
    operation = clientSocket->readAll();
    char *data = operation.data();

    switch(*data)
    {
    case '1':
        qDebug()<<"User choose cameraSettings";

        break;
    case '2':
        qDebug()<<"User choose Close connection";
        clientSocket->close();
        delete clientSocket;
        break;
    }
}

void Client::disconnected()
{
    qDebug()<<"Connection closed";
    clientSocket->close();
}
