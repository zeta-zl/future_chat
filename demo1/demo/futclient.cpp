#include "futclient.h"

#include<QTcpSocket>
#include<QString>
#include<QQuickItem>

FutClient::FutClient(QQmlApplicationEngine *engine, QObject *parent)
{
    //保存前端指针
    this->engine=engine;
    //Qt对象树结构,root是qml全局的根节点，root指向startpage
    this->root=engine->rootObjects().first();
    qDebug() << "root class:" << root->metaObject()->className();

    //端口 ip
    quint16 m_port=8899;
    m_ip=QHostAddress("127.0.0.1");
    m_tcpsocket=new QTcpSocket(this);
    m_tcpsocket->connectToHost(QHostAddress(m_ip),m_port);

    // 登录
    QObject::connect(root,SIGNAL(loginSignal(QString,QString)),this,SLOT(loginfunc(QString,QString)));
    // 注册
    QObject::connect(root,SIGNAL(regSignal(QString,QString)),this,SLOT(regfunc(QString,QString)));

}

//向服务器发送消息
void FutClient::sendmsg(QString msg){
    m_tcpsocket->write(msg.toUtf8());
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

//注册
void FutClient::regfunc(QString name,QString pwd){
        qDebug()<<"SIGNAL(regSignal(QString,QString))被唤起";
        QJsonObject jsonobj;
        jsonobj["request"]="register";
        jsonobj.insert("id",-1); //未注册用户发送的数据包ID默认为随机非正数，传一个随机负数就行
        jsonobj.insert("userName",name);
        jsonobj.insert("password",pwd);
        QString jsonstring=QJsonDocument(jsonobj).toJson();
        sendmsg(jsonstring);
}


