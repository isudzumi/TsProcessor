#ifndef COMMANDLINEPROCESS_H
#define COMMANDLINEPROCESS_H

#include <QObject>
#include <QSettings>
#include <QFileDialog>
#include <QFileInfoList>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <functional>
#include <array>

class CommandlineProcess : public QObject
{
    Q_OBJECT

public:
    CommandlineProcess(QString& fileName);
    ~CommandlineProcess();

public slots:
    void execute();

private slots:
    void onProcessOutput();

private:
    const QString ORG_NAME = "TsProcessor";
    const QString APP_NAME = "TsProcessor";
    const QString TEMP_FILE = "temp";
    QString inputFile;
    QString tempDir;
    QString outputDir;
    QProcess *process;
    QSettings *settings;
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
