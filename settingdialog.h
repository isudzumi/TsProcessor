#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QLineEdit>
#include "readsettings.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_pushButton_TsSplitter_clicked();

    void on_pushButton_BonTsDemux_clicked();

    void on_pushButton_FAW_clicked();

    void on_pushButton_DGIndex_clicked();

    void on_pushButton_cciconv_clicked();

    void on_buttonBox_accepted();

    void on_pushButton_tempfolder_clicked();

    void on_pushButton_outputfolder_clicked();

private:
    Ui::SettingDialog *ui;
    QString openFileDialog(QString program);
    QString openDirectoryDialog();
    ReadSettings *settings;
};

#endif // SETTINGDIALOG_H
