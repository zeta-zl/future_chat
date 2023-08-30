#ifndef FUTCLIENT_H
#define FUTCLIENT_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QHostAddress>
#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include <QDateTime>
#include <iostream>


class FutClient:public QObject
{
    Q_OBJECT
public:
    FutClient(QQmlApplicationEngine *engine, QObject *parent);
    void sendmsg(QString msg);
    void receivemsg();
    void parsecommand( QJsonDocument jsonDoc );
    void printNodeNames(QObject* item);
    void mainpageconnect(QObject* mainpage);

    //c++ -> qml
    void loginBack( QJsonObject jsondata );
    void registerBack( QJsonObject jsondata );
    void addFriendBack( QJsonObject jsondata );
    void setHistoryBack( QJsonObject jsondata );
    void sendChatMessageBack(QJsonObject jsondata);
    void createChatPageBack(QJsonObject jsondata);

private:
    //前端通信engine
    QQmlApplicationEngine* engine=NULL;
    QObject* root=NULL;
    //端口 IP
    QTcpSocket* m_tcpsocket;
    quint16 m_port;
    QHostAddress m_ip;
    //用户信息
    int clientid = -1;
    //指针
    QObject* addPage;

private slots:
    void loginfunc(QString id,QString pwd);
    void regfunc(QString name,QString pwd);
    void addFriendfunc( QString friendId, QString verificationInfo );
    void setHistoryfunc( int userid );
    void searchStrangerfunc(QString targetid,QString curid);
    void sendChatMessagefunc(QString clientId, QString targetId, QString targetType, QString content, QString time) ;
    void createAddPagefunc();
    void createChatPagefunc(QString clientId, QString targetId, QString targetType);

};

#endif // FUTCLIENT_H
