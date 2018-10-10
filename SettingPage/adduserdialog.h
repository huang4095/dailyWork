#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include<SqlMag/connectpool.h>
#include"SqlMag/sqldatasource.h"
#include<QUuid>
namespace Ui {
class addUserDialog;
}

class addUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addUserDialog(QWidget *parent = 0);
    ~addUserDialog();
    QString selectId="";

public slots:
    void showDialog();
protected:

private slots:
    void on_btnMenu_Close_clicked();
    void on_Btn_Submit_clicked();

    void getDepartmentinfo();
    void on_ComB_Department_activated(int index);

    void on_ComB_Leader_activated(int index);

    void getUserinfo();
    void getProductLine(QString currentDepartmentId);
    void on_ComB_ProductLine_activated(int index);

    void on_ComB_Role_activated(const QString &arg1);

private:
    Ui::addUserDialog *ui;
    addUserInfor userInfor;
    sqlDataSource addSql;
    QStringList departmentList,userList,productLineList;
    QStringList departmentListId,userListId,productLineListId;
};

#endif // ADDUSERDIALOG_H
