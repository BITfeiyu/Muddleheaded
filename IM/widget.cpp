#include "widget.h"
#include "ui_widget.h"

#include <server.h>


#include<QHostInfo>
#include<QMessageBox>
#include<QScrollBar>
#include<QDateTime>
#include<QNetworkInterface>
#include<QProcess>
#include<QFileDialog>
#include <QLabel>

Widget::Widget(QWidget *parent,QString name):
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    InitSocket();

     IPLabel =new QLabel(this);

     ui->IPLabel->setText(QNetworkInterface().allAddresses().at(2).toString());
     ui->userLabel->setText("Myself");
      ui->IPLabel1->setText("192.168.113.135");
      ui->userLabel1->setText("Receiver");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitSocket()
{
    myClient = new QTcpSocket(this);    //分配空间
}

//连接服务器槽函数
void Widget::on_But_socket_lianjie_clicked()
{
    QString serveIP = ui->Edit_serve_IP->text();    //获取服务器IP
    QString servePort = ui->Edit_serve_Port->text();    //获取服务器端口号
    myClient->connectToHost(QHostAddress(serveIP),servePort.toInt());   //连接服务器
    //myClient->connectToHost("192.168.85.1",10086);
    connect(myClient,SIGNAL(connected()),this,SLOT(oneProcessConnected()));     //连接成功
    connect(myClient,SIGNAL(readyRead()),this,SLOT(oneProcessReadyRead()));     //读取服务器信息数据
    connect(myClient,SIGNAL(disconnected()),this,SLOT(oneProcessDisconnected()));       //服务器断开
    connect(myClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(oneProcessError(QAbstractSocket::SocketError)));     //出错函数

}

//连接成功函数
void Widget::oneProcessConnected()
{
    QString msg = "Success";
    ui->textEdit_serve->append(msg);
}

//读取服务器信息函数
void Widget::oneProcessReadyRead()
{
    QString msg,str1,str2;
    str1 = QString("服务器[%1:%2] 说：").arg(myClient->peerAddress().toString()).arg(myClient->peerPort());
    while(!myClient->atEnd())
    {
        str2.append(QString(myClient->readAll()));
    }
    msg = QString("%1%2").arg(str1).arg(str2);
    ui->textEdit_serve->append(msg);
}

//服务器断开函数
void Widget::oneProcessDisconnected()
{
    QString msg = "服务器退出 ";
    ui->textEdit_serve->append(msg);
}

//出错函数
void Widget::oneProcessError(QAbstractSocket::SocketError err)
{
    qDebug() << err;
}

//点击发送按键向服务器发送信息
void Widget::on_Btn_socket_send_clicked()
{
    QString msg = ui->textEdit_socket->toPlainText();
    int ret = myClient->write(msg.toUtf8());
    if(ret <= 0)
    {
        return;
    }
    ui->textEdit_socket->clear();

}

QString Widget::getIP(){
    QList<QHostAddress>list=QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, list) {
        if(addr.protocol()==QAbstractSocket::IPv4Protocol)
            return addr.toString();

    }
    return 0;
}

/*  QTableWidgetItem *usr=new QTableWidgetItem(usrname);
QTableWidgetItem *ip=new QTableWidgetItem(ipaddr);
ui->usrTblWidget->insertRow(0);
ui->usrTblWidget->setItem(0,0,usr);
ui->usrTblWidget->setItem(0,1,ip); */

void Widget::on_toolButton_clicked()
{
    Server  seve;
 seve.exec();
}

void Widget::closeEvent(QCloseEvent*)
{
    emit this -> closeWidget();
}
