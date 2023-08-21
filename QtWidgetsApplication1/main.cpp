#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QWidget>

#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    QPushButton button( "Quit" );
    QObject::connect( &button, &QPushButton::clicked,
        &app, &QApplication::quit );
    button.show();
    return app.exec();
}
