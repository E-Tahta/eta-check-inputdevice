#include "usbdevicemonitorprivate.h"

UsbDeviceMonitorPrivate::UsbDeviceMonitorPrivate(QObject *parent) : QObject(parent)
{

}

int UsbDeviceMonitorPrivate::getCount() const
{
    return count;
}

int UsbDeviceMonitorPrivate::getCount() const
{
    return count;
}

void UsbDeviceMonitorPrivate::setCount(int value)
{
    count = value;
}
