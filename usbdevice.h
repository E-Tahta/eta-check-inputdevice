#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QObject>
#include <QString>
#include <QRegExp>

enum class UsbDeviceType {
    Phase1,
    Phase2,
    Mouse
};

class UsbDevice
{
public:
    explicit UsbDevice(const QString &vendor = "",
                       const QString &model = ""
                       );

    UsbDeviceType getType() const;
    QString getVendor() const;
    QString getModel() const;

    QString getTypeString() const;

    QString getPidName() const;

    QString getPidTypeNumber() const;

    bool operator ==(const UsbDevice &d);
    bool operator !=(const UsbDevice &d);

private:
    UsbDeviceType udt;
    QString m_vendor;
    QString m_model;
};

#endif // USBDEVICE_H
