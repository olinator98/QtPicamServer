#ifndef CAMERA_H
#define CAMERA_
#include <QDebug>
#include <QProcess>
#include <time.h>
#include <QImage>
#include <QBuffer>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam,
           char infraredOnParam, char takePicParam);
    QByteArray takeImage();

private:
    QString rotationHorizontal;
    QString rotationVertical;
    QString exposure;
    QString resolution;
    QString infraredOn;
    QString takePic;
    QString closeConn;
    QString off;

    QImage image;

    QObject *parent;
    QString command;



    const char inactive = '0';


};

#endif // CAMERA_H
