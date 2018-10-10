#ifndef addProductLineDialog_H
#define addProductLineDialog_H

#include <QDialog>
#include<SqlMag/connectpool.h>
#include"SqlMag/sqldatasource.h"
#include<QUuid>

namespace Ui {
class addProductLineDialog;
}

class addProductLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addProductLineDialog(QWidget *parent = 0);
    ~addProductLineDialog();
    QString selectId="";
public slots:
    void showDialog();
private slots:
    void on_Btn_Submit_clicked();

    void on_btnMenu_Close_clicked();

    void getUserinfo();
    void getDepartmentinfo();

    void on_ComB_charger_activated(int index);

    void on_ComB_department_activated(int index);

private:
    Ui::addProductLineDialog *ui;
    addProductLine productLineInfor;
    sqlDataSource addSql;
    QStringList departmentList,userList;
    QStringList departmentListId,userListId;


};

#endif // addProductLineDialog_H
