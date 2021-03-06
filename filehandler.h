#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = 0);
    QString getPath() const;
    QString getUser() const;
    void log(const QString &str);
    bool createPid(const QString &name);
    bool removePid(const QString &name);
    bool createPidType(const QString &pt);
    bool NoPidTypeFileDetected();
    bool CreateNoPidTypeFile();

    QString red_color = "\033[1;31m";
    QString yellow_color = "\033[1;33m";
    QString green_color = "\033[1;32m";
    QString no_color = "\033[0m";

private:

    QString m_current_time;
    QString m_path;
    QString file_fullpath;
    QString whoami;

    QDir *d;
    QFile file;

    bool createFile(const QString &file_path, const QString &file_name);
    bool createFileForPidType(const QString &file_path, const QString &file_name);
    void updateTime();
    bool writeData(const QString &str);
};

#endif // FILEHANDLER_H
