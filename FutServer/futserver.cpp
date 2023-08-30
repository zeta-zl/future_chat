#include "futserver.h"
#include "ui_futserver.h"

#include <QJsonDocument>
#include <QJsonObject>

string init_sql_server =
"CREATE TABLE IF NOT EXISTS friend_message_library ( \
id INTEGER PRIMARY KEY AUTOINCREMENT,\
client_account INTEGER NOT NULL,\
friend_account INTEGER NOT NULL,\
time TIMESTAMP NOT NULL,\
type INTEGER,\
content TEXT,\
status INTEGER\
);\
CREATE TABLE IF NOT EXISTS group_message_library ( \
id INTEGER PRIMARY KEY AUTOINCREMENT,\
group_account INTEGER NOT NULL,\
sender_account INTEGER NOT NULL,\
time TIMESTAMP NOT NULL,\
type INTEGER,\
content TEXT,\
status INTEGER\
);\
CREATE TABLE IF NOT EXISTS user_info (\
account INTEGER PRIMARY KEY AUTOINCREMENT,\
password TEXT NOT NULL,\
user_name VARCHAR( 255 ) NOT NULL,\
avatar_path TEXT DEFAULT 'https://c-ssl.duitang.com/uploads/blog/201408/15/20140815095903_ttcnF.jpeg',\
signature TEXT,\
gender VARCHAR( 20 ),\
birthday DATE,\
location TEXT,\
education_experience TEXT\
);\
CREATE TABLE IF NOT EXISTS user_friends (\
client_account INTEGER,\
friend_account INTEGER,\
friend_nickname VARCHAR( 255 ),\
add_time TIMESTAMP,\
status INTEGER,\
PRIMARY KEY( client_account, friend_account )\
);\
CREATE TABLE IF NOT EXISTS group_info (\
group_account INTEGER PRIMARY KEY AUTOINCREMENT,\
group_owner_account INTEGER NOT NULL,\
name VARCHAR( 255 ) NOT NULL,\
group_avatar_path TEXT DEFAULT 'https://c-ssl.duitang.com/uploads/blog/201408/15/20140815095903_ttcnF.jpeg'\
);\
CREATE TABLE IF NOT EXISTS group_members (\
group_account INTEGER NOT NULL,\
member_account INTEGER NOT NULL,\
position TEXT,\
join_time TIMESTAMP,\
PRIMARY KEY( group_account, member_account )\
);\
CREATE TABLE IF NOT EXISTS ip_library (\
account INTEGER PRIMARY KEY,\
ip VARCHAR( 255 )\
);\
";

string db_path = "future_chat1.db";

static int init_database( DataBase& db ) {
    char* error_mes = nullptr;
    int error_code = sqlite3_exec( db, init_sql_server.c_str(), 0, 0, &error_mes );
    if ( error_code == SQLITE_OK ) {
        fprintf( stdout, "Init successed\n" );
        return 1;
    }
    else {
        fprintf( stderr, "Init failed:%d %s\n", error_code, error_mes );
        return 0;
    }
}

FutServer::FutServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FutServer)
    , db(DataBase(db_path))
{
    //初始化数据库
    init_database( db );

    ui->setupUi(this);
    //监听端口
    listenPort = 8899;
    //创建服务器对象
    myServer = new QTcpServer(this);
    myServer->listen(QHostAddress::Any, listenPort);
    //等待客户端连接
    connect(myServer, &QTcpServer::newConnection,this,&FutServer::handleNewConnection);
}

FutServer::~FutServer()
{
    QMapIterator<int, QTcpSocket*> iterator(clientMap);
    while (iterator.hasNext()) {
        iterator.next();
        iterator.value()->disconnectFromHost();
        iterator.value()->deleteLater(); // 清理资源
    }
    // 清理map
    clientMap.clear();
    delete ui;
}


void FutServer::handleNewConnection()
{
    QTcpSocket *newClientSocket = myServer->nextPendingConnection();

    qDebug()<<"New Connection";

    // 客户端提交请求
    connect(newClientSocket,&QTcpSocket::readyRead,this,[=](){handleReadyRead(newClientSocket);});
    // 客户端断开连接
    connect(newClientSocket, &QTcpSocket::disconnected,this,&FutServer::clientDisconnect);
}


void FutServer::clientDisconnect()
{
    QTcpSocket* dyingTcpSocket = static_cast<QTcpSocket*>(sender());
    int dyingId = clientMap.key(dyingTcpSocket);

    qDebug()<<"client: "<<dyingId <<" disconnect!";

    dyingTcpSocket->deleteLater();
    // 更新在线用户
    clientMap.remove(dyingId);

    qDebug() << "当前在线人数： "<<clientMap.size();

}


void FutServer::handleReadyRead(QTcpSocket *newClientSocket)
{
    while (newClientSocket->bytesAvailable()){
        // 读取数据包
        QByteArray data = newClientSocket->readAll();
        // 将接收到的数据解析为Json对象
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonData = jsonDoc.object();

            // 用户ID
            int client_id = jsonData["clientId"].toInt();
            // 用户请求类型
            QString request= jsonData["request"].toString();

            // 对应下线又上线(理论上应该不会发生此情况：在用户下线时已经清理了对应的记录。后续可删除此段代码）
            if (clientMap.contains(client_id) && clientMap.value(client_id)!= newClientSocket)
            {
                // 如果之前已经存储过这个 client_id 的连接且客户端接口变化，替换为新的连接
                QTcpSocket *oldClientSocket = clientMap.value(client_id);
                oldClientSocket->deleteLater(); // 关闭并删除之前的连接
                clientMap[client_id] = newClientSocket; // 存储新的连接

                qDebug()<<"Client ID:"<<client_id<<" 重新上线";

            }
            // 对应首次上线
            else if (!clientMap.contains(client_id))
            {
                // 如果之前没有存储过这个 client_id 的连接，直接存储新的连接
                clientMap.insert(client_id, newClientSocket);
                if(client_id == -1){
                    qDebug()<<"有未注册用户连接服务器";
                }
                else{
                    qDebug()<<"Client ID:"<<client_id<<" 上线";
                }
                int userNum = clientMap.size();
                if(clientMap.contains(-1)){
                    userNum--;
                }
                qDebug()<<"当前在线人数："<< userNum;
            }

            qDebug() << "Client ID:" << client_id << " Request：" << request;
            // 处理请求
            FutServer::parseRequest(jsonData);
        }
    }
}

void FutServer::parseRequest(QJsonObject jsonData)
{
    //解析命令
    QString request=jsonData["request"].toString();

    if (request=="register") //注册
    {
        registerRespond(jsonData);
    }
    else if(request=="login")//登录
    {
        loginRespond(jsonData);
    }
    else if(request=="setHistory")
    {
        setHistoryRespond(jsonData);
    }
    else if(request=="sendChatMessage")//发消息
    {
        sendChatMessageRespond(jsonData);
    }
    else if(request=="initChatWindow")
    {
        initChatWindow(jsonData);
    }
    else if(request=="search")//查找群/人
    {
//        searchRespond
    }
    else if(request=="add")//添加
    {
//        addRespond
    }
    else if(request=="createGroup")//拉群
    {
//        createGroupRespond
    }
    else if(request=="delete")//删除
    {
//        deleteRespond
    }
    else if(request=="friendRequest")//好友列表
    {
//        friendRespond
    }
    else if(request=="groupRequest")//群列表
    {
//        groupRespond
    }
    else if(request=="messageRequest")//历史消息
    {
//        messageRespond
    }
    else if(request=="personInfoRequest")//查找个人信息
    {
//        getPersonalInfoRespond
    }
    else if(request=="groupInfoRequest")//查找群信息
    {
//        getGroupInfoRespond
    }
    else if(request=="changePInfoRequest")//更新个人信息
    {
//        changePInfo
    }
    else if(request=="changeGInfoRequest")//更新群信息
    {
//        changeGInfo
    }
    else
    {
        //未知命令
//        sendMessage
    }
}

QTcpSocket *FutServer::getSocketById(int id)
{
    return clientMap.value(id);
}

void FutServer::respondToClient(QJsonObject jsonData, QTcpSocket* targetSocket)
{
    QJsonDocument jsonDoc(jsonData);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    // 将JSON字符串 转化为 QString 并通过Socket进行通信传输
    targetSocket->write(jsonString.toUtf8());
}



// 以下，为具体请求的反馈操作
// 注册
void FutServer::registerRespond(QJsonObject jsonData)
{
    //解析
    int clientId = jsonData["clientId"].toInt(); // 未注册用户发送的数据包ID默认为随机非正数
    QString userName = jsonData["userName"].toString();
    QString password = jsonData["password"].toString();

    if (clientMap.contains(clientId))
    {
        QTcpSocket *targetSocket = getSocketById(clientId);
        QJsonObject jsonResult = addAccount(userName, password);
        respondToClient(jsonResult, targetSocket);
    }
    else{
        qDebug()<< "用户离线";
    }
}



// 登录
void FutServer::loginRespond(QJsonObject jsonData)
{
    //解析
    int clientId = jsonData["clientId"].toInt();
    QString password = jsonData["password"].toString();

    if (clientMap.contains(clientId))
    {
        QTcpSocket *targetSocket = getSocketById(clientId);
        QJsonObject jsonResult = confirmLogin(clientId, password);
        respondToClient(jsonResult, targetSocket);
    }
    else{
        qDebug()<< "用户离线";
    }
}


// 加载主界面消息列表
void FutServer::setHistoryRespond(QJsonObject jsonData)
{
    //解析
    int clientId = jsonData["clientId"].toInt();

    if (clientMap.contains(clientId))
    {
        QTcpSocket *targetSocket = getSocketById(clientId);
        QJsonObject jsonResult = loadMessageList(clientId);
        respondToClient(jsonResult, targetSocket);
    }
    else
    {
        qDebug()<< "用户离线";
    }
}



// 发消息
void FutServer::sendChatMessageRespond(QJsonObject jsonData)
{
    int clientId = jsonData["clientId"].toInt();
    int targetId = jsonData["targetId"].toInt();
    bool targetType = jsonData["targetType"].toBool();
    QString content  = jsonData["content"].toString();
    QString time = jsonData["time"].toString();

    // 保存聊天记录到数据库
    QJsonObject jsonResult = saveMessage(clientId, targetId, targetType, content, time);

    if(targetType) //私聊
    {
        // 若对方在线，则返回实时消息给接收方
        if(clientMap.contains(targetId))
        {
            QTcpSocket *targetSocket = getSocketById(targetId);
            respondToClient(jsonResult, targetSocket);
        }
    }
    else //群聊
    {
        // 获取该群聊的名单(注意：包括信息发送者)
        QList<int> idList = getGroupMemberList(targetId);
        for(int i = 0;i < idList.size();i++)
        {
            int receiver = idList.at(i);
            // 若对方在线，则返回实时消息给接收方(不包括信息发送者)
            if(clientMap.contains(receiver) && receiver != clientId)
            {
                QTcpSocket *targetSocket = getSocketById(receiver);
                respondToClient(jsonResult, targetSocket);
            }
        }
    }
}

void FutServer::initChatWindow(QJsonObject jsonData)
{
    int clientId = jsonData["clientId"].toInt();
    int targetId = jsonData["targetId"].toInt();
    bool targetType = jsonData["targetType"].toBool();


    if (clientMap.contains(clientId))
    {
        QTcpSocket *targetSocket = getSocketById(clientId);
        QJsonObject jsonResult = getHistoryMessage(clientId, targetId, targetType);
        respondToClient(jsonResult, targetSocket);
    }
    else
    {
        qDebug()<< "用户离线";
    }
}
