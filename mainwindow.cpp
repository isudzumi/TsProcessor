#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.cpp"
#include "commandlineprocess.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, ORG_NAME, APP_NAME))
{
    ui->setupUi(this);

    settings->beginGroup("history");
    ui->lineEdit_TsFile->setText(settings->value("recentUse").toString());
    settings->endGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

void MainWindow::on_menuFileQuit_triggered()
{
    close();
    qApp->quit();
}

void MainWindow::on_menuOptionSetting_triggered()
{
    SettingDialog *dialog = new SettingDialog();
    dialog->show();
}

void MainWindow::on_pushButton_execute_clicked()
{
    QString inputFile = ui->lineEdit_TsFile->text();
    if(inputFile != ""){
        process = new CommandlineProcess(inputFile);
        connect(process->process, SIGNAL(readyReadStandardOutput()), this, SLOT(insertToTextField()));
        process->execute();
        settings->beginGroup("history");
        settings->setValue("recentUse", inputFile);
        settings->endGroup();
    }
}

void MainWindow::on_pushButton_TsFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Set Ts File"),
                QDir::homePath(),
                tr("Ts File (*.ts)"));
    ui->lineEdit_TsFile->setText(fileName);
}

void MainWindow::insertToTextField()
{
    QByteArray arr = process->process->readAllStandardOutput();
    QTextStream out(&arr);
    QString str = out.readLine();
    ui->logField->insertPlainText(str);
}
