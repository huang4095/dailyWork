#include "mainWidget.h"
#include"ui_MainWidget.h"
#include "appInit/quiwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->initForm();


}

MainWidget::~MainWidget()
{
    delete ui;
}
void MainWidget::showWidget()
{

    getDepartmentList();
    /********绑定各个page***************/

    dailyWorkPage=new DailyWorkPage();
    ui->page_DailyWork->layout()->addWidget(dailyWorkPage);
    dailyWorkPage->departmentList = departmentList;
    dailyWorkPage->userInfor = userInfor;
    dailyWorkPage->departmentListId = departmentListId;
    //传递用户信息
    dailyWorkPage->showPage();

    dailyProblemPage=new DailyProblemPage();    
    ui->page_DailyProblem->layout()->addWidget(dailyProblemPage);
    dailyProblemPage->departmentList = departmentList;
    dailyProblemPage->userInfor = userInfor;
    dailyProblemPage->departmentListId = departmentListId;
    dailyProblemPage->showPage();

    settingPage=new SettingPage();
    ui->page_Setting->layout()->addWidget(settingPage);



    Timer1s=new QTimer();
    connect(Timer1s, SIGNAL(timeout()), this, SLOT(TopMenu_SysInfo()));
    Timer1s->start(1000);
}
bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        if (watched == ui->widgetTitle) {
            on_btnMenu_Max_clicked();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void MainWidget::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf073), 40);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));


    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);
    ui->widgetTop->setProperty("nav", "top");
    ui->labTitle->setText("万利达车间生产日志");
    ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->labTitle->text());



    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }


    ui->btnMain->click();

}

void MainWidget::buttonClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }

    if (name == "生产日志") {
        ui->stackedWidget_main->setCurrentIndex(0);
    } else if (name == "问题记录") {


        ui->stackedWidget_main->setCurrentIndex(1);
    } else if (name == "设  置") {
        ui->stackedWidget_main->setCurrentIndex(2);
    } else if (name == "调试帮助") {
        ui->stackedWidget_main->setCurrentIndex(3);
    } else if (name == "用户退出") {
        close();
    }
}
void MainWidget::TopMenu_SysInfo()
{
    QDateTime  time = QDateTime::currentDateTime();
    QString   currenttime = time.toString("yyyy年MM月dd日 hh:mm:ss ");
    ui->LB_SysTime->setText(currenttime);
    ui->LB_CurrentUser->setText(userInfor.name+"  "+userInfor.position);
}
void MainWidget::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void MainWidget::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    this->setProperty("canMove", max);
    max = !max;
}

void MainWidget::on_btnMenu_Close_clicked()
{
    close();
}

void MainWidget::getDepartmentList()
{
    sqlDataSource addSql;
    QList<QStringList> strlist=addSql.getFormListbyCondition(QString("department"),QString("*"));
    departmentList.clear();
    departmentListId.clear();
    departmentList.append("");
    departmentListId.append("00000000-0000-0000-0000-000000000000");
    for(int i=0;i<strlist.count();i++)
    {
        departmentListId.append(strlist.at(i).at(2));
        departmentList.append(strlist.at(i).at(3)+"-"+strlist.at(i).at(4));
    }
}
