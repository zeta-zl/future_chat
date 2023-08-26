QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    widget.cpp \
    ../database/database_operations/database_operations.cpp \
    ../database/database_operations/database_operations_linux.cpp \
    ../database/database_operations/database_operations_windows.cpp \
    ../database/database_operations/init_database.cpp \
    ../database/database_operations/test_database.cpp \
    ../database/database_operations/test_database_operations.cpp \
    ../database/sqlite_functions/sqlite3.c

HEADERS += \
    login.h \
    widget.h \
    ../database/database_operations/database_operations.h \
    ../database/sqlite_functions/sqlite3.h

FORMS += \
    login.ui \
    server.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    old.qrc \
    resource.qrc

DISTFILES += \
    ../database/database_files/furure_chat.db \
    ../database/database_files/furure_chat_server.db
