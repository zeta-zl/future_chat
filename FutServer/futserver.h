#ifndef FUTSERVER_H
#define FUTSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "./database/sqlite_functions/sqlite3.h"
#include "./database/database_operations/database_operations.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FutServer; }
QT_END_NAMESPACE

class FutServer : public QWidget
{
    Q_OBJECT

public:
    explicit FutServer(QWidget *parent = nullptr);
    ~FutServer();

private:
    Ui::FutServer *ui;
    quint16 listenPort; // 监听端口号
    QTcpServer* myServer; // 服务器对象
    QMap<int, QTcpSocket*> clientMap; // 存储在线用户Map Id-Socket
    QMap<int, QJsonObject*> clientMessages;
    DataBase db;
    // 处理新客户端socket通信连接
    void handleNewConnection();
    // 处理客户端断连
    void clientDisconnect();
    // 对客户端请求进行响应
    void handleReadyRead(QTcpSocket *newClientSocket);
    // 数据包通信解析
    void parseRequest(QJsonObject jsonData);

    // 根据用户ID查找相应socket
    QTcpSocket* getSocketById(int id);

    // 对请求进行反馈
    void respondToClient(QJsonObject jsonData, QTcpSocket* targetSocket);
    // 具体请求的反馈
    void registerRespond(QJsonObject jsonData);
    void loginRespond(QJsonObject jsonData);
    void setHistoryRespond(QJsonObject jsonData);
    void sendChatMessageRespond(QJsonObject jsonData);
    void initChatWindowRespond(QJsonObject jsonData);
    void createAddPageRespond(QJsonObject jsonData);
    void setFriendsRespond(QJsonObject jsonData);
    void addStrangerRespond(QJsonObject jsonData);
    void confirmAddStrangerRespond(QJsonObject jsonData);

    // 一些数据库操作
    QJsonObject addAccount(QString userName, QString password);
    QJsonObject confirmLogin(int clientId, QString password);
    QJsonObject loadMessageList(int clientId);
    void setFriendsGroupsList(int clientId, QJsonArray messages);
    QJsonObject saveMessage(int clientId, int targetId, bool targetType, QString content, QString time);
    QList<int> getGroupMemberList(int groupId);
    QJsonObject getHistoryMessage(int clientId, int targetId, bool targetType);
    QJsonObject getTargetMessageList(int clientId, bool targetType);
    QJsonObject searchUser(int targetId);
    QJsonObject confirmAdd(int clientId, int targetId);

};
#endif // FUTSERVER_H
