#include "futclient.h"
#include "userinfo.h"

#include<QTcpSocket>
#include<QString>
#include<QQuickItem>

FutClient::FutClient(QQmlApplicationEngine *engine, QObject *parent)
{
    //保存前端指针
    this->engine=engine;
    //Qt对象树结构,root是qml全局的根节点，root指向startpage
    this->root=engine->rootObjects().first();

    //端口 ip
    quint16 m_port=9999;
    m_ip=QHostAddress("127.0.0.1");
    m_tcpsocket=new QTcpSocket(this);
    m_tcpsocket->connectToHost(QHostAddress(m_ip),m_port);

    receivemsg();

    // 登录
    QObject::connect(root,SIGNAL(loginSignal(QString,QString)),this,SLOT(loginfunc(QString,QString)));
    // 注册
    QObject::connect(root,SIGNAL(regSignal(QString,QString)),this,SLOT(regfunc(QString,QString)));
    // 请求聊天历史记录，创建mainpage
    // QObject* mainwindow=root->findChild<QObject*>("mainPage_object");
    QObject::connect(root,SIGNAL(requestHistoryMessage(int)),this,SLOT(setHistoryfunc(int)));

}

//向服务器发送消息
void FutClient::sendmsg(QString msg){
    m_tcpsocket->write(msg.toUtf8());
}

//从服务器接受信息
void FutClient::receivemsg(){
    connect(m_tcpsocket,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = m_tcpsocket->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        qDebug()<<"客户端已接收信息:"<<jsonDoc;
        parsecommand(jsonDoc);
    });
}

void FutClient::parsecommand(QJsonDocument jsonDoc){
    QJsonObject jsonData = jsonDoc.object();
    QString request = jsonData["request"].toString();
    qDebug()<<"parsecommand request:"<<request;
    if (request=="loginBack"){
        loginBack(jsonData);
    } else if(request=="registerBack"){
        registerBack(jsonData);
    }
}

//登录
void FutClient::loginfunc(QString id, QString pwd){
    QJsonObject jsonobj;
    jsonobj["request"]="login";
    jsonobj["id"]=id;
    jsonobj["password"]=pwd;
    QString jsonstring=QJsonDocument(jsonobj).toJson();
    sendmsg(jsonstring);
}

void FutClient::loginBack(QJsonObject jsondata){
    bool result=jsondata["result"].toBool();
    if(!result){
        clientid=-1;
    }else{
        int id=jsondata["id"].toInt();
        //其他函数调用clientid
        clientid=id;
    }
    //调用QML函数
    QVariant res;
    QMetaObject::invokeMethod(root,"loginBack",Q_RETURN_ARG(QVariant,res),Q_ARG(QVariant,result));
}

//注册
void FutClient::regfunc(QString name,QString pwd){
        QJsonObject jsonobj;
        jsonobj["request"]="register";
        jsonobj.insert("id",-1); //未注册用户发送的数据包ID默认为随机非正数，传一个随机负数就行
        jsonobj.insert("userName",name);
        jsonobj.insert("password",pwd);
        QString jsonstring=QJsonDocument(jsonobj).toJson();
        sendmsg(jsonstring);
}

void FutClient::registerBack(QJsonObject jsondata){
    bool id=jsondata["id"].toInt();
    //调用QML函数
    QVariant res;
    QMetaObject::invokeMethod(root,"registerBack",Q_RETURN_ARG(QVariant,res),Q_ARG(QVariant,id));
}

//初始化历史消息界面
void FutClient::setHistoryfunc(int userid){
    qDebug()<<"setHistoryfunc"<<userid;
}




