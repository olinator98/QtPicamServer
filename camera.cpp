#include "camera.h"

Camera::Camera(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam,
               char infraredOnParam, char takePicParam)
{
    parent = nullptr;

    takePic = takePicParam;
    qDebug()<<"0"<<"0"<<takePicParam<<infraredOnParam<<resolutionParam<<exposureParam<<rotationHorizontalParam<<rotationVerticalParam;

    (rotationVerticalParam == inactive)?(rotationVertical = ""):(rotationVertical = " -rot 90 ");
    (rotationHorizontalParam == inactive)?(rotationHorizontal = ""):(rotationHorizontal = " -rot 180   ");
    (exposureParam == inactive)?(exposure = "-ex auto"):(exposure = "-ex night");
    (resolutionParam == inactive)?(resolution = " -w 640 -h 480"):(resolution = " -w 1920 -h 1080");
    (infraredOnParam == inactive)?(infraredOn = "infraredOff"):(infraredOn = "infrared on");
}

void Camera::takeImage()
{

    if(takePic == "0")
    {
        qDebug()<<"No pic";
    }
    else
    {
        //GetTime For more informations visit the cpp reference
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "Pic_%a_%F_%I:%M%p.", timeinfo);
        qDebug()<<buffer;
        command = "raspistill "+rotationVertical+rotationHorizontal + exposure + resolution +" -o "+buffer+"jpg";
        qDebug()<< command;

        QProcess *process = new QProcess(parent);
        connect(process, SIGNAL(finished(int)), this, SLOT(sendPicture()));
        process->start(command);
    }
}

void Camera::sendPicture()
{
    QString pathToGlory = (QString)buffer + "jpg";

    emit this->imageReady(pathToGlory);

}
