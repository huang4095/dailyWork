#include "adddailyworkproduct.h"
#include "ui_adddailyworkproduct.h"
#include "appInit/quiwidget.h"
#include "adddailyready.h"
#include<QHBoxLayout>
AddDailyWorkProduct::AddDailyWorkProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDailyWorkProduct)
{
    ui->setupUi(this);

    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);


    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);
    ui->DE_Date->setDisplayFormat("yyyy-MM-dd");


    LB=new QLabel();
    LB->setText("审核批注");

    TE_checkRemark=new QTextEdit();
    TE_checkRemark->setText("同意");

    Btn_checkOk=new QPushButton();
    Btn_checkOk->setText("审核通过");
    Btn_checkReject=new QPushButton();
    Btn_checkReject->setText("审核驳回");

}

void AddDailyWorkProduct::init_checkTableWidget()
{
    checkTableWidget=new QTableWidget();


    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("id"));
    HStrList.push_back(QString("审批时间"));
    HStrList.push_back(QString("审批人"));
    HStrList.push_back(QString("职位"));
    HStrList.push_back(QString("审批信息"));
    HStrList.push_back(QString("审批结果"));

    QStringList fieldName;
    fieldName.append("isDelete");
    fieldName.append("recordTime");
    fieldName.append("id");
    fieldName.append("recordTime");
    fieldName.append("checkerId");
    fieldName.append("details");
    fieldName.append("result");


    //qDebug()<<selectId;

    QStringList condition;
    condition.append("recordId='"+selectId+"'");
    QList<QStringList> strlist = sql.getFormListbyCondition("checkRecord",fieldName,condition,"2");
    //qDebug()<<strlist;
    QList<QStringList> data;
    for(int i=0;i<strlist.count();i++)
    {
        QStringList dateList;

        for(int j=0;j<strlist.at(i).count();j++)
        {

            switch(j)
            {
                case 3:
                {
                  QString date=strlist.at(i).at(j);

                  dateList.append( date.replace(10,1," "));
                  break;
                }

                case 4:
                {
                    dateList.append(sql.idToName(strlist.at(i).at(j),"userInfo"));
                    QStringList condition;
                    condition.append("id = '"+ strlist.at(i).at(j) +"'");
                    QString role=sql.getFormListbyCondition("userInfo","role",condition).at(0).at(0);
                    dateList.append(role);
                    break;
                }

                default:
                {
                  dateList.append(strlist.at(i).at(j));
                  break;
                }
            };
        }
        data.append(dateList);
    }
    sql.tableWidgetShow(HStrList,data,checkTableWidget); //表格显示
    checkTableWidget->setColumnWidth(6,300);
    ui->tableWidget_productType->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等分列宽

}

AddDailyWorkProduct::~AddDailyWorkProduct()
{
    delete ui;
}
void AddDailyWorkProduct::on_Btn_checkOk()
{
    QUuid Id=QUuid::createUuid();
    AddCheckRecord.id=Id.toString().mid(1,36);
    AddCheckRecord.checkerId=userInfor.id;
    AddCheckRecord.recordId=selectId;
    AddCheckRecord.result="通过";
    AddCheckRecord.details=TE_checkRemark->toPlainText().simplified();
    QStringList fieldName;
    fieldName.append("id");
    fieldName.append("checkerId");
    fieldName.append("details");
    fieldName.append("recordId");
    fieldName.append("result");
    QVariantList value;
    value.append(AddCheckRecord.id);
    value.append(AddCheckRecord.checkerId);
    value.append(AddCheckRecord.details);
    value.append(AddCheckRecord.recordId);
    value.append(AddCheckRecord.result);
    sql.addFormList("checkRecord",fieldName,value);
    fieldName.clear();
    fieldName.append("status");
    value.clear();
    if(userInfor.role=="主任")
        value.append("1");
    if(userInfor.role=="厂长")
        value.append("2");
    sql.updateForm(selectId,"dailyWork",fieldName,value);
}
void AddDailyWorkProduct::on_Btn_checkReject()
{
    QUuid Id=QUuid::createUuid();
    AddCheckRecord.id=Id.toString().mid(1,36);
    AddCheckRecord.checkerId=userInfor.id;
    AddCheckRecord.recordId=selectId;
    AddCheckRecord.result="驳回";
    AddCheckRecord.details=TE_checkRemark->toPlainText().simplified();
    QStringList fieldName;
    fieldName.append("id");
    fieldName.append("checkerId");
    fieldName.append("details");
    fieldName.append("recordId");
    fieldName.append("result");
    QVariantList value;
    value.append(AddCheckRecord.id);
    value.append(AddCheckRecord.checkerId);
    value.append(AddCheckRecord.details);
    value.append(AddCheckRecord.recordId);
    value.append(AddCheckRecord.result);
    sql.addFormList("checkRecord",fieldName,value);
    fieldName.clear();
    fieldName.append("status");
    value.clear();
    if(userInfor.role=="主任")
        value.append("3");
    if(userInfor.role=="厂长")
        value.append("4");
    sql.updateForm(selectId,"dailyWork",fieldName,value);

}
void AddDailyWorkProduct::showDialog()
{


    if(selectId=="")
    {
        QString department=sql.idToName(userInfor.departmentId,"department");

        QString productLine=sql.idToName(userInfor.productLineId,"productLine");
        //qDebug()<<department<<productLine;
        ui->LE_Department->setText(department);
        ui->LE_ProductLine->setText(productLine);
        ui->DE_Date->setDate(QDate::currentDate());
        QStringList HStrList;
        HStrList.push_back(QString("isDelete"));
        HStrList.push_back(QString("record"));
        HStrList.push_back(QString("id"));
        HStrList.push_back(QString("产品机型"));
        HStrList.push_back(QString("合同号"));
        HStrList.push_back(QString("订单号"));
        HStrList.push_back(QString("出口地"));
        HStrList.push_back(QString("今日计划数"));
        HStrList.push_back(QString("今日完成数"));
        HStrList.push_back(QString("今日不良数"));

        //int HlableCnt = HStrList.count();

        //ui->tableWidget_productType->setRowCount(1);
       // ui->tableWidget_productType->setColumnCount(HlableCnt);

        QStringList fieldName;
        fieldName.append("isDelete");
        fieldName.append("recordTime");
        fieldName.append("id");
        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        fieldName.append("exportPlace");
        fieldName.append("planQTY");
        //fieldName.append("productQTY");
        //fieldName.append("badQTY");


        QString day= QDate::currentDate().toString("yyyy-MM-dd");        

        QStringList condition;
        condition.append("userId='"+ userInfor.id +"'");
        condition.append(" and productday ='"+day +"'");

        QList<QStringList> strlist=sql.getFormListbyCondition("planrecord",fieldName,condition);
        QList<QStringList> data;
        for(int i=0;i<strlist.count();i++){
            QStringList datalist;
            datalist.clear();
            for(int j=0;j<strlist.at(i).count();j++){
                datalist.append(strlist.at(i).at(j));
            }
            datalist.append("0");
            datalist.append("0");
            data.append(datalist);
        }

        sql.tableWidgetShow(HStrList,data,ui->tableWidget_productType); //表格显示
        ui->tableWidget_productType->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等分列宽
         int planNum = 0;
        for(int i=0;i<data.count();i++){
            QString sum;
            sum = data.at(i).at(5);
            planNum +=  sum.toInt();
           // qDebug()<<sum<<planNum;
       }
       ui->LE_PlanProductQty->setText( QString::number(planNum,10));


    }else
    {

        if(userInfor.role!="组长")
        {

            ui->Btn_DailyWorkSubmit->setVisible(false);
            ui->Btn_Reset->setVisible(false);
            //ui->horizontalLayout_sumit->removeWidget(ui->Btn_DailyWorkSubmit);
            //ui->horizontalLayout_sumit->removeWidget(ui->Btn_Reset);
            ui->TE_UncompleteReason->setEnabled(false);
            ui->LB_uncompleteReason->setEnabled(false);
            ui->DE_Date->setEnabled(false);
            ui->LE_badQty->setEnabled(false);
            ui->LE_Department->setEnabled(false);
            ui->LE_inputWorkTime->setEnabled(false);
            ui->LE_NoWorktime->setEnabled(false);
            ui->LE_outputWorkTime->setEnabled(false);
            ui->LE_PlanProductQty->setEnabled(false);
            ui->LE_ProductLine->setEnabled(false);
            ui->LE_RealProductQty->setEnabled(false);
            ui->LE_Worktime->setEnabled(false);
            ui->Btn_addProcutType->setEnabled(false);
            ui->Btn_deleteProcutType->setEnabled(false);
            ui->tableWidget_productType->setEnabled(false);
    //        ui->verticalLayout_mainWidget->removeItem(ui->horizontalLayout_reason);

            if(userInfor.role=="主任" && checkStatus!="新增")
            {
                LB->setEnabled(false);
                TE_checkRemark->setEnabled(false);
                Btn_checkOk->setEnabled(false);
                Btn_checkReject->setEnabled(false);
            }
            if(userInfor.role=="厂长" && checkStatus!="主任已审核")
            {
                LB->setEnabled(false);
                TE_checkRemark->setEnabled(false);
                Btn_checkOk->setEnabled(false);
                Btn_checkReject->setEnabled(false);
            }

            init_checkTableWidget();


            QHBoxLayout *hBoxLayout=new QHBoxLayout();

            hBoxLayout->addWidget(LB);
            hBoxLayout->addWidget(TE_checkRemark);

            QHBoxLayout *hBoxLayout_tableWidget=new QHBoxLayout();

            hBoxLayout_tableWidget->addWidget(checkTableWidget);
            ui->verticalLayout_mainWidget->insertLayout(4,hBoxLayout);
            ui->verticalLayout_mainWidget->insertLayout(6,hBoxLayout_tableWidget);

            connect(Btn_checkOk, SIGNAL(clicked()), this, SLOT(on_Btn_checkOk()));
            connect(Btn_checkReject, SIGNAL(clicked()), this, SLOT(on_Btn_checkReject()));

            ui->horizontalLayout_sumit->addWidget(Btn_checkOk);
            ui->horizontalLayout_sumit->addWidget(Btn_checkReject);

        }else{

            if(checkStatus=="主任已审核" || checkStatus=="厂长已审核")
            {
                ui->Btn_DailyWorkSubmit->setVisible(false);
                ui->Btn_Reset->setVisible(false);

                ui->TE_UncompleteReason->setEnabled(false);
                ui->LB_uncompleteReason->setEnabled(false);
                ui->DE_Date->setEnabled(false);
                ui->LE_badQty->setEnabled(false);
                ui->LE_Department->setEnabled(false);
                ui->LE_inputWorkTime->setEnabled(false);
                ui->LE_NoWorktime->setEnabled(false);
                ui->LE_outputWorkTime->setEnabled(false);
                ui->LE_PlanProductQty->setEnabled(false);
                ui->LE_ProductLine->setEnabled(false);
                ui->LE_RealProductQty->setEnabled(false);
                ui->LE_Worktime->setEnabled(false);
                ui->Btn_addProcutType->setEnabled(false);
                ui->Btn_deleteProcutType->setEnabled(false);
                ui->tableWidget_productType->setEnabled(false);

                init_checkTableWidget();
                QHBoxLayout *hBoxLayout_tableWidget=new QHBoxLayout();

                hBoxLayout_tableWidget->addWidget(checkTableWidget);

                ui->verticalLayout_mainWidget->insertLayout(6,hBoxLayout_tableWidget);

            }
        }
        QStringList fieldname,condition;
        fieldname.append("*");
        condition.append("id='"+selectId +"'");

        QStringList strList=sql.getFormListbyCondition("dailyWork",fieldname,condition).at(0);

        //qDebug()<<strList;
        QString department=sql.idToName(strList.at(3),"department");
        QString productLine=sql.idToName(strList.at(4),"productLine");

        ui->LE_Department->setText(department);
        ui->LE_ProductLine->setText(productLine);
        QDate currentday;
        currentday = QDate::fromString(strList.at(6),"yyyy-MM-dd");
        ui->DE_Date->setDate(currentday);
        ui->LE_Worktime->setText(strList.at(7));
        ui->LE_NoWorktime->setText(strList.at(8));
        ui->LE_PlanProductQty->setText(strList.at(9));
        ui->LE_RealProductQty->setText(strList.at(10));
        ui->LE_inputWorkTime->setText(strList.at(11));
        ui->LE_outputWorkTime->setText(strList.at(12));
        ui->TE_UncompleteReason->setText(strList.at(14));


        QStringList HStrList;
        HStrList.push_back(QString("isDelete"));
        HStrList.push_back(QString("recordTime"));
        HStrList.push_back(QString("id"));
        HStrList.push_back(QString("产品机型"));
        HStrList.push_back(QString("合同号"));
        HStrList.push_back(QString("订单号"));
        HStrList.push_back(QString("出口地"));
        HStrList.push_back(QString("今日计划数"));
        HStrList.push_back(QString("今日完成数"));
        HStrList.push_back(QString("今日不良数"));

        QStringList fieldName;
        fieldName.append("isDelete");
        fieldName.append("recordTime");
        fieldName.append("id");
        fieldName.append("machineCode");
        fieldName.append("CN");
        fieldName.append("PN");
        fieldName.append("exportPlace");
        fieldName.append("planQTY");
        fieldName.append("QTY");
        fieldName.append("badQTY");

        //qDebug()<<selectId;


         condition.clear();
        condition.append("recordId='"+selectId+"'");
        QList<QStringList> strlist = sql.getFormListbyCondition("productRecord",fieldName,condition);
        //qDebug()<<strlist;
        sql.tableWidgetShow(HStrList,strlist,ui->tableWidget_productType); //表格显示
        ui->tableWidget_productType->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等分列宽
    }

         int Qty= 0;
         for(int i=0;i<ui->tableWidget_productType->rowCount();i++){
                if(ui->tableWidget_productType->item(i,7)!=NULL)
                     Qty += ui->tableWidget_productType->item(i,7)->text().toInt();
              }
         ui->LE_PlanProductQty->setText(QString::number(Qty,10));

}
void AddDailyWorkProduct::on_btnMenu_Close_clicked()
{
    close();
}


void AddDailyWorkProduct::on_Btn_DailyWorkSubmit_clicked()
{
    int rowCount=ui->tableWidget_productType->rowCount();
    int colCount=ui->tableWidget_productType->columnCount();


    DailyWork.recordDate=ui->DE_Date->date().toString("yyyy-MM-dd");
    DailyWork.workTime=ui->LE_Worktime->text().toFloat();
    DailyWork.noWorkTime=ui->LE_NoWorktime->text().toFloat();
    DailyWork.planCompleteQTY=ui->LE_PlanProductQty->text().toInt();
    DailyWork.realCompleteQTY=ui->LE_RealProductQty->text().toInt();
    DailyWork.inputWorkTime=ui->LE_inputWorkTime->text().toFloat();
    DailyWork.outWorkTime=ui->LE_outputWorkTime->text().toFloat();
    DailyWork.uncompleteReason=ui->TE_UncompleteReason->toPlainText();
    DailyWork.badQty = ui->LE_badQty->text().toInt();

    if(selectId=="")
    {

        QUuid Id=QUuid::createUuid();
        DailyWork.id=Id.toString().mid(1,36);
        //qDebug()<<DepartmentInfor.id;

        DailyWork.departmentId=userInfor.departmentId;
        DailyWork.productLineId=userInfor.productLineId;
        DailyWork.userId=userInfor.id;


        if(DailyWork.inputWorkTime==0)
        {
            DailyWork.workRate=0;
        }else{

            DailyWork.workRate=DailyWork.outWorkTime/DailyWork.inputWorkTime;
            //qDebug()<<DailyWork.outWorkTime<<DailyWork.inputWorkTime<<DailyWork.workRate;
        }

        DailyWork.uncompleteReason=ui->TE_UncompleteReason->toPlainText();
        ProductList.clear();
        //qDebug()<<rowCount<<colCount;
        if(rowCount!=0)
        {

            for(int i=0;i<rowCount;i++)
            {
                bool isNull=false;
                for(int j=3;j<colCount;j++)
                {
                    if(j!=5)
                    {
                        if(ui->tableWidget_productType->item(i,j)==0x0)
                        {
                            isNull=true;
                            break;
                        }
                    }
                }
                if(isNull)
                {
                    //qDebug()<<"请输入所有值！";
                    QUIHelper::showMessageBoxInfo("请输入所有值！",0,true) ;
                    return;
                }else{

                    QStringList fieldName;


                    fieldName.append("id");
                    fieldName.append("departmentId");
                    fieldName.append("productLineId");
                    fieldName.append("machineCode");
                    fieldName.append("CN");
                    fieldName.append("PN");
                    fieldName.append("exportPlace");
                    fieldName.append("planQTY");
                    fieldName.append("QTY");
                    fieldName.append("badQTY");
                    fieldName.append("recordId");
                    fieldName.append("productDate");

                    QVariantList value;

                    addProduct  productdata;
                    productdata.machineCode =ui->tableWidget_productType->item(i,3)->text();
                    productdata.CN = ui->tableWidget_productType->item(i,4)->text();
                    productdata.PN = ui->tableWidget_productType->item(i,5)->text();
                    productdata.exportPlace = ui->tableWidget_productType->item(i,6)->text();
                    productdata.planQTY = ui->tableWidget_productType->item(i,7)->text().toInt();
                    productdata.QTY = ui->tableWidget_productType->item(i,8)->text().toInt();
                    productdata.badQTY = ui->tableWidget_productType->item(i,9)->text().toInt();
                    productdata.productLineId = userInfor.productLineId;
                    productdata.departmentId = userInfor.departmentId;
                    productdata.productDate = ui->DE_Date->text();
                     QUuid Id=QUuid::createUuid();
                    productdata.id=Id.toString().mid(1,36);
                    productdata.recordId = DailyWork.id;

                    value.append(productdata.id);
                     value.append(productdata.departmentId);
                    value.append(productdata.productLineId);
                    value.append(productdata.machineCode);
                    value.append(productdata.CN);
                    value.append(productdata.PN);
                    value.append(productdata.exportPlace);
                    value.append(productdata.planQTY);
                    value.append(productdata.QTY);
                    value.append(productdata.badQTY);
                    value.append(productdata.recordId);
                    value.append(productdata.productDate);

                    sql.addFormList("productRecord",fieldName,value);

                }
            }
        }


        QStringList field;
        field.append("Id");
        field.append("departmentId");
        field.append("productLineId");
        field.append("userId");
        field.append("recordDate");
        field.append("workTime");
        field.append("noWorkTime");
        field.append("planCompleteQTY");
        field.append("realCompleteQTY");
        field.append("inputWorkTime");
        field.append("outWorkTime");
        field.append("workRate");
        field.append("uncompleteReason");
        field.append("badQty");
        QVariantList value;
        value.append(DailyWork.id);
        value.append(DailyWork.departmentId);
        value.append(DailyWork.productLineId);
        value.append(DailyWork.userId);
        value.append(DailyWork.recordDate);
        value.append(DailyWork.workTime);
        value.append(DailyWork.noWorkTime);
        value.append(DailyWork.planCompleteQTY);
        value.append(DailyWork.realCompleteQTY);
        value.append(DailyWork.inputWorkTime);
        value.append(DailyWork.outWorkTime);
        value.append(DailyWork.workRate);
        value.append(DailyWork.uncompleteReason);
        value.append(DailyWork.badQty);

        sql.addFormList("dailyWork",field,value);
        //sql.addDailyWorkInfo(DailyWork);
        close();
    }
    else{

        if(checkStatus=="新增" || checkStatus=="主任驳回"|| checkStatus=="厂长驳回")
        {

        if(DailyWork.inputWorkTime==0)
        {
            DailyWork.workRate=0;
        }else{

            DailyWork.workRate=DailyWork.outWorkTime/DailyWork.inputWorkTime;
            //qDebug()<<DailyWork.outWorkTime<<DailyWork.inputWorkTime<<DailyWork.workRate;
        }
        QStringList field;
        field.append("recordDate");
        field.append("uncompleteReason");
        field.append("workTime");
        field.append("noWorkTime");
        field.append("planCompleteQTY");
        field.append("realCompleteQTY");
        field.append("inputWorkTime");
        field.append("outWorkTime");
        field.append("workRate");
        field.append("badQty");


        QVariantList value;
        value.append(DailyWork.recordDate);
        value.append(DailyWork.uncompleteReason);
        value.append(DailyWork.workTime);
        value.append(DailyWork.noWorkTime);
        value.append(DailyWork.planCompleteQTY);
        value.append(DailyWork.realCompleteQTY);
        value.append(DailyWork.inputWorkTime);
        value.append(DailyWork.outWorkTime);
        value.append(DailyWork.workRate);
        value.append(DailyWork.badQty);

        sql.updateForm(selectId,"dailyWork",field,value);
        //qDebug()<<" sql.updateForm(selectId,dailyWork,field,value);";

        for(int i=0;i<rowCount;i++)
        {
            bool isNull=false;
            for(int j=3;j<colCount;j++)
            {
                if(j!=6)
                {
                    if(ui->tableWidget_productType->item(i,j)==0x0)
                    {
                        isNull=true;
                        break;
                    }
                }
            }
            if(isNull)
            {
                //qDebug()<<"请输入所有值！";
                QUIHelper::showMessageBoxInfo("请输入所有值！",0,true) ;
                return;
            }else{

                QStringList fieldName;
                fieldName.append("departmentId");
                fieldName.append("productLineId");
                fieldName.append("machineCode");
                fieldName.append("CN");
                fieldName.append("PN");
                fieldName.append("exportPlace");
                fieldName.append("planQTY");
                fieldName.append("QTY");
                fieldName.append("badQTY");
                fieldName.append("productDate");

                QVariantList value;

                addProduct  productdata;
                productdata.machineCode =ui->tableWidget_productType->item(i,3)->text();
                productdata.CN = ui->tableWidget_productType->item(i,4)->text();
                productdata.PN = ui->tableWidget_productType->item(i,5)->text();
                productdata.exportPlace = ui->tableWidget_productType->item(i,6)->text();
                productdata.planQTY = ui->tableWidget_productType->item(i,7)->text().toInt();
                productdata.QTY = ui->tableWidget_productType->item(i,8)->text().toInt();
                productdata.badQTY = ui->tableWidget_productType->item(i,9)->text().toInt();
                productdata.productLineId = userInfor.productLineId;
                productdata.departmentId = userInfor.departmentId;
                productdata.productDate = ui->DE_Date->text();

               value.append(productdata.departmentId);
               value.append(productdata.productLineId);
               value.append(productdata.machineCode);
               value.append(productdata.CN);
               value.append(productdata.PN);
               value.append(productdata.exportPlace);
               value.append(productdata.planQTY);
               value.append(productdata.QTY);
               value.append(productdata.badQTY);
               value.append(productdata.productDate);

                    QString CurrentId = ui->tableWidget_productType->item(i,2)->data(0).toString();
                    sql.updateForm(CurrentId,"productRecord",fieldName,value);
                }
            }
        }else
        {
            QUIHelper::showMessageBoxInfo("已审批，不允许修改",0,true) ;
        }
    }
}

void AddDailyWorkProduct::on_Btn_addProcutType_clicked()
{
    int rowCount=ui->tableWidget_productType->rowCount()+1;
    ui->tableWidget_productType->setRowCount(rowCount);

    QStringList list;
    list.append("");
    list.append("美国");
    list.append("俄罗斯");
    list.append("日本");
    QComboBox *comBox=new QComboBox(ui->tableWidget_productType);
    comBox->setEditable(true);
    QCompleter *NewFind = new QCompleter(list);
    comBox->setCompleter(NewFind);
    comBox->addItems(list);

    ui->tableWidget_productType->setCellWidget(rowCount-1,6,comBox);

}

void AddDailyWorkProduct::on_Btn_deleteProcutType_clicked()
{
    ui->tableWidget_productType->removeRow(ui->tableWidget_productType->currentRow());
}

void AddDailyWorkProduct::on_Btn_Reset_clicked()
{
    ui->TE_UncompleteReason->clear();
}

void AddDailyWorkProduct::on_tableWidget_productType_itemChanged(QTableWidgetItem *item)
{
    int Qty= 0;

    switch (item->column()) {
    case 7:
        for(int i=0;i<ui->tableWidget_productType->rowCount();i++){
            if(ui->tableWidget_productType->item(i,7)!=NULL)
                 Qty += ui->tableWidget_productType->item(i,7)->text().toInt();
        }
          ui->LE_PlanProductQty->setText(QString::number(Qty,10));
        break;
    case 8:
        for(int i=0;i<ui->tableWidget_productType->rowCount();i++){
          if(ui->tableWidget_productType->item(i,8)!=NULL)
             Qty += ui->tableWidget_productType->item(i,8)->text().toInt();
        }
          ui->LE_RealProductQty->setText(QString::number(Qty,10));
        break;
     case 9:
        for(int i = 0; i < ui->tableWidget_productType->rowCount(); i++){
            if(ui->tableWidget_productType->item(i,9)!= NULL)
                Qty += ui->tableWidget_productType->item(i,9)->text().toInt();
        }
        ui->LE_badQty->setText(QString::number(Qty,10));
    default:
        break;
    }






}
