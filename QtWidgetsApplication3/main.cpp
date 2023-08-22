#include "QtWidgetsApplication3.h"
#include <QtWidgets/QApplication>
#include "test2.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
    QApplication a(argc, argv);

    test2 w;
    w.show();
    return a.exec();
}
