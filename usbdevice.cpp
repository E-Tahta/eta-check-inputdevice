#include "usbdevice.h"

#define IWB_PHASE1 "6615:0084|6615:0085|6615:0086|6615:0087|6615:0088|6615:0c20"
#define IWB_PHASE2 "2621:2201|2621:4501"


UsbDevice::UsbDevice(const QString &vendor,
                     const QString &model)
{
    m_vendor = vendor;
    m_model = model;
    QString vm = m_vendor + ":" + m_model;
    QRegExp m_phase1_device_list(IWB_PHASE1);
    QRegExp m_phase2_device_list(IWB_PHASE2);
    if ( m_phase1_device_list.exactMatch(vm) ) {
        udt = UsbDeviceType::Phase1;
    } else if ( m_phase2_device_list.exactMatch(vm) ) {
        udt = UsbDeviceType::Phase2;
    } else {
        udt = UsbDeviceType::Mouse;
    }
}

UsbDeviceType UsbDevice::getType() const
{
    return udt;
}

QString UsbDevice::getVendor() const
{
    return m_vendor;
}

QString UsbDevice::getModel() const
{
    return m_model;
}

QString UsbDevice::getTypeString() const
{
    QString out = "";
    switch (udt) {
    case UsbDeviceType::Mouse:
        out = "Mouse";
        break;
    case UsbDeviceType::Phase1:
        out = "IWB PHASE 1";
        break;
    case UsbDeviceType::Phase2:
        out = "IWB PHASE 2";
        break;
    default:
        out = "Unknown type";
        break;
    }
    return out;
}

QString UsbDevice::getPidName() const
{
    QString out = "";
    switch (udt) {
    case UsbDeviceType::Mouse:
        out = "mice.pid";
        break;
    case UsbDeviceType::Phase1:
        out = "optictouch.pid";
        break;
    case UsbDeviceType::Phase2:
        out = "optictouch.pid";
        break;
    default:
        out = "inputdevice.pid";
        break;
    }
    return out;
}

QString UsbDevice::getPidTypeNumber() const
{
    QString out = "";
    switch (udt) {
    case UsbDeviceType::Phase1:
        out = "1";
        break;
    case UsbDeviceType::Phase2:
        out = "2";
        break;
    default:
        out = "0";
        break;
    }
    return out;
}

bool UsbDevice::operator == (const UsbDevice &d)
{
    if(d.getVendor().compare(m_vendor) == 0) {
        if(d.getModel().compare(m_model) == 0) {
            return true;

        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool UsbDevice::operator !=(const UsbDevice &d)
{
    if(d.getVendor().compare(m_vendor) == 0) {
        if(d.getModel().compare(m_model) == 0) {

            return false;

        } else {
            return true;
        }
    } else {
        return true;
    }
}
