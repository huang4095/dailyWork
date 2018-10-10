#ifndef DAILYPROBLEMPAGE_H
#define DAILYPROBLEMPAGE_H
#include "adddailyproblemdialog.h"
#include "logindialog.h"
#include<SqlMag/sqldatasource.h>

#include <QWidget>

namespace Ui {
class DailyProblemPage;
}

class DailyProblemPage : public QWidget
{
    Q_OBJECT

public:
    explicit DailyProblemPage(QWidget *parent = 0);
    ~DailyProblemPage();
        addUserInfor userInfor;
         QStringList departmentList, departmentListId;

public slots:
         void showPage();
private slots:
    void initPage();
    void MenuClick();
    void on_Btn_AddPQC_clicked();
    void getDepartmentinfo();
    void getProductLine(QString currentDepartmentId);
    void on_BN_Search_PQCProblem_clicked();

    void on_tableWidget_PQC_doubleClicked(const QModelIndex &index);

    void on_Btn_DeletePQC_clicked();

private:
    Ui::DailyProblemPage *ui;
    sqlDataSource sql;

    QList<int> pixChar;
    QList<QToolButton *> btns;
    QString selectId;

    QStringList productLineList, productLineListId;
    QComboBox * ComB_CheckStatus;

};

#endif // DAILYPROBLEMPAGE_H
