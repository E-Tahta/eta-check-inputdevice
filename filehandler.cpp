#include "filehandler.h"
#include "usbdevice.h"
#include <QDateTime>
#include <QtWidgets>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#define log_file_path "/var/log"
#define log_file_name "eta.log"
#define pid_path "/var/run"

#define pidtype_path "/usr/share/eta/eta-check-inputdevice"
#define pidtype_name "type-of-iwb"

FileHandler::FileHandler(QObject *parent) :
    QObject(parent)
{
    m_path = QCoreApplication::applicationFilePath();

    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    whoami = homePath.first().split(QDir::separator()).last();
}

bool FileHandler::createFile(const QString &file_path, const QString &file_name)
{
    file_fullpath = file_path + "/" + file_name;
    QFileInfo checkFile(file_fullpath);
    d = new QDir(file_path);
    if(!checkFile.exists() || !checkFile.isFile()) {
        d->mkpath(file_path);
        QFile file(file_fullpath);
        if (file.open(QIODevice::ReadWrite)) {
            file.setPermissions(QFileDevice::ReadOther |
                                QFileDevice::WriteOther |
                                QFileDevice::ReadGroup |
                                QFileDevice::WriteGroup |
                                QFileDevice::ReadOwner |
                                QFileDevice::WriteOwner |
                                QFileDevice::ExeOwner);
            file.close();
            return true;
        } else {
            qDebug() << file.errorString();
        }
    }return false;
}

void FileHandler::log(const QString &str)
{
    createFile(log_file_path, log_file_name);
    file.setFileName(file_fullpath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)){
        if (writeData(str)) {
            file.close();
        }
        else qDebug() << "Log information could not write to log file";
    } else {
        qDebug() << "Log information could not open";
    }
}

bool FileHandler::writeData(const QString &str)
{
    try {
        updateTime();
        QTextStream out(&file);
        out << m_current_time + " " + red_color + getPath() + no_color + " " + str + "\n";
        return true;
    } catch (...) {
        return false;
    }
}

bool FileHandler::createPid(const QString &name)
{
    if( createFile(pid_path, name) ){
        return true;
    }
    else{
        return false;
    }
}

bool FileHandler::removePid(const QString &name)
{
    mice_pid_fullpath = pid_path + QString("/") + name;
    QFileInfo checkFile(mice_pid_fullpath);
    if(checkFile.exists() || checkFile.isFile()) {
        QFile file(mice_pid_fullpath);

        if (file.remove()){
            return true;
        } else {
            qDebug() << name + " could not deleted";

        }
    }return false;
}

bool FileHandler::createPidType(const QString &pt)
{

    createFile(pidtype_path, pidtype_name);

    pidtype_file.setFileName(file_fullpath);
    if ( pidtype_file.open(QIODevice::WriteOnly) ){
        QTextStream out(&pidtype_file);
        out << pt;
        pidtype_file.close();
        return true;
    } else {
        qDebug() << "Pid Type can not write to file";
        return false;
    }
}

bool FileHandler::NoPidTypeFileDetected()
{
    if (createFile(pidtype_path, pidtype_name)) {
        return true;
    } else {
        return false;
    }
}

bool FileHandler::CreateNoPidTypeFile()
{
    file_fullpath = pid_path + QString("/") + pidtype_path;
    pidtype_file.setFileName(file_fullpath);
    if ( !pidtype_file.size() ) {
        if ( file.open(QIODevice::WriteOnly) ){
            QTextStream out(&pidtype_file);
            out << "0";
            pidtype_file.close();
        }
        return true;
    } else {
        return false;
    }
}

void FileHandler::updateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    m_current_time = now.toString("dd-MM-yyyy hh:mm:ss.zzz");
}

QString FileHandler::getPath() const
{
    return m_path;
}

QString FileHandler::getUser() const
{
    return whoami;
}
