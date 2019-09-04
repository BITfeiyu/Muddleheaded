#include "widget.h"
#include "ui_widget.h"
#include "headers.h"
#include "server.h"
#include "client.h"
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <QFileDialog>
#include <QLabel>

//#define serverIP "10.195.199.168"
#define serverPort 9000;

Widget::Widget(QDialog *parent,QString name):
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->IPLabelClient->setText(getLocalIPv4());
    ui->userLabelClient->setText("Client");
    ui->IPLabelServer->setText("请输入服务器IP地址");
    ui->userLabelServer->setText("Server");

    clientSocket = new QTcpSocket();

    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(ClientRecvData()));
}

Widget::~Widget()
{
    delete this->clientSocket;
    this->close();
    delete ui;
}

void Widget::on_But_socket_lianjie_clicked()
{
    ip = ui->Edit_serve_IP->text();
    if(ip.length() > 0){
        //QString ip = serverIP;
        int port = serverPort;
        clientSocket->abort();
        clientSocket->connectToHost(ip, port);
        if(!clientSocket->waitForConnected(30000))
        {
            qDebug() << "Server connection failed!";
            return;
        }
        qDebug() << "Server connection succeeded!";

        QMessageBox::information(NULL, "提示", "链接成功",  QMessageBox::Ok, QMessageBox::Ok);
        ui->IPLabelServer->setText(ip);
    } else{
        QMessageBox::information(NULL, "提示", "请输入正确的IP地址",  QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
}

QString Widget::getLocalIPv4()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); i++){
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  ipAddressesList.at(i).toIPv4Address()){
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}

//点击发送按键向服务器发送信息
void Widget::on_Btn_socket_send_clicked()
{
    if(ip == NULL){
        QMessageBox::information(NULL, "提示", "请输入服务器IP地址",  QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    msgClienttoServer = "chat#";
    QString message = ui->textEdit_socket->toPlainText();
    msgClienttoServer.append(message);
    qDebug() << "Message from client to server:" << msgClienttoServer;

    char sendMsgChar[1024] = {0};
    strcpy(sendMsgChar, msgClienttoServer.toStdString().c_str());

    int sendRe = clientSocket->write(sendMsgChar, strlen(sendMsgChar));
    if(sendRe == -1){
        qDebug() << "Send message failed!";
    } else {
        qDebug() << "Send message succeeded!";
        qDebug() << "Message from Client to Server: " << msgClienttoServer;
    }

    ui->textEdit_socket->clear();
    ui->textEdit_serve->setText(ui->textEdit_serve->toPlainText().append("\nClient:\n").append(message));
    return;
}

void Widget::ClientRecvData()
{
    QString msgServertoClient = clientSocket->readAll();
    qDebug() << "Message from Server to Client:" << msgServertoClient;
    MsgPack *msgServertoClientPack = new MsgPack(msgServertoClient);
    allUserInfo = msgServertoClientPack->getDataList();
    if(msgServertoClientPack ->getMsgKind() == "chat"){
        QString message = msgServertoClientPack->getDataAt(0);
        ui->textEdit_serve->setText(ui->textEdit_serve->toPlainText().append("\nServer:\n").append(message));
    }
}


void Widget::on_toolButton_clicked()
{
    Server seve;
    seve.exec();
}

void Widget::closeEvent(QCloseEvent*)
{
    emit this->closeWidget();
}

void Widget::on_toolButton_2_clicked()
{
    Client cc;
    cc.exec();
}


