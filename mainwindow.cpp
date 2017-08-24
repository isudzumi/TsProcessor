#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.cpp"
#include "commandlineprocess.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        process->execute();
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
