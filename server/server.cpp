#include "server.h"
#include "ui_server.h"

#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>

server::server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    myport = 8899;
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
    int id=0;
    //检测是否可以接受数据
    connect(newClientSocket,&QTcpSocket::readyRead,this,[=]()mutable{id=handleReadyRead(newClientSocket);});
    // 存储服务器对客户端的socket
    clientSockets.insert(id, newClientSocket);
    connect(newClientSocket, &QTcpSocket::disconnected, this, [=](){handleDisconnected(id);});
}

int server::handleReadyRead(QTcpSocket *newClientSocket)
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    int id;
    while (newClientSocket->bytesAvailable()) {
            QByteArray data = newClientSocket->readAll();
            // 将接收到的 JSON 数据解析为对象
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                QJsonObject jsonData = jsonDoc.object();
                int client_id = jsonData["client_id"].toInt();
                int target_client_id = jsonData["target_client_id"].toInt();
                QString message = jsonData["message"].toString();
                id = client_id;

                // 存储客户端连接
                if (!m_clientMap.contains(client_id)){
                    m_clientMap.insert(client_id, clientSocket);
                    qDebug()<<client_id<<"clientSocket已存储";
                }

                qDebug() << "Client ID:" << client_id;
                qDebug() << "Target Client ID:" << target_client_id;
                qDebug() << "Message:" << message;

                if(message == "start client"){
                    return id;
                }

                // 在此处可以根据目标客户 ID 发送消息给特定客户
                if (m_clientMap.contains(target_client_id))
                {
                    qDebug()<<"搜索到目标客户端";
                    QTcpSocket *targetSocket = m_clientMap.value(target_client_id);
                    targetSocket->write(message.toUtf8()); // 发送消息
                }
            }
        }
    return id;
}

void server::handleDisconnected(int id){
    cleanupClient(id);
    cleanupServerSocket(id);
}

void server::cleanupClient(int client_id) {
    if (m_clientMap.contains(client_id)) {
        QTcpSocket *clientSocket = m_clientMap.value(client_id);
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater(); // 清理资源
        m_clientMap.remove(client_id);
        qDebug() << "Client with ID" << client_id << "removed";
    }
}

void server::cleanupServerSocket(int client_id){
    if (clientSockets.contains(client_id)) {
        QTcpSocket *clientSocket = clientSockets.value(client_id);
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater(); // 清理资源
        clientSockets.remove(client_id);
        qDebug() << "ServerSocket with ID" << client_id << "removed";
    }
}
