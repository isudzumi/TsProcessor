#include "commandlineprocess.h"

CommandlineProcess::CommandlineProcess(QString &fileName) :
    inputFile(fileName),
    process(new QProcess()),
    settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, ORG_NAME, APP_NAME)),
    functionAry{{std::bind(&CommandlineProcess::TsSplitter, this),
                std::bind(&CommandlineProcess::BonTsDemux, this),
                std::bind(&CommandlineProcess::FAW, this),
                std::bind(&CommandlineProcess::RemoveTempFile, this)}},
    itr(functionAry.cbegin())
{
    settings->beginGroup("Directory");
    tempDir   = settings->value("tempDirectory").toString();
    outputDir = settings->value("outputDirectory").toString();
    settings->endGroup();
    QObject::connect(process, SIGNAL(finished(int)), this, SLOT(execute()));

    if(tempDir == "" || outputDir == "") exit(1);

    process->setWorkingDirectory(tempDir);
}

CommandlineProcess::~CommandlineProcess()
{
    delete process;
    delete settings;
}

void CommandlineProcess::TsSplitter()
{
    ++itr;

    qDebug() << "TsSplitter";
    settings->beginGroup("Software Path");
    QString program = settings->value("TsSplitter").toString();
    settings->endGroup();

    QString inputFile = this->getInputFile();

    QStringList arguments;
    arguments << inputFile << "-SD" << "1SEG" << "-OUT" << outputDir;

    //change (QString)inputFile into output filename
    int pos = inputFile.lastIndexOf("/");
    inputFile = inputFile.replace(0, pos, tempDir);
    inputFile = inputFile.insert(inputFile.size() - 3, "_HD");
    this->setInputFile(inputFile);

    process->start(program, arguments);
    if(!process->waitForFinished()){
        qWarning() << process->errorString();
    }
}

void CommandlineProcess::BonTsDemux()
{
    ++itr;

    qDebug() << "BonTsDemux";
    settings->beginGroup("Software Path");
    QString program = settings->value("BonTsDemux").toString();
    settings->endGroup();

    QString outputFile= TEMP_FILE;
    QStringList arguments;
    arguments << "-i" << inputFile <<
                 "-o" << outputFile <<
                 "-encode" <<  "Demux(m2v+aac)" <<
                 "-nogui" << "-nd" << "-rf64" <<
                 "-delay" << "167" << "-start" << "-quit";

    QString inputFile = this->getInputFile();
    qDebug() << inputFile;
    //change (QString)inputFile into output filename
    inputFile = tempDir + "/" + TEMP_FILE + ".ts";
    this->setInputFile(inputFile);

    process->start(program, arguments);
    if(!process->waitForFinished()){
        qWarning() << process->errorString();
    }
}

void CommandlineProcess::FAW()
{
    ++itr;

    qDebug() << "FAW";
    settings->beginGroup("Software Path");;
    QString program = settings->value("FAW").toString();
    settings->endGroup();

    QDir *dir = new QDir(tempDir);
    QStringList filter;
    filter << "temp DELAY*.aac";
    dir->setNameFilters(filter);
    dir->setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList infoList = dir->entryInfoList();
    if(infoList.isEmpty())
    {
        exit(1);
    }
    QString inputFile = infoList.constFirst().fileName();

    qDebug() << inputFile;

    QString outputFile = TEMP_FILE + ".wav";
    QStringList arguments;
    arguments << inputFile << outputFile;

    process->start(program, arguments);
    if(!process->waitForFinished()){
        qWarning() << process->errorString();
    }
}

void CommandlineProcess::RemoveTempFile()
{
    QDir *dir = new QDir(tempDir);
    QStringList filter;
    filter << "*.ts" << "*.aac";
    dir->setNameFilters(filter);
    dir->setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList infoList = dir->entryInfoList();
    if(infoList.isEmpty()) exit(1);
    for(auto i : infoList)
    {
        dir->remove(i.fileName());
    }
}

void CommandlineProcess::execute()
{
    if(itr != functionAry.end())
    {
        (*itr)();
    }
}
