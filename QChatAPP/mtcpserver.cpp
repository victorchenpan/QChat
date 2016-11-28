#include "mtcpserver.h"

MTCPServer::MTCPServer(QObject* parent):QTcpServer(parent)
{

}
MTCPServer::~MTCPServer()
{

}

void MTCPServer::incomingConnection(qintptr handle)
{
    MClientSocket* clientSocket=new MClientSocket(this);
    connect(clientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(slotUpdateClients(QString,int)));
    connect(clientSocket,SIGNAL(disconnected(int)),this,SLOT(disconnectClients(int)));

    clientSocket->setSocketDescriptor(handle);
    ClientList.append(clientSocket);
}
void MTCPServer::slotUpdateClients(QString msg,int length)
{
    emit updateServer(msg,length);
    for(int count=0;count<ClientList.size();++count)
    {
        QTcpSocket* socketItem=ClientList.at(count);
        if(socketItem->write(msg.toLatin1(),length)!=length)
            continue;
    }
}
void MTCPServer::startServerListen(quint16 port)
{
    if(this->listen(QHostAddress::AnyIPv4,port))
    {
        QString msg("Server is listenning...");
        emit updateServer(msg,msg.size());
    }
}
void MTCPServer::disconnectClients(int despt)
{
    QTcpSocket* item;
    for(int count=0;count<ClientList.size();++count)
    {
        item=ClientList.at(count);
        if(item->socketDescriptor()==despt)
        {
            ClientList.removeAt(count);
            return;
        }
    }
}
