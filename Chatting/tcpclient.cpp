#include "tcpclient.h"
#include "ui_tcpclient.h"

#include<QMessageBox>
#include<QHostInfo>
#include<QObject>

tcpclient::tcpclient(QWidget *parent,Qt::WindowFlags f) :
    QDialog(parent,f),
    ui(new Ui::tcpclient)
{
    ui->setupUi(this);
    setWindowTitle(tr("TCP Client"));
    contentListWidget=new QListWidget;

    sendLineEdit =new QLineEdit;
    sendBtn =new QPushButton(tr("send"));

    userNameLabel =new QLabel(tr("UserName:"));
    userNameEdit =new QLineEdit;

    serverIPLabel =new QLabel(tr("serverAddr:"));
    serverIPLineEdit=new QLineEdit;

    protLable =new QLabel(tr("port:"));
    portLineEdit=new QLineEdit;

    enterBtn=new QPushButton(tr("join in chatting room"));

    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(sendLineEdit,1,0);
    mainLayout->addWidget(sendBtn,1,1);
    mainLayout->addWidget(userNameLabel,2,0);
    mainLayout->addWidget(userNameEdit,2,1);
    mainLayout->addWidget(serverIPLabel,3,0);
      mainLayout->addWidget(serverIPLineEdit,3,1);
        mainLayout->addWidget(protLable,4,0);
          mainLayout->addWidget(portLineEdit,4,1);
            mainLayout->addWidget(enterBtn,5,0,1,2);

            status=false;
            port=8010;
            portLineEdit->setText(QString::number(port));


            serverIP=new QHostAddress();

            connect(enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));
            connect(sendBtn,SIGNAL(clicked()),this,SLOT(slotSend()));

            sendBtn->setEnabled(false);




}

tcpclient::~tcpclient()
{
    delete ui;
}



void tcpclient::slotEnter()
{

    QString userName;
    if(!status)
    {

        if(userNameEdit->text()=="")
        {
            QMessageBox::information(this,tr("error"),tr("username error!"));
            return;
        }

        QString ip=serverIPLineEdit->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
            return;
        }
         userName=userNameEdit->text();

        tcpSocket=new QTcpSocket(this);

        connect(tcpSocket,SIGNAL(connect()),this,SLOT(slotConnected()));
         connect(tcpSocket,SIGNAL(disconnect()),this,SLOT(slotDisconnected()));
          connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

          tcpSocket->connectToHost(*serverIP,port);
          status=true;
    }

    else {
        int length=0;
        QString msg=userName+tr(":Leave Chat Room");
        if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
        {
            return;
        }
        tcpSocket->disconnectFromHost();
        status=false;

    }
}

void tcpclient::slotConnected(){
    QString userName;
    sendBtn->setEnabled(true);
    enterBtn->setText(tr("Leave"));

    int length=0;
    QString msg=userName+ tr(":Enter Char Room");
    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
    {
        return;
    }
}

void tcpclient::slotSend()
{
    if(sendLineEdit->text()=="")
    {
        return;
    }
    QString userName=userNameEdit->text();
    QString msg= userName+ ":"+sendLineEdit->text();
    tcpSocket->write(msg.toLatin1(),msg.length());
    sendLineEdit->clear();
}

void tcpclient::slotDisoconnected()
{    sendBtn->setEnabled(false);
    enterBtn->setText(tr("join in chat room"));
}

void tcpclient::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        tcpSocket->read(datagram.data(),datagram.size());
        QString msg=datagram.data();
        contentListWidget->addItem(msg.left(datagram.size()));
    }
}
