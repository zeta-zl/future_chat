#ifndef APPINFO_H
#define APPINFO_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "tool/IPC.h"
#include "lang/Lang.h"
#include "stdafx.h"

class AppInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,version)
    Q_PROPERTY_AUTO(Lang*,lang)
public:
    explicit AppInfo(QObject *parent = nullptr);
    void init(QQmlApplicationEngine *engine);
    bool isOwnerProcess(IPC *ipc);
    Q_INVOKABLE void changeLang(const QString& locale);
    Q_SIGNAL void activeWindow();
};

#endif // APPINFO_H
