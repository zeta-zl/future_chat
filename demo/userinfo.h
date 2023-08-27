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
    // Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
public:
    userinfo();
    int getId();
    void setId(int id);
    QString getName();
    void setName(QString name);
    void parse(QJsonObject jsonobject);

private:
    int m_id;
    QString m_name;

signals:
    void idchanged();
    void namechanged();
};

#endif // USERINFO_H
