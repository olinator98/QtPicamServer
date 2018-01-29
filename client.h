#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include <QDebug>


class Client  : public QObject
{
    Q_OBJECT

public:
    Client(QTcpSocket *conn);

private:

    QTcpSocket *clientSocket;
    bool verificationRequired;
    int password;
    QByteArray clientMessage;
    void selectOperation();


public slots:
    void bytesWritten(qint64 bytes);
    void readyRead();
    void disconnected();
};

#endif // CLIENT_H
