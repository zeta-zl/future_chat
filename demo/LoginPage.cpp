#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    // 设置Qt应用程序属性，启用高DPI缩放
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    // 创建了一个QQmlApplicationEngine类的实例，用于加载和运行QML（Qt Meta-Object Language）界面
    QQmlApplicationEngine engine;
    // 指定资源文件
    const QUrl url(QStringLiteral("qrc:/StartPage.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
