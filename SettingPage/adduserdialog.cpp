#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "appInit/quiwidget.h"
#include"SqlMag/sqldatasource.h"
#include<QUuid>
addUserDialog::addUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addUserDialog)
{
    ui->setupUi(this);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);


    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);

    getDepartmentinfo();
    getUserinfo();
    //getProductLine();


}

addUserDialog::~addUserDialog()
{
    delete ui;
}

void addUserDialog::on_btnMenu_Close_clicked()
{
    close();
}
void addUserDialog::showDialog()
{

   if(selectId=="")
   {
   }else
   {
        sqlDataSource addSql;

        QStringList condition;
        condition.append("id = '"+selectId+"'");

        QStringList strList=addSql.getFormListbyCondition("v_userInfo","*",condition).at(0);

        //qDebug()<<strList;
        ui->LE_UserNo->setText(strList.at(3));
        ui->LE_UserName->setText(strList.at(4));
        ui->LE_Position->setText(strList.at(5));
        ui->ComB_Role->setCurrentText(strList.at(6));
        userInfor.role=strList.at(6);

        userInfor.leaderId=strList.at(7);
        userInfor.departmentId=strList.at(8);
        userInfor.productLineId=strList.at(9);
        ui->ComB_Leader->setCurrentText(addSql.idToName(strList.at(7),"userInfo"));
        ui->ComB_Department->setCurrentText(addSql.idToName(strList.at(8),"department"));
        ui->ComB_ProductLine->setCurrentText(addSql.idToName(strList.at(9),"productLine"));
        //qDebug()<<addSql.idToName(strList.at(8),"productLine");
   }
}
void addUserDialog::getDepartmentinfo()
{
    sqlDataSource addSql;
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
    ui->ComB_Department->setCompleter(NewFind);
    ui->ComB_Department->addItems(departmentList);

}
void addUserDialog::getUserinfo()
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
    ui->ComB_Leader->setCompleter(NewFind);
    ui->ComB_Leader->addItems(userList);

}
void addUserDialog::getProductLine(QString currentDepartmentId)
{

    QList<QStringList> strlist;


    if(currentDepartmentId=="00000000-0000-0000-0000-000000000000")
    {
        QStringList fieldname;
        fieldname.append("*");
        strlist=addSql.getFormListbyCondition("productLine",fieldname,"recordTime");
    }else
    {

        QStringList condition;
        condition.append("departmentId = '"+currentDepartmentId+"'");

        strlist=addSql.getFormListbyCondition("productLine","*",condition,"recordTime");
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
    ui->ComB_ProductLine->clear();
    ui->ComB_ProductLine->setCompleter(NewFind);

    ui->ComB_ProductLine->addItems(productLineList);

}

void addUserDialog::on_Btn_Submit_clicked()
{


    userInfor.name=ui->LE_UserName->text().simplified();
    userInfor.code=ui->LE_UserNo->text().simplified();
    userInfor.position=ui->LE_Position->text().simplified();
    userInfor.role=ui->ComB_Role->currentText().simplified();

    if(selectId=="")
    {
        QUuid userId=QUuid::createUuid();
        userInfor.id=userId.toString().mid(1,36);


        QStringList field;
        field.append("Id");
        field.append("code");
        field.append("name");
        field.append("position");
        field.append("departmentId");
        field.append("leaderId");
        field.append("productLineId");
        field.append("role");

        QVariantList value;

        value.append(userInfor.id);
        value.append(userInfor.code);
        value.append(userInfor.name);
        value.append(userInfor.position);
        value.append(userInfor.departmentId);
        value.append(userInfor.leaderId);
        value.append(userInfor.productLineId);
        value.append(userInfor.role);
//        addSql.addUserInfo(userInfor);

        addSql.addFormList("userInfo",field,value);
    }else{

        QStringList field;
        field.append("code");
        field.append("name");
        field.append("position");
        field.append("departmentId");
        field.append("leaderId");
        field.append("productLineId");
        field.append("role");

        QVariantList value;
        value.append(userInfor.code);
        value.append(userInfor.name);
        value.append(userInfor.position);
        value.append(userInfor.departmentId);
        value.append(userInfor.leaderId);
        value.append(userInfor.productLineId);
        value.append(userInfor.role);

        addSql.updateForm(selectId,"userInfo",field,value);
    }

}



void addUserDialog::on_ComB_Department_activated(int index)
{
    userInfor.departmentId=departmentListId.at(index);
    getProductLine(departmentListId.at(index));
    //qDebug()<<index;
}

void addUserDialog::on_ComB_Leader_activated(int index)
{
    userInfor.leaderId=userListId.at(index);
}

void addUserDialog::on_ComB_ProductLine_activated(int index)
{
    userInfor.productLineId=productLineListId.at(index);
}

void addUserDialog::on_ComB_Role_activated(const QString &arg1)
{
    userInfor.role=arg1;
}
