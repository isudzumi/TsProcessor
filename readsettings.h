#ifndef READSETTINGS_H
#define READSETTINGS_H

#include <QSettings>

class ReadSettings
{
private:
    inline ReadSettings();
    inline ~ReadSettings();
    ReadSettings(const ReadSettings&) = delete;
    ReadSettings& operator=(const ReadSettings&) = delete;
    ReadSettings(ReadSettings&&) = delete;
    ReadSettings&& operator=(ReadSettings&&) = delete;

public:
    static ReadSettings* getInstance()
    {
        static ReadSettings *instance = new ReadSettings();
        return instance;
    }

    QString getHistory();
    void setHistory(QString fileName);
    QString getSoftware(QString key);
    void setSoftware(QString key, QString value);
    QString getDirectory(QString key);
    void setDirectory(QString key, QString value);

private:
    const QString ORG_NAME = "TsProcessor";
    const QString APP_NAME = "TsProcessor";
    const QString SOFTWARE = "Software Path";
    const QString DIRECTORY= "Directory";
    const QString HISTORY = "history";
    const QString HISTORY_VALUE = "recentUse";

    QSettings *const settings;
};

ReadSettings::ReadSettings() :
    settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, ORG_NAME, APP_NAME))
{
}

ReadSettings::~ReadSettings()
{
    delete settings;
}

#endif // READSETTINGS_H
