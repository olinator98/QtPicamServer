#ifndef CAMERA_H
#define CAMERA_H

#include <QDebug>
#include <QProcess>
#include <time.h>
#include <QImage>
#include <QBuffer>
#include "bcm2835.h"
#include <QMutex>
#include "camerasettings.h"




class Camera : public QObject
{
    Q_OBJECT
public:
    void takeImage();
    static Camera *getInstance();
    void setCameraSettings(CameraSettings set);
signals:
    void imageReady(QString pathToImage);
public slots:
    void sendPicture();
private:
    Camera();
    char buffer [80];
    QObject *parent;
    QString command;
    QProcess *process;
    QString cameraCommand;
    QMutex mutex;
    static Camera *instance;
};

#endif // CAMERA_H
