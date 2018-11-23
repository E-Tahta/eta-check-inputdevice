#include "devicehandler.h"
#include "singleinstance.h"
#include <QCoreApplication>
#include <QtCore>
#include <QDebug>
#include <QFileInfo>

#define SINGLE_INSTANCE ".eta-check-inputdevice"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DeviceHandler dh;

    QString name = SINGLE_INSTANCE;
    SingleInstance cInstance;
    if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
    {
        qDebug() << "eta-check-inputdevice is allready open";
        return 0;
    }
    if (cInstance.listen(name)) {
        qDebug() << "creating single instance";
    } else {
        qDebug() << "couldnt create single instance aborting";
        return 0;
    }


    return a.exec();
}
