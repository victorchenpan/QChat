#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T09:38:28
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QChatAPP
TEMPLATE = app


SOURCES += main.cpp\
        qserverwidget.cpp \
    mtcpserver.cpp \
    mclientsocket.cpp

HEADERS  += qserverwidget.h \
    mtcpserver.h \
    mclientsocket.h

RESOURCES += \
    src.qrc
