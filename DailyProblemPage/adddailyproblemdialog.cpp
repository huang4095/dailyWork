#include "adddailyproblemdialog.h"
#include "ui_adddailyproblemdialog.h"

AddDailyProblemDialog::AddDailyProblemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDailyProblemDialog)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);

    LB=new QLabel();
    LB->setText("审核批注");

    TE_checkRemark=new QTextEdit();
    TE_checkRemark->setText("同意");

    Btn_checkOk=new QPushButton();
    Btn_checkOk->setText("审核通过");
    Btn_checkReject=new QPushButton();
    Btn_checkReject->setText("审核驳回");


}
AddDailyProblemDialog::~AddDailyProblemDialog()
{
     delete ui;
}

AddDailyProblemDialog::showDialog()
{
    QString Department = sql.idToName(userInfor.departmentId,"department");
    ui->LE_Department->setText(Department);
    qDebug()<<selectId;
    QString productLine = sql.idToName(userInfor.productLineId,"productLine");
    ui->LE_ProductLine->setText(productLine);
    ui->DE_problemDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_problemDate->setDate(QDate::currentDate());
    if(selectId == "")
    {
        QStringList fieldName,condition;
        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        condition.append(QString("productLineId = '%1'").arg(userInfor.productLineId));
        condition.append(QString("and productDay like '%1'").arg(ui->DE_problemDate->text()));
        QList<QStringList> strList = sql.getFormListbyCondition("planRecord",fieldName,condition);

        for(int i=0;i<strList.count();i++)
        {

           machineCode.append(strList.at(i).at(0));
           CN.append(strList.at(i).at(1));
           PN.append(strList.at(i).at(2));
        }
        QCompleter *completer = new QCompleter(machineCode,this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        ui->LE_productionCode->setCompleter(completer);
        completer = new QCompleter(CN,this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        ui->LE_CN->setCompleter(completer);
        completer = new QCompleter(PN,this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        ui->LE_PN->setCompleter(completer);
    }else
    {
        QStringList fieldName;
        fieldName.append("departmentId");
        fieldName.append("productLineId");
        fieldName.append("recordDate");
        fieldName.append("problemDetail");
        fieldName.append("solutionDetail");
        fieldName.append("verification");
        fieldName.append("problemStatus");
        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        fieldName.append("checkStatus");
        QStringList condition;
        condition.append("id = '"+selectId + "'");
        QStringList value = sql.getFormListbyCondition("PQCProblem",fieldName,condition).at(0);
        QString department = sql.idToName(value.at(0),"department");
        ui->LE_Department->setText(department);
        QString prodctLineName = sql.idToName(value.at(1),"productLine");
        ui->LE_ProductLine->setText(prodctLineName);
        ui->DE_problemDate->setDate(QDate::fromString(value.at(2), "yyyy-MM-dd"));
        ui->TE_problemDetail->setPlainText(value.at(3));
        ui->TE_solutionDetail->setPlainText(value.at(4));
        ui->TE_verificationDetail->setPlainText(value.at(5));
        ui->ComB_problemStutas->setCurrentIndex(value.at(6).toInt());
        ui->LE_productionCode->setText(value.at(7));
        ui->LE_CN->setText(value.at(8));
        ui->LE_PN->setText(value.at(9));
        currentStatus = value.at(10).toInt();
        if(userInfor.role =="主任"|| userInfor.role =="厂长"){
        QHBoxLayout *hBoxLayout=new QHBoxLayout();
        hBoxLayout->addWidget(LB);
        hBoxLayout->addWidget(TE_checkRemark);
        hBoxLayout->setMargin(10);
        ui->verticalLayout_main->insertLayout(6,hBoxLayout);
        ui->horizontalLayout_OK->addWidget(Btn_checkOk);
        ui->horizontalLayout_OK->addWidget(Btn_checkReject);
        connect(Btn_checkOk, SIGNAL(clicked()), this, SLOT(on_Btn_checkOk()));
        connect(Btn_checkReject, SIGNAL(clicked()), this, SLOT(on_Btn_checkReject()));
        }
         ui->Btn_Submit->setText("修改");
    }

}

void AddDailyProblemDialog::on_Btn_checkOk()
{
    QUuid Id=QUuid::createUuid();
    addCheckRecord checkRecord;
    checkRecord.id=Id.toString().mid(1,36);
    checkRecord.checkerId=userInfor.id;
    checkRecord.recordId=selectId;
    checkRecord.result="通过";
    checkRecord.details=TE_checkRemark->toPlainText().simplified();
    QStringList fieldName;
    fieldName.append("id");
    fieldName.append("checkerId");
    fieldName.append("details");
    fieldName.append("recordId");
    fieldName.append("result");
    QVariantList value;
    value.append(checkRecord.id);
    value.append(checkRecord.checkerId);
    value.append(checkRecord.details);
    value.append(checkRecord.recordId);
    value.append(checkRecord.result);
    sql.addFormList("checkRecord",fieldName,value);
    fieldName.clear();
    fieldName.append("checkStatus");
    value.clear();
    if(userInfor.role=="主任"){

        if(currentStatus ==1|| currentStatus ==2)
        {
           QUIHelper::showMessageBoxInfo("已审核状态不允许再次审核",1);
           return;
        }
        else
        {
            value.append("1");
        }
    }
    if(userInfor.role=="厂长")
    {
        if(currentStatus ==2)
        {
            QUIHelper::showMessageBoxInfo("已审核状态不允许再次审核",1);
            return;
        }
        else
        {
            value.append("2");
        }
    }
    sql.updateForm(selectId,"PQCProblem",fieldName,value);
}
void AddDailyProblemDialog::on_Btn_checkReject()
{
    addCheckRecord checkRecord;
    QUuid Id=QUuid::createUuid();
    checkRecord.id=Id.toString().mid(1,36);

    checkRecord.checkerId=userInfor.id;
    checkRecord.recordId=selectId;
    checkRecord.result="驳回";
    checkRecord.details=TE_checkRemark->toPlainText().simplified();
    QStringList fieldName;
    fieldName.append("id");
    fieldName.append("checkerId");
    fieldName.append("details");
    fieldName.append("recordId");
    fieldName.append("result");
    QVariantList value;
    value.append(checkRecord.id);
    value.append(checkRecord.checkerId);
    value.append(checkRecord.details);
    value.append(checkRecord.recordId);
    value.append(checkRecord.result);
    sql.addFormList("checkRecord",fieldName,value);
    fieldName.clear();
    fieldName.append("checkStatus");
    value.clear();
    if(userInfor.role=="主任"){

        if(currentStatus ==2|| currentStatus ==3|| currentStatus ==4)
        {
           QUIHelper::showMessageBoxInfo("当前状态不允许驳回",1);
           return;
        }
        else
        {
            value.append("3");
        }
    }
    if(userInfor.role=="厂长")
    {
        if(currentStatus ==4 )
        {
            QUIHelper::showMessageBoxInfo("已驳回",1);
            return;
        }
        else
        {
            value.append("4");
        }
    }
    sql.updateForm(selectId,"PQCProblem",fieldName,value);

}


void AddDailyProblemDialog::on_Btn_Submit_clicked()
{
    addPQCProblem problemData;

    problemData.departmentId = userInfor.departmentId;
    problemData.productLineId = userInfor.productLineId;
    problemData.userId = userInfor.id;
    problemData.machineCode = ui->LE_productionCode->text();

    problemData.PN = ui->LE_PN->text();
    problemData.CN = ui->LE_CN->text();
    problemData.problemDetail = ui->TE_problemDetail->toPlainText();
    problemData.solutionDetail = ui->TE_solutionDetail ->toPlainText();
    problemData.verification = ui->TE_verificationDetail->toPlainText();
    problemData.problemStatus = ui->ComB_problemStutas->currentIndex();
    problemData.recordDate = ui->DE_problemDate->text();
    if(selectId == "")
    {
        QUuid Id=QUuid::createUuid();
        problemData.id=Id.toString().mid(1,36);
        QStringList fieldName;
        QVariantList value;
        fieldName.append("id");
        fieldName.append("departmentId");
        fieldName.append("productLineId");
        fieldName.append("userId");
        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        fieldName.append("problemDetail");
        fieldName.append("solutionDetail");
        fieldName.append("verification");
        fieldName.append("problemStatus");
        fieldName.append("recordDate");

        value.append(problemData.id);
        value.append(problemData.departmentId);
        value.append(problemData.productLineId);
        value.append(problemData.userId);
        value.append(problemData.machineCode);
        value.append(problemData.CN);
        value.append(problemData.PN);
        value.append(problemData.problemDetail);
        value.append(problemData.solutionDetail);
        value.append(problemData.verification);
        value.append(problemData.problemStatus);
        value.append(problemData.recordDate);
        sql.addFormList("PQCProblem",fieldName,value);
    }else
    {
        QStringList fieldName;
        QVariantList value;

        fieldName.append("recordDate");
        fieldName.append("problemDetail");
        fieldName.append("solutionDetail");        
        fieldName.append("verification");
        fieldName.append("problemStatus");

        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        fieldName.append("checkStatus");


        value.append(problemData.recordDate);
        value.append(problemData.problemDetail);
        value.append(problemData.solutionDetail);
        value.append(problemData.verification);
        value.append(problemData.problemStatus);

        value.append(problemData.machineCode);
        value.append(problemData.CN);
        value.append(problemData.PN);
        value.append(0);
        sql.updateForm(selectId,"PQCProblem",fieldName,value);

    }

}

void AddDailyProblemDialog::on_btnMenu_Close_clicked()
{
    close();
}
