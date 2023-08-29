#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

#include "futclient.h"

int main(int argc, char *argv[])
{
    // 设置Qt应用程序属性，启用高DPI缩放
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    userinfo curuser;
    // 创建了一个QQmlApplicationEngine类的实例，用于加载和运行QML（Qt Meta-Object Language）界面。
    QQmlApplicationEngine engine;
    QQmlContext* root = engine.rootContext();
    root->setContextProperty( "curuser", &curuser );

    // 指定资源文件
    const QUrl url(QStringLiteral("qrc:/StartPage.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    //C++后台通讯
    FutClient* futclient=new FutClient(&engine,&app);
    root->setContextProperty("FutClient",futclient);

    return app.exec();
}
