#include "addproductlinedialog.h"
#include "ui_addproductlinedialog.h"
#include "appInit/quiwidget.h"

addProductLineDialog::addProductLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addProductLineDialog)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);


    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);

    getUserinfo();
    getDepartmentinfo();
}

addProductLineDialog::~addProductLineDialog()
{
    delete ui;
}

void addProductLineDialog::on_btnMenu_Close_clicked()
{
    close();
}
void addProductLineDialog::showDialog()
{

   if(selectId=="")
   {
   }else
   {
        sqlDataSource addSql;


        QStringList condition;
        condition.append("id = '"+selectId+"'");
        QStringList strList=addSql.getFormListbyCondition("productLine","*",condition).at(0);

        //qDebug()<<strList;
        ui->LE_No->setText(strList.at(3));
        ui->LE_Name->setText(strList.at(4));
        productLineInfor.chargerId=strList.at(5);
        productLineInfor.departmentId=strList.at(6);
        ui->ComB_charger->setCurrentText(addSql.idToName(strList.at(5),"userInfo"));
        ui->ComB_department->setCurrentText(addSql.idToName(strList.at(6),"department"));


   }
}
void addProductLineDialog::getUserinfo()
{

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
void addProductLineDialog::getDepartmentinfo()
{
    QStringList fieldname;
    fieldname.append("*");

    QList<QStringList> strlist=addSql.getFormListbyCondition("department",fieldname,"recordTime");

    departmentList.clear();
    departmentListId.clear();
    departmentList.append("");
    departmentListId.append("00000000-0000-0000-0000-000000000000");
    for(int i=0;i<strlist.count();i++)
    {

        departmentListId.append(strlist.at(i).at(2));
        departmentList.append(strlist.at(i).at(4)+"-"+strlist.at(i).at(3));
    }

    QCompleter *NewFind = new QCompleter(departmentList);
    ui->ComB_department->setCompleter(NewFind);
    ui->ComB_department->addItems(departmentList);

}
void addProductLineDialog::on_Btn_Submit_clicked()
{
    if(selectId=="")
    {

        QUuid Id=QUuid::createUuid();
        productLineInfor.id=Id.toString().mid(1,36);
        qDebug()<<productLineInfor.id;
        productLineInfor.name=ui->LE_Name->text().simplified();
        productLineInfor.code=ui->LE_No->text().simplified();

        //addSql.addProductLineinfo(productLineInfor);
        QStringList field;
        field.append("code");
        field.append("name");
        field.append("chargerId");
        field.append("departmentId");
        field.append("id");

        QVariantList value;
        value.append(productLineInfor.code);
        value.append(productLineInfor.name);
        value.append(productLineInfor.chargerId);
        value.append(productLineInfor.departmentId);
        value.append(productLineInfor.id);
        addSql.addFormList("productLine",field,value);




    }else
    {
        QStringList field;
        field.append("code");
        field.append("name");

        field.append("chargerId");
        field.append("departmentId");

        QVariantList value;
        value.append(ui->LE_No->text().simplified());
        value.append(ui->LE_Name->text().simplified());
        value.append(productLineInfor.chargerId);
        value.append(productLineInfor.departmentId);
        addSql.updateForm(selectId,"productLine",field,value);
    }
}

void addProductLineDialog::on_ComB_charger_activated(int index)
{
    productLineInfor.chargerId=userListId.at(index);
}

void addProductLineDialog::on_ComB_department_activated(int index)
{
     productLineInfor.departmentId=departmentListId.at(index);
}
