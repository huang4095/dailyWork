#ifndef ADDDAILYWORKPRODUCT_H
#define ADDDAILYWORKPRODUCT_H

#include <QDialog>
#include<SqlMag/sqldatasource.h>
//#include"mainwidget.h"
#include"logindialog.h"

namespace Ui {
class AddDailyWorkProduct;
}

class AddDailyWorkProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddDailyWorkProduct(QWidget *parent = 0);
    ~AddDailyWorkProduct();
    QString selectId="";
    QString checkStatus="";
    addUserInfor userInfor;
public slots:
    void showDialog();
protected:

private:
    Ui::AddDailyWorkProduct *ui;
    sqlDataSource sql;
    addDailyWork  DailyWork;
    addCheckRecord AddCheckRecord;

    QPushButton *Btn_checkOk;
    QPushButton *Btn_checkReject;
    QTextEdit   *TE_checkRemark;
    QLabel *LB;
    QTableWidget *checkTableWidget;
    QList<addProduct>    ProductList;

private slots:

    void on_btnMenu_Close_clicked();

    void on_Btn_DailyWorkSubmit_clicked();
    void on_Btn_addProcutType_clicked();

    void on_Btn_deleteProcutType_clicked();
    void on_Btn_Reset_clicked();


    void on_tableWidget_productType_itemChanged(QTableWidgetItem *item);
    void on_Btn_checkOk();
    void on_Btn_checkReject();
    void init_checkTableWidget();
};

#endif // ADDDAILYWORKPRODUCT_H
