#include "login.h"
#include "ui_login.h"
#include "widget.h"
#include <QIcon>
#include <QToolButton>
#include <QMap>

login::login(QString name, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    clientname = name;
    clientid = id;
    // 设置图标
    // 路径： 冒号+前缀+路径
    this->setWindowIcon(QIcon(":/images/QQ.png"));
    // 设置名称
    this->setWindowTitle("mychat");
    QVector< QToolButton *> toolbuttons;
    //QVector< Widget *> widgetlist;
    QMap<int, Widget *> widgetmap;
    for (int i=0;i<9;i++) {
      QToolButton *btn = new QToolButton(this);
      //加载图标
      //btn->setIcon(QPixmap(QString(":/images/%1.png").arg(iconNamelist[i])))
      btn->setIcon(QPixmap(":/images/user_man.png"));
      //设置图片大小
      btn->setIconSize(QPixmap(":/images/user_man.png").size());
      //设置网名
      btn->setText(QString("user1"));
      //设置透明
      btn->setAutoRaise(true);
      //设置显示格式
      btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
      //放到vlayout格式中
      ui->vlayout->addWidget(btn);
      toolbuttons.push_back(btn);
      IsShow.push_back(false);
    };
    for(int i=0;i<9;i++){
      connect(toolbuttons[i],&QToolButton::clicked,
              [=]()mutable{
          if(IsShow[i]){
              widgetmap[i]->showNormal();
              widgetmap[i]->activateWindow();
              return;
          }
          // 传入id 唯一标识符
          Widget *widget = new Widget(nullptr,toolbuttons[i]->text(),2,"jieshou",1);
          widget->setWindowIcon(toolbuttons[i]->icon());
          widget->setWindowTitle(toolbuttons[i]->text());
          widget->show();
          //widgetlist.push_back(widget);
          widgetmap.insert(i,widget);
          IsShow[i] = true;
          connect(widget,&Widget::closeWidget,this,[=]{
              IsShow[i]=false;
          });
      });
    };
}

login::~login()
{
    delete ui;
}
