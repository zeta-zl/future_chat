#include "widget.h"
#include "login.h"
#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();
    Widget w(NULL,"temp",1,"ljy",2);
    w.show();
//    login l("name",1);
//    l.show();

    return a.exec();
}
