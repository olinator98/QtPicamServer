#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include <QDebug>
#include <camera.h>
#include <QProcess>


class Client  : public QObject
{
    Q_OBJECT

public:
    Client(QTcpSocket *conn);

private:
    QTcpSocket *clientSocket;
    bool verificationRequired;
    int password;
    void checkPassword(QByteArray arr);
    char cameraSetting;
    char closeConnParam;
    char rebootParam;
    QObject *parent;


public slots:
    void bytesWritten(qint64 bytes);
    void readyRead();
    void disconnected();
};

#endif // CLIENT_H
