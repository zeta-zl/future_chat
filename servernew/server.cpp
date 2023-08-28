#include "server.h"
#include "ui_server.h"

#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//服务器端接口数量没有控制，未修复

server::server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    myport = 9999;
    //创建监听的服务器对象
    m_s = new QTcpServer(this);
    s_setListener();
    //等待客户端连接
    connect(m_s, &QTcpServer::newConnection,this,&server::handleNewConnection);
}

server::~server()
{
    for (QTcpSocket *clientSocket : clientSockets) {
           clientSocket->disconnectFromHost();
           clientSocket->deleteLater(); // 清理资源
       }
    delete ui;
}

void server::s_setListener(){
    unsigned short port = myport;
    //参数1绑定本地ip地址 参数2指定端口
    m_s->listen(QHostAddress::Any, port);
}


void server::handleNewConnection(){
    QTcpSocket *newClientSocket = m_s->nextPendingConnection();
    qDebug()<<"Client connected";
    //检测是否可以接受数据
    connect(newClientSocket,&QTcpSocket::readyRead,this,[=](){handleReadyRead(newClientSocket);});
    // 存储服务器对客户端的socket
    clientSockets.append(newClientSocket);
    qDebug()<<"服务器端接口数量："<<clientSockets.size();
}

void server::handleReadyRead(QTcpSocket *newClientSocket)
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<"客户端接口"<<clientSocket;
    while (newClientSocket->bytesAvailable()) {
            QByteArray data = newClientSocket->readAll();
            // 将接收到的 JSON 数据解析为对象
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                QJsonObject jsonData = jsonDoc.object();
                //QString message = jsonData.toString();
                qDebug()<<jsonData["request"].toString();
                if(jsonData["request"].toString()=="setHistory"){
                    qDebug()<<"正确启动";
                    QJsonObject jsonObj;
                    jsonObj.insert("targetld", 1); // 分配的id
                    jsonObj.insert("targetType",true);//注册成功与否
                    jsonObj.insert("targetName","<_>");
                    jsonObj.insert("avatar","./");
                    jsonObj.insert("message","这是一条消息");
                    jsonObj.insert("msgSender","大黄");
                    jsonObj.insert("msgTime","19:20:21");

                    QJsonObject jsonObj1;
                    jsonObj1.insert("targetld", 1); // 分配的id
                    jsonObj1.insert("targetType",true);//注册成功与否
                    jsonObj.insert("targetName","生于未来");
                    jsonObj1.insert("avatar","./");
                    jsonObj1.insert("message","这是一条消息");
                    jsonObj1.insert("msgSender","大黄");
                    jsonObj1.insert("msgTime","19:20:21");

                    QJsonArray jsonArray;
                    jsonArray.append(jsonObj);
                    jsonArray.append(jsonObj1);

                    QJsonObject sendobj;
                    sendobj.insert("request","setHistoryBack");
                    sendobj.insert("messages",jsonArray);

                    QString jsonstring=QJsonDocument(sendobj).toJson();
                    clientSocket->write(jsonstring.toUtf8());
                }else if(jsonData["request"].toString()=="login"){
                    qDebug()<<"正确启动";
                    QJsonObject jsonObj;
                    jsonObj.insert("request","loginBack"); //反馈类型
                    jsonObj.insert("id", 1); // 分配的id
                    jsonObj.insert("result",true);//注册成功与否
                    QString jsonstring=QJsonDocument(jsonObj).toJson();
                    clientSocket->write(jsonstring.toUtf8());
                }
            }
        }
//    QJsonObject jsonObj;
//    jsonObj.insert("request","registerBack"); //反馈类型
//    jsonObj.insert("id", 1); // 分配的id
//    jsonObj.insert("result",false);//注册成功与否
//    QString jsonstring=QJsonDocument(jsonObj).toJson();
//    clientSocket->write(jsonstring);
}





//void server::cleanupServerSocket(int client_id){
//    if (clientSockets.contains(client_id)) {
//        QTcpSocket *clientSocket = clientSockets.value(client_id);
//        clientSocket->disconnectFromHost();
//        clientSocket->deleteLater(); // 清理资源
//        clientSockets.remove(client_id);
//        qDebug() << "ServerSocket with ID" << client_id << "removed";
//    }
//}
