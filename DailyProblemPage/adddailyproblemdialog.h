#ifndef ADDDAILYPROBLEMDIALOG_H
#define ADDDAILYPROBLEMDIALOG_H
#include"logindialog.h"

#include <QDialog>

namespace Ui {
class AddDailyProblemDialog;
}

class AddDailyProblemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDailyProblemDialog(QWidget *parent = 0);
    ~AddDailyProblemDialog();
    QString selectId = "" ,checkStatus ="";
    addUserInfor userInfor;
    
public slots:
    showDialog();
private slots:
    void on_Btn_Submit_clicked();    
    void on_btnMenu_Close_clicked();
    
    void on_Btn_checkOk();
    void on_Btn_checkReject();
    void init_checkTableWidget();
private:
    Ui::AddDailyProblemDialog *ui;
    sqlDataSource sql;
    QStringList machineCode,CN,PN;
    QPushButton *Btn_checkOk;
    QPushButton *Btn_checkReject;
    QTextEdit   *TE_checkRemark;
    QLabel *LB;
    QTableWidget *checkTableWidget;
    QList<addProduct>    ProductList;
    int currentStatus = 0;
};

#endif // ADDDAILYPROBLEMDIALOG_H
