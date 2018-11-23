#ifndef UDEVMONITOR_H
#define UDEVMONITOR_H

#include <QObject>

#include <QAbstractNativeEventFilter>
#include <QSocketNotifier>


class UdevMonitor : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit UdevMonitor(QObject *parent = 0);
    ~UdevMonitor();

    struct udev* m_udev;
    struct udev_monitor* m_udevMonitor;
    QSocketNotifier* m_udevNotifier;

    // Implements QAbstractNativeEventFilter interface for processing WM_DEVICECHANGE messages (Windows)
    bool nativeEventFilter(const QByteArray& eventType, void* message, long* result);

protected:
    // Closes handles and frees resources
    void cleanup();

signals:
    // Emitted when device change notification arrives
    void deviceChanged();

public slots:
    void processUdevNotification(int socket);
    bool startMonitoring();
};

#endif // UDEVMONITOR_H
