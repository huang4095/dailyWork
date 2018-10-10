#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QString iniFilePath = QCoreApplication::applicationDirPath()+"/login.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);


    for(int i=0;i<4;i++)
    {
        QString user=settings.allKeys().value(i);
        ui->user_LE->addItem(user.mid(7,9));
    }

    IconHelper::Instance()->setIcon(ui->minBtn, QChar(0xf068));

    IconHelper::Instance()->setIcon(ui->quitBtn, QChar(0xf00d));

    ui->loginBtn->setDefault(true);
}

void LoginDialog::on_loginBtn_clicked()//登录窗口判断
{
    QString user=ui->user_LE->currentText();
    QString pwd =ui->passwd_LE->text();
    if(user==NULL)
    {
        QUIHelper::showMessageBoxInfo("请输入工号！",0,true);
        return;
    }
    if(pwd==NULL)
    {
        QUIHelper::showMessageBoxInfo("请输入密码！",0,true);

        return;
    }
    ConnectionPool sql;
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    query.exec("select * from userInfo where code='"+user+"' and passWord='"+pwd+"'");
    if(query.next())
    {
       userInfor.id=query.value(2).toString();
       userInfor.code=query.value(3).toString();
       userInfor.name=query.value(4).toString();
       userInfor.position=query.value(5).toString();
       userInfor.departmentId=query.value(6).toString();
       userInfor.leaderId=query.value(7).toString();
       userInfor.productLineId=query.value(8).toString();
       userInfor.role=query.value(10).toString();

       QDialog ::accept();
       if(ui->checkBox->isChecked())
       {
           QString iniFilePath = QCoreApplication::applicationDirPath()+"/login.ini";
           QSettings settings(iniFilePath,QSettings::IniFormat);
           settings.setValue("Group1/"+user+"",user);
       }

    }
    else
    {

        QUIHelper::showMessageBoxError("工号或密码错误，登录失败！",0,true);
        ui->passwd_LE->clear();
        ui->passwd_LE->setFocus();
    }
    sql.closeConnection(db);
}
void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_changeinfor_Btn_clicked()
{
    // pwdchange dlg;
     //dlg.exec();
}

void LoginDialog::on_minBtn_clicked()
{

    this->showMinimized();
}
