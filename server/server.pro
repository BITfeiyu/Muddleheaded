QT       += core gui
QT       += network
QT       += sql widgets

HEADERS += \ \
    database.h \
    headers.h \
    msgpack.h


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        database.cpp \
        main.cpp \
        msgpack.cpp \
        server.cpp

HEADERS += \
    server.h

FORMS += \

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
