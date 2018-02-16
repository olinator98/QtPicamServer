#include "camerasettings.h"

CameraSettings::CameraSettings(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam, char infraredOnParam, char takePicParam)
{
    takePic = takePicParam;

    (rotationVerticalParam == inactive)?(rotationVertical = ""):(rotationVertical = " -rot 90 ");
    (rotationHorizontalParam == inactive)?(rotationHorizontal = ""):(rotationHorizontal = " -rot hf ");
    (exposureParam == inactive)?(exposure = " -ex auto"):(exposure = " -ex night");
    (resolutionParam == inactive)?(resolution = " -w 640 -h 480"):(resolution = " -w 1920 -h 1080");

    if(infraredOnParam == inactive)
    {
        infraredOn = false;
    }
    else
    {
        infraredOn = true;
    }

}

QString CameraSettings::getRotationHorizontal() const
{
    return rotationHorizontal;
}

void CameraSettings::setRotationHorizontal(const QString &value)
{
    rotationHorizontal = value;
}

QString CameraSettings::getRotationVertical() const
{
    return rotationVertical;
}

void CameraSettings::setRotationVertical(const QString &value)
{
    rotationVertical = value;
}

QString CameraSettings::getExposure() const
{
    return exposure;
}

void CameraSettings::setExposure(const QString &value)
{
    exposure = value;
}

QString CameraSettings::getResolution() const
{
    return resolution;
}

void CameraSettings::setResolution(const QString &value)
{
    resolution = value;
}

QString CameraSettings::getTakePic() const
{
    return takePic;
}

void CameraSettings::setTakePic(const QString &value)
{
    takePic = value;
}

QString CameraSettings::getCloseConn() const
{
    return closeConn;
}

void CameraSettings::setCloseConn(const QString &value)
{
    closeConn = value;
}

QString CameraSettings::getOff() const
{
    return off;
}

void CameraSettings::setOff(const QString &value)
{
    off = value;
}

bool CameraSettings::getInfraredOn() const
{
    return infraredOn;
}

void CameraSettings::setInfraredOn(bool value)
{
    infraredOn = value;
}
