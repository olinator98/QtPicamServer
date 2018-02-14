#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include <QDebug>
#include <QProcess>
#include <QFile>

#include <camera.h>



class Client  : public QObject
{
    Q_OBJECT

public:
    Client(QTcpSocket *conn);
private:
    QTcpSocket *clientSocket;
    bool verificationRequired;
    const char* password;
    void checkPassword(QByteArray arr);
    char cameraSetting;
    char closeConnParam;
    char rebootParam;
    QObject *parent;

signals:
    void signalDisconnected(QTcpSocket *clientSocket); //Signal if client is disconnected

public slots:
    void sendImage(QString pathToImage);
    void bytesWritten(qint64 bytes);
    void readyRead();
    void disconnected();

};

#endif // CLIENT_H
