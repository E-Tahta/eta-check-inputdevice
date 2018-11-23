#include "devicehandler.h"
#include "usbdevicemonitor.h"
#include "usbdevice.h"
#include "filehandler.h"
#include <libudev.h>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QStringList>


DeviceHandler::DeviceHandler(QObject *parent) :
    QObject(parent)
{
    udm = new UsbDeviceMonitor(this);
    fh = new FileHandler(this);
    if(!udm->startMonitoring()) {
        qDebug() << "Could not start monitoring in udev";
        exit(1);
    }

    fh->log("running as " +fh->getUser());

    m_deviceList = getDeviceList();

    fh->log( QString::number(m_deviceList.length()) + " mouse detected on start");

    if (m_deviceList.length() == 0 ){
        if (fh->removePid("mice.pid")) {
            fh->log("mice.pid deleted on start");
        }
    }
    else{
        if (fh->createPid("mice.pid")) {
            fh->log("mice.pid created on start");
        }
    }

    connect(udm,SIGNAL(deviceChanged(QString,QString,QString)),this,SLOT(handle(QString,QString,QString)));
}

DeviceHandler::~DeviceHandler()
{
    delete(&m_deviceList);
}

QList<UsbDevice> DeviceHandler::getDeviceList()
{
    QList<UsbDevice> list;
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;

    udev = udev_new();
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_add_match_property(enumerate, "ID_INPUT_MOUSE", "1");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;
        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);
        dev = udev_device_get_parent_with_subsystem_devtype(dev,"usb","usb_device");
        UsbDevice device(udev_device_get_sysattr_value(dev,"idVendor"),
                         udev_device_get_sysattr_value(dev,"idProduct"));

        if(!list.contains(device)) {
            list.append(device);
        }
        udev_device_unref(dev);
    }
    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    return list;
}

void DeviceHandler::handle(const QString &action, const QString &vendor, const QString &model)
{
    UsbDevice device(vendor, model);
    if ( device.getTypeString() == "Mouse" ) {

        if(action == "add") {
            if(!m_deviceList.contains(device)) {
                m_deviceList.append(device);
                fh->log("Mouse plugged and Mouse Count is " + QString::number(m_deviceList.length()));
                if (m_deviceList.length() > 0 ){
                    if( fh->createPid(device.getPidName())){
                        fh->log(device.getPidName()+" created");
                    }
                }
            }
        }

        else if (action == "remove") {
            if(m_deviceList.contains(device)) {
                m_deviceList.removeOne(device);
                fh->log("Mouse unplugged and Mouse Count is " + QString::number(m_deviceList.length()));
                if (m_deviceList.length() == 0 ){
                    if( fh->removePid(device.getPidName())) {
                        fh->log(device.getPidName()+" deleted");
                    }
                }
            }
        }

        else {
            fh->log("Unknown action in Mouse");
        }
    }

    else if ( device.getTypeString() == "IWB Phase 1"  || device.getTypeString() == "IWB Phase 2") {

        if(fh->createPidType(device.getPidTypeNumber())){
            fh->log("The IWB number is "+device.getPidTypeNumber() + " and written to file");
        } else {
            fh->log("Type Number of iwb could not write to type-of-iwb file");
        }

        if(action == "add") {
            fh->log(device.getTypeString()+ " plugged");
            if( fh->createPid(device.getPidName())){
                fh->log(device.getPidName()+" created");
            }
        }

        else if (action == "remove") {
            fh->log(device.getTypeString()+ " ungplugged");
            if( fh->removePid(device.getPidName())) {
                fh->log(device.getPidName()+" deleted");
            }
        }
        else {
            fh->log("Unknown action in IWB Phase");
        }
    }

    else {

        fh->log("Unknown action");

        if(fh->createPidType(device.getPidTypeNumber())){
            fh->log("The IWB number is "+device.getPidTypeNumber() + " and written to file");
        } else {
            fh->log("Type Number of iwb could not write to type-of-iwb file");
        }
    }

}