#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include <QDebug>
#include "camera.h"
#include <QThread>
#include <QRunnable>
#include <QBuffer>
#include <QTextCodec>


class Client  : public QObject
{
    Q_OBJECT
    QThread *thread = new QThread;

public:
    Client(QTcpSocket *conn);
    Camera *camera;

private:
    QTcpSocket *clientSocket;
    QByteArray arrCameraSettings;
    bool verificationRequired;
    char password;
    void selectOperation();
    void userAuth(QByteArray arrPassword);
    QList<QString> arrCameraSettingsQList;
    QBuffer buffer;



    QString imageSetting;

    //void newPicture(QString brightness, QString exposure, QString rotation, QString width, QString height, QString infraredOn);


public slots:
    void bytesWritten(qint64 bytes);
    void readyRead();
    void disconnected();

};

#endif // CLIENT_H
