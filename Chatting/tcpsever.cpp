#include "tcpsever.h"
#include "ui_tcpsever.h"

TcpSever::TcpSever(QWidget *parent,Qt::WindowFlags f) :
    QDialog(parent,f),
    ui(new Ui::TcpSever)
{
    ContentListWidget =new QListWidget;

    PortLabel =new QLabel(tr("prot:"));
    PortLineEdit=new QLineEdit;

     IPlabel =new QLabel(this);

    mainLayout=new QGridLayout(this);
    CreateBtn = new QPushButton(tr("create chat room"));

    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(CreateBtn,2,0,1,2);
    mainLayout->addWidget(IPlabel,1,2);

    port=8010;
    PortLineEdit->setText(QString::number(port));

    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotCreateServer()));

    ui->setupUi(this);


    setWindowTitle(tr("TCP Sever"));


   ui->IPLabel->setText(QNetworkInterface().allAddresses().at(0).toString());

}

TcpSever::~TcpSever()
{
    delete ui;

}



void TcpSever::on_pushButton_clicked()
{
    port=8010;
    PortLineEdit->setText(QString::number(port));

    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotCreateServer()));
}

void TcpSever::slotCreateServer()
{
    server=new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));

    CreateBtn->setEnabled(false);
}

void TcpSever::updateServer(QString msg,int length)
{
    ContentListWidget->addItem(msg.left(length));
}


