#include "widget.h"
#include "ui_widget.h"
#include "server.h"
#include "headers.h"
#define clientPort 9000

#define MAXNUM 100

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->labelClientName->setText("Client");
    ui->labelClientIP->setText("ClientIP");
    ui->labelServerName->setText("Server");
    ui->labelSeverIP->setText(getLocalIPv4());
    initServer();
    initServerSocket();
}

Widget::~Widget()
{
    delete ui;
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

void Widget::initServer()
{
    createDatabase();
}

void Widget::initServerSocket()
{
    server = new QTcpServer();
    int port = clientPort;
    if(!server->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server listen failed!";
        return;
    }
    qDebug() << "Server listen succeed!";
    connect(server, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));
    return;
}

void Widget::ServerNewConnection()
{
    clientSocket = server->nextPendingConnection();
    if(!clientSocket)
    {
        qDebug() << "Client connection incorrect!";
        return;
    }
    qDebug() << "Client connection correct!";
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(ServerReadData()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(ServerDisConnection()));
}

void Widget::ServerReadData()
{
    QString msgClienttoServer = clientSocket->readAll();
    qDebug() << "Message from Client to Server:" << msgClienttoServer;
    if(msgClienttoServer.length() > 0)
    {
        if(checkInput(msgClienttoServer)){
            QString msgServertoClient = "yes";
            getAllUserInfo();
            msgServertoClient.append(allUserInfo);
            ServerSendData(msgServertoClient);
        }
    } else {
        qDebug() << "Unable to get data!";
        return;
    }
}

void Widget::ServerSendData(QString sendMsg)
{
    char sendMsgChar[1024] = {0};
    strcpy(sendMsgChar, sendMsg.toStdString().c_str());

    if(clientSocket->isValid()){
        int sendRe = clientSocket->write(sendMsgChar, strlen(sendMsgChar));
        if(sendRe == -1){
            qDebug() << "Server sent message failed!";
            return;
        } else {
            qDebug() << "Server sent message succeeded!";
            qDebug() << "Message from server to client: " << sendMsg;
        }
    } else {
        qDebug() << "Invaild socket!";
        return;
    }
}

void Widget::ServerDisConnection()
{
    return;
}

bool Widget::checkInput(QString msgClienttoServer)
{
    MsgPack *msgClienttoServerPack;
    msgClienttoServerPack = new MsgPack(msgClienttoServer);

    QString msgKind = msgClienttoServerPack->getMsgKind();

    if(msgKind == "login"){
        QString pcUsername = msgClienttoServerPack->getDataAt(0);
        QString pcUserPasswd = msgClienttoServerPack->getDataAt(1);
        qDebug() << "login:username:" << pcUsername << "passwd:" << pcUserPasswd;

        return login(pcUsername, pcUserPasswd);
    } else if(msgKind == "register"){
        QString pcUsername = msgClienttoServerPack->getDataAt(0);
        QString pcUserPasswd = msgClienttoServerPack->getDataAt(1);
        QString pcUserIP = msgClienttoServerPack->getDataAt(2);
        qDebug() << "register:username:" << pcUsername << "passwd:" << pcUserPasswd << "ip:" << pcUserIP;

        return addNewUser(pcUsername, pcUserPasswd, pcUserIP);
    } else if(msgKind == "chat"){
        QString message = msgClienttoServerPack->getDataAt(0);
        ui->textEdit_serve->setText(ui->textEdit_serve->toPlainText().append("\nClient:\n").append(message));
        qDebug() << "message from client to server:" << msgClienttoServer;
        qDebug() << "messag is: " << message;
    } else {
        qDebug() << "Message package kind illegal!";
        return false;
    }
}

void Widget::on_Btn_socket_send_clicked()
{

    QString msg = ui->textEdit_socket->toPlainText();
    msgServertoClient = "chat#";
    msgServertoClient.append(msg);
    qDebug() << "Message from client to server:" << msgServertoClient;
    ServerSendData(msgServertoClient);
    ui->textEdit_socket->clear();
    ui->textEdit_serve->setText(ui->textEdit_serve->toPlainText().append("\nServer: \n").append(msg));

}

void Widget::on_toolButton_clicked()
{
    Server seva;
    seva.exec();
}



