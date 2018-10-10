#ifndef LoginDialog_H
#define LoginDialog_H
#include <QtSql/QSqlQuery>
#include <QDebug>
#include"SqlMag/sqldatasource.h"
#include "Appinit/quiwidget.h"
#include"SqlMag/connectpool.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
     addUserInfor userInfor;

private:


private:
    Ui::LoginDialog *ui;

private slots:


    void on_loginBtn_clicked();

    void on_quitBtn_clicked();

    void on_changeinfor_Btn_clicked();

    void on_minBtn_clicked();
};

#endif // LoginDialog_H
