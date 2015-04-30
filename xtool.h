#ifndef XTOOL_H
#define XTOOL_H

#include <QMainWindow>

namespace Ui {
class XTool;
}

class XTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit XTool(QWidget *parent = 0);
    ~XTool();

private slots:
    void on_Backup_clicked();

    void on_Restore_clicked();

    void on_ScreenShot_clicked();

    void on_Srec_clicked();

    void on_ApkI_clicked();

    void on_ApkU_clicked();

    void on_Push_clicked();

    void on_PushF_clicked();

    void on_PushS_clicked();

    void on_PushP_clicked();

    void on_PullP_clicked();

    void on_InstallRec_clicked();

    void on_RebootRec_clicked();

    void on_Sideload_clicked();

    void on_FlashZip_clicked();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

private:
    Ui::XTool *ui;
};

#endif // XTOOL_H
