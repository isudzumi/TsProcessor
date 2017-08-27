#include "commandlineprocess.h"

CommandlineProcess::CommandlineProcess(QString &fileName) :
    inputFile(fileName),
    process(new QProcess()),
    settings(ReadSettings::getInstance()),
    functionAry{{std::bind(&CommandlineProcess::TsSplitter, this),
                std::bind(&CommandlineProcess::BonTsDemux, this),
                std::bind(&CommandlineProcess::FAW, this),
                std::bind(&CommandlineProcess::RemoveTempFile, this)}},
    itr(functionAry.cbegin())
{
    tempDir   = settings->getDirectory("tempDirectory");
    outputDir = settings->getDirectory("outputDirectory");
    QObject::connect(process, SIGNAL(finished(int)), this, SLOT(execute()));

    if(tempDir == "" || outputDir == "") exit(1);

    process->setWorkingDirectory(tempDir);
}

CommandlineProcess::~CommandlineProcess()
{
    delete process;
//    delete settings;
}

void CommandlineProcess::TsSplitter()
{
    ++itr;

    QString program = settings->getSoftware("TsSplitter");

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

    QString program = settings->getSoftware("BonTsDemux");

    QString outputFile= TEMP_FILE;
    QStringList arguments;
    arguments << "-i" << inputFile <<
                 "-o" << outputFile <<
                 "-encode" <<  "Demux(m2v+aac)" <<
                 "-nogui" << "-nd" << "-rf64" <<
                 "-delay" << "167" << "-start" << "-quit";

    QString inputFile = this->getInputFile();
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

    QString program = settings->getSoftware("FAW");

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
