#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Btn_socket_send_clicked();
    void on_toolButton_clicked();

    void initServer();
    void ServerNewConnection();
    void initServerSocket();
    void ServerReadData();
    void ServerSendData(QString permi);
    void ServerDisConnection();
    bool checkInput(QString msgClienttoServer);

private:
    Ui::Widget *ui;
    //QList <QTcpSocket *> arrayClient;
    QString getLocalIPv4();

    QTcpServer *server;
    QTcpSocket *clientSocket;
    QString msgServertoClient;
    QString msgClienttoServer;


};

#endif // WIDGET_H
