#include "dailyproblempage.h"
#include "ui_dailyproblempage.h"
#include "appInit/quiwidget.h"

DailyProblemPage::DailyProblemPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyProblemPage)
{
    ui->setupUi(this);
    this->initPage();
    ComB_CheckStatus=new QComboBox();

}

DailyProblemPage::~DailyProblemPage()
{
    delete ui;
}

void DailyProblemPage::initPage()
{
    ui->widget_Menu->setProperty("flag", "left");
    this->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));

    pixChar << 0xf031 << 0xf036   ;
    btns << ui->tBtn_Menu1 << ui->tBtn_Menu2 ;

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
    ui->DE_PQCstartDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_PQCendDate->setDisplayFormat("yyyy-MM-dd");
    ui->DE_PQCstartDate->setDate(QDate::currentDate());
    ui->DE_PQCendDate->setDate(QDate::currentDate().addDays(1));


    ui->tBtn_Menu1->click();

}


void DailyProblemPage::showPage()
{
    ComB_CheckStatus->addItem("未审核");
    ComB_CheckStatus->addItem("已审核");
    ui->horizontalLayout_Search_PQC->insertWidget(7,ComB_CheckStatus);


    if(userInfor.role=="组长")
    {
        ui->ComB_department_PQC->setEnabled(false);
        ui->ComB_productLine_PQC->setEnabled(false);

    }if(userInfor.role=="主任"||userInfor.role=="厂长")
    {

        ui->ComB_department_PQC->setEnabled(false);

    }

        getDepartmentinfo();
        getProductLine(userInfor.departmentId);



}


void DailyProblemPage::getDepartmentinfo()
{

    int index;
    for(int i=0;i<departmentListId.count();i++)
    {

        if(departmentListId.at(i) == userInfor.departmentId){
            index = i;
        }
    }
    QCompleter *NewFind = new QCompleter(departmentList);
    ui->ComB_department_PQC->setCompleter(NewFind);
    ui->ComB_department_PQC->clear();
    ui->ComB_department_PQC->addItems(departmentList);

    //qDebug()<<userInfor.id;

    if(userInfor.role != "总监" ){
        ui->ComB_department_PQC->setCurrentIndex(index);

    }

}
void DailyProblemPage::getProductLine(QString currentDepartmentId)
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
            index = i+1;
        }
    }

    QCompleter *NewFind = new QCompleter(productLineList);
    ui->ComB_productLine_PQC->setCompleter(NewFind);
    ui->ComB_productLine_PQC->clear();
    ui->ComB_productLine_PQC->addItems(productLineList);



    if(userInfor.role != "总监" ){
        ui->ComB_productLine_PQC->setCurrentIndex(index);

    }

}


void DailyProblemPage::MenuClick()
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

void DailyProblemPage::on_Btn_AddPQC_clicked()
{
      //  qDebug()<<userInfor.id;
    AddDailyProblemDialog  addPQC;
    addPQC.userInfor=userInfor;
    addPQC.showDialog();
    addPQC.exec();

}

void DailyProblemPage::on_BN_Search_PQCProblem_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("车间"));
    HStrList.push_back(QString("生产线"));
    HStrList.push_back(QString("日期"));
    HStrList.push_back(QString("巡检问题"));
    HStrList.push_back(QString("分析对策"));
    HStrList.push_back(QString("效果验证"));
    HStrList.push_back(QString("是否解决"));
    HStrList.push_back(QString("确认情况"));
    QStringList fieldName;
    fieldName.append("isDelete");
    fieldName.append("recordTime");
    fieldName.append("id");
    fieldName.append("departmentId");
    fieldName.append("productLineId");
    fieldName.append("recordDate");
    fieldName.append("problemDetail");
    fieldName.append("solutionDetail");
    fieldName.append("verification");
    fieldName.append("problemStatus");
    fieldName.append("checkStatus");
    fieldName.append("machineCode");
    fieldName.append("CN");
    fieldName.append("PN");
    QStringList condition;
    QString id;
    if(ui->ComB_department_PQC->currentText()!=""){
        id = departmentListId.at(ui->ComB_department_PQC->currentIndex());
        condition.append(QString("departmentId = '%1' and ").arg(id));
    }
    if(ui->ComB_productLine_PQC->currentText()!=""){
        id = productLineListId.at(ui->ComB_productLine_PQC->currentIndex());
        condition.append(QString("productLineId = '%1' and ").arg(id));
    }
    QString startDate,endDate;
    startDate = ui->DE_PQCstartDate->text();
    endDate = ui->DE_PQCendDate->text();
    condition.append(QString("(recordDate between '%1' and '%2')").arg(startDate).arg(endDate));
    if(ComB_CheckStatus->currentIndex() ==0){
        if(userInfor.role != "厂长")
        {
        condition.append("and checkStatus in (0,3,4)");
        }
        else
        {
            condition.append("and checkStatus in (0,1,3,4)");
        }
    }
    if(ComB_CheckStatus->currentIndex() ==1){
        if(userInfor.role != "厂长")
        {
           condition.append("and checkStatus in (1,2)");
        }
        else
        {
            condition.append("and checkStatus =2");
        }

    }
    QList<QStringList>strList= sql.getFormListbyCondition("PQCProblem",fieldName,condition);
    QList<QStringList> data;
    for(int i=0;i<strList.count();i++)
    {
        QStringList dataList;
        QString date;QString str="";
        int status = 0;

        for(int j=0; j<strList.at(i).count(); j++)
        {
            switch (j) {
            case 3:
                 dataList.append(sql.idToName(strList.at(i).at(j),"department"));
                break;
            case 4:
                 dataList.append(sql.idToName(strList.at(i).at(j),"productLine"));
                break;
            case 5:
                 date=strList.at(i).at(j);
                 dataList.append(date.mid(0,10));
                break;
            case 6:

                str = "机型：" + strList.at(i).at(11) + "合同号：" + strList.at(i).at(12);
                str += "订单号：" + strList.at(i).at(13)+"\r\n";
                str += "问题点："+ strList.at(i).at(j);
                dataList.append(str);
                break;
            case 9:
                status = strList.at(i).at(j).toInt();
                switch (status)
                {
                case 0:
                    dataList.append("未解决");
                    break;
                case 1:
                    dataList.append("已解决");
                    break;
                default:
                     dataList.append("未知");
                    break;
                }
               break;
            case 10:
               status=strList.at(i).at(j).toInt();
                switch (status)
                {
                    case 0:
                    {
                        dataList.append("新增");
                        break;
                    }
                    case 1:
                    {
                        dataList.append("主任已审核");
                        break;
                    }case 2:
                    {
                        dataList.append("厂长已审核");
                        break;
                    }case 3:
                    {
                        fieldName.clear();
                        condition.clear();
                        fieldName.append("details");
                        fieldName.append("checkerId");
                        condition.append("recordId = '"+strList.at(i).at(2)+"'");
                        condition.append("and result = '驳回'");
                        QList<QStringList> tmpStr =sql.getFormListbyCondition("checkRecord",fieldName,condition);
                        int count = tmpStr.count();
                        QString name =sql.idToName(tmpStr.at(count-1).at(1),"userInfo");
                        dataList.append(name+"主任驳回,驳回信息："+tmpStr.at(count-1).at(0));
                        break;
                    }case 4:
                    {
                        fieldName.clear();
                        condition.clear();
                        fieldName.append("details");
                        fieldName.append("checkerId");
                        condition.append("recordId = '"+strList.at(i).at(2)+"'");
                        condition.append("and result = '驳回'");
                        QList<QStringList> tmpStr =sql.getFormListbyCondition("checkRecord",fieldName,condition);
                        int count = tmpStr.count();
                        QString name =sql.idToName(tmpStr.at(count-1).at(1),"userInfo");
                        dataList.append(name+"厂长驳回,驳回信息："+tmpStr.at(count-1).at(0));
                        break;
                    }
                    default:
                    dataList.append("未知");
                        break;
                }
                break;
            case 11:
            case 12:
            case 13:
                break;

            default:
                dataList.append(strList.at(i).at(j));
                break;
            }

        }
    data.append(dataList);
    }
    //qDebug()<<data;
    sql.tableWidgetShow(HStrList,data,ui->tableWidget_PQC); //表格显示
    ui->tableWidget_PQC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_PQC->resizeRowsToContents();

}

void DailyProblemPage::on_tableWidget_PQC_doubleClicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_PQC->item(index.row(),2)->data(0).toString();
    QString checkStatus=ui->tableWidget_PQC->item(index.row(),10)->data(0).toString();
    AddDailyProblemDialog addPQC;
    addPQC.selectId=selectId;
    addPQC.checkStatus=checkStatus;
    addPQC.userInfor=userInfor;
    addPQC.showDialog();
    addPQC.exec();
    on_BN_Search_PQCProblem_clicked();
}

void DailyProblemPage::on_Btn_DeletePQC_clicked()
{
    if(ui->tableWidget_PQC->currentRow()!=-1)
    {
        selectId = ui->tableWidget_PQC->item(ui->tableWidget_PQC->currentRow(),2)->data(0).toString();
        QString checkStatus=ui->tableWidget_PQC->item(ui->tableWidget_PQC->currentRow(),10)->data(0).toString();
        if(checkStatus == "主任已审核"|| checkStatus == "厂长已审核")
        {
            QUIHelper::showMessageBoxInfo("当前状态不允许删除！",1);
            return;
        }
        else
        {
            QStringList condition,field;
            QVariantList value;
            field.append("isDelete");
            value.append(1);
            condition.append("id = '"+selectId +"'");
            sql.updateForm(selectId,"PQCProblem",field,value);
            on_BN_Search_PQCProblem_clicked();
        }
    }
}
