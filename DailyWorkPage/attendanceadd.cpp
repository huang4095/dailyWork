#include "attendanceadd.h"
#include "ui_attendanceadd.h"

AttendanceAdd::AttendanceAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttendanceAdd)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);
}

AttendanceAdd::~AttendanceAdd()
{
    delete ui;
}

void AttendanceAdd::on_btnMenu_Close_clicked()
{
    close();
}

void AttendanceAdd::on_Btn_Reset_clicked()
{
    ui->TE_namelist->clear();
}

void AttendanceAdd::showDialog()
{
    QString Department = sql.idToName(userInfor.departmentId,"department");
    ui->LE_Department->setText(Department);
    QString productLine = sql.idToName(userInfor.productLineId,"productLine");
    ui->LE_ProductLine->setText(productLine);
    ui->DE_date->setDisplayFormat("yyyy-MM-dd");
    ui->DE_date->setDate(QDate::currentDate());
    ui->LE_onLeave->setText("0");
    ui->LE_absenteeism->setText("0");
    ui->LE_violation->setText("0");
    if(selectId !=""){
        QStringList fieldname,condition;
        fieldname.append("*");
        condition.append("id = '"+selectId +"'");
        QStringList strList=sql.getFormListbyCondition("dutyrecord",fieldname,condition).at(0);

        ui->DE_date->setDate(QDate::fromString(strList.at(6),"yyyy-MM-dd"));
        ui->LE_onduty->setText(strList.at(7));
        ui->LE_onLeave->setText(strList.at(8));
        ui->LE_absenteeism->setText(strList.at(9));
        ui->LE_violation->setText(strList.at(10));
        ui->TE_namelist->setPlainText(strList.at(11));
    }

}

void AttendanceAdd::on_Btn_Submit_clicked()
{
    //新增和更新分开写，结构清洗
    if( ui->LE_onduty->text()!= NULL)
    {
        int qty= ui->LE_onduty->text().toInt();
        if(qty <= 0)
        {
            QUIHelper::showMessageBoxInfo("请确认出勤数！",2);
            return;
        }else
        {
            attendancedata.onduty = ui->LE_onduty->text();

        }
    }else
    {
        QUIHelper::showMessageBoxInfo("出勤数为空！",2);
        return;
    }

    QStringList fieldname;
    QVariantList value;
    
    fieldname.empty();
    value.empty();
    fieldname.append("id");
    fieldname.append("departmentId");
    fieldname.append("productlineId");
    fieldname.append("userid");
    fieldname.append("recordDate");
    fieldname.append("onduty");
    fieldname.append("onleave");
    fieldname.append("absenteeism");
    fieldname.append("violation");
    fieldname.append("dutyMsg");



    attendancedata.recordDate = ui->DE_date->text();
    attendancedata.onleave = ui->LE_onLeave->text();
    attendancedata.absenteeism = ui->LE_absenteeism->text();
    attendancedata.violation = ui->LE_violation->text();
    attendancedata.dutyMsg = ui->TE_namelist->toPlainText();



     if(selectId==""){
         QString id;
         QUuid Id=QUuid::createUuid();
         id=Id.toString().mid(1,36);
         value.append(id);
         value.append(userInfor.departmentId);
         value.append(userInfor.productLineId);
         value.append(userInfor.id);
         value.append(attendancedata.recordDate);
         value.append(attendancedata.onduty);
         value.append(attendancedata.onleave);
         value.append(attendancedata.absenteeism);
         value.append(attendancedata.violation);
         value.append(attendancedata.dutyMsg);
         sql.addFormList("dutyrecord",fieldname,value);
     }else
     {

       value.append(selectId);
       value.append(userInfor.departmentId);
       value.append(userInfor.productLineId);
       value.append(userInfor.id);
       value.append(attendancedata.recordDate);
       value.append(attendancedata.onduty);
       value.append(attendancedata.onleave);
       value.append(attendancedata.absenteeism);
       value.append(attendancedata.violation);
       value.append(attendancedata.dutyMsg);
       bool ret =  sql.updateForm(selectId,"dutyrecord",fieldname,value);
         if(ret){
              close();
         }
    }
}
