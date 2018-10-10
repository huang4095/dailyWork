#ifndef DAILYWORKPAGE_H
#define DAILYWORKPAGE_H
#include"appInit/TextEditDelegate.h"
#include <QWidget>
#include<QToolButton>
#include"adddailyworkproduct.h"
#include "adddailyready.h"
#include<SqlMag/sqldatasource.h>
#include "addRejects.h"
#include "attendanceadd.h"
#include"addmaintaindialog.h"
//#include"mainwidget.h"
namespace Ui {
class DailyWorkPage;
}

class DailyWorkPage : public QWidget
{
    Q_OBJECT

public:
    explicit DailyWorkPage(QWidget *parent = 0);
    ~DailyWorkPage();
    addUserInfor userInfor;
    QString selectId , productId;
    QStringList departmentList,departmentListId;
	QString checkStatus;
public slots:
    void showPage();
private slots:
    void initPage();
    void MenuClick();
    void on_Btn_AddDailyProduct_clicked();

    void on_Btn_searchDailyWork_clicked();

    void on_Btn_deleteDailyProduct_clicked();

    void on_tableWidget_dailyProduct_doubleClicked(const QModelIndex &index);

    void getDepartmentinfo();
    void getProductLine(QString currentDepartmentId);
    void on_ComB_dailyWork_department_activated(int index);
    void on_Btn_AddDailyReady_clicked();

    void on_Btn_search_DailyReady_clicked();

    void on_Btn_deleteDailyReady_clicked();



    void on_tableWidget_dailyReady_doubleClicked(const QModelIndex &index);

    void on_Btn_Add_Attendance_clicked();

    void on_Btn_search_attendance_clicked();

    void on_tableWidget_attendance_doubleClicked(const QModelIndex &index);

    void on_Btn_delete_attendance_clicked();

    void on_ComB_qcm_department_activated(int index);

    void on_ComB_attendance_department_activated(int index);

    void on_ComB_dailyReady_department_activated(int index);

    void on_Btn_AddMaintain_clicked();

    void getMaintainer();
    void on_Btn_searchMaintain_clicked();

    void on_tableWidget_Maintain_doubleClicked(const QModelIndex &index);

    void on_Btn_deleteMaintian_clicked();

    void on_tableWidget_Rejects_doubleClicked(const QModelIndex &index);

    void on_Btn_search_rejects_clicked();

    void on_Btn_delete_rejects_clicked();

    void on_Btn_Add_Rejects_clicked();

    void on_Btn_search_qcm_clicked();
    void on_tableWidget_QCRecord_doubleClicked(const QModelIndex &index);
    void on_tableWidget_QCRecord_itemSelectionChanged();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::DailyWorkPage *ui;
 	QComboBox * ComB_CheckStatus;
    QStringList  productLineList, maintainerlist;
    QStringList  productLineListId, maintainerId;
    sqlDataSource sql;
    QList<int> pixChar;
    QList<QToolButton *> btns;

};

#endif // DAILYWORKPAGE_H
