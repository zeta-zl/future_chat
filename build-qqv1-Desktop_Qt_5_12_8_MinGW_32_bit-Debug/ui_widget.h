/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolButton_5;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_6;
    QToolButton *toolButton_4;
    QTextBrowser *TextRecord;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *msgTextEdit;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *backBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *sendBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(670, 527);
        verticalLayout_4 = new QVBoxLayout(Widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_3 = new QWidget(Widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        toolButton_5 = new QToolButton(widget_5);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_5->setIcon(icon);

        horizontalLayout_4->addWidget(toolButton_5);

        horizontalSpacer_5 = new QSpacerItem(184, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        lineEdit = new QLineEdit(widget_5);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);

        horizontalSpacer_6 = new QSpacerItem(184, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        toolButton_4 = new QToolButton(widget_5);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/more.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon1);

        horizontalLayout_4->addWidget(toolButton_4);


        verticalLayout->addWidget(widget_5);

        TextRecord = new QTextBrowser(widget);
        TextRecord->setObjectName(QString::fromUtf8("TextRecord"));

        verticalLayout->addWidget(TextRecord);


        verticalLayout_3->addWidget(widget);

        frame_2 = new QFrame(widget_3);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(frame_2);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/emoji.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon2);

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(frame_2);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/files.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon3);

        horizontalLayout->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(frame_2);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon4);

        horizontalLayout->addWidget(toolButton_3);

        horizontalSpacer = new QSpacerItem(172, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(frame_2);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        msgTextEdit = new QTextEdit(widget_2);
        msgTextEdit->setObjectName(QString::fromUtf8("msgTextEdit"));

        verticalLayout_2->addWidget(msgTextEdit);


        verticalLayout_3->addWidget(widget_2);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(146, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        backBtn = new QPushButton(widget_4);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout_2->addWidget(backBtn);

        horizontalSpacer_3 = new QSpacerItem(147, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        sendBtn = new QPushButton(widget_4);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));

        horizontalLayout_2->addWidget(sendBtn);

        horizontalSpacer_4 = new QSpacerItem(146, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(widget_4);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_4->addWidget(widget_3);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        toolButton_5->setText(QApplication::translate("Widget", "...", nullptr));
        toolButton_4->setText(QApplication::translate("Widget", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("Widget", "\345\233\276\347\211\207", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton->setText(QApplication::translate("Widget", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton_2->setToolTip(QApplication::translate("Widget", "\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_2->setText(QApplication::translate("Widget", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton_3->setToolTip(QApplication::translate("Widget", "\350\241\250\346\203\205", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_3->setText(QApplication::translate("Widget", "...", nullptr));
        backBtn->setText(QApplication::translate("Widget", "\345\217\226\346\266\210", nullptr));
        sendBtn->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
#ifndef QT_NO_SHORTCUT
        sendBtn->setShortcut(QApplication::translate("Widget", "Return", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
