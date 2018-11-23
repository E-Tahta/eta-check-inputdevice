#include "udevmonitor.h"
#include <libudev.h>
#include <QDebug>



UdevMonitor::UdevMonitor(QObject *parent) : QObject(parent)
{
    m_udev = NULL;
    m_udevMonitor = NULL;
    m_udevNotifier = NULL;
}

bool UdevMonitor::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(message);
    Q_UNUSED(result);
    return false;
}

void UdevMonitor::processUdevNotification(int socket)
{
    Q_UNUSED(socket);
    struct udev_device* dev = udev_monitor_receive_device(m_udevMonitor);
    if (dev)
    {
        udev_device_unref(dev);
        emit deviceChanged();
    }
}

bool UdevMonitor::startMonitoring()
{
    m_udev = udev_new();
    if(m_udev == NULL) {
        qDebug() << "m_udev varible is null";
        return false;
    }
    m_udevMonitor = udev_monitor_new_from_netlink(m_udev, "udev");
    if(m_udevMonitor == NULL) {
        qDebug() << "m_udevMonitor varible is null";
        return false;
    }
    if (udev_monitor_filter_add_match_subsystem_devtype(m_udevMonitor, "block", "disk") < 0) {
        qDebug() << "cannot add filter";
        return false;
    }
    if (udev_monitor_enable_receiving(m_udevMonitor) < 0) {
        qDebug() << "cannot enable receiving";
        return false;
    }
    int fd = udev_monitor_get_fd(m_udevMonitor);
    m_udevNotifier = new QSocketNotifier(fd, QSocketNotifier::Read);

    connect(m_udevNotifier, &QSocketNotifier::activated, this, &(processUdevNotification));
    m_udevNotifier->setEnabled(true);
    return true;
}
