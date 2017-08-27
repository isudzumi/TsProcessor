#ifndef COMMANDLINEPROCESS_H
#define COMMANDLINEPROCESS_H

#include <QObject>
#include <QFileDialog>
#include <QFileInfoList>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <functional>
#include <array>
#include "readsettings.h"

class CommandlineProcess : public QObject
{
    Q_OBJECT

public:
    CommandlineProcess(QString& fileName);
    ~CommandlineProcess();

    QProcess *process;

public slots:
    void execute();

private:
    const QString TEMP_FILE = "temp";
    QString inputFile;
    QString tempDir;
    QString outputDir;
//    QProcess *process;
    ReadSettings *settings;
    inline QString getInputFile();
    inline void setInputFile(QString& fileName);
    void TsSplitter();
    void BonTsDemux();
    void FAW();
    void RemoveTempFile();
    const std::array<std::function<void()>, 4> functionAry;
    std::array<std::function<void()>, 4>::const_iterator itr;
};

inline QString CommandlineProcess::getInputFile()
{
    return this->inputFile;
}

inline void CommandlineProcess::setInputFile(QString& fileName)
{
    this->inputFile = fileName;
}

#endif // COMMANDLINEPROCESS_H
