#ifndef ADDDEPARTMENTDIALOG_H
#define ADDDEPARTMENTDIALOG_H

#include <QDialog>
#include<SqlMag/connectpool.h>
#include"SqlMag/sqldatasource.h"
#include<QUuid>

namespace Ui {
class addDepartmentDialog;
}

class addDepartmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDepartmentDialog(QWidget *parent = 0);
    ~addDepartmentDialog();
    QString selectId="";


public slots:
    void showDialog();
private slots:
    void on_Btn_Submit_clicked();

    void on_btnMenu_Close_clicked();

    void getUserinfo();
    void on_ComB_charger_activated(int index);

private:
    Ui::addDepartmentDialog *ui;

    sqlDataSource addSql;
    addDepartment DepartmentInfor;
    QStringList userList;
    QStringList userListId;


};

#endif // ADDDEPARTMENTDIALOG_H
