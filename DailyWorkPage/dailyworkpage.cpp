#include "dailyworkpage.h"
#include "ui_dailyworkpage.h"
#include "appInit/quiwidget.h"

DailyWorkPage::DailyWorkPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyWorkPage)
{
    ui->setupUi(this);
    this->initPage();

    ui->tableWidget_QCRecord->installEventFilter(this);

    ComB_CheckStatus=new QComboBox();

}

DailyWorkPage::~DailyWorkPage()
{
    delete ui;
}
void DailyWorkPage::showPage()
{

    if(userInfor.role=="组长")
    {
        ui->ComB_dailyWork_department->setEnabled(false);
        ui->ComB_dailyWork_productLine->setEnabled(false);
        ui->ComB_dailyReady_department->setEnabled(false);
        ui->ComB_dailyReady_productLine->setEnabled(false);
        ui->ComB_qcm_department->setEnabled(false);
        ui->ComB_qcm_productLine->setEnabled(false);
        ui->ComB_attendance_department->setEnabled(false);
        ui->ComB_attendance_productLine->setEnabled(false);
    }if(userInfor.role=="主任"||userInfor.role=="厂长")
    {
        ui->ComB_dailyWork_department->setEnabled(false);
        ui->ComB_dailyReady_department->setEnabled(false);
        ui->ComB_attendance_department->setEnabled(false);
        ui->ComB_qcm_department->setEnabled(false);

        ui->Btn_AddDailyProduct->setVisible(false);
        ui->Btn_deleteDailyProduct->setVisible(false);


        ComB_CheckStatus->addItem("未审核");
        ComB_CheckStatus->addItem("已审核");

        ui->horizontalLayout_dailyWork->insertWidget(7,ComB_CheckStatus);

    }else
    {

    }
    getDepartmentinfo();
    getProductLine(userInfor.departmentId);
    getMaintainer();
}
void DailyWorkPage::initPage()
{
    ui->widget_Menu->setProperty("flag", "left");
    this->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));

    pixChar << 0xf031 << 0xf036 << 0xf249<< 0xf031 << 0xf036  ;
    btns << ui->tBtn_Menu1 << ui->tBtn_Menu2 << ui->tBtn_Menu3<<ui->tBtn_Menu4<<ui->tBtn_Menu5;

    int count = btns.count();
    for (int i = 0; i < count; i++) {
        btns.at(i)->setCheckable(true);
        btns.at(i)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(btns.at(i), SIGNAL(clicked(bool)), this, SLOT(MenuClick()));
    }

    QString borderColor = QUIConfig::HighColor;
    QString normalBgColor = QUIConfig::NormalColorStart;
    QString darkBgColor = QUIConfig::PanelColor;
    QString normalTextColor = QUIConfig::TextColor;
    QString darkTextColor = QUIConfig::TextColor;
    IconHelper::Instance()->setStyle(ui->widget_Menu, btns, pixChar, 20, 25, 20, "left", 4,
                                     borderColor, normalBgColor, darkBgColor, normalTextColor, darkTextColor);




    ui->DE_startDate->setDate(QDate::currentDate());
    ui->DE_endDate->setDate(QDate::currentDate().addDays(1));
    ui->DE_startDate1->setDate(QDate::currentDate());
    ui->DE_endDate1->setDate(QDate::currentDate().addDays(1));
    ui->DE_startDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_endDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_startDate1->setDisplayFormat("yyyy-MM-dd");
    ui->DE_endDate1->setDisplayFormat("yyyy-MM-dd");

    ui->DE_startDate_qcm->setDisplayFormat("yyyy-MM-dd");
    ui->DE_endDate_qcm->setDisplayFormat("yyyy-MM-dd");
    ui->DE_startDate_qcm->setDate(QDate::currentDate());
    ui->DE_endDate_qcm->setDate(QDate::currentDate().addDays(1));

    ui->DE_startDate_attendance->setDisplayFormat("yyyy-MM-dd");
    ui->DE_endDate_attendance->setDisplayFormat("yyyy-MM-dd");
    ui->DE_startDate_attendance->setDate(QDate::currentDate());
    ui->DE_endDate_attendance->setDate(QDate::currentDate().addDays(1));

    ui->DE_maintainStartDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_maintainEndDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_maintainStartDate->setDate(QDate::currentDate());
    ui->DE_maintainEndDate->setDate(QDate::currentDate().addDays(1));
    ui->tBtn_Menu1->click();
}

void DailyWorkPage::MenuClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = btns.count();
    for (int i = 0; i < count; i++) {
        if (btns.at(i) == b) {
            btns.at(i)->setChecked(true);
            ui->stackedWidget->setCurrentIndex(i);
            btns.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btns.at(i), false)));
        } else {
            btns.at(i)->setChecked(false);
            btns.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btns.at(i), true)));
        }
    }
}


void DailyWorkPage::getDepartmentinfo()
{

    int index;

    for(int i=0;i<departmentListId.count();i++)
    {

        if(departmentListId.at(i) == userInfor.departmentId){
            index = i;
        }
    }

    QCompleter *NewFind = new QCompleter(departmentList);
    ui->ComB_dailyWork_department->setCompleter(NewFind);    
    ui->ComB_dailyWork_department->clear();
    ui->ComB_dailyWork_department->addItems(departmentList);

    ui->ComB_dailyReady_department->setCompleter(NewFind);
    ui->ComB_dailyReady_department->clear();
    ui->ComB_dailyReady_department->addItems(departmentList);

    ui->ComB_qcm_department->setCompleter(NewFind);
    ui->ComB_qcm_department->clear();
    ui->ComB_qcm_department->addItems(departmentList);

    ui->ComB_attendance_department->setCompleter(NewFind);
    ui->ComB_attendance_department->clear();
    ui->ComB_attendance_department->addItems(departmentList);

    if(userInfor.role != "总监" ){
        ui->ComB_dailyWork_department->setCurrentIndex(index);
        ui->ComB_dailyReady_department->setCurrentIndex(index);
        ui->ComB_attendance_department->setCurrentIndex(index);
        ui->ComB_qcm_department->setCurrentIndex(index);
    }
    //qDebug()<<userInfor.role;
}
void DailyWorkPage::getProductLine(QString currentDepartmentId)
{
    sqlDataSource addSql;
    QList<QStringList> strlist;

    if(currentDepartmentId=="00000000-0000-0000-0000-000000000000")
    {
        strlist=addSql.getFormListbyCondition(QString("productLine"),QString("*"));
    }else
    {


        QStringList condition;
        condition.append(QString("departmentId = '%1'").arg(currentDepartmentId));
        //condition.append("departmentId = '"+currentDepartmentId+"'");
        strlist=addSql.getFormListbyCondition("productLine","*",condition);
    }

    productLineList.clear();
    productLineListId.clear();
    productLineList.append("");
    productLineListId.append("00000000-0000-0000-0000-000000000000");
    int index;
    for(int i=0;i<strlist.count();i++)
    {

        productLineListId.append(strlist.at(i).at(2));
        productLineList.append(strlist.at(i).at(3)+"-"+strlist.at(i).at(4));
        if(strlist.at(i).at(2) == userInfor.productLineId){
            index = i;
        }
    }

    QCompleter *NewFind = new QCompleter(productLineList);
    ui->ComB_dailyWork_productLine->setCompleter(NewFind);  
    ui->ComB_dailyWork_productLine->clear();
    ui->ComB_dailyWork_productLine->addItems(productLineList);

    ui->ComB_dailyReady_productLine->setCompleter(NewFind);
    ui->ComB_dailyReady_productLine->clear();
    ui->ComB_dailyReady_productLine->addItems(productLineList);

    ui->ComB_qcm_productLine->setCompleter(NewFind);
    ui->ComB_qcm_productLine->clear();
    ui->ComB_qcm_productLine->addItems(productLineList);

    ui->ComB_attendance_productLine->setCompleter(NewFind);
    ui->ComB_attendance_productLine->clear();
    ui->ComB_attendance_productLine->addItems(productLineList);

    if(userInfor.role != "总监" ){
        ui->ComB_dailyReady_productLine->setCurrentIndex(index);
        ui->ComB_dailyWork_productLine->setCurrentIndex(index);
        ui->ComB_qcm_productLine->setCurrentIndex(index);
        ui->ComB_attendance_productLine->setCurrentIndex(index);
    }

}

void DailyWorkPage::getMaintainer()
{


    maintainerId.clear();
    maintainerlist.clear();

    QStringList condition;
    condition.append("role ='作业员'");

    QList<QStringList> maintainer = sql.getFormListbyCondition("userInfo","*",condition);

     for(int i=0;i<maintainer.count();i++)
     {

         maintainerId.append(maintainer.at(i).at(2));

         maintainerlist.append(maintainer.at(i).at(3)+"-"+maintainer.at(i).at(4));
     }
    QCompleter *NewFind = new QCompleter(maintainerlist);
    ui->ComB_maintainPerson->setCompleter(NewFind);
    ui->ComB_maintainPerson->clear();
    ui->ComB_maintainPerson->addItems(maintainerlist);
}
void DailyWorkPage::on_Btn_AddDailyProduct_clicked()
{
    AddDailyWorkProduct addDailyWP;
    //qDebug()<<userInfor.id;
    addDailyWP.userInfor=userInfor;
    addDailyWP.showDialog();
    addDailyWP.exec();
    on_Btn_searchDailyWork_clicked();
}

void DailyWorkPage::on_Btn_searchDailyWork_clicked()
{


    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("车间"));
    HStrList.push_back(QString("生产线"));
    HStrList.push_back(QString("报告人"));
    HStrList.push_back(QString("报告时间"));
    HStrList.push_back(QString("上班时长（小时）"));
    HStrList.push_back(QString("非作业时长（小时）"));
    HStrList.push_back(QString("计划完成数"));
    HStrList.push_back(QString("实际完成数"));
    HStrList.push_back(QString("今日不良数"));
    HStrList.push_back(QString("投入工时"));
    HStrList.push_back(QString("产出工时"));
    HStrList.push_back(QString("生产效率"));
    HStrList.push_back(QString("未达标原因"));
    HStrList.push_back(QString("状态"));
    HStrList.push_back(QString("生产产品"));

    QStringList fieldName;
    fieldName<<"[isDelete]"<<"[recordTime]"<<"[id]"<<"[departmentId]"<<"[productLineId]"<<"[userId]";
    fieldName<<"[recordDate]"<<"[workTime]"<<"[noWorkTime]"<<"[planCompleteQTY]"<<"[realCompleteQTY]";
    fieldName<<"[badQty]"<<"[inputWorkTime]"<<"[outWorkTime]"<<"[workRate]"<<"[uncompleteReason]";
    fieldName<<"[status]";

    //设置行列数(只有列存在的前提下，才可以设置列标签)

    QString enddate = ui->DE_endDate->text();
    QString startdate = ui->DE_startDate->text();
    int departmentIndex=ui->ComB_dailyWork_department->currentIndex();
    int productLineIndex=ui->ComB_dailyWork_productLine->currentIndex();

    if(productLineIndex==-1)
    {
        productLineIndex=0;
    }
    if(departmentIndex==-1)
    {
        departmentIndex=0;
    }
    QList<QStringList> dailyWorklist;

    if(userInfor.role=="组长")
    {
        QStringList condition;
        //condition.append("status in( 0,3,4)  ) and (");
        condition.append("userId = '"+userInfor.id+"'  ");
        QStringList orderField;
        orderField.append("recordTime");
        dailyWorklist=sql.getFormListbyCondition("dailyWork",fieldName,condition,orderField);
    }
    /*******************查找下属************/
    else if(userInfor.role=="主任")
    {


        QStringList condition;
        condition.append("leaderId = '"+userInfor.id+"' ");
        QList<QStringList> underlinglist=sql.getFormListbyCondition("userInfo","*",condition);
        condition.clear();
        condition.append("recordDate between '"+startdate+"' and '"+enddate+"' ) and (");
        if(ComB_CheckStatus->currentText()=="未审核")
        {
            condition.append("status = 0   ) and (");

        }else
        {

            condition.append("status in(1,2,3,4)  ) and (");
        }

        for(int i=0;i<underlinglist.count();i++)
        {
            condition.append("userId = '"+underlinglist.at(i).at(2)+"' or ");

        }
        condition.append("userId = '"+userInfor.id+"' ");

        if(productLineIndex!=0)
        {
             condition.append("and productLineId = '"+productLineListId.at(productLineIndex)+"'");
        }
        QStringList orderField;
        orderField.append("recordTime");

        dailyWorklist=sql.getFormListbyCondition("dailyWork",fieldName,condition,orderField);

    }else if(userInfor.role=="厂长")//查看本厂的生产情况
    {

        QStringList condition;
        condition.append("recordDate between '"+startdate+"' and '"+enddate+"' ) and (");
        if(ComB_CheckStatus->currentText()=="未审核")
        {
            condition.append("status = 1   ) and (");

        }else
        {

            condition.append("status in(2,4)  ) and (");
        }

        condition.append("departmentId = '"+userInfor.departmentId+"' ");

        if(productLineIndex!=0)
        {
             condition.append(" and productLineId = '"+productLineListId.at(productLineIndex)+"'");
        }

        QStringList orderField;
        orderField.append("recordTime");

        dailyWorklist=sql.getFormListbyCondition("dailyWork",fieldName,condition,orderField);
    }else
    {

        QStringList condition;
        condition.append("recordDate between '"+startdate+"' and '"+enddate+"' and ");
        condition.append("status = 2 ");
        if(departmentIndex!=0)
        {
            condition.append("and departmentId = '"+departmentListId.at(departmentIndex)+"'");
        }
        if(productLineIndex!=0)
        {
             condition.append(" and productLineId = '"+productLineListId.at(productLineIndex)+"'");
        }

        dailyWorklist=sql.getFormListbyCondition("dailyWork",fieldName,condition);


    }

    QList<QStringList> data;
    QList<int> redRow;
    for(int i=0;i<dailyWorklist.count();i++)
    {
        QStringList dateList;
        for(int j=0;j<dailyWorklist.at(i).count();j++)
        {

            switch(j)
            {
                case 3:
                {
                  dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"department"));
                  break;
                }

                case 4:
                {
                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"productLine"));
                    break;
                }
                case 5:
                {
                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"userInfo"));
                    break;
                }
                case 6:
                {
                    QString date=dailyWorklist.at(i).at(j);
                    dateList.append(date.mid(0,10));

                    break;
                }
                case 14:
                {
                    QString rate=dailyWorklist.at(i).at(j);

                    float frate=rate.toFloat()*100;
                    if(frate<85)
                    {
                        redRow.append(i);
                        //
                    }
                    QString ra=QUIHelper::floatToQString(frate)+"%";
                    dateList.append(ra);
                    break;
                }
                case 16:
                {
                    QString strStatus=dailyWorklist.at(i).at(j);
                    int status=strStatus.toInt();
                    //qDebug()<<status;
                    switch (status)
                    {
                        case 0:
                        {
                            dateList.append("新增");
                            break;
                        }
                        case 1:
                        {
                            dateList.append("主任已审核");
                            break;
                        }case 2:
                        {
                            dateList.append("厂长已审核");
                            break;
                        }case 3:
                        {
                            dateList.append("主任驳回");
                            break;
                        }case 4:
                        {
                            dateList.append("厂长驳回");
                            break;
                        }

                        default:
                            break;
                    }
                    break;
                }
                default:
                {
                  dateList.append(dailyWorklist.at(i).at(j));
                  break;
                }
            };


        }
        QStringList condition;
        condition.append("recordId = '"+dailyWorklist.at(i).at(2)+"'");


        QStringList fieldName;
        fieldName << "machineCode" << "exportPlace" << "QTY"<<"recordTime";

        QStringList orderField;
        orderField.append("recordTime");

        QList<QStringList> productList=sql.getFormListbyCondition("productRecord",fieldName,condition,orderField);
        QString strProduct;
        for(int i=0;i<productList.count();i++)
        {
            strProduct.append(productList.at(i).at(0)+" 出口地："+productList.at(i).at(1)+" 生产数量:"+productList.at(i).at(2)+"  ||  ");
        }

        dateList.append(strProduct);
      data.append(dateList);
    }
    sql.tableWidgetShow(HStrList,data,ui->tableWidget_dailyProduct); //表格显示
    ui->tableWidget_dailyProduct->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_dailyProduct->setColumnWidth(17,200);
    ui->tableWidget_dailyProduct->resizeRowsToContents();
    //ui->print_tw2->setItemDelegateForColumn(5,textEditer);//换行
    for(int i;i<redRow.count();i++)//颜色标记
    {
        ui->tableWidget_dailyProduct->item(redRow.at(i),14)->setBackgroundColor(QColor(255,0,0));
    }
}

void DailyWorkPage::on_Btn_deleteDailyProduct_clicked()
{
    if(ui->tableWidget_dailyProduct->currentRow()!=-1)
    {
        selectId=ui->tableWidget_dailyProduct->item(ui->tableWidget_dailyProduct->currentRow(),2)->text();
        QStringList field;
        QVariantList value;

        field.append("isDelete");
        value.append("1");
        sql.updateForm(selectId,"dailyWork",field,value);
        on_Btn_searchDailyWork_clicked();
    }
}

void DailyWorkPage::on_tableWidget_dailyProduct_doubleClicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_dailyProduct->item(index.row(),2)->data(0).toString();
    checkStatus=ui->tableWidget_dailyProduct->item(index.row(),16)->data(0).toString();

    AddDailyWorkProduct addDailyWorkProduct;
    addDailyWorkProduct.selectId=selectId;
    addDailyWorkProduct.checkStatus=checkStatus;

    addDailyWorkProduct.userInfor=userInfor;
    addDailyWorkProduct.showDialog();
    addDailyWorkProduct.exec();
    on_Btn_searchDailyWork_clicked();
}

void DailyWorkPage::on_ComB_dailyWork_department_activated(int index)
{

    getProductLine(departmentListId.at(index));
    QCompleter *NewFind = new QCompleter(productLineList);
    ui->ComB_dailyWork_productLine->setCompleter(NewFind);
    ui->ComB_dailyWork_productLine->clear();
    ui->ComB_dailyWork_productLine->addItems(productLineList);
}

void DailyWorkPage::on_Btn_AddDailyReady_clicked()
{
    AddDailyReady adddailyready;
    adddailyready.selectId= "" ;
    adddailyready.userInfor=userInfor;
    adddailyready.showDialog();
    adddailyready.exec();


}

void DailyWorkPage::on_tableWidget_dailyReady_doubleClicked(const QModelIndex &index)
{

    AddDailyReady adddailyready;
    adddailyready.selectId= ui->tableWidget_dailyReady->item(index.row(),2)->text();
    adddailyready.userInfor=userInfor;
    adddailyready.showDialog();
    adddailyready.exec();
    on_Btn_search_DailyReady_clicked();
}
void DailyWorkPage::on_Btn_search_DailyReady_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("车间"));
    HStrList.push_back(QString("生产线"));
    HStrList.push_back(QString("生产日期"));
    HStrList.push_back(QString("合同号"));
    HStrList.push_back(QString("订单号"));
    HStrList.push_back(QString("国内机型"));
    HStrList.push_back(QString("类型"));
    HStrList.push_back(QString("出口地"));
    HStrList.push_back(QString("计划数"));
    HStrList.push_back(QString("备产信息"));

    QStringList fieldName;
    fieldName<<"isDelete" ;
    fieldName<<"recordTime";
    fieldName<<"id";
    fieldName<<"departmentId";
    fieldName<<"productLineId";
    fieldName<<"productday";
    fieldName<<"CN";
    fieldName<<"PN";
    fieldName<<"machineCode";
    fieldName<<"machineType";
    fieldName<<"exportPlace";
    fieldName<<"planQTY";
    fieldName<<"readyMsg";

    QList<QStringList> planlist;
    QStringList orderField;
    orderField.append("recordTime");
    //qDebug()<<userInfor.role<<userInfor.id;
    /*******************查找下属************/
    if(userInfor.role=="主任"||userInfor.role=="组长")
    {


        QStringList condition;
        condition.append("leaderId = '"+userInfor.id+"'");
        QList<QStringList> underlinglist=sql.getFormListbyCondition("userInfo","*",condition);


        condition.clear();
        for(int i=0;i<underlinglist.count();i++)
        {
            condition.append("userId = '"+underlinglist.at(i).at(2)+"' or ");

        }
        condition.append("userId = '"+userInfor.id+"' ");




        planlist=sql.getFormListbyCondition("planrecord",fieldName,condition,orderField);


    }else if(userInfor.role=="厂长")//查看本厂的生产情况
    {


        QStringList condition;
        condition.append("departmentId = '"+userInfor.departmentId+"'");

        planlist=sql.getFormListbyCondition("planrecord",fieldName,condition,orderField);
    }else
    {

        int departmentIndex=ui->ComB_dailyReady_department->currentIndex();
        int productLineIndex=ui->ComB_dailyReady_productLine->currentIndex();

        if(departmentIndex==0 && productLineIndex==0)
        {

            planlist=sql.getFormListbyCondition("planrecord",fieldName);

        }else if(departmentIndex==0)
        {

            QStringList condition;
            condition.append("productLineId = '"+productLineListId.at(productLineIndex)+"'");

            planlist=sql.getFormListbyCondition("planrecord",fieldName,condition,orderField);

        }else if(productLineIndex==0)
        {


            QStringList condition;
            condition.append("departmentId = '"+departmentListId.at(departmentIndex)+"'");

            planlist=sql.getFormListbyCondition("planrecord",fieldName,condition,orderField);
        }else
        {

            QStringList condition;
            condition.append("departmentId = '"+departmentListId.at(departmentIndex)+"' and");
            condition.append("productLineId = '"+productLineListId.at(productLineIndex)+"'");


            //qDebug()<<value.at(0)<<value.at(1);
            planlist=sql.getFormListbyCondition("planrecord",fieldName,condition,orderField);

        }
    }
    QList<QStringList> data;

    //qDebug()<<strlist.at(0).at(13);
    for(int i=0;i<planlist.count();i++)
    {
        QStringList dateList;
        QString date=planlist.at(i).at(5);
        QString enddate = ui->DE_endDate1->text();
        QString startdate = ui->DE_startDate1->text();
        if(date<startdate || date > enddate ){
            planlist.removeAt(i);
             i--;
            continue;
        }
        for(int j=0;j<planlist.at(i).count();j++)
        {


            switch(j)
            {
                case 3:
                {
                  dateList.append(sql.idToName(planlist.at(i).at(j),"department"));
                  break;
                }

                case 4:
                {
                    dateList.append(sql.idToName(planlist.at(i).at(j),"productLine"));
                    break;
                }

                case 5:
                {
                QString date=planlist.at(i).at(j);
                dateList.append(date.mid(0,10));
                break;
                }
                default:
                {
                  dateList.append(planlist.at(i).at(j));
                  break;
                }
            };


        }

      data.append(dateList);
    }


    sql.tableWidgetShow(HStrList,data,ui->tableWidget_dailyReady); //表格显示

    ui->tableWidget_dailyReady->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_dailyReady->setColumnWidth(12,150);

    ui->tableWidget_dailyReady->resizeRowsToContents();

}

void DailyWorkPage::on_Btn_deleteDailyReady_clicked()
{
    if(ui->tableWidget_dailyReady->currentRow()!=-1){
        selectId=ui->tableWidget_dailyReady->item(ui->tableWidget_dailyReady->currentRow(),2)->text();
        QStringList field;
        QVariantList value;
        field.append("isDelete");
        value.append("1");
        sql.updateForm(selectId,"planrecord",field,value);
        on_Btn_search_DailyReady_clicked();
    }
}


void DailyWorkPage::on_Btn_Add_Attendance_clicked()
{
    AttendanceAdd attendanceadd;
    attendanceadd.selectId = "";
    attendanceadd.userInfor=userInfor;
    attendanceadd.showDialog();
    attendanceadd.exec();
    on_Btn_search_attendance_clicked();
}

void DailyWorkPage::on_Btn_search_attendance_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("车间"));
    HStrList.push_back(QString("生产线"));
    HStrList.push_back(QString("报告人"));
    HStrList.push_back(QString("报告时间"));
    HStrList.push_back(QString("出勤人数"));
    HStrList.push_back(QString("请假人数"));
    HStrList.push_back(QString("旷工人数"));
    HStrList.push_back(QString("违规人数"));
    HStrList.push_back(QString("请假&旷工&违规名字"));

    QStringList fieldName;
    fieldName.append("isDelete");
    fieldName.append("recordTime");
    fieldName.append("id");
    fieldName.append("departmentId");
    fieldName.append("productLineId");
    fieldName.append("userId");
    fieldName.append("recordDate");
    fieldName.append("onduty");
    fieldName.append("onleave");
    fieldName.append("absenteeism");
    fieldName.append("violation");
    fieldName.append("dutyMsg");
    QStringList condition("");
    QString id,start,end;
    if(ui->ComB_attendance_department->currentText()!=""){
        id=departmentListId.at(ui->ComB_attendance_department->currentIndex());
        condition.append(QString("departmentId = '%1' and ").arg(id));
    }
    if(ui->ComB_attendance_productLine->currentText()!=""){
        id=productLineListId.at(ui->ComB_attendance_productLine->currentIndex());
        condition.append(QString("productLineId = '%1' and ").arg(id));
    }
    start = ui->DE_startDate_attendance->text();
    end = ui->DE_endDate_attendance->text();
    condition.append(QString("recordDate between '%1' and '%2'").arg(start).arg(end));
    QList<QStringList> dailyWorklist = sql.getFormListbyCondition("dutyrecord",fieldName,condition);

    QList<QStringList> data;
    QList<int> redRow;
    //qDebug()<<strlist.at(0).at(13);
    for(int i=0;i<dailyWorklist.count();i++)
    {
        QStringList dateList;
        for(int j=0;j<dailyWorklist.at(i).count();j++)
        {
            switch(j)
            {
                case 3:
                {
                  dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"department"));
                  break;
                }

                case 4:
                {
                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"productLine"));
                    break;
                }
                case 5:
                {
                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"userInfo"));
                    break;
                }
                case 6:
                {
                    QString date=dailyWorklist.at(i).at(j);
                    dateList.append(date.mid(0,10));

                    break;
                }

              default:
                {
                  dateList.append(dailyWorklist.at(i).at(j));
                  break;
                }
            }


        }

      data.append(dateList);
    }
    //qDebug()<<data;
    sql.tableWidgetShow(HStrList,data,ui->tableWidget_attendance); //表格显示
    ui->tableWidget_attendance->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_attendance->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 自适应列宽
    ui->tableWidget_attendance->resizeRowsToContents();
}

void DailyWorkPage::on_tableWidget_attendance_doubleClicked(const QModelIndex &index)
{
    AttendanceAdd attendanceadd;
    attendanceadd.selectId = ui->tableWidget_attendance->item(index.row(),2)->data(0).toString();
    attendanceadd.userInfor=userInfor;
    attendanceadd.showDialog();
    attendanceadd.exec();
    on_Btn_search_attendance_clicked();
}

void DailyWorkPage::on_Btn_delete_attendance_clicked()
{
    if(ui->tableWidget_attendance->currentRow()!=-1)
    {
        selectId=ui->tableWidget_attendance->item(ui->tableWidget_attendance->currentRow(),2)->text();
        QStringList field;
        QVariantList value;
        field.append("isDelete");
        value.append("1");
        sql.updateForm(selectId,"dutyrecord",field,value);
        on_Btn_search_attendance_clicked();
    }
}

void DailyWorkPage::on_ComB_qcm_department_activated(int index)
{
    getProductLine(departmentListId.at(index));
   QCompleter *NewFind = new QCompleter(productLineList);

    ui->ComB_qcm_productLine->setCompleter(NewFind);
    ui->ComB_qcm_productLine->clear();
    ui->ComB_qcm_productLine->addItems(productLineList);

}

void DailyWorkPage::on_ComB_attendance_department_activated(int index)
{
    getProductLine(departmentListId.at(index));

    QCompleter *NewFind = new QCompleter(productLineList);

    ui->ComB_attendance_productLine->setCompleter(NewFind);
    ui->ComB_attendance_productLine->clear();
    ui->ComB_attendance_productLine->addItems(productLineList);
}

void DailyWorkPage::on_ComB_dailyReady_department_activated(int index)
{
    getProductLine(departmentListId.at(index));

    QCompleter *NewFind = new QCompleter(productLineList);
    ui->ComB_dailyReady_productLine->setCompleter(NewFind);
    ui->ComB_dailyReady_productLine->clear();
    ui->ComB_dailyReady_productLine->addItems(productLineList);
}

void DailyWorkPage::on_Btn_AddMaintain_clicked()
{
    AddMaintainDialog addMaintain;
    addMaintain.selectId= "" ;
    addMaintain.maintainerlist = maintainerlist;
    addMaintain.maintainerId = maintainerId;
    addMaintain.userInfor=userInfor;
    addMaintain.showDialog();
    addMaintain.exec();
}

void DailyWorkPage::on_Btn_searchMaintain_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
//    HStrList.push_back(QString("车间"));
//    HStrList.push_back(QString("生产线"));
    HStrList.push_back(QString("报告人"));
    HStrList.push_back(QString("维修日期"));
    HStrList.push_back(QString("维修人员"));
    HStrList.push_back(QString("机型"));
    HStrList.push_back(QString("合同号"));
    HStrList.push_back(QString("订单号"));
    HStrList.push_back(QString("维修数量"));
    HStrList.push_back(QString("维修类别"));
    HStrList.push_back(QString("维修说明"));



    QStringList fieldName;
    fieldName.append("isDelete");
    fieldName.append("recordTime");
    fieldName.append("id");
//    fieldName.append("departmentId");
//    fieldName.append("productLineId");
    fieldName.append("userId");
    fieldName.append("maintainDate");
    fieldName.append("maintainerId");
    fieldName.append("machineCode");
    fieldName.append("CN");
    fieldName.append("PN");
    fieldName.append("maintainQty");
    fieldName.append("maintainType");
    fieldName.append("remark");

    QString condition("");
    QString id,start,end;
//    if(ui->ComB_attendance_department->currentText()!=""){
//        id=departmentListId.at(ui->ComB_attendance_department->currentIndex());
//        condition += QString("departmentId = '%1' and ").arg(id);
//    }
    condition += QString("maintainType = '%1' and ").arg(ui->ComB_maintainType->currentText());

    if(ui->ComB_maintainPerson->currentText()!=""){
        id=maintainerId.at(ui->ComB_maintainPerson->currentIndex());
        condition += QString("maintainerId = '%1' and ").arg(id);

    }

    start = ui->DE_maintainStartDate->text();
    end = ui->DE_maintainEndDate->text();
    condition += QString("maintainDate between '%1' and '%2'").arg(start).arg(end);
    QList<QStringList> dailyWorklist= sql.getFormListbyCondition("maintainRecord",fieldName,condition);

    QList<QStringList> data;
    //QList<int> redRow;

    for(int i=0;i<dailyWorklist.count();i++)
    {
        QStringList dateList;
        for(int j=0;j<dailyWorklist.at(i).count();j++)
        {
            switch(j)
            {
//                case 3:
//                {
//                  dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"department"));
//                  break;
//                }

//                case 4:
//                {
//                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"productLine"));
//                    break;
//                }
                case 3:
                {
                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"userInfo"));
                    break;
                }
                case 4:
                {
                    QString date=dailyWorklist.at(i).at(j);
                    dateList.append(date.mid(0,10));

                    break;
                }
                case 5:
                {
                    dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"userInfo"));
                    break;
                }

              default:
                {
                  dateList.append(dailyWorklist.at(i).at(j));
                  break;
                }
            }


        }

      data.append(dateList);
    }
    qDebug()<<data;
    sql.tableWidgetShow(HStrList,data,ui->tableWidget_Maintain); //表格显示
    ui->tableWidget_Maintain->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Maintain->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 自适应列宽
    ui->tableWidget_Maintain->resizeRowsToContents();

}

void DailyWorkPage::on_tableWidget_Maintain_doubleClicked(const QModelIndex &index)
{
    AddMaintainDialog maintain;
    maintain.selectId = ui->tableWidget_Maintain->item(index.row(),2)->data(0).toString();
    maintain.userInfor=userInfor;
    maintain.maintainerlist = maintainerlist;
    maintain.maintainerId = maintainerId;
    maintain.showDialog();
    maintain.exec();
    on_Btn_searchMaintain_clicked();
}

void DailyWorkPage::on_Btn_deleteMaintian_clicked()
{
    if(ui->tableWidget_Maintain->currentRow()!=-1){
        selectId=ui->tableWidget_Maintain->item(ui->tableWidget_Maintain->currentRow(),2)->text();
        QStringList field;
        QVariantList value;
        field.append("isDelete");
        value.append("1");
        sql.updateForm(selectId,"maintainRecord",field,value);
        on_Btn_searchMaintain_clicked();
    }
}

void DailyWorkPage::on_tableWidget_Rejects_doubleClicked(const QModelIndex &index)
{
    QString id = ui->tableWidget_Rejects->item(index.row(),2)->data(0).toString();
    QcmAdd qcmadd;
    qcmadd.rejectsId = id;
    qcmadd.userInfor=userInfor;
    qcmadd.showDialog();
    qcmadd.exec();
}

void DailyWorkPage::on_Btn_search_rejects_clicked()
{

}

void DailyWorkPage::on_Btn_delete_rejects_clicked()
{
    if(ui->tableWidget_Rejects->currentRow()!=-1)
    {
        selectId=ui->tableWidget_Rejects->item(ui->tableWidget_Rejects->currentRow(),2)->text();
        QStringList field;
        QVariantList value;
        field.append("isDelete");
        value.append("1");
        sql.updateForm(selectId,"rejectsRecord",field,value);
    }
}

void DailyWorkPage::on_Btn_Add_Rejects_clicked()
{
    QcmAdd qcmadd;
    qcmadd.productId = productId;
    qcmadd.userInfor=userInfor;
    qcmadd.showDialog();
    qcmadd.exec();
}

void DailyWorkPage::on_tableWidget_QCRecord_doubleClicked(const QModelIndex &index)
{

    QString day = ui->tableWidget_QCRecord->item(index.row(),6)->data(0).toString();
    QString currentId =ui->tableWidget_QCRecord->item(index.row(),2)->data(0).toString();

    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("组别"));
    HStrList.push_back(QString("日期"));
    HStrList.push_back(QString("前三大不良"));
    HStrList.push_back(QString("属性"));
    HStrList.push_back(QString("机型"));
    HStrList.push_back(QString("合同"));
    HStrList.push_back(QString("订单"));
    HStrList.push_back(QString("问题描述"));
    HStrList.push_back(QString("不良数"));
    HStrList.push_back(QString("原因分析"));
    HStrList.push_back(QString("责任人"));
    HStrList.push_back(QString("对策"));

    QStringList fieldName,condition;
    fieldName.clear();
    fieldName<<"isDelete"<<"recordTime"<<"id";
    fieldName<<"productLineId"<<"productDate"<<"QCType"<<"rejectsType"<<"machineCode"<<"CN"<<"PN"<<"rejectsDetail";
    fieldName<<"badQTY"<<"reason"<<"responsible"<<"solution";

    condition.append(QString("recordId = '%1'").arg(currentId));

    QStringList orderField;
    orderField.append("QCtype");

    QList<QStringList> qcmlist = sql.getFormListbyCondition("rejectsRecord",fieldName,condition,orderField);
    QList<QStringList> data;
     for(int i=0;i<qcmlist.count();i++)
     {
         QStringList dateList;

         for(int j=0;j<qcmlist.at(i).count();j++)
         {
             switch(j)
             {
             case 3:
             {
                 dateList.append(sql.idToName(qcmlist.at(i).at(j),"productLine"));
                 break;
             }
             case 5:
             {
                 int type = qcmlist.at(i).at(j).toInt();
                 switch (type) {
                 case 0:
                     dateList.append("第一大");
                      break;
                 case 1:
                     dateList.append("第二大");
                      break;
                 case 2:
                     dateList.append("第三大");
                      break;
                 case 3:
                     dateList.append("OQC抽检");
                      break;
                 case 4:
                     dateList.append("客户抽检");
                      break;
                 case 5:
                     dateList.append("重大工艺差错");
                      break;

                 default:
                     dateList.append(qcmlist.at(i).at(j));
                     break;
                 }
               break;
             }
             case 6:
             {
                 int type = qcmlist.at(i).at(j).toInt();
                 switch (type) {
                 case 0:
                     dateList.append("来料问题");
                      break;
                 case 1:
                     dateList.append("作业问题");
                      break;
                 case 2:
                     dateList.append("设计问题");
                      break;
                 case 3:
                     dateList.append("软件问题");
                      break;


                 default:
                     dateList.append("其他问题");
                     break;
                 }
               break;
             }


               default:
                 {
                   dateList.append(qcmlist.at(i).at(j));
                   break;
                 }
             }


         }
         //qDebug()<<dateList;
         data.append(dateList);
     }
     sql.tableWidgetShow(HStrList,data,ui->tableWidget_Rejects); //表格显示
     ui->tableWidget_Rejects->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWidget_Rejects->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tableWidget_Rejects->resizeRowsToContents();
}

void DailyWorkPage::on_Btn_search_qcm_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("机型"));
    HStrList.push_back(QString("合同"));
    HStrList.push_back(QString("订单"));
    HStrList.push_back(QString("不良数"));
    HStrList.push_back(QString("直通率"));
    HStrList.push_back(QString("组别"));
    HStrList.push_back(QString("日期"));

    QStringList fieldName;
    fieldName.append("isDelete");
    fieldName.append("recordTime");
    fieldName.append("id");

    fieldName.append("machineCode");
    fieldName.append("CN");
    fieldName.append("PN");
    fieldName.append("badQTY");
    fieldName.append("QTY");
    fieldName.append("productLineId");
    fieldName.append("productDate");

    QStringList condition;
    QString id,start,end;
    if(ui->ComB_qcm_department->currentText()!=""){
        id = departmentListId.at(ui->ComB_qcm_department->currentIndex());
        condition.append(QString("departmentId = '%1' and ").arg(id));
    }
    if(ui->ComB_qcm_productLine->currentText()!=""){
        id = productLineListId.at(ui->ComB_qcm_productLine->currentIndex());
        condition.append(QString("productLineId = '%1' and ").arg(id));
    }
    start = ui->DE_startDate_qcm->text();
    end = ui->DE_endDate_qcm->text();
    condition.append(QString("productDate between '%1' and '%2'").arg(start).arg(end));
    QStringList orderList;
    orderList.append("recordTime");
    QList<QStringList> dailyWorklist = sql.getFormListbyCondition("productRecord",fieldName,condition,orderList);

    QList<QStringList> data;
    QList<int> redRow;
    //qDebug()<<strlist.at(0).at(13);
    for(int i=0;i<dailyWorklist.count();i++)
    {
        QStringList dateList;

        for(int j=0;j<dailyWorklist.at(i).count();j++)
        {

            switch(j)
            {
                case 8:
                {
                 dateList.append(sql.idToName(dailyWorklist.at(i).at(j),"productLine"));
                  break;
                }

                case 9:
                {
                    QString date=dailyWorklist.at(i).at(j);
                    dateList.append(date.mid(0,10));
                    break;
                }

                case 7:
                {
                    float qty = dailyWorklist.at(i).at(j).toFloat(),
                     badqty =dailyWorklist.at(i).at(j-1).toFloat();


                    float frate=(qty/(qty+badqty))*100;

                    if(frate<98)
                    {
                        redRow.append(i);

                    }
                    QString ra=QUIHelper::floatToQString(frate)+"%";
                    dateList.append(ra);
                    break;
                }


              default:
                {
                  dateList.append(dailyWorklist.at(i).at(j));
                  break;
                }
            }


        }



      data.append(dateList);
    }
    //qDebug()<<data;
    sql.tableWidgetShow(HStrList,data,ui->tableWidget_QCRecord); //表格显示

    ui->tableWidget_QCRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget_QCRecord->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 自适应列宽
   // ui->tableWidget_QCRecord->setColumnWidth(9,200);
    ui->tableWidget_QCRecord->resizeRowsToContents();

}




void DailyWorkPage::on_tableWidget_QCRecord_itemSelectionChanged()
{
   ui->Btn_Add_Rejects->setEnabled(true);
   productId =ui->tableWidget_QCRecord->item(ui->tableWidget_QCRecord->currentIndex().row(),2)->text();
}
bool DailyWorkPage::eventFilter(QObject *watched, QEvent *event)
{

   // qDebug()<<event;
//    if (event->type() == QEvent::MouseButtonPress) {

//        if (watched == ui->widgetTitle) {
//            on_btnMenu_Max_clicked();
//            return true;
//        }
//    }


    return QWidget::eventFilter(watched, event);
}
