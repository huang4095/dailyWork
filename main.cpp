#include "mainWidget.h"
#include "appInit/appinit.h"
#include "appInit/quiwidget.h"
#include"logindialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));
    AppInit::Instance()->start();

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    //加载样式表
    QFile file(":/qss/silvery.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QUIHelper::getQssColor(qss, QUIConfig::TextColor, QUIConfig::PanelColor, QUIConfig::BorderColor, QUIConfig::NormalColorStart,
                               QUIConfig::NormalColorEnd, QUIConfig::DarkColorStart, QUIConfig::DarkColorEnd, QUIConfig::HighColor);

        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    MainWidget w;

//    w.show();
    LoginDialog dlg;

    if (dlg.exec() == QDialog::Accepted)
    {

        w.userInfor=dlg.userInfor;
        w.show();//登录窗口确认
        w.showWidget();
       // w.dailyWorkPage->userInfor=userInfor;//传递用户信息

    } else {
        return 0;
    }

    return a.exec();
}
