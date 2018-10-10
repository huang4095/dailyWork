#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H
#include"SqlMag/connectpool.h"
#include <QWidget>
#include"adduserdialog.h"
#include"adddepartmentdialog.h"
#include"addproductlinedialog.h"
#include<QToolButton>
namespace Ui {
class SettingPage;
}

class SettingPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = 0);
    ~SettingPage();

private slots:
    void initPage();
    void MenuClick();
    void on_Btn_AddUser_clicked();
    void on_Btn_SearchUser_clicked();

    void on_Btn_addDepartment_clicked();

    void on_tBtn_Menu2_clicked();

    void on_tableWidget_user_doubleClicked(const QModelIndex &index);

//    void tableWidgetShow(QStringList HStrList, QList<QStringList> date, QTableWidget *tableWidget);
    void on_Btn_DeleteUser_clicked();

    void on_tableWidget_user_clicked(const QModelIndex &index);

    void on_Btn_AddProductLine_clicked();

    void on_tBtn_Menu3_clicked();

    void on_tableWidget_department_doubleClicked(const QModelIndex &index);

    void on_tableWidget_department_clicked(const QModelIndex &index);

    void on_Btn_DeleteDepartment_clicked();

    void on_tableWidget_productLine_doubleClicked(const QModelIndex &index);

    void on_tableWidget_productLine_clicked(const QModelIndex &index);

    void on_Btn_DeleteProductLine_clicked();

private:
    Ui::SettingPage *ui;
    //ConnectionPool sql;
    QList<int> pixChar;
    QList<QToolButton *> btns;
    sqlDataSource sql;
    QString selectId;
};

#endif // SETTINGPAGE_H
