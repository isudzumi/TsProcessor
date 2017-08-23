#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog),
    settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, ORG_NAME, APP_NAME))
{
    ui->setupUi(this);

    settings->beginGroup("Software Path");
    ui->lineEdit_TsSplitter->setText(settings->value("TsSplitter").toString());
    ui->lineEdit_BonTsDemux->setText(settings->value("BonTsDemux").toString());
    ui->lineEdit_FAW->setText(settings->value("FAW").toString());
    ui->lineEdit_DGIndex->setText(settings->value("DGIndex").toString());
    ui->lineEdit_cciconv->setText(settings->value("cciconv").toString());
    settings->endGroup();

    settings->beginGroup("Directory");
    ui->lineEdit_tempfolder->setText(settings->value("tempDirectory").toString());
    ui->lineEdit_outputfolder->setText(settings->value("outputDirectory").toString());
    settings->endGroup();
}

SettingDialog::~SettingDialog()
{
    delete ui;
    delete settings;
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

void SettingDialog::on_pushButton_tempfolder_clicked()
{
    ui->lineEdit_tempfolder->setText(openDirectoryDialog());
}

void SettingDialog::on_pushButton_outputfolder_clicked()
{
    ui->lineEdit_outputfolder->setText(openDirectoryDialog());
}

QString SettingDialog::openFileDialog(QString program)
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Set program path"),
                QDir::homePath(),
                "Program Files (" + program + ".exe)"
                );
    return fileName;
}

QString SettingDialog::openDirectoryDialog()
{
    QString dirName = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                QDir::homePath(),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    return dirName;
}

void SettingDialog::writeConfig()
{
    settings->beginGroup("Software Path");
    settings->setValue("TsSplitter", ui->lineEdit_TsSplitter->text());
    settings->setValue("BonTsDemux", ui->lineEdit_BonTsDemux->text());
    settings->setValue("FAW", ui->lineEdit_FAW->text());
    settings->setValue("DGIndex", ui->lineEdit_DGIndex->text());
    settings->setValue("cciconv", ui->lineEdit_cciconv->text());
    settings->endGroup();

    settings->beginGroup("Directory");
    settings->setValue("tempDirectory", ui->lineEdit_tempfolder->text());
    settings->setValue("outputDirectory", ui->lineEdit_outputfolder->text());
    settings->endGroup();
}

void SettingDialog::on_buttonBox_accepted()
{
    writeConfig();
}
