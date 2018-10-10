#ifndef DAILYWORK_H
#define DAILYWORK_H

#include <QWidget>
#include<QStackedWidget>
#include"DailyWorkPage/dailyworkpage.h"
#include"DailyProblemPage/dailyproblempage.h"
#include"SettingPage/settingpage.h"
#include"SqlMag/connectpool.h"
class QToolButton;



namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    ConnectionPool sql;
    addUserInfor userInfor;
    QStringList departmentList;
    QStringList departmentListId;

public slots:
    void showWidget();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWidget *ui;
    QTimer *Timer1s;

    DailyProblemPage *dailyProblemPage;
    DailyWorkPage *dailyWorkPage;
    SettingPage *settingPage;
    int ss;

private slots:
    void initForm();
    void buttonClick();


private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

    void TopMenu_SysInfo();
    void getDepartmentList();
};

#endif // DAILYWORK_H
