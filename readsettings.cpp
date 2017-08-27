#include "readsettings.h"

QString ReadSettings::getHistory()
{
    settings->beginGroup(HISTORY);
    QString value = settings->value(HISTORY_VALUE).toString();
    settings->endGroup();
    return value;
}

void ReadSettings::setHistory(QString fileName)
{
    settings->beginGroup(HISTORY);
    settings->setValue(HISTORY_VALUE, fileName);
    settings->endGroup();
}

QString ReadSettings::getSoftware(QString key)
{
    settings->beginGroup(SOFTWARE);
    QString value = settings->value(key).toString();
    settings->endGroup();
    return value;
}

void ReadSettings::setSoftware(QString key, QString value)
{
    settings->beginGroup(SOFTWARE);
    settings->setValue(key, value);
    settings->endGroup();
}

QString ReadSettings::getDirectory(QString key)
{
    settings->beginGroup(DIRECTORY);
    QString value = settings->value(key).toString();
    settings->endGroup();
    return value;
}

void ReadSettings::setDirectory(QString key, QString value)
{
    settings->beginGroup(DIRECTORY);
    settings->setValue(key, value);
    settings->endGroup();
}
