#ifndef USBDEVICEMONITORPRIVATE_H
#define USBDEVICEMONITORPRIVATE_H

#include <QObject>
#include <QSocketNotifier>
#include <QString>

// Class with platform-specific data
class UsbDeviceMonitor;
class UsbDeviceMonitorPrivate : public QObject
{
    Q_OBJECT

public:
    explicit UsbDeviceMonitorPrivate(QObject *parent = 0);
    virtual ~UsbDeviceMonitorPrivate();

    UsbDeviceMonitor* q_ptr;

    // Handle to dynamically loaded udev library
    void* m_udevLib;
    // udev library context
    struct udev* m_udev;
    // udev device monitor handle
    struct udev_monitor* m_udevMonitor;
    // Watcher for udev monitor socket
    QSocketNotifier* m_udevNotifier;

    QString model_id, vendor_id, action_type;

private:
    QString m_action;
    QString m_vendor;
    QString m_model;

public slots:
    // Processes udev socket notification
    void processUdevNotification(int socket);
};

#endif // USBDEVICEMONITORPRIVATE_H
