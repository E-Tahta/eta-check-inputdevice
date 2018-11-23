QT += core widgets network
QT -= gui
QT_PLUGINS -= qdds qicns qjp2 qmng qtga qtiff qwbmp qwebp

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = eta-check-inputdevice

TEMPLATE = app

SOURCES += main.cpp \
    usbdevicemonitor.cpp \
    devicehandler.cpp \
    usbdevice.cpp \
    filehandler.cpp \
    singleinstance.cpp

HEADERS += \
    usbdevicemonitorprivate.h \
    usbdevicemonitor.h \
    devicehandler.h \
    usbdevice.h \
    filehandler.h \
    singleinstance.h

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -ludev

linux:gcc {
        LIBS += -ldl
        QMAKE_LFLAGS_RELEASE -= -Wl,-z,now       # Make sure weak symbols are not resolved on link-time
        QMAKE_LFLAGS_DEBUG -= -Wl,-z,now
        QMAKE_LFLAGS -= -Wl,-z,now
        GCCSTRVER = $$system(g++ -dumpversion)
        GCCVERSION = $$split(GCCSTRVER, .)
        GCCV_MJ = $$member(GCCVERSION, 0)
        GCCV_MN = $$member(GCCVERSION, 1)
        greaterThan(GCCV_MJ, 3) {
                lessThan(GCCV_MN, 7) {
                        QMAKE_CXXFLAGS += -std=gnu++0x
                }
                greaterThan(GCCV_MN, 6) {
                        QMAKE_CXXFLAGS += -std=gnu++11
                }
        }
        contains(QT_CONFIG, static) {
                # Static build is meant for releasing, clean up the binary
                QMAKE_LFLAGS += -s
        }
}

target.path = /usr/bin/

service.files = eta-check-optictouch.service
service.path = /lib/systemd/system/

INSTALLS += target service
