#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    settings(ReadSettings::getInstance()),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->lineEdit_TsSplitter->setText(settings->getSoftware(QStringLiteral("TsSplitter")));
    ui->lineEdit_BonTsDemux->setText(settings->getSoftware(QStringLiteral("BonTsDemux")));
    ui->lineEdit_FAW->setText(settings->getSoftware(QStringLiteral("FAW")));
    ui->lineEdit_DGIndex->setText(settings->getSoftware(QStringLiteral("DGIndex")));
    ui->lineEdit_cciconv->setText(settings->getSoftware(QStringLiteral("cciconv")));

    ui->lineEdit_tempfolder->setText(settings->getDirectory(QStringLiteral("tempDirectory")));
    ui->lineEdit_outputfolder->setText(settings->getDirectory(QStringLiteral("outputDirectory")));
}

SettingDialog::~SettingDialog()
{
//    delete settings;
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

void SettingDialog::on_buttonBox_accepted()
{
    settings->setSoftware(QStringLiteral("TsSplitter"), ui->lineEdit_TsSplitter->text());
    settings->setSoftware(QStringLiteral("BonTsDemux"), ui->lineEdit_BonTsDemux->text());
    settings->setSoftware(QStringLiteral("FAW"), ui->lineEdit_FAW->text());
    settings->setSoftware(QStringLiteral("DGIndex"), ui->lineEdit_DGIndex->text());
    settings->setSoftware(QStringLiteral("cciconv"), ui->lineEdit_cciconv->text());

    settings->setDirectory(QStringLiteral("tempDirectory"), ui->lineEdit_tempfolder->text());
    settings->setDirectory(QStringLiteral("outputDirectory"), ui->lineEdit_outputfolder->text());
}
