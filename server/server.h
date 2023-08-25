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
    void handleReadyRead(QTcpSocket *newClientSocket);
    void cleanupServerSocket(int client_id);
    ~server();

private:
    Ui::server *ui;
    QTcpServer* m_s;
    //QMap<int, QTcpSocket*> clientSockets;  // 在服务器的头文件中定义一个私有成员变量来存储所有客户端的 QTcpSocket
    QList <QTcpSocket*> clientSockets;
    int myport;
    QMap<int, QTcpSocket*> m_clientMap; // 存储客户端连接的哈希表
};

#endif // SERVER_H
