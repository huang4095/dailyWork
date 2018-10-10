#include "settingpage.h"
#include "ui_settingpage.h"
#include "appInit/quiwidget.h"

SettingPage::SettingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingPage)
{
    ui->setupUi(this);
    this->initPage();
    on_Btn_SearchUser_clicked();
}

SettingPage::~SettingPage()
{
    delete ui;
}

void SettingPage::initPage()
{
    ui->widget_Menu->setProperty("flag", "left");
    this->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));

    pixChar << 0xf031 << 0xf036 << 0xf249  ;
    btns << ui->tBtn_Menu1 << ui->tBtn_Menu2 << ui->tBtn_Menu3;

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

    ui->tBtn_Menu1->click();
}

void SettingPage::MenuClick()
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

void SettingPage::on_Btn_AddUser_clicked()
{
    addUserDialog adduser;
    adduser.exec();
    on_Btn_SearchUser_clicked();
}

void SettingPage::on_Btn_SearchUser_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("recordTime"));
    HStrList.push_back(QString("ID"));
    HStrList.push_back(QString("员工工号"));
    HStrList.push_back(QString("姓名"));
    HStrList.push_back(QString("职位"));
    HStrList.push_back(QString("职级"));
    HStrList.push_back(QString("直属领导"));
    HStrList.push_back(QString("所属部门"));
    HStrList.push_back(QString("所属线体"));

    //设置行列数(只有列存在的前提下，才可以设置列标签)
    QStringList fieldname;
    fieldname.append("*");

    QList<QStringList> strlist=sql.getFormListbyCondition("v_userInfo",fieldname,"recordTime");

    //qDebug()<<strlist;
    QList<QStringList> date;
    for(int i=0;i<strlist.count();i++)
    {
        QStringList dateList;
        for(int j=0;j<strlist.at(i).count();j++)
        {
            if(j==7)
            {
                //qDebug()<<sql.idToName(strlist.at(i).at(j),"userInfo");
                dateList.append(sql.idToName(strlist.at(i).at(j),"userInfo"));
            }else if(j==8)
            {
                dateList.append(sql.idToName(strlist.at(i).at(j),"department"));
            }else if(j==9)
            {
                dateList.append(sql.idToName(strlist.at(i).at(j),"productLine"));
            }
            else
            {
                dateList.append(strlist.at(i).at(j));
            }
        }
      date.append(dateList);
    }


    sql.tableWidgetShow(HStrList,date,ui->tableWidget_user); //表格显示
    ui->tableWidget_user->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_user->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等分列宽

}



void SettingPage::on_Btn_addDepartment_clicked()
{
    addDepartmentDialog add;
    add.exec();
    on_tBtn_Menu2_clicked();
}

void SettingPage::on_tBtn_Menu2_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("记录时间"));
    HStrList.push_back(QString("id"));
    HStrList.push_back(QString("车间代号"));
    HStrList.push_back(QString("车间名称"));
    HStrList.push_back(QString("负责人"));
    QStringList fieldname;
    fieldname.append("*");

    QList<QStringList> strlist=sql.getFormListbyCondition("department",fieldname,"recordTime");

    //qDebug()<<strlist;
    QList<QStringList> date;
    for(int i=0;i<strlist.count();i++)
    {
        QStringList dateList;
        for(int j=0;j<strlist.at(i).count();j++)
        {
            if(j==5)
            {
                dateList.append(sql.idToName(strlist.at(i).at(j),"userInfo"));
            }else
            {
                dateList.append(strlist.at(i).at(j));
            }
        }
      date.append(dateList);
    }
    sql.tableWidgetShow(HStrList,date,ui->tableWidget_department); //表格显示
    ui->tableWidget_department->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SettingPage::on_tableWidget_user_doubleClicked(const QModelIndex &index)
{
   selectId=ui->tableWidget_user->item(index.row(),2)->data(0).toString();
   addUserDialog adduser;
   adduser.selectId=selectId;
   adduser.showDialog();
   adduser.exec();
   on_Btn_SearchUser_clicked();
}

void SettingPage::on_tableWidget_user_clicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_user->item(index.row(),2)->data(0).toString();

}
void SettingPage::on_Btn_DeleteUser_clicked()
{
    QStringList field;
    QVariantList value;

    field.append("isDelete");
    value.append("1");
    sql.updateForm(selectId,"userInfo",field,value);

    on_Btn_SearchUser_clicked();
}


void SettingPage::on_Btn_AddProductLine_clicked()
{
    addProductLineDialog add;
    add.exec();
    on_tBtn_Menu3_clicked();
}

void SettingPage::on_tBtn_Menu3_clicked()
{
    QStringList HStrList;
    HStrList.push_back(QString("isDelete"));
    HStrList.push_back(QString("记录时间"));
    HStrList.push_back(QString("id"));
    HStrList.push_back(QString("产线代号"));
    HStrList.push_back(QString("产线名称"));
    HStrList.push_back(QString("负责人"));
    HStrList.push_back(QString("所属车间"));

    QStringList fieldname;
    fieldname.append("*");
    QList<QStringList> strlist=sql.getFormListbyCondition("productLine",fieldname,"recordTime");

    QList<QStringList> date;
    for(int i=0;i<strlist.count();i++)
    {
        QStringList dateList;
        for(int j=0;j<strlist.at(i).count();j++)
        {
            if(j==5)
            {
                dateList.append(sql.idToName(strlist.at(i).at(j),"userInfo"));
            }else if(j==6)
            {
                dateList.append(sql.idToName(strlist.at(i).at(j),"department"));
            }else
            {
                dateList.append(strlist.at(i).at(j));
            }
        }
      date.append(dateList);
    }
    sql.tableWidgetShow(HStrList,date,ui->tableWidget_productLine); //表格显示
    ui->tableWidget_productLine->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SettingPage::on_tableWidget_department_doubleClicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_department->item(index.row(),2)->data(0).toString();
    addDepartmentDialog addDepartment;
    addDepartment.selectId=selectId;
    addDepartment.showDialog();
    addDepartment.exec();
    on_tBtn_Menu2_clicked();
}

void SettingPage::on_tableWidget_department_clicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_department->item(index.row(),2)->data(0).toString();
}

void SettingPage::on_Btn_DeleteDepartment_clicked()
{
    QStringList field;
    QVariantList value;

    field.append("isDelete");
    value.append("1");
    sql.updateForm(selectId,"department",field,value);

    on_tBtn_Menu2_clicked();
}

void SettingPage::on_tableWidget_productLine_doubleClicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_productLine->item(index.row(),2)->data(0).toString();
    addProductLineDialog addProductLine;
    addProductLine.selectId=selectId;
    addProductLine.showDialog();
    addProductLine.exec();
    on_tBtn_Menu3_clicked();
}

void SettingPage::on_tableWidget_productLine_clicked(const QModelIndex &index)
{
    selectId=ui->tableWidget_productLine->item(index.row(),2)->data(0).toString();
}

void SettingPage::on_Btn_DeleteProductLine_clicked()
{
    QStringList field;
    QVariantList value;

    field.append("isDelete");
    value.append("1");
    sql.updateForm(selectId,"productLine",field,value);

    on_tBtn_Menu3_clicked();
}
