#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent, QString targetname, int targetid, QString clientname, int clientid);
    void c_connectServer();
    void start();

    //重写关闭事件
    void closeEvent(QCloseEvent *);
    ~Widget();

signals:
    void closeWidget();
    void chatWindowClosed(int clientid);

private slots:
    void on_sendBtn_clicked();
    void on_backBtn_clicked();

private:
    Ui::Widget *ui;
    //用户唯一标示符
    int targetid;
    QString targetname;
    int clientid;
    QString clientname;
    //套接字
    QTcpSocket* m_tcp;
    //port与ip
    int m_port;
    QString m_ip;
};
#endif // WIDGET_H
