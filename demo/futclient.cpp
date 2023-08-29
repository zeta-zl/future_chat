#include "futclient.h"
#include "userinfo.h"

#include<QTcpSocket>
#include<QString>
#include<QQuickItem>
#include<QJsonArray>

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
    receivemsg();
    // 登录
    QObject::connect(root,SIGNAL(loginSignal(QString,QString)),this,SLOT(loginfunc(QString,QString)));
    // 注册
    QObject::connect(root,SIGNAL(regSignal(QString,QString)),this,SLOT(regfunc(QString,QString)));
    // 请求聊天历史记录，创建mainpage
    QObject* MainPage=root->findChild<QObject*>("MainPage_object");
    qDebug()<<"构造函数中MainPage"<<MainPage;
    QObject::connect(root,SIGNAL(requestHistoryMessage(int)),this,SLOT(setHistoryfunc(int)));
<<<<<<< HEAD
=======
    // 添加好友
    QObject::connect(root,SIGNAL(addFriendSignal(QString,QString)),this,SLOT(addFriendfunc(QString,QString)));
    // 返回消息
    QObject::connect(root,SIGNAL(sendChatMessageSignal(QString,QString,QString,QString,QString)),\
                     this,SLOT(sendChatMessagefunc(QString,QString,QString,QString,QString)));
>>>>>>> ea1cff82de0dd0d2ef882c5adb1fe13f5c9c425e
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
        parsecommand(jsonDoc);
    });
}

void FutClient::parsecommand(QJsonDocument jsonDoc){
    QJsonObject jsonData = jsonDoc.object();
    QString request = jsonData["request"].toString();
    if (request=="loginBack"){
        loginBack(jsonData);
    } else if(request=="registerBack"){
        registerBack(jsonData);
    } else if(request=="add_friend"){
        addFriendBack(jsonData);
    } else if(request=="setHistoryBack"){
        setHistoryBack(jsonData);
    } else if(request=="sendChatMessageBack"){
        sendChatMessageBack(jsonData);
    }
}
//登录
void FutClient::loginfunc(QString id, QString pwd){
    QJsonObject jsonobj;
    jsonobj["request"]="login";
    jsonobj["clientId"]=id;
    jsonobj["password"]=pwd;
    QString jsonstring=QJsonDocument(jsonobj).toJson();
    sendmsg(jsonstring);
}
void FutClient::loginBack(QJsonObject jsondata){
    bool result=jsondata["result"].toBool();
    QString name=jsondata["userName"].toString();
    if(!result){
        clientid=-1;
    }else{
        int id=jsondata["clientId"].toInt();
        //其他函数调用clientid
        clientid=id;
    }
    //调用QML函数
    QVariant res;
    QMetaObject::invokeMethod(root,"loginBack",Q_RETURN_ARG(QVariant,res),Q_ARG(QVariant,result),Q_ARG(QVariant,name));
}
//注册
void FutClient::regfunc(QString name,QString pwd){
        QJsonObject jsonobj;
        jsonobj["request"]="register";
        jsonobj.insert("clientId",-1); //未注册用户发送的数据包ID默认为随机非正数，传一个随机负数就行
        jsonobj.insert("userName",name);
        jsonobj.insert("password",pwd);
        QString jsonstring=QJsonDocument(jsonobj).toJson();
        sendmsg(jsonstring);
}

void FutClient::registerBack(QJsonObject jsondata){
    bool id=jsondata["clientId"].toInt();
    //调用QML函数
    QVariant res;
    QMetaObject::invokeMethod(root,"registerBack",Q_RETURN_ARG(QVariant,res),Q_ARG(QVariant,id));
}


//初始化历史消息界面
void FutClient::setHistoryfunc(int userid){
    QJsonObject jsonobj;
    jsonobj["request"] = "setHistory";
    jsonobj["clientId"] = userid;
    QString jsonstring=QJsonDocument(jsonobj).toJson();
    sendmsg(jsonstring);
}

void FutClient::setHistoryBack(QJsonObject jsondata){
    QJsonArray jsonArray=jsondata["messages"].toArray();
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject obj = jsonArray[i].toObject();
        QString targetid=obj["targetId"].toString();
        qDebug()<<"targetid"<<targetid;
        bool targetType=obj["targetType"].toBool();
        QString targetName=obj["targetName"].toString();
        qDebug()<<"targetName"<<targetName;
        QString avatar=obj["avatar"].toString();
        QString message=obj["message"].toString();
        QString msgSender=obj["msgSender"].toString();
        QString timestamp=obj["msgTime"].toString();
        //调用QML函数
        QVariant res;
        QObject* MainPage=root->findChild<QObject*>("MainPage_object");
        qDebug()<<"MainPage"<<MainPage;
        QMetaObject::invokeMethod(MainPage,"setHistoryBack",Q_RETURN_ARG(QVariant,res),Q_ARG(QVariant,targetName),Q_ARG(QVariant,avatar),Q_ARG(QVariant,message),Q_ARG(QVariant,msgSender),Q_ARG(QVariant,timestamp));
    }
}

//搜索陌生人
void FutClient::searchStrangerfunc(QString targetid,QString curid){
    QJsonObject jsonobj;
    jsonobj["request"]="addStranger";
    jsonobj["clientId"]=curid;
    jsonobj["targetId"]=targetid;
    QString jsonstring=QJsonDocument(jsonobj).toJson();
    sendmsg(jsonstring);
    qDebug()<<jsonstring;
}

void FutClient::addFriendfunc(QString friendId, QString verificationInfo = "") {
       QJsonObject jsonobj;
       jsonobj["request"] = "add_friend";
       jsonobj["friend_id"] = friendId;
       jsonobj["verification_info"] = verificationInfo;

       QString jsonstring = QJsonDocument(jsonobj).toJson();
       sendmsg(jsonstring);
   }

void FutClient::addFriendBack(QJsonObject jsondata){
    bool id=jsondata["result"].toInt();
    //调用QML函数
    QVariant res;
    QMetaObject::invokeMethod(root,"addFriendBack",Q_RETURN_ARG(QVariant,res),Q_ARG(QVariant,id));
}

void FutClient::sendChatMessagefunc(QString clientId, QString targetId, QString targetType, QString content, QString time) {
    QJsonObject jsonobj;
    jsonobj["request"] = "sendChatMessage";
    jsonobj["clientId"] = clientId;
    jsonobj["targetId"] = targetId;
    jsonobj["targetType"] = targetType;
    jsonobj["content"] = content;
    jsonobj["time"] = time;

    QString jsonstring = QJsonDocument(jsonobj).toJson();
    qDebug()<<jsonstring.toStdString().c_str();
    sendmsg(jsonstring);
}

void FutClient::sendChatMessageBack(QJsonObject jsondata) {
    QString groupId = jsondata["groupId"].toString();
    QString sendId = jsondata["sendId"].toString();
    QString content = jsondata["content"].toString();
    QString time = jsondata["time"].toString();

    // Call QML function
    QVariant res;
    QMetaObject::invokeMethod(root, "sendChatMessageBack", Q_RETURN_ARG(QVariant, res),
                              Q_ARG(QVariant, groupId), Q_ARG(QVariant, sendId),
                              Q_ARG(QVariant, content), Q_ARG(QVariant, time));
}






