#include "mclientsocket.h"

MClientSocket::MClientSocket(QObject* parent):QTcpSocket(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

MClientSocket::~MClientSocket()
{

}

void MClientSocket::dataReceived()
{
    while(bytesAvailable()>0)
    {
     //   char buffer[1024];
        int length=bytesAvailable();
     //   read(buffer,length);

        QString msg(this->readAll());
        emit updateClients(msg,length);
    }
}
void MClientSocket::slotDisconnected()
{
    quint16 socketdesp=this->socketDescriptor();
    emit disconnected(socketdesp);
}
