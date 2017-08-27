#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    settings(ReadSettings::getInstance()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_TsFile->setText(settings->getHistory());
}

MainWindow::~MainWindow()
{
    delete ui;
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
        settings->setHistory(inputFile);
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
