#include "adddailyready.h"
#include "ui_adddailyready.h"
#include <QDebug>
#include"appInit/quiwidget.h"

AddDailyReady::AddDailyReady(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDailyReady)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);

}

AddDailyReady::~AddDailyReady()
{
    delete ui;
}

void AddDailyReady::showDialog()
{


    QString Department = sql.idToName(userInfor.departmentId,"department");
    ui->LE_Department->setText(Department);

    QString productLine = sql.idToName(userInfor.productLineId,"productLine");
    ui->LE_ProductLine->setText(productLine);
    ui->DE_productday->setDisplayFormat("yyyy-MM-dd");
    ui->DE_productday->setDate(QDate::currentDate().addDays(1));
    if(selectId != ""){
        QStringList condition,fieldName;
        condition.append(QString("id = '%1'").arg(selectId));
        fieldName.append("*");
        QStringList datalist = sql.getFormListbyCondition("planrecord",fieldName,condition).at(0);
        ui->DE_productday->setDate(QDate::fromString(datalist.at(5),"yyyy-MM-dd"));
        ui->LE_CN->setText(datalist.at(6));
        ui->LE_PN->setText(datalist.at(7));
        ui->LE_productionCode->setText(datalist.at(8));
        ui->LE_PlanProductQty->setText(datalist.at(9));
        ui->TE_readyMsg->setText(datalist.at(10));
        ui->LE_ProductType->setText(datalist.at(11));
        ui->LE_ExportPlace->setText(datalist.at(12));

    }

}
void AddDailyReady::on_Btn_dailyReadySubmit_clicked()
{
    if(ui->LE_PN->text().isEmpty()||ui->LE_productionCode->text().isEmpty()||ui->TE_readyMsg->toPlainText().isEmpty())
    {
        QUIHelper::showMessageBoxInfo("订单号或机型或备产信息不能空！",2);
        return;
    }



    plandata.productday=ui->DE_productday->date().toString("yyyy-MM-dd");
    plandata.CN = ui->LE_CN->text();
    plandata.PN = ui->LE_PN->text();
    plandata.machineCode = ui->LE_productionCode->text();
    plandata.PlanQty = ui->LE_PlanProductQty->text().toInt();
    plandata.readyMsg = ui->TE_readyMsg->toPlainText();
    //plandata.productQTY = 0;
    //plandata.badQTY = 0;
    plandata.departmentId = userInfor.departmentId;
    plandata.productLineId = userInfor.productLineId;
    plandata.machineType = ui->LE_ProductType->text();
    plandata.exportPlace = ui->LE_ExportPlace->text();
    plandata.userId = userInfor.id;
    if(selectId == ""){

        QStringList condition;
        condition.append("PN = "+ui->LE_PN->text().simplified()+" ");


        QList<QStringList> PNlist = sql.getFormListbyCondition("planrecord","PN",condition);

        if(PNlist.count()!=0)
        {
            QUIHelper::showMessageBoxInfo("订单号重复！",2);
            return;
        }

        QUuid Id=QUuid::createUuid();
        plandata.id=Id.toString().mid(1,36);

        QStringList field;
        field.append("id");
        field.append("productday");
        field.append("CN");
        field.append("PN");
        field.append("machineCode");
        field.append("planQty");
        field.append("readyMsg");
        field.append("machineType");
        field.append("exportPlace");
        field.append("departmentId");
        field.append("productLineId");
        field.append("userId");

        QVariantList value;
        value.append(plandata.id);
        value.append(plandata.productday);
        value.append(plandata.CN);
        value.append(plandata.PN);
        value.append(plandata.machineCode);
        value.append(plandata.PlanQty);
        value.append(plandata.readyMsg);
        value.append(plandata.machineType);
        value.append(plandata.exportPlace);
        value.append(plandata.departmentId);
        value.append(plandata.productLineId);
        value.append(plandata.userId);

        bool ret = sql.addFormList("planRecord",field,value);
        if(ret)
        {
            on_Btn_Reset_clicked();
        }
     }else{
         plandata.id = selectId;
         QStringList field;
         field.append("productday");
         field.append("CN");
         field.append("PN");
         field.append("machineCode");
         field.append("planQty");
         field.append("readyMsg");
         field.append("machineType");
         field.append("exportPlace");
         QVariantList value;
         value.append(plandata.productday);
         value.append(plandata.CN);
         value.append(plandata.PN);
         value.append(plandata.machineCode);
         value.append(plandata.PlanQty);
         value.append(plandata.readyMsg);
         value.append(plandata.machineType);
         value.append(plandata.exportPlace);

         bool ret = sql.updateForm(selectId,"planrecord",field,value);
         if(ret)
         {
             on_Btn_Reset_clicked();
         }
    }

}

void AddDailyReady::on_btnMenu_Close_clicked()
{
    close();
}

void AddDailyReady::on_Btn_Reset_clicked()
{
    ui->LE_CN->setText("");
    ui->LE_PN->setText("");
    ui->LE_PlanProductQty->setText("");
    ui->LE_productionCode->setText("");
    ui->TE_readyMsg->setText("");
    ui->LE_ProductType->setText("");
    ui->LE_ExportPlace->setText("");
}
