#ifndef USERINFO_H
#define USERINFO_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QHostAddress>
#include <QUdpSocket>
#include <QQmlApplicationEngine>
#include <QDateTime>
#include <iostream>


class userinfo:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idchanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY namechanged)
    Q_PROPERTY(QString avatar READ getAvatar WRITE setAvatar NOTIFY avatarchanged)
public:
    userinfo();
    int getId();
    void setId(int id);
    QString getName();
    void setName(QString name);
    QString getAvatar();
    void setAvatar(QString path);
    void parse(QJsonObject jsonobject);

public:
    int m_id=-1;
    QString m_name="";
    QString m_avatar="test.png";

signals:
    void idchanged();
    void namechanged();
    void avatarchanged();
};

class User //储存用户信息
{
public:
    User(int id,QString name,QString icon)
    {
        this->id=id;
        this->name=name;
        this->icon=icon;
        qDebug()<<"构建User:"<<id<<name;
    }

    int id;
    QString name;
    QString icon;
};

class contactlist{
    public:
        QVector<User> contacts; // 定义users数组
};

#endif // USERINFO_H
