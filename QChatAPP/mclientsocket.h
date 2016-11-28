#ifndef MCLIENTSOCKET_H
#define MCLIENTSOCKET_H
#include <QTcpSocket>

class MClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    MClientSocket(QObject* parent=0);
    ~MClientSocket();
signals:
    void updateClients(QString msg,int length);
    void disconnected(int despt);
private slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // MCLIENTSOCKET_H
