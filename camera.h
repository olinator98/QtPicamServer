#ifndef CAMERA_H
#define CAMERA_

#include <QDebug>
#include <QProcess>
#include <time.h>
#include <QImage>
#include <QBuffer>
#include "bcm2835.h"

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam,
           char infraredOnParam, char takePicParam);
    void takeImage();

    QProcess *process;

signals:
    void imageReady(QString pathToImage);

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
    QObject *parent;
    QString command;

    const char inactive = '0';

};

#endif // CAMERA_H
