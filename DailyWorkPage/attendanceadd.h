#ifndef ATTENDANCEADD_H
#define ATTENDANCEADD_H

#include <QDialog>
#include "logindialog.h"

namespace Ui {
class AttendanceAdd;
}

class AttendanceAdd : public QDialog
{
    Q_OBJECT

public:
    explicit AttendanceAdd(QWidget *parent = 0);
    ~AttendanceAdd();
    QString selectId="";
    addUserInfor userInfor;

public slots:
    void showDialog();
private slots:
    void on_btnMenu_Close_clicked();
    void on_Btn_Reset_clicked();

    void on_Btn_Submit_clicked();

private:
    Ui::AttendanceAdd *ui;
    sqlDataSource sql;
    AttendanceData attendancedata;

};

#endif // ATTENDANCEADD_H
