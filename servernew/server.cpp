#include "server.h"
#include "ui_server.h"

#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>

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
                qDebug()<<jsonData;
            }
        }
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
