#include "headers.h"
#include "ui_login.h"
#include <QString>
#include <string.h>
#include<widget.h>
#include<dialoglist.h>

#define serverIP "127.0.0.1"
#define serverPort 9000;

QStringList allUserInfo;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->textEditUsername->setAlignment(Qt::AlignHCenter);
    ui->textEditUsername->setAlignment(Qt::AlignVCenter);
    ui->textEditPasswd->setAlignment(Qt::AlignHCenter);
    ui->textEditPasswd->setAlignment(Qt::AlignVCenter);

    clientSocket = new QTcpSocket();

    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(ClientRecvData()));
}

Login::~Login()
{
    delete this->clientSocket;
    this->close();
    delete ui;
}

void Login::on_pushButtonLogin_released(){

    QString ip = serverIP;
    int port = serverPort;
    clientSocket->abort();
    clientSocket->connectToHost(ip, port);
    if(!clientSocket->waitForConnected(30000))
    {
        qDebug() << "Server connection failed!";
        return;
    }

    QString pcUsername = ui->textEditUsername->toPlainText();
    QString pcUserPasswd = ui->textEditPasswd->toPlainText();

    QString msgClienttoServer = "login#";
    msgClienttoServer.append(pcUsername).append("#").append(pcUserPasswd);

    char sendMsgChar[1024] = {0};
    strcpy(sendMsgChar, msgClienttoServer.toStdString().c_str());

    int sendRe = clientSocket->write(sendMsgChar, strlen(sendMsgChar));
    if(sendRe == -1){
        qDebug() << "Send message failed!";
        return;
    } else {
        qDebug() << "Send message succeeded!";
        return;
    }
}

void Login::ClientRecvData()
{
    QString msgServertoClient = clientSocket->readAll();
    MsgPack *msgPack = new MsgPack(msgServertoClient);
    allUserInfo = msgPack->getDataList();
    if(msgPack->getMsgKind() == "yes"){
        QMessageBox::information(nullptr, "用户登录", "登陆成功", QMessageBox::Ok, QMessageBox::Ok);
        LoginPermitted();
    }
}

void Login::on_pushButtonRegister_released()
{
     Register r;
     r.exec();
}

void Login::LoginPermitted()
{
    delete this->clientSocket;
    this->close();
    DialogList hi;
    hi.exec();
}
