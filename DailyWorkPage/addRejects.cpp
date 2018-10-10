#include "addRejects.h"
#include "ui_addRejects.h"

QcmAdd::QcmAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QcmAdd)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);
}

QcmAdd::~QcmAdd()
{
    delete ui;
}
void QcmAdd::showDialog()
{
    QString Department = sql.idToName(userInfor.departmentId,"department");
    ui->LE_Department->setText(Department);
    QString productLine = sql.idToName(userInfor.productLineId,"productLine");
    ui->LE_ProductLine->setText(productLine);
    ui->DE_Date->setDisplayFormat("yyyy-MM-dd");
    ui->DE_Date->setDate(QDate::currentDate());
    if(rejectsId == ""){
        QStringList fieldName;
        fieldName.append("id");
        fieldName.append("productDate");
        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        fieldName.append("badQTY");
        QStringList condition;

        condition.append("id = '"+productId +"'");
        QStringList strList=sql.getFormListbyCondition("productRecord",fieldName,condition).at(0);


        QDate currentday = QDate::fromString(strList.at(1),"yyyy-MM-dd");
        ui->DE_Date->setDate(currentday);
        ui->LE_machineCode->setText(strList.at(2));
        ui->LE_CN->setText(strList.at(3));
        ui->LE_PN->setText(strList.at(4));
        ui->LE_badQTY->setText(strList.at(5));
    }
    if(productId==""){
        QStringList fieldname,condition;

        fieldname.append("QCType");
        fieldname.append("productDate");
        fieldname.append("machineCode");
        fieldname.append("CN");
        fieldname.append("PN");
        fieldname.append("badQTY");
        fieldname.append("rejectsType");
        fieldname.append("rejectsDetail");
        fieldname.append("reason");
        fieldname.append("solution");
        fieldname.append("responsible");

        condition.append(QString("id = '%1'").arg(rejectsId));
        QStringList strList=sql.getFormListbyCondition("rejectsRecord",fieldname,condition).at(0);

        ui->CB_QCM_TYPE->setCurrentIndex(strList.at(0).toInt());
        QDate currentday = QDate::fromString(strList.at(1),"yyyy-MM-dd");
        ui->DE_Date->setDate(currentday);
        ui->LE_machineCode->setText(strList.at(2));
        ui->LE_CN->setText(strList.at(3));
        ui->LE_PN->setText(strList.at(4));
        ui->LE_badQTY->setText(strList.at(5));
        ui->CB_QCM_rejectsType->setCurrentIndex(strList.at(6).toInt());
        ui->TE_rejectSPec->setText(strList.at(7));
        ui->TE_reason->setText(strList.at(8));
        ui->TE_measures->setText(strList.at(9));
        ui->LE_Responsible->setText(strList.at(10));

    }
}

void QcmAdd::on_Btn_QcmSubmit_clicked()
{
    if(ui->LE_badQTY->text() != NULL)
    {
        int qty= ui->LE_badQTY->text().toInt();
        if(qty <= 0)
        {
            QUIHelper::showMessageBoxInfo("请确认不良数！",2);
            return;
        }else
        {
            rejectsData.badQTY = ui->LE_badQTY->text().toInt();
        }
    }else
    {
        QUIHelper::showMessageBoxInfo("不良数为空！",2);
        return;
    }
    if(ui->TE_rejectSPec->toPlainText()!= NULL)
    {
        rejectsData.rejectsDetail=ui->TE_rejectSPec->toPlainText();
    }

    else{
        QUIHelper::showMessageBoxInfo("不良现象为空",2);
        return;
    }
    if(ui->TE_reason->toPlainText()!= NULL)
    {
         rejectsData.reason= ui->TE_reason->toPlainText();
    }
    else{
        QUIHelper::showMessageBoxInfo("原因分析为空",2);
        return;
    }
    if(ui->TE_measures->toPlainText()!= NULL)
    {
        rejectsData.solution= ui->TE_measures->toPlainText();
    }
    else
    {
        QUIHelper::showMessageBoxInfo("对策为空",2);
        return;
    }

    rejectsData.CN = ui->LE_CN->text();
    rejectsData.PN =ui->LE_PN->text();
    rejectsData.machineCode = ui->LE_machineCode->text();
    rejectsData.departmentId = userInfor.departmentId;
    rejectsData.productLineId = userInfor.productLineId;
    rejectsData.userId = userInfor.id;
    rejectsData.productDate =ui->DE_Date->text();
    rejectsData.QCType  = ui->CB_QCM_TYPE->currentIndex();
    rejectsData.rejectsType = ui->CB_QCM_rejectsType->currentIndex();
    rejectsData.responsible = ui->LE_Responsible->text();



    QStringList fieldname;
    QVariantList  value;
    QString id;
    fieldname.empty();
    value.empty();

    fieldname.append("departmentId");
    fieldname.append("productLineId");
    fieldname.append("userId");
    fieldname.append("QCType");
    fieldname.append("productDate");
    fieldname.append("machineCode");
    fieldname.append("CN");
    fieldname.append("PN");
    fieldname.append("badQTY");
    fieldname.append("rejectsType");

    fieldname.append("rejectsDetail");
    fieldname.append("reason");
    fieldname.append("solution");
    fieldname.append("responsible");


    value.append(rejectsData.departmentId);
    value.append(rejectsData.productLineId);
    value.append(rejectsData.userId);
    value.append(rejectsData.QCType);
    value.append(rejectsData.productDate);
    value.append(rejectsData.machineCode);
    value.append(rejectsData.CN);
    value.append(rejectsData.PN);
    value.append(rejectsData.badQTY);
    value.append(rejectsData.rejectsType);

    value.append(rejectsData.rejectsDetail);
    value.append(rejectsData.reason);
    value.append(rejectsData.solution);
    value.append(rejectsData.responsible);


    if(rejectsId==""){
        QUuid Id=QUuid::createUuid();
        id=Id.toString().mid(1,36);
        fieldname.append("id");
        fieldname.append("recordId");

        value.append(id);
        value.append(productId);



        bool ret =  sql.addFormList("rejectsRecord",fieldname,value);
        if(ret){
            on_Btn_Reset_clicked();
        }
     }else
     {
         id = rejectsId;
        bool ret = sql.updateForm(id,"rejectsRecord",fieldname,value);
        if(ret){
             on_Btn_Reset_clicked();
        }
    }

}

void QcmAdd::on_btnMenu_Close_clicked()
{
    close();
}

void QcmAdd::on_Btn_Reset_clicked()
{
    ui->TE_measures->clear();
    ui->TE_reason->clear();
    ui->TE_rejectSPec->clear();
}
