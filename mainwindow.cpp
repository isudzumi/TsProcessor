#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.cpp"

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
