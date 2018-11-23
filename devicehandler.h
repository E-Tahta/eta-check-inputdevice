#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <QObject>
#include <QString>
#include <QList>

class UsbDeviceMonitor;
class UsbDevice;
class FileHandler;

class DeviceHandler : public QObject
{
    Q_OBJECT
public:
    explicit DeviceHandler(QObject *parent = 0);
    ~DeviceHandler();

private:
    UsbDeviceMonitor *udm;
    QList<UsbDevice> m_deviceList;
    QList<UsbDevice> getDeviceList();
    FileHandler *fh;
public slots:
    void handle(const QString &action, const QString &vendor, const QString &model);
};

#endif // DEVICEHANDLER_H
