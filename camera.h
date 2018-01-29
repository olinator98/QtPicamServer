#ifndef CAMERA_H
#define CAMERA_H
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QProcess>
#include <QThread>
#include <QRunnable>
#include <QThreadPool>

class Camera : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Camera(QString rotationParam, QString infraredOnParam, QString qualityParam,
           QString modeParam, QString takePicParam, QString closeConnParam, QString offParam, QString controllBitParam);


private:

    QByteArray imageSettings;
    QString rotation; //bit 0
    QString infraredOn; //Bit 1 possible if infrared lamps are there
    QString quality; //bit 2
    QString mode;   //bit 3
    QString takePic; //bit 4
    QString closeConn; //bit 5
    QString off; //bit 6
    QString controllBit; //bit 7
    QRunnable *runnable;

    QString raspistillCommand;
    QString getCommand();

    bool takePicture();


protected:
    void run();

public slots:
    //void setSettings();
    void toTest();

};

#endif // CAMERA_H
