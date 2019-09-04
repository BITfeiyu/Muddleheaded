#include "ui_server.h"
#include "headers.h"
#define clientPort 9000

Server::Server()
{
    initServer();
    initServerSocket();
}

Server::~Server()
{
    //deletedatabase();
}

void Server::initServer()
{
    createDatabase();
}

void Server::initServerSocket()
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

void Server::ServerReadData()
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

void Server::ServerSendData(QString sendMsg)
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

void Server::ServerDisConnection()
{
    return;
}

bool Server::checkInput(QString msgClienttoServer)
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
    } else {
        qDebug() << "Message package kind illegal!";
        return false;
    }
}

void Server::ServerNewConnection()
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


