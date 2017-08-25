#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include "commandlineprocess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void insertToTextField();

private slots:
    void on_menuFileQuit_triggered();
    void on_menuOptionSetting_triggered();

    void on_pushButton_execute_clicked();

    void on_pushButton_TsFile_clicked();

private:
    const QString ORG_NAME = "TsProcessor";
    const QString APP_NAME = "TsProcessor";
    Ui::MainWindow *ui;
    QSettings *settings;
    CommandlineProcess *process;
};

#endif // MAINWINDOW_H
