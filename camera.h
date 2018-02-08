#ifndef CAMERA_H
#define CAMERA_
#include <QDebug>
#include <QProcess>
#include <time.h>
#include <QImage>
#include <QBuffer>
#include <QTcpSocket>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam,
           char infraredOnParam, char takePicParam, QTcpSocket *socket);
    void takeImage();

public slots:
    void sendPicture();

private:
    QString rotationHorizontal;
    QString rotationVertical;
    QString exposure;
    QString resolution;
    QString infraredOn;
    QString takePic;
    QString closeConn;
    QString off;

    char buffer [80];

    QTcpSocket *clientSocket;

    QImage image;

    QObject *parent;
    QString command;



    const char inactive = '0';


};

#endif // CAMERA_H
