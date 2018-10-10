#ifndef ADDMAINTAINDIALOG_H
#define ADDMAINTAINDIALOG_H

#include <QDialog>
#include<SqlMag/sqldatasource.h>
namespace Ui {
class AddMaintainDialog;
}

class AddMaintainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMaintainDialog(QWidget *parent = 0);
    ~AddMaintainDialog();
    addUserInfor userInfor;
    QString selectId="";
    QStringList maintainerId,  maintainerlist;

public slots:
    void showDialog();

private slots:

    void on_Btn_maintainSubmit_clicked();
    void on_btnMenu_Close_clicked();
    void on_Btn_Reset_clicked();
private:
    Ui::AddMaintainDialog *ui;
    sqlDataSource sql;
    addMaintain maintain;

};

#endif // ADDMAINTAINDIALOG_H
