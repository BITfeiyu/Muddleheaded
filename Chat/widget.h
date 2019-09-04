#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QtCore/QObject>
#include  <QLabel>


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
    void on_But_socket_lianjie_clicked();
    void on_Btn_socket_send_clicked();

    void oneProcessConnected();     //连接成功函数
    void oneProcessReadyRead();     //读取服务器信息函数
    void oneProcessDisconnected();      //服务器断开函数
    void oneProcessError(QAbstractSocket::SocketError err);     //出错函数

    void on_toolButton_clicked();

private:
    Ui::Widget *ui;

    QTcpSocket *myClient;    //定义客户端对象
    QLabel  *IPLabel;


    void InitSocket();      //初始化客户端函数

protected:
    void usrEnter(QString username,QString ipaddr);//处理新用户加入
    void usrLeft(QString username,QString time);//处理用户离开

    QString ipAddress();
    QString getUsr();
    QString getIP();

};

#endif // WIDGET_H
