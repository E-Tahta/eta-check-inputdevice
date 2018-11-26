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

private:

    QString m_current_time;
    QString m_path;
    QString file_fullpath;
    QString mice_pid_fullpath;
    QString whoami;

    QDir *d;
    QFile file;

    QFile pidtype_file;

    bool createFile(const QString &file_path, const QString &file_name);
    void updateTime();
    bool writeData(const QString &str);
};

#endif // FILEHANDLER_H
