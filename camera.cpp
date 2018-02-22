#include "camera.h"

Camera *Camera::instance = 0;

Camera::Camera()
{
    parent = nullptr;
    process = nullptr;
}

void Camera::takeImage()
{
        mutex.lock();
        QProcess *process = new QProcess(parent);
        connect(process, SIGNAL(finished(int)), this, SLOT(sendPicture())); //connect slot processFinished -> image taken
        process->start(cameraCommand);
        mutex.unlock();

}

Camera* Camera::getInstance()
{

    //Singleton
    if(!Camera::instance)
        Camera::instance = new Camera();
    return Camera::instance;
}


void Camera::setCameraSettings(CameraSettings set)
{

    if(set.getTakePic() == "0")
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

        strftime(buffer, 80, "Image_%a_%F_%I:%M%p.", timeinfo);
        if(set.getInfraredOn())
        {
            bcm2835_gpio_write(PIN,HIGH); //turn on infrared
        }
        else
        {
            bcm2835_gpio_write(PIN,LOW ); //turn off infrared
        }
        cameraCommand = "raspistill -n "+set.getRotationVertical()+set.getRotationHorizontal()+set.getExposure()+set.getResolution()+" -o "+buffer+"jpg";
        takeImage();
    }
}


void Camera::sendPicture()
{
    qDebug()<<"Image taken";
    QString pathToGlory = (QString)buffer + "jpg"; //pathToImage
    emit this->imageReady(pathToGlory); //call signal from client.cpp to send image to client
}

