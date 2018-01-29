#include "client.h"
#include <unistd.h>
#include <QThread>



Client::Client(QTcpSocket *conn)
{
    clientSocket = conn;
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug()<<"new socket created";

    password = '3'; //User verificational password
    verificationRequired = true;
    clientSocket->write("Hello. Please insert your password");


}

void Client::userAuth(QByteArray arrPassword)
{

        if(arrPassword.contains(password)) //check if password is correct
        {
            qDebug()<<"Connection ethablished. Ready to take a picture";
            verificationRequired = false;
           // readyRead();
        }
        else
        {
           verificationRequired = true;
           qDebug()<<"wrongPassword";
        }
}
void Client::bytesWritten(qint64 bytes)
{
}


void Client::readyRead()
{
        if(verificationRequired == true) //First login
        {
            QByteArray arrPassword;
            arrPassword.append(clientSocket->readAll());
            userAuth(arrPassword);//Check if password was correct
        }
        else
        {
            arrCameraSettings = clientSocket->readAll();
//            //qDebug()<<arrCameraSettings;
//            for(uint i = 0; arrCameraSettings.length(); i++)
//            {
//                qDebug()<<arrCameraSettings.data();
//            }
            //QString dataAsString = QTextCodec::codecForMib(106)->toUnicode(arrCameraSettings);



        }


//            arrCameraSettings.append("11111100");

//        }
//        camera = new Camera(arrCameraSettingsQList.at(0), arrCameraSettingsQList.at(1), arrCameraSettingsQList.at(2),
//                            arrCameraSettingsQList.at(3), arrCameraSettingsQList.at(4), arrCameraSettingsQList.at(5),
//                            arrCameraSettingsQList.at(6), arrCameraSettingsQList.at(7));


            //arr.append(clientSocket->readAll());
            //arr.append("00000000");

             //camera = new Camera(arrCameraSettings);
            //camera->setSettings();
            //QThreadPool::globalInstance()->start(camera); //QRunnable to create a new Threa

}

void Client::disconnected()
{
    qDebug()<<"Connection closed";
    clientSocket->close();
    delete clientSocket;
}






