#include "qserverwidget.h"
#include "mtcpserver.h"
#include <QApplication>
#include <QThread>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QChat");
    a.setApplicationVersion("version_1.0");
    a.setOrganizationName("xidian_chenpan");

    QServerWidget w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();

    MTCPServer tcpServer;

    /***** init conections between tcpServer and w *****/
    QObject::connect(&w,SIGNAL(signal_start_server(quint16)),&tcpServer,SLOT(startServerListen(quint16)),Qt::QueuedConnection);
    QObject::connect(&tcpServer,SIGNAL(updateServer(QString,int)),&w,SLOT(slot_update_server(QString,int)),Qt::QueuedConnection);

    QThread serverThread;
    tcpServer.moveToThread(&serverThread);
    serverThread.start(QThread::NormalPriority);

    QFile qss(":/qss/default");
    qss.open(QFile::ReadOnly);
    if(qss.isOpen())
    {
        QString qss_content=qss.readAll();
     //   qDebug()<<qss_content;
        qApp->setStyleSheet(qss_content);
        qss.close();
    }
    return a.exec();
}
