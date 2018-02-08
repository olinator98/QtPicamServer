#include "client.h"

Client::Client(QTcpSocket *conn)
{
    parent = nullptr;
    clientSocket = conn;
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug()<<"new socket created";
    verificationRequired = true;
    password = 'theNextLevel'; //User verificational password


}

void Client::checkPassword(QByteArray arr)
{
    if(arr.contains(password)) //check if password is correct
    {
        qDebug()<<"Connection ethablished";
        verificationRequired = false;
        readyRead();
    }
    else
    {
       qDebug()<<"wrongPassword";
       clientSocket->write("Wrong password");
       qDebug()<<"Connection closed";
       clientSocket->close();
    }
}

void Client::bytesWritten(qint64 bytes)
{

}

void Client::readyRead()
{
    //qDebug()<<clientSocket->readAll();

    if(verificationRequired == true) //First login
    {
        QByteArray arr;
        arr = clientSocket->readAll();
        checkPassword(arr);
    }
    else
    {

            QByteArray cameraSettings;
            qDebug()<<"IP from client:"<<clientSocket->peerAddress();
            cameraSettings = clientSocket->readAll();
            qDebug()<<"Received something";

            char *data = cameraSettings.data();


            qDebug()<<data;
            qDebug()<<cameraSettings.size();
            if(cameraSettings.size() == 8)
            {

//               Check if user would reboot or close connection
                QString command = "sudo reboot now";
                QProcess *rebootProcess = new QProcess(parent);

                const char zero = '0';
                if (data[6] == zero)
                {
                    qDebug()<<"3";

                    if(data[7] == zero)
                    {
                        qDebug()<<"reboot or close conn not active";
                        //Check completeted, create new camera object
                        Camera *camera = new Camera(data[0], data[1], data[2],
                                data[3], data[4], data[5], clientSocket);
                        camera->takeImage();
                    }
                    else

                    {
                        qDebug()<<"Restarting server";
                        clientSocket->write("restarting");
                        (rebootProcess->start(command));
                    }
                }
                else
                {
                    qDebug()<<"Closing connection";
                    disconnected();
                }
            }
    }

}

void Client::disconnected()
{
    emit this->signalDisconnected(clientSocket);
    qDebug()<<"Connection closed";
    clientSocket->close();
    delete clientSocket;
}
