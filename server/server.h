#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class server;
}

class server : public QWidget
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    void s_setListener();
    void s_sendMsg(QString msg);
    void handleNewConnection();
    int handleReadyRead(QTcpSocket *newClientSocket);
    void cleanupClient(int clientid);
    void cleanupServerSocket(int client_id);
    void handleDisconnected(int id);
    ~server();

private:
    Ui::server *ui;
    QTcpServer* m_s;
    QMap<int, QTcpSocket*> clientSockets;  // 在服务器的头文件中定义一个私有成员变量来存储所有客户端的 QTcpSocket
    int myport;
    QMap<int, QTcpSocket*> m_clientMap; // 存储客户端连接的哈希表

//private slots:
//    void handleChatWindowClosed(int client_id);
};

#endif // SERVER_H
