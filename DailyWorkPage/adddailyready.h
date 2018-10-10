#ifndef ADDDAILYREADY_H
#define ADDDAILYREADY_H

#include"logindialog.h"
#include <QDialog>

namespace Ui {
class AddDailyReady;
}

class AddDailyReady : public QDialog
{
    Q_OBJECT

public:
    explicit AddDailyReady(QWidget *parent = 0);
    ~AddDailyReady();
    addUserInfor userInfor;
    QString selectId="";

public slots:
    void showDialog();
private slots:
    void on_Btn_dailyReadySubmit_clicked();

    void on_btnMenu_Close_clicked();

    void on_Btn_Reset_clicked();

private:
    Ui::AddDailyReady *ui;
    sqlDataSource sql;
    addPlanData plandata;
};

#endif // ADDDAILYREADY_H
