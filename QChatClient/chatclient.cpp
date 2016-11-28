#include "chatclient.h"
#include <QApplication>
#include <QHostAddress>
#include <QMessageBox>

ChatClient::ChatClient(QWidget *parent)
    : QDialog(parent)
{
    this->setObjectName("clientWidget");
    resize(400,600);
    socketState=false;

    initLabel();
    initPushbutton();
    initLineEdit();

    listWidget=new QListWidget(this);
    listWidget->setObjectName("listWidget");
    listWidget->setGeometry(20,40,360,360);
    listWidget->addItem(" Welcome to our QChat room...");

    connect(sendMsg,SIGNAL(clicked(bool)),this,SLOT(slotSendMsg()));
    connect(exitApp,SIGNAL(clicked(bool)),this,SLOT(slotExitApp()));
    connect(connectOrClose,SIGNAL(clicked(bool)),this,SLOT(slotConnectOrClose()));
}
void ChatClient::slotConnected()
{
    listWidget->addItem("Congratulations: You Have connected to Server!");
}
void ChatClient::slotDisconnected()
{
    listWidget->addItem("Notify: You Have leave the Chat room!");
    listWidget->addItem("       bye bye......");
}

void ChatClient::slotDataReceive()
{
    QString msg(clientSocket->readAll());
    listWidget->addItem(msg);
}
void ChatClient::slotSendMsg()
{
    QString Msg=myName+tr(": ")+setMsg->text();
    clientSocket->write(Msg.toLatin1(),Msg.size());

}
void ChatClient::slotExitApp()
{
    QApplication::exit(0);
}
void ChatClient::slotConnectOrClose()
{
    if(!socketState)
    {
        QHostAddress ipAddr;
        if(!ipAddr.setAddress(setServerIP->text()))
        {
            QMessageBox::information(this,"error","IP is not correct......");
            return;
        }
        myName=setUserName->text();
        connectOrClose->setText("Log out :");

        //
        setUserName->setDisabled(true);
        setServerIP->setDisabled(true);
        setServerPort->setDisabled(true);

        clientSocket=new QTcpSocket(this);
        connect(clientSocket,SIGNAL(readyRead()),this,SLOT(slotDataReceive()));
        connect(clientSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        connect(clientSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        clientSocket->connectToHost(ipAddr,(quint16)setServerPort->text().toInt());

        socketState=true;
        sendMsg->setEnabled(true);
        listWidget->addItem("You have log in our QChat Server,now you can chat with others....");
    }
    else
    {
        //int msgLength=0;
        QString leaveMsg=myName+tr(": leave chat room...");
        if(clientSocket->write(leaveMsg.toLatin1(),leaveMsg.length())!=leaveMsg.length())
           return;
        clientSocket->disconnectFromHost();
        socketState=false;
        connectOrClose->setText("Login :");
        setUserName->setEnabled(true);
        setServerIP->setEnabled(true);
        setServerPort->setEnabled(true);
    }
}
void ChatClient::initLabel()
{
    logo=new QLabel(this);
    logo->setObjectName("logo");
    logo->setGeometry(2,2,16,16);

    appName=new QLabel("QCC",this);
    appName->setToolTip("QT Chat Client");
    appName->setGeometry(30,2,100,20);

    userName=new QLabel(" User Name:",this);
    userName->setObjectName("userName");
    userName->setGeometry(20,405,120,30);

    serverIP=new QLabel(" Server IP:",this);
    serverIP->setObjectName("serverIP");
    serverIP->setGeometry(20,445,120,30);

    serverPort=new QLabel(" Server Port:",this);
    serverPort->setObjectName("serverPort");
    serverPort->setGeometry(20,485,120,30);

}

void ChatClient::initLineEdit()
{
    setUserName=new QLineEdit(this);
    setUserName->setObjectName("setUserName");
    setUserName->setGeometry(200,405,180,30);

    setServerIP=new QLineEdit(this);
    setServerIP->setObjectName("setServerIP");;
    setServerIP->setGeometry(200,445,180,30);

    setServerPort=new QLineEdit(this);
    setServerPort->setObjectName("setServerPort");
    setServerPort->setGeometry(200,485,180,30);

    setMsg=new QLineEdit(this);
    setMsg->setObjectName("setMsg");
    setMsg->setGeometry(20,525,360,30);
}

void ChatClient::initPushbutton()
{
    exitApp=new QPushButton(this);
    exitApp->setObjectName("exitApp");
    exitApp->setGeometry(380,4,16,16);

    connectOrClose=new QPushButton("Login :",this);
    connectOrClose->setObjectName("connectOrClose");
    connectOrClose->setGeometry(20,565,80,30);

    sendMsg=new QPushButton("send",this);
    sendMsg->setObjectName("sendMsg");
    sendMsg->setGeometry(340,565,40,30);
    sendMsg->setDisabled(true);
}
ChatClient::~ChatClient()
{

}
