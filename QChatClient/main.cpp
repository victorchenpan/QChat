#include "chatclient.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatClient w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();

    QFile qss(":/qss/default");
    qss.open(QFile::ReadOnly);
    if(qss.isOpen())
    {
        QString qssContent=qss.readAll();
        qApp->setStyleSheet(qssContent);
        qDebug()<<qssContent;
        qss.close();
    }
    return a.exec();
}
