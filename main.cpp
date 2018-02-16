#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include "server.h"
#include "bcm2835.h"

int main(int argc, char *argv[])
{

    bcm2835_init();
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN,LOW);

    QCoreApplication a(argc, argv);
    Server server;
    server.doConnect();
    return a.exec();
}
