#ifndef MTCPSERVER_H
#define MTCPSERVER_H
#include <QtNetwork>
#include <QTcpServer>
#include <QList>
#include "mclientsocket.h"

class MTCPServer : public QTcpServer
{
    Q_OBJECT
public:
    MTCPServer(QObject* parent=0);
    ~MTCPServer();
signals:
    void updateServer(QString,int);

public slots:

    void disconnectClients(int);
    void startServerListen(quint16 port);
private slots:
    void slotUpdateClients(QString msg,int length);
private:
    void incomingConnection(qintptr handle);
public:
    QList<MClientSocket*> ClientList;

};

#endif // MTCPSERVER_H
