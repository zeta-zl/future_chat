/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QVBoxLayout *verticalLayout_3;
    QToolBox *toolBox;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *vlayout;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(300, 700);
        verticalLayout_3 = new QVBoxLayout(login);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 9);
        toolBox = new QToolBox(login);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 300, 669));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(page_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        vlayout = new QVBoxLayout(widget);
        vlayout->setObjectName(QString::fromUtf8("vlayout"));
        vlayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(widget);

        toolBox->addItem(page_2, QString::fromUtf8("\346\266\210\346\201\257"));

        verticalLayout_3->addWidget(toolBox);


        retranslateUi(login);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Form", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("login", "\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
