#include "camera.h"

Camera *Camera::instance = 0;

Camera::Camera()
{
    parent = nullptr;
    process = nullptr;
}

Camera::~Camera()
{
    if(Camera::instance != NULL)
    {
       delete Camera::instance;
       Camera::instance = NULL;
    }
}

void Camera::takeImage()
{


        mutex.lock();
        QProcess *process = new QProcess(parent);
        connect(process, SIGNAL(finished(int)), this, SLOT(sendPicture()));
        process->start(cameraCommand);
        mutex.unlock();

    mutex.lock();
    QProcess *process = new QProcess(parent);
    connect(process, SIGNAL(finished(int)), this, SLOT(sendPicture()));
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
            bcm2835_gpio_write(PIN,HIGH);
        }
        else
        {
            bcm2835_gpio_write(PIN,LOW );
        }
        cameraCommand = "raspistill -n "+set.getRotationVertical()+set.getRotationHorizontal()+set.getExposure()+set.getResolution()+" -o "+buffer+"jpg";

        cameraCommand = "raspistill -n"+set.getRotationVertical()+set.getRotationHorizontal()+set.getExposure()+set.getResolution()+" -o "+buffer+"jpg";

        takeImage();
    }
}


void Camera::sendPicture()
{
    qDebug()<<"Image taken";
    QString pathToGlory = (QString)buffer + "jpg";
    emit this->imageReady(pathToGlory);
}

