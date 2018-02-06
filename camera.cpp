#include "camera.h"

Camera::Camera(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam,
               char infraredOnParam, char takePicParam)
{
    parent = nullptr;

    takePic = takePicParam;
    qDebug()<<"0"<<"0"<<takePicParam<<infraredOnParam<<resolutionParam<<exposureParam<<rotationHorizontalParam<<rotationVerticalParam;

    (rotationVerticalParam == inactive)?(rotationVertical = ""):(rotationVertical = " -vf");
    (rotationHorizontalParam == inactive)?(rotationHorizontal = ""):(rotationHorizontal = " -hf");
    (exposureParam == inactive)?(exposure = "-ex auto"):(exposure = "-ex night");
    (resolutionParam == inactive)?(resolution = " -w 640 -h 480"):(resolution = " -w 1920 -h 1080");
    (infraredOnParam == inactive)?(infraredOn = "infraredOff"):(infraredOn = "infrared on");





}

QByteArray Camera::takeImage()
{

    if(takePic == "1") //temporary changed
    {
        qDebug()<<"No pic";
    }
    else
    {
        //GetTime For more informations visit the cpp reference
        time_t rawtime;
        struct tm *timeinfo;
        char buffer [80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "Pic_%a_%F_%I:%M%p.", timeinfo);
        qDebug()<<buffer;
        command = "raspistill "+rotationVertical+rotationHorizontal + exposure + resolution +" -o "+buffer+"jpg";
        qDebug()<< command;

        QProcess *process = new QProcess(parent);
        process->start(command);
        //qDebug()<<takePic;
        QString pathToGlory = (QString)buffer + "jpg";

        image.load(pathToGlory);
        QByteArray imageArray;
        QBuffer imageBuffer(&imageArray);
        image.save(&imageBuffer, "jpg");

        return imageArray;


    }
}

