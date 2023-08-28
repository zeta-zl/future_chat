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
    void parsecommand(QJsonDocument jsonDoc);

    //c++ -> qml
    void loginBack(QJsonObject jsondata);
    void registerBack(QJsonObject jsondata);
    void addFriendBack(QJsonObject jsondata);

private:
    //前端通信engine
    QQmlApplicationEngine* engine=NULL;
    QObject* root=NULL;
    //端口 IP
    QTcpSocket* m_tcpsocket;
    quint16 m_port;
    QHostAddress m_ip;
    //用户信息
    int clientid=-1;

private slots:
    void loginfunc(QString id,QString pwd);
    void regfunc(QString name,QString pwd);
    void addFriendfunc(QString friendId, QString verificationInfo) ;


};

#endif // FUTCLIENT_H
