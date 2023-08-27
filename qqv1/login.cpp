#include "login.h"
#include "ui_login.h"
#include "widget.h"
#include <QIcon>
#include <QToolButton>
#include "../database/database_operations/database_operations.h"

login::login(QString name, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    string db_path = "future_chat.db";
    DataBase db = DataBase(db_path);

//    vector<vector<string>> v_s_res = get_all_data_from_table( db, "user_info" );
//    for ( auto& i : v_s_res ) {
//        for ( auto& j : i ) {
//            qDebug() << j.c_str() << " ";
//        }
//        qDebug() << endl;
//    }
    string sql;
    sql = "select * from user_info";
    sql = "SELECT name FROM sqlite_master WHERE type='table' order by name";
    auto s_res = SelectResult();
    s_res.executeSelect( db, sql );
    s_res.check_result();
    cout<<s_res.row<<" "<<s_res.column<<endl;
    for ( int i = 0; i < s_res.row; i++ ) {
        for ( int j = 0; j < s_res.column; j++ ) {
            cout << s_res.data[i][j] << " ";
        }
        cout << endl;
    }
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
      btn->setText(QString("qq v1 copy"));
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
          //Widget(QWidget *parent, QString targetname, int targetid, QString clientname, int clientid);
          Widget *widget = new Widget(nullptr,toolbuttons[i]->text(),2,"qq v1",1);
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
