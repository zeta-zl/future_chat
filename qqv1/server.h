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
    void handleReadyRead();
    ~server();

private:
    Ui::server *ui;
    QTcpServer* m_s;
    QTcpSocket* m_tcp;
    int myport;
    QMap<int, QTcpSocket*> m_clientMap; // 存储客户端连接的哈希表
};

#endif // SERVER_H
