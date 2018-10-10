#ifndef QCMADD_H
#define QCMADD_H

#include"logindialog.h"
#include <QDialog>

namespace Ui {
class QcmAdd;
}

class QcmAdd : public QDialog
{
    Q_OBJECT

public:
    explicit QcmAdd(QWidget *parent = 0);
    ~QcmAdd();
    addUserInfor userInfor;
     QString productId="";
     QString rejectsId="";

public slots:
    void showDialog();

private slots:
    void on_Btn_QcmSubmit_clicked();

    void on_btnMenu_Close_clicked();

    void on_Btn_Reset_clicked();

private:
    Ui::QcmAdd *ui;
    addRejects rejectsData;
    sqlDataSource sql;
};

#endif // QCMADD_H
