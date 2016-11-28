#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QTcpSocket>

class ChatClient : public QDialog
{
    Q_OBJECT

public:
    ChatClient(QWidget *parent = 0);
    ~ChatClient();
private slots:
    void slotExitApp(void);
    void slotConnectOrClose(void);
    void slotSendMsg(void);

    void slotDataReceive(void);
    void slotConnected(void);
    void slotDisconnected(void);
private:
    void initLabel(void);
    void initPushbutton(void);
    void initLineEdit(void);

private:
     QLabel* logo;
     QLabel* appName;
     QLabel* userName;
     QLabel* serverIP;
     QLabel* serverPort;

     QPushButton* exitApp;
     QPushButton* connectOrClose;
     QPushButton* sendMsg;

     QLineEdit* setUserName;
     QLineEdit* setServerIP;
     QLineEdit* setServerPort;
     QLineEdit* setMsg;

     QListWidget* listWidget;

     bool socketState;
     QString myName;
     QTcpSocket* clientSocket;
};

#endif // CHATCLIENT_H
