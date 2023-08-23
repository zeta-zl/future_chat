QT += core gui #模块的名字
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = test #应用程序名
TEMPLATE = app #生成的 makefile 的模板类

#源文件
#SOURCES += main.cpp\
#mainwindow.cpp
##头文件
#HEADERS += mainwindow.h
##窗口设计文件
#FORMS += mainwindow.u

SOURCES += \
    test1.cpp \
    qtwidgetsapplication3.cpp

FORMS += \
    QtWidgetsApplication3/QtWidgetsApplication3.ui

HEADERS += \
    QtWidgetsApplication3.h

RESOURCES +=\
    future_chat/QtWidgetsApplication3/QtWidgetsApplication3.qrc
