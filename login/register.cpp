#include "headers.h"
#include "ui_register.h"
#include <QString>
#include <string.h>
#define serverIP "127.0.0.1"
#define serverPort 9000;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->textEditNickName->setAlignment(Qt::AlignHCenter);
    ui->textEditNickName->setAlignment(Qt::AlignVCenter);
    ui->textEditPasswd->setAlignment(Qt::AlignHCenter);
    ui->textEditPasswd->setAlignment(Qt::AlignVCenter);
    ui->textEditPasswdRe->setAlignment(Qt::AlignHCenter);
    ui->textEditPasswdRe->setAlignment(Qt::AlignVCenter);

    clientSocket = new QTcpSocket();
    QString ip = serverIP;
    int port = serverPort;
    clientSocket->connectToHost(ip, port);
    if(!clientSocket->waitForConnected(30000))
    {
        qDebug() << "Server connection failed!";
        return;
    }
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(ClientRecvData()));
}

QString Register::getLocalIPv4()
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

Register::~Register()
{
    this->close();
    delete ui;
}

void Register::on_pushButtonSubmit_released()
{
    QString pcUserNickName = ui->textEditNickName->toPlainText();
    QString pcUserPasswd = ui->textEditPasswd->toPlainText();
    QString pcUserPasswdRe = ui->textEditPasswdRe->toPlainText();

    if(pcUserPasswd != pcUserPasswdRe){
        QMessageBox::information(NULL, "用户注册", "重复输入密码错误", QMessageBox::Ok, QMessageBox::Ok);
        return;
    } else if(pcUserPasswd.length() > 16 || pcUserPasswd < 8){
        QMessageBox::information(NULL, "用户注册", "密码必须是8-16位的字符串", QMessageBox::Ok, QMessageBox::Ok);
    }

    QString msg = "register#";
    msg.append(pcUserNickName).append("#");
    msg.append(pcUserPasswd).append("#");
    msg.append(getLocalIPv4());

    char sendMsgChar[1024] = {0};
    strcpy(sendMsgChar, msg.toStdString().c_str());
    int sendRe = clientSocket->write(sendMsgChar, strlen(sendMsgChar));
    if(sendRe == -1){
         qDebug() << "Send message failed!";
         return;
    } else {
        qDebug() << "Send message succeeded!";
    }
}

void Register::ClientRecvData()
{
    //将接收内容存储到字符串中
    char recvMsg[1024] = {0};
    int recvRe = clientSocket->read(recvMsg, 1024);
    if(recvRe == -1)
    {
        qDebug() << "Receive from server failed!";
        return;
    }
    QString msgServertoClient = recvMsg;
    qDebug() << "Message from Server to Client:" << msgServertoClient;
    MsgPack *msgServertoClientPack = new MsgPack(msgServertoClient);
    if(msgServertoClientPack->getMsgKind() == "yes"){
        QMessageBox::information(NULL, "用户注册", "注册成功", QMessageBox::Ok, QMessageBox::Ok);
    } else {
        QMessageBox::information(NULL, "用户注册", "注册失败", QMessageBox::Ok, QMessageBox::Ok);
    }
}

