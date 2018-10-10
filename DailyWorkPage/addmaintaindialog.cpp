#include "addmaintaindialog.h"
#include "ui_addmaintaindialog.h"
#include"appInit/quiwidget.h"
AddMaintainDialog::AddMaintainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMaintainDialog)
{

    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);
}

AddMaintainDialog::~AddMaintainDialog()
{
    delete ui;
}

void AddMaintainDialog::showDialog()
{
    QStringList field,value;
    field.append("role");
    value.append("作业员");


    QCompleter *NewFind = new QCompleter(maintainerlist);

    ui->ComB_maintainPerson->setCompleter(NewFind);
    ui->ComB_maintainPerson->clear();
    ui->ComB_maintainPerson->addItems(maintainerlist);

    ui->DE_maintainDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_maintainDate->setDate(QDate::currentDate());
    if(selectId!=""){

        QStringList condition;

        condition.append("id = '"+selectId +"'");
        QStringList datalist= sql.getFormListbyCondition("maintainRecord","*",condition,"maintainDate").at(0);

        ui->DE_maintainDate->setDate(QDate::fromString(datalist.at(11),"yyyy-MM-dd"));
        ui->LE_CN->setText(datalist.at(8));
        ui->LE_PN->setText(datalist.at(9));
        ui->LE_machineCode->setText(datalist.at(10));
        ui->LE_MaintainQTY->setText(datalist.at(6));
        ui->TE_maintainRemark->setText(datalist.at(7));
        ui->ComB_maintainType->setCurrentText(datalist.at(5));
        //ui->ComB_maintainPerson->setCurrentText(sql.idToName(datalist.at(4),"userInfo");

    }

}
void AddMaintainDialog::on_Btn_maintainSubmit_clicked()
{
    if(ui->LE_PN->text().isEmpty()||ui->LE_machineCode->text().isEmpty()||ui->TE_maintainRemark->toPlainText().isEmpty())
   {
        QUIHelper::showMessageBoxInfo("订单号或机型或维修信息不能空！",2);
       return;
   }

    maintain.maintainDate=ui->DE_maintainDate->date().toString("yyyy-MM-dd");
    maintain.CN = ui->LE_CN->text();
    maintain.PN = ui->LE_PN->text();
    maintain.machineCode = ui->LE_machineCode->text();
    maintain.maintainQTY = ui->LE_MaintainQTY->text().toInt();
    maintain.remark = ui->TE_maintainRemark->toPlainText();  
    maintain.maintainType=ui->ComB_maintainType->currentText();
    maintain.userId=userInfor.id;
    maintain.maintainerId = maintainerId.at(ui->ComB_maintainPerson->currentIndex());
    QStringList fieldname;
    QVariantList value;
    fieldname.empty();
    value.empty();
    if(selectId == "")
    {
        QString id;
        QUuid Id=QUuid::createUuid();
        id=Id.toString().mid(1,36);
        maintain.id = id;
        fieldname.append("id");
        fieldname.append("userId");
        fieldname.append("maintainerId");
        fieldname.append("maintainDate");
        fieldname.append("machineCode");
        fieldname.append("CN");
        fieldname.append("PN");
        fieldname.append("maintainQty");
        fieldname.append("maintainType");
        fieldname.append("remark");

        value.append(maintain.id);
        value.append(maintain.userId);
        value.append(maintain.maintainerId);
        value.append(maintain.maintainDate);
        value.append(maintain.machineCode);
        value.append(maintain.CN);
        value.append(maintain.PN);
        value.append(QString::number(maintain.maintainQTY,10));
        value.append(maintain.maintainType);
        value.append(maintain.remark);
        sql.addFormList("maintainRecord",fieldname,value);

    }
    else
    {


        fieldname.append("userId");
        fieldname.append("maintainerId");
        fieldname.append("maintainDate");
        fieldname.append("machineCode");
        fieldname.append("CN");
        fieldname.append("PN");
        fieldname.append("maintainQty");
        fieldname.append("maintainType");
        fieldname.append("remark");


        value.append(maintain.userId);
        value.append(maintain.maintainerId);
        value.append(maintain.maintainDate);
        value.append(maintain.machineCode);
        value.append(maintain.CN);
        value.append(maintain.PN);
        value.append(QString::number(maintain.maintainQTY,10));
        value.append(maintain.maintainType);
        value.append(maintain.remark);
        sql.updateForm(selectId,"maintainRecord",fieldname,value);


    }

}

void AddMaintainDialog::on_btnMenu_Close_clicked()
{
    close();
}

void AddMaintainDialog::on_Btn_Reset_clicked()
{

}
