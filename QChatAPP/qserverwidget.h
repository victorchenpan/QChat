#ifndef QSERVERWIDGET_H
#define QSERVERWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
class QServerWidget : public QDialog
{
    Q_OBJECT

public:
    QServerWidget(QWidget *parent = 0);
    ~QServerWidget();

signals:
    void signal_start_server(quint16 port);

public slots:
    void slot_update_server(QString,int);

private:
    void label_init(void);
    void pushbutton_init(void);

    void init_connect(void);
private slots:
    void app_exit(void);
    void start_server(void);
    void set_port(void);
    void stop_server(void);

private:
    QLabel* logo;
    QLabel* app_name;
    QLabel* start_label;
    QLabel* stop_label;
    QLabel* port_name;

    QPushButton* App_close;
    QPushButton* start;
    QPushButton* stop;
    QPushButton* ensure;

    QLineEdit* port_edit;

    QListWidget* listWidget;

    quint16 port;
};

#endif // QSERVERWIDGET_H
