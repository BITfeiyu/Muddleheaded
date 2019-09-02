#include "server.h"

Server::Server(QObject *parent,int port)
    :QTcpServer (parent)
{
  listen(QHostAddress::Any,port);
}

void Server::incomingConnection(int socketDescriptor)
{
    tcpclientsocket *tcpclientsocket=new  class tcpclientsocket(this);
    connect(tcpclientsocket,SIGNAL(updateclients(QString,int)),this,SLOT(updateclient(QString,int)));
    connect(tcpclientsocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));

    tcpclientsocket->setSocketDescriptor(socketDescriptor);
   tcpclientSocketList.append(tcpclientsocket);
};
void Server::updateClients(QString msg,int length)
{
    emit updateClients(msg,length);
    for(int i=0;i<tcpclientSocketList.count();i++)
    {
        QTcpSocket *item =tcpclientSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length)
        {
            continue;
        }
    }
}

void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpclientSocketList.count();i++)
    {
        QTcpSocket *item =tcpclientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpclientSocketList.removeAt(i);
            return;
        }
    }
    return;
}
