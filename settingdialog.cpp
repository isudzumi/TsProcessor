#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog),
    settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, ORG_NAME, APP_NAME))
{
    ui->setupUi(this);

    ui->lineEdit_TsSplitter->setText(settings->value("TsSplitter").toString());
    ui->lineEdit_BonTsDemux->setText(settings->value("BonTsDemux").toString());
    ui->lineEdit_FAW->setText(settings->value("FAW").toString());
    ui->lineEdit_DGIndex->setText(settings->value("DGIndex").toString());
    ui->lineEdit_cciconv->setText(settings->value("cciconv").toString());
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButton_TsSplitter_clicked()
{
    ui->lineEdit_TsSplitter->setText(openFileDialog("TsSplitter"));
}

void SettingDialog::on_pushButton_BonTsDemux_clicked()
{
    ui->lineEdit_BonTsDemux->setText(openFileDialog("BonTsDemuxC"));
}

void SettingDialog::on_pushButton_FAW_clicked()
{
    ui->lineEdit_FAW->setText(openFileDialog("fawcl"));
}

void SettingDialog::on_pushButton_DGIndex_clicked()
{
    ui->lineEdit_DGIndex->setText(openFileDialog("DGIndex"));
}

void SettingDialog::on_pushButton_cciconv_clicked()
{
    ui->lineEdit_cciconv->setText(openFileDialog("cciconv188"));
}

QString SettingDialog::openFileDialog(QString program)
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Set program path"),
                QDir::currentPath(),
                "Program Files (" + program + ".exe)"
                );
    return fileName;
}

void SettingDialog::writeConfig()
{
    settings->setValue("TsSplitter", ui->lineEdit_TsSplitter->text());
    settings->setValue("BonTsDemux", ui->lineEdit_BonTsDemux->text());
    settings->setValue("FAW", ui->lineEdit_FAW->text());
    settings->setValue("DGIndex", ui->lineEdit_DGIndex->text());
    settings->setValue("cciconv", ui->lineEdit_cciconv->text());
}

void SettingDialog::on_buttonBox_accepted()
{
    writeConfig();
}
