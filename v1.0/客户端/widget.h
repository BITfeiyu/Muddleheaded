#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QtCore/QObject>
#include <QLabel>


namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QDialog *parent, QString name);
    //explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_But_socket_lianjie_clicked();
    void on_Btn_socket_send_clicked();
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void ClientRecvData();

//    void oneProcessConnected();     //连接成功函数
//    void oneProcessReadyRead();     //读取服务器信息函数
//    void oneProcessDisconnected();      //服务器断开函数
//    void oneProcessError(QAbstractSocket::SocketError err);     //出错函数



private:
    Ui::Widget *ui;
    QTcpSocket *clientSocket;
    QString msgClienttoServer;
    QString msgServertoClient;
    QString getLocalIPv4();
    QString ip = NULL;

//    QTcpSocket *myClient;    //定义客户端对象
//    QLabel  *IPLabel;


//    void InitSocket();      //初始化客户端函数

//protected:
//    void usrEnter(QString username,QString ipaddr);//处理新用户加入
//    void usrLeft(QString username,QString time);//处理用户离开

//    QString ipAddress();
//    QString getUsr();
//    QString getIP();



signals:
    void closeWidget();


 public:
    void closeEvent(QCloseEvent*);

};

#endif // WIDGET_H
