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

private:
    //前端通信engine
    QQmlApplicationEngine* engine=NULL;
    QObject* root=NULL;
    //端口 IP
    QTcpSocket* m_tcpsocket;
    quint16 m_port;
    QHostAddress m_ip;

private slots:
    void loginfunc(QString id,QString pwd);
    void regfunc(QString name,QString pwd);


};

#endif // FUTCLIENT_H
