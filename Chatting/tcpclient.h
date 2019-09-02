#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include<QListWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QGridLayout>

#include <QHostAddress>
#include <QTcpSocket>

namespace Ui {
class tcpclient;
}

class tcpclient : public QDialog
{
    Q_OBJECT

public:
    explicit tcpclient(QWidget *parent = nullptr,Qt::WindowFlags f=nullptr);
    ~tcpclient();

private:
    Ui::tcpclient *ui;

private:
    QListWidget *contentListWidget;
    QLineEdit *sendLineEdit;
    QPushButton *sendBtn;
    QLabel *userNameLabel;
    QLineEdit *userNameEdit;
    QLabel *serverIPLabel;
    QLineEdit *serverIPLineEdit;
    QLabel *protLable;
    QLineEdit *portLineEdit;
    QPushButton *enterBtn;
    QGridLayout *mainLayout;

private:
    bool status;
    int port;
    QHostAddress *serverIP;
    QTcpSocket *tcpSocket;

public slots:
    void slotEnter();
    void slotConnected();
    void slotDisoconnected();
    void dataReceived();
    void slotSend();



};

#endif // TCPCLIENT_H
