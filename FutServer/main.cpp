#include "futserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FutServer w;
    w.show();
    return a.exec();
}
