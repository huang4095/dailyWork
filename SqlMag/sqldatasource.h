#ifndef SQLDATASOURCE_H
#define SQLDATASOURCE_H
#include<QUuid>
#include<QList>
#include"connectpool.h"

struct addUserInfor{
    QString   id;
    QString   code;
    QString   name;
    QString   position;
    QString   departmentId="00000000-0000-0000-0000-000000000000";
    QString   productLineId="00000000-0000-0000-0000-000000000000";
    QString   leaderId="00000000-0000-0000-0000-000000000000";
    QString   passWord;
    QString   role;

};
struct addDepartment{
    QString id;
    QString code;
    QString name;
    QString   chargerId="00000000-0000-0000-0000-000000000000";

};
struct addProductLine{
    QString id;
    QString code;
    QString name;
    QString   chargerId="00000000-0000-0000-0000-000000000000";
    QString   departmentId="00000000-0000-0000-0000-000000000000";


};
struct addDailyWork{
    QString id;
    QString departmentId="00000000-0000-0000-0000-000000000000" ;
    QString productLineId="00000000-0000-0000-0000-000000000000" ;
    QString userId="00000000-0000-0000-0000-000000000000" ;
    QString recordDate ;
    float workTime ;
    float noWorkTime ;
    int planCompleteQTY ;
    int realCompleteQTY ;
    float inputWorkTime ;
    float outWorkTime ;
    float workRate ;
    QString uncompleteReason ;
    int badQty;

};


struct addPlanData{
     QString id;
     QString departmentId="00000000-0000-0000-0000-000000000000" ;
     QString productLineId="00000000-0000-0000-0000-000000000000" ;
     QString productday;
     QString CN;
     QString PN;
     QString machineCode;
     int PlanQty;
     int productQTY;
     int badQTY;
     QString readyMsg;
     QString  machineType;
     QString  exportPlace;
     QString recordId;
     QString userId="00000000-0000-0000-0000-000000000000" ;
};


struct AttendanceData{
    QString id;
    QString departmentId="00000000-0000-0000-0000-000000000000";
    QString productLineId="00000000-0000-0000-0000-000000000000" ;
    QString userid;
    QString recordDate;
    QString onduty;
    QString onleave;
    QString absenteeism;
    QString violation;
    QString dutyMsg;

};


struct addProduct{
    QString id;
    QString machineCode;
    QString productDate;
    QString CN;
    QString PN;
    QString exportPlace;
    int     planQTY;
    int     QTY;
    int     badQTY;
    QString   departmentId="00000000-0000-0000-0000-000000000000";
    QString   productLineId="00000000-0000-0000-0000-000000000000";
    QString   recordId="00000000-0000-0000-0000-000000000000";
};

struct addRejects{
    QString id;
    QString   departmentId="00000000-0000-0000-0000-000000000000";
    QString   productLineId="00000000-0000-0000-0000-000000000000";
    QString   userId="00000000-0000-0000-0000-000000000000";
    QString machineCode;
    QString productDate;
    QString CN;
    QString PN;
    QString rejectsDetail;
    QString reason;
    QString solution;
    QString responsible;
    int     QCType;
    int     rejectsType;
    int     badQTY;
    QString   recordId="00000000-0000-0000-0000-000000000000";
};

struct addMaintain{
    QString id;
    QString userId;
    QString maintainerId;
    QString maintainType;
    int     maintainQTY;

    QString   remark;
    QString   CN;
    QString   PN;
    QString   machineCode;
    QString   maintainDate;
};

struct addPQCProblem{
    QString  id;
    QString  departmentId="00000000-0000-0000-0000-000000000000";
    QString  productLineId="00000000-0000-0000-0000-000000000000";
    QString  userId="00000000-0000-0000-0000-000000000000";
    QString recordDate;
    QString machineCode;
    QString CN;
    QString PN;
    QString problemDetail;
    QString solutionDetail;
    QString verification;
    int problemStatus;
   // int checkStatus;
    QString  confirmUserId="00000000-0000-0000-0000-000000000000";
    QString confirmTime;
};


struct addCheckRecord{
    QString id;
    QString checkerId;
    QString details;
    QString recordId;
    QString     date;
    QString     result;


};
//enum dailyWorkStatus{
//       "新增"=0,
//       主任审批,
//       厂长审批,
//       总监审批
//   };
class sqlDataSource
{
public:
    sqlDataSource();
public slots:



    bool addFormList(QString formName, QStringList fieldName, QVariantList value);

    QString idToName(QString id, QString from);
    bool updateForm(QString id,QString fromName, QStringList field, QVariantList value);


    //QList<QStringList> getFormList(QString formName, QString orderField, QString id="");

    void tableWidgetShow(QStringList HStrList, QList<QStringList> date, QTableWidget *tableWidget);

//    QList<QStringList> getFieldListByFieldOr(QString formName, QStringList FieldName, QString orderField, QStringList Field, QStringList value);

//    QList<QStringList> getFieldListByField(QString formName, QStringList FieldName, QString orderField, QStringList Field, QStringList value);
//    QList<QStringList> getFieldList(QString formName, QStringList FieldName, QString orderField, QString id="");



    QList<QStringList> getFormListbyCondition(QString formName, QStringList fieldName,QStringList condition,QStringList orderField);

    QList<QStringList> getFormListbyCondition(QString formName, QString fieldName, QStringList condition, QString orderField="recordTime");



    QList<QStringList> getFormListbyCondition(QString formName, QString fieldName, QString orderField="recordTime");
    QList<QStringList> getFormListbyCondition(QString formName, QStringList fieldName, QString orderField="recordTime");
    QList<QStringList> getFormListbyCondition(QString formName, QStringList fieldName, QStringList condition, QString orderField="recordTime");
private:
    ConnectionPool sql;

};


#endif // SQLDATASOURCE_H
