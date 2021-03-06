#ifndef USBDEVICEMONITOR_H
#define USBDEVICEMONITOR_H

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QSocketNotifier>

//#include "src/common.h"

class UsbDeviceMonitorPrivate;
class UsbDeviceMonitor : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

protected:
    UsbDeviceMonitorPrivate* const d_ptr;

public:
    explicit UsbDeviceMonitor(QObject *parent = 0);
    ~UsbDeviceMonitor();

    // Implements QAbstractNativeEventFilter interface for processing WM_DEVICECHANGE messages (Windows)
    bool nativeEventFilter(const QByteArray& eventType, void* message, long* result);

protected:
    // Closes handles and frees resources
    void cleanup();

signals:
    // Emitted when device change notification arrives
    void deviceChanged(const QString &action, const QString &vendor, const QString &model);

public slots:
    // Initializes monitoring for USB devices
    bool startMonitoring();
};

#endif // USBDEVICEMONITOR_H
