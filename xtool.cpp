#include "xtool.h"
#include "ui_xtool.h"
#include <stdlib.h>
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QProgressDialog>
#include <QProcessEnvironment>


XTool::XTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XTool)
{
    ui->setupUi(this);
    // setup device chooser
    ui->comboBox->addItem("Select device");
    ui->comboBox->addItem("Mi 2(s)");
    ui->comboBox->addItem("Mi 3w");
    ui->comboBox->addItem("Mi 4");
    ui->comboBox->addItem("Mi 2a");
    ui->comboBox->addItem("RedMi 1s");
    ui->comboBox->addItem("RedMi 2s");
    ui->comboBox->addItem("Mi Note");
}

XTool::~XTool()
{
    delete ui;
}

/*
 * Actions
 */
void XTool::on_Backup_clicked()
{
    /*
     * Create a backup, asking user where to save backup
     */
    QString file=QFileDialog::getSaveFileName(this,
        tr("Save file"), "", ".ab;;All Files (*.*)");
    const char *backupf = qPrintable(file);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("file", file);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb backup -apk -nosystem -noshared f " + env.value("backupf"));
    QMessageBox::information(this,tr("Backup"),"Done!","OK");
}

void XTool::on_Restore_clicked()
{
    /*
     * Restore a backup picking an ab file
     */
    QString file=QFileDialog::getOpenFileName(this,
        tr("Choose File"),"~","Backups (*.ab);;All Files (*.*)");
    const char *backupf = qPrintable(file);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("file", file);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb restore " + env.value("file"));
    QMessageBox::information(this,tr("Restore backup"),"Restored backup!","OK");
}

void XTool::on_ScreenShot_clicked()
{
    /*
     * Pick a screenshot of the device
     */
}

void XTool::on_Srec_clicked()
{
    /*
     * Record the screen (kk+)
     */
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Screen Recorder",
    "You need android 4.4.x+ in order to record your screen.\nDo you want to start?)",
        QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QMessageBox::information(this,
            tr("Screen Recorder"),
            "UnPlug the device when you want to stop the registration.");
        system("adb shell screenrecord /sdcard/video.mp4");
        QMessageBox::information(this,tr("Xiaomi Tool"),"Done! You can find the video on your phone.","OK");
    }

}

void XTool::on_ApkI_clicked()
{
    /*
     * Install an app
     */
    QString apk=QFileDialog::getOpenFileName(this,
        tr("Choose File"), "~", "App (*.apk);;All Files (*.*)");
    const char *fapk = qPrintable(apk);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("fapk", fapk);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb install " + env.value("fapk"));
    QMessageBox::information(this,tr("Xiaomi Tool"),"App installed!","OK");
}

void XTool::on_ApkU_clicked()
{
    /*
     * Ask user package name and unistall it
     */
}

void XTool::on_Push_clicked()
{
    /*
     * Push a generic file from pc to /sdcard
     */
    QString pushfile=QFileDialog::getOpenFileName(this,
        tr("Choose file"), "~", "All Files (*.*)");
    const char *file = qPrintable(pushfile);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("pushfile", file);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push " + env.value("pushfile") + " /sdcard/");
    QMessageBox::information(this,tr("Xiaomi Tool"),"The file has been pushed!","OK");
}

void XTool::on_PushF_clicked()
{
    /*
     * Push a folder to /sdcard from pc
     */
}

void XTool::on_PushS_clicked()
{
    /*
     * Push a song to /sdcard/Music
     */
    QString pushfile=QFileDialog::getOpenFileName(this,
        tr("Choose song"), "~", "Song (*.mp3);;All Files (*.*)");
    const char *file = qPrintable(pushfile);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("pushfile", file);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push " + env.value("pushfile") + " /sdcard/Music/");
    QMessageBox::information(this,tr("Xiaomi Tool"),"The song has been pushed!","OK");

}

void XTool::on_PushP_clicked()
{
    /*
     * Push a picture to /sdcard/Pictures
     */
    QString dir=QFileDialog::getExistingDirectory(this,
        tr("Choose the destination folder"), "~");
    const char *out = qPrintable(dir);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("dir", out);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push " + env.value("dir") + " /sdcard/");
    QMessageBox::information(this, tr("Xiaomi Tool"), "Directory pushed to the device!");
}

void XTool::on_PullP_clicked()
{
    /*
     * Pull photos and videos from camera
     */
    QString camdir=QFileDialog::getExistingDirectory(this,
        tr("Choose the destination folder"), "~");
    const char *out = qPrintable(camdir);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("out", out);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb pull /sdcard/DCIM/Camera " + env.value("out"));
    QMessageBox::information(this,tr("XiaomiTool"),"Your photos and videos have been imported!","OK");
}

/*
 * Modding
 */

void XTool::on_InstallRec_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "XiaomiTool",
    "You\'re installing a recovery.\nThis might brick the device if something goes wong.\nContinue?",
        QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QMessageBox::information(this, tr("XiaomiTool"),
            "Flashing recovery...");
        system("adb reboot bootloader");
        system("fastboot devices");
        int id(0);
        if (ui->comboBox->currentText() == "Mi 2(s)")
            id = 1;
        if (ui->comboBox->currentText() == "Mi 3w" || ui->comboBox->currentText() == "Mi 4")
            id = 2;
        if (ui->comboBox->currentText() == "Mi 2a")
            id = 3;
        if (ui->comboBox->currentText() == "RedMi 1s")
            id = 4;
        /*
         * Disable unsupported devices
        if (ui->comboBox->currentText() == "RedMi 2s")
            id = 5;
        if (ui->comboBox->currentText() == "Mi Note")
            id = 6;
        */
        switch (id){
            // my windows pc does not have enought ram to code recoveries inside the exe :(
            case 1: system("fastboot flash recovery recovery/aries.img"); break;
            case 2: system("fastboot flash recovery recovery/cancro.img"); break;
            case 3: system("fastboot flash recovery recovery/taurus.img"); break;
            case 4: system("fastboot flash recovery recovery/armani.img"); break;
            default: QMessageBox::warning(this, tr("XiaomiTool"), "No recovery found for this device!"); break;
        }
        system("fastboot reboot");
        // we've just flashed a recovery
        ui->InstallRec->setChecked(true);
    }
}

void XTool::on_RebootRec_clicked()
{
    /*
     * Boot device to recovery
     */
    QMessageBox::information(this, tr("XiaomiTool"), "Rebooting to recovery..");
    system("adb reboot recovery");
}

void XTool::on_Sideload_clicked()
{
    /*
     * Sideload file from pc
     */
    QString fbboot=QFileDialog::getOpenFileName(this,
                tr("Choose File"), "~", "Images (*.img);;All Files (*.*)");
    QMessageBox::information(this,tr("Fastboot Boot"),fbboot,"OK");
    const char *ffbboot = qPrintable(fbboot);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Fastboot Boot", "Do you want to sideload an img file from your computer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.insert("ffbboot", ffbboot);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader; fastboot devices; fastboot boot " + env.value("ffbboot"));
        QMessageBox::information(this,tr("Fastboot Boot"),"Done!","OK");
    }

}

void XTool::on_FlashZip_clicked()
{
    if (ui->CustomRec->isChecked()){
        QString zip=QFileDialog::getOpenFileName(this,
                    tr("Choose File"), "~", "Flashable file (*.zip);;All Files (*.*)");
        QMessageBox::information(this,tr("Flasher"),zip,"OK");
        const char *file = qPrintable(zip);
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Flasher", "Do you want to flash a file?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            env.insert("sideload", file);
            QMessageBox::information(this, tr("Flasher"), "Installing file...\nDo not touch the device!");
            system("adb reboot recovery; adb wait-for-device; adb 'shell rm -fr /cache/recovery'; adb shell 'mkdir /cache/recovery'");
            system("adb shell 'echo -e sideload > /cache/recovery/command");
            if (ui->DatCheck->isChecked())
                system("adb shell 'echo -e wipe_data >> /cache/recovery/command'");
            system("adb reboot recovery");
            QProcess process;
            QProgressDialog *dialog = new QProgressDialog;
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            dialog->setRange(0,0);
            connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
            process.start("adb sideload " + env.value("sideload"));
            QMessageBox::information(this, tr("XiaomiTool"),
                "Zip file has been installed, wait until the device applies changes.");
        }
    }
    else {
        QMessageBox::warning(this, tr("XiaomiTool"),
            "You can\'t use this feature if you have no custom recovery. If you have then check the option.");
    }
}

void XTool::on_actionAbout_triggered()
{
        QMessageBox::about(this,tr("About XTool"),"©2015 Joey Rizzoli (@linuxx)\nSources: https://github.com/linuxxxxx/XTool\nXiaomiTool is a software that has the goal to provide a fast, safe and user friendly tool to manage your Xiaomi device.");
}

void XTool::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "XiaomiTool", "Do you want to quit XiaomiTool?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        XTool::~XTool();
}
