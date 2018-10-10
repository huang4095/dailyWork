#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T18:38:15
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = dailyWork
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../bin/DailyWork
PRECOMPILED_HEADER  = appInit/head.h

SOURCES     += main.cpp \
            SqlMag/connectpool.cpp \
            SqlMag/sqldatasource.cpp \
    DailyWorkPage/dailyworkpage.cpp \
    mainWidget.cpp \
    DailyProblemPage/dailyproblempage.cpp \
    DailyWorkPage/adddailyworkproduct.cpp \
    SettingPage/settingpage.cpp \
    SettingPage/adduserdialog.cpp \
    SettingPage/adddepartmentdialog.cpp \
    SettingPage/addproductlinedialog.cpp \
    logindialog.cpp \
    DailyWorkPage/adddailyready.cpp \
    appInit/TextEditDelegate.cpp \
    DailyWorkPage/attendanceadd.cpp \
    DailyWorkPage/addmaintaindialog.cpp \
    DailyWorkPage/addRejects.cpp \
    DailyProblemPage/adddailyproblemdialog.cpp

SOURCES     += appInit/quiwidget.cpp
SOURCES     += appInit/appinit.cpp
SOURCES     +=

HEADERS     += appInit/quiwidget.h \
               SqlMag/connectpool.h \
               SqlMag/sqldatasource.h \
    DailyWorkPage/dailyworkpage.h \
    mainWidget.h \
    DailyProblemPage/dailyproblempage.h \
    DailyWorkPage/adddailyworkproduct.h \
    SettingPage/settingpage.h \
    SettingPage/adduserdialog.h \
    SettingPage/adddepartmentdialog.h \
    SettingPage/addproductlinedialog.h \
    logindialog.h \
    DailyWorkPage/adddailyready.h \
    appInit/TextEditDelegate.h \
    DailyWorkPage/attendanceadd.h \
    DailyWorkPage/addmaintaindialog.h \
    DailyWorkPage/addRejects.h \
    DailyProblemPage/adddailyproblemdialog.h

HEADERS     += appInit/appinit.h
HEADERS     +=

FORMS       += \
    DailyWorkPage/dailyworkpage.ui \
    MainWidget.ui \
    DailyProblemPage/dailyproblempage.ui \
    DailyWorkPage/adddailyworkproduct.ui \
    SettingPage/settingpage.ui \
    SettingPage/adduserdialog.ui \
    SettingPage/adddepartmentdialog.ui \
    SettingPage/addproductlinedialog.ui \
    logindialog.ui \
    DailyWorkPage/adddailyready.ui \
    DailyWorkPage/attendanceadd.ui \
    DailyWorkPage/addmaintaindialog.ui \
    DailyWorkPage/addRejects.ui \
    DailyProblemPage/adddailyproblemdialog.ui

RESOURCES   += main.qrc
RESOURCES   += qss.qrc
CONFIG      += qt warn_off
INCLUDEPATH += $$PWD
