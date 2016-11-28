#include "qserverwidget.h"
#include <QApplication>
QServerWidget::QServerWidget(QWidget *parent)
    : QDialog(parent)
{
    setObjectName("mainWidget");
    resize(500,400);

    label_init();
    pushbutton_init();

    listWidget=new QListWidget(this);
    listWidget->setObjectName("listWidget");
    listWidget->setGeometry(10,50,390,350);
    listWidget->addItem("     Welcome to ChatRoom of Local Area Network...!");

    port_edit=new QLineEdit(this);
    port_edit->setGeometry(410,120,50,20);

    init_connect();
}

void QServerWidget::start_server()
{
    start->setDisabled(true);
    emit signal_start_server((quint16)port);
}
void QServerWidget::set_port(void)
{
    int port_num=port_edit->text().toInt();
    if(port_num>=9000 && port_num<65535)
    {
        this->port=port_num;
        port_edit->setDisabled(true);
        //start->setDisabled(false);
        start->setEnabled(true);
        listWidget->addItem("Our server port is:"+port_edit->text());
    }
    else {
        listWidget->addItem("Error: Please input port from 9000 to 65535...");
        return;
    }
}

void QServerWidget::slot_update_server(QString msg, int length)
{

    listWidget->addItem(msg);
    //listWidget->addItem(QString::number(length));

}

void QServerWidget::init_connect(void)
{
    connect(App_close,SIGNAL(clicked(bool)),this,SLOT(app_exit(void)));
    connect(start,SIGNAL(clicked()),this,SLOT(start_server()));
    connect(ensure,SIGNAL(clicked(bool)),this,SLOT(set_port()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stop_server()));
}
void QServerWidget::stop_server()
{

}

void QServerWidget::app_exit(void)
{
    QApplication::exit(0);
}

void QServerWidget::label_init(void)
{
    logo=new QLabel(this);
    logo->setObjectName("logo");
    logo->setGeometry(10,10,16,16);

    start_label=new QLabel("start: ",this);
    start_label->setObjectName("start_label");
    start_label->setGeometry(410,210,35,20);
  //  start_label->setFrameStyle(QFrame::Plain);

    stop_label=new QLabel("stop:",this);
    stop_label->setObjectName("stop_label");
    stop_label->setGeometry(410,330,35,20);

    port_name=new QLabel("port:",this);
    port_name->setObjectName("port_name");
    port_name->setGeometry(410,90,30,20);

    app_name=new QLabel("QChat_server",this);
    app_name->setObjectName("app_name");
    app_name->setGeometry(30,2,100,30);

}

void QServerWidget::pushbutton_init(void)
{
    App_close=new QPushButton(this);
    App_close->setObjectName("app_close");
    App_close->setGeometry(480,5,16,16);

    start=new QPushButton(this);
    start->setObjectName("start");
    start->setGeometry(460,210,24,24);
    start->setDisabled(true);

    stop=new QPushButton(this);
    stop->setObjectName("stop");
    stop->setGeometry(460,330,24,24);

    ensure=new QPushButton(this);
    ensure->setObjectName("ensure");
    ensure->setGeometry(470,120,16,16);
}

QServerWidget::~QServerWidget()
{
    delete App_close;
    delete start;
    delete stop;
    delete ensure;

    delete start_label;
    delete stop_label;
    delete port_name;

    delete port_edit;
    delete listWidget;

}
