#include "camera.h"

Camera::Camera(QString rotationParam, QString infraredOnParam, QString qualityParam,
               QString modeParam, QString takePicParam, QString closeConnParam, QString offParam,
               QString controllBitParam)
{
    rotation = rotationParam;
    infraredOn = infraredOnParam;
    quality = qualityParam;
    mode = modeParam;
    takePic = takePicParam;
    closeConn = closeConnParam;
    off = offParam;
    controllBit = controllBitParam;

    this->takePicture();
}

bool Camera::takePicture()
{    
    //(closeConn == "1")?(closeConn = "--exposure night"):(closeConn = "");
    //(off == "1")?(off = "--exposure night"):(off = "");

    (rotation == "1")?(rotation = " -vf -hf"):(rotation = ""); //shorthand if else statement
    //(infraredOn == "1")?(infraredOn = ""):(infraredOn = "");
    //(quality == "1")?(quality = "-h 1080 -w 1920"):(quality = "-h 600 -w 800");
    (quality == "1")?(quality = " --quality 100"):(quality = " --quality 50");
    (mode == "1")?(mode = " --exposure night"):(mode = "");




     QString command = "raspistill -o cam_%d.jpg"+mode+rotation;
     qDebug()<<command;
//        qDebug()<<command;
//        //command = "raspistill -- fullscreen -o cam_%d.jpg";

//        QProcess *process = new QProcess(this);
//        process->start(command);

//        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(toTest()));
//        //Close the CameraThread and return to main-thread

}

void Camera::run()
{
    //NOTE: Everytime when you create a new Thread in Qt, this error will occurent.
    qDebug()<<"Hello from Thread";
    //setSettings();

}


void Camera::toTest()
{
    qDebug()<<"QProcess finished()";
}
