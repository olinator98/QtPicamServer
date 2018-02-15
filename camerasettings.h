#ifndef CAMERASETTINGS_H
#define CAMERASETTINGS_H

#include <QString>
#include <QDebug>


class CameraSettings
{
public:
    CameraSettings(char rotationVerticalParam, char rotationHorizontalParam, char exposureParam, char resolutionParam,
                   char infraredOnParam, char takePicParam);

    QString getRotationHorizontal() const;
    void setRotationHorizontal(const QString &value);

    QString getRotationVertical() const;
    void setRotationVertical(const QString &value);

    QString getExposure() const;
    void setExposure(const QString &value);

    QString getResolution() const;
    void setResolution(const QString &value);

    QString getTakePic() const;
    void setTakePic(const QString &value);

    QString getCloseConn() const;
    void setCloseConn(const QString &value);

    QString getOff() const;
    void setOff(const QString &value);

    bool getInfraredOn() const;
    void setInfraredOn(bool value);

private:
    QString rotationHorizontal;
    QString rotationVertical;
    QString exposure;
    QString resolution;
    bool infraredOn;
    QString takePic;
    QString closeConn;
    QString off;

    const char inactive = '0';
};

#endif // CAMERASETTINGS_H
