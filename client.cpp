#include "client.h"

Client::Client(QTcpSocket *conn)
{
    parent = nullptr;
    clientSocket = conn;
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    verificationRequired = true;
    password = "theNextLevel"; //User verification password
}

void Client::checkPassword(QByteArray arr)
{
    if(arr.contains(password)) //check if password is correct
    {
        qDebug()<<"Connection esthablished";
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

void Client::createSettings()
{
    char *data = cameraSettingsArr.data();
    if(cameraSettingsArr.size() == 8)
    {
        //Check if user would reboot or close connection
        QString command = "sudo reboot now";
        QProcess *rebootProcess = new QProcess(parent);

        const char zero = '0';
        if (data[6] == zero)
        {
            if(data[7] == zero)
            {
                //Check completeted, create new camera object
                CameraSettings *settings = new CameraSettings(data[0], data[1], data[2], data[3], data[4], data[5]);
                camera = Camera::getInstance();
                camera->setCameraSettings(*settings);
                connect(camera, SIGNAL(imageReady(QString)), this, SLOT(sendImage(QString)), Qt::UniqueConnection); //Connect the slot for sending the picture to the Object
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
            clientSocket->close();
        }
    }

}

void Client::sendImage(QString pathToImage)
{

    QDataStream s(clientSocket);
    QByteArray imageArray;
    //Write a QFile to the stream (image as QFile)
    QFile data(pathToImage);
    if(!data.open(QIODevice::ReadOnly))
    return;

    qint32 length = data.size();
    s << length;

    while(!data.atEnd())
    {
        imageArray.clear();
        imageArray = data.read(10000);
        clientSocket->write(imageArray);
        clientSocket->waitForBytesWritten();
    }
    qDebug()<<"Image sended with "<<length<<" bytes to host "<<clientSocket->peerAddress();
}

void Client::readyRead()
{
    if(verificationRequired == true) //First login
    {
        QByteArray arr;
        arr = clientSocket->readAll();
        checkPassword(arr);
    }
    else
    {
        cameraSettingsArr = clientSocket->readAll();
        createSettings();
    }
}

void Client::disconnected()
{
    emit this->signalDisconnected(clientSocket);
    qDebug()<<"Connection closed";
    clientSocket->close();
    delete clientSocket;
}
