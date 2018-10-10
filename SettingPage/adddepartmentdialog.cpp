#include "adddepartmentdialog.h"
#include "ui_adddepartmentdialog.h"
#include "appInit/quiwidget.h"

addDepartmentDialog::addDepartmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDepartmentDialog)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);


    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);

    getUserinfo();
}

addDepartmentDialog::~addDepartmentDialog()
{
    delete ui;
}

void addDepartmentDialog::on_btnMenu_Close_clicked()
{
    close();
}


void addDepartmentDialog::showDialog()
{

   if(selectId=="")
   {
   }else
   {
        sqlDataSource addSql;
        QStringList fieldname,condition;
        fieldname.append("*");
        condition.append("id = '"+selectId+"'");
        QStringList strList=addSql.getFormListbyCondition("department",fieldname,condition).at(0);

        //qDebug()<<strList;
        ui->LE_No->setText(strList.at(3));
        ui->LE_Name->setText(strList.at(4));

        DepartmentInfor.chargerId=strList.at(5);
        ui->ComB_charger->setCurrentText(addSql.idToName(strList.at(5),"userInfo"));


   }
}
void addDepartmentDialog::getUserinfo()
{
    sqlDataSource addSql;
    QStringList fieldname;
    fieldname.append("*");


    QList<QStringList> strlist=addSql.getFormListbyCondition("userInfo",fieldname,"recordTime");

    userList.clear();
    userListId.clear();
    userList.append("");
    userListId.append("00000000-0000-0000-0000-000000000000");
    for(int i=0;i<strlist.count();i++)
    {

        userListId.append(strlist.at(i).at(2));
        userList.append(strlist.at(i).at(4)+"-"+strlist.at(i).at(3));
    }

    QCompleter *NewFind = new QCompleter(userList);
    ui->ComB_charger->setCompleter(NewFind);
    ui->ComB_charger->addItems(userList);

}
void addDepartmentDialog::on_Btn_Submit_clicked()
{

    if(selectId=="")
    {

        QUuid Id=QUuid::createUuid();
        DepartmentInfor.id=Id.toString().mid(1,36);
        //qDebug()<<DepartmentInfor.id;
        DepartmentInfor.name=ui->LE_Name->text().simplified();
        DepartmentInfor.code=ui->LE_No->text().simplified();


        QStringList field;
        field.append("id");
        field.append("code");
        field.append("name");
        field.append("chargerId");
         QVariantList value;
         value.append(DepartmentInfor.id);
         value.append(DepartmentInfor.code);
         value.append(DepartmentInfor.name);
         value.append(DepartmentInfor.chargerId);
         addSql.addFormList("department",field,value);
    }
    else{

        QStringList field;
        field.append("code");
        field.append("name");

        field.append("chargerId");

        QVariantList value;
        value.append(ui->LE_No->text().simplified());
        value.append(ui->LE_Name->text().simplified());
        value.append(DepartmentInfor.chargerId);
        addSql.updateForm(selectId,"department",field,value);
    }
}

void addDepartmentDialog::on_ComB_charger_activated(int index)
{
    DepartmentInfor.chargerId=userListId.at(index);
}
