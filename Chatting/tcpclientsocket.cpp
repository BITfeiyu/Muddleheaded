#include "tcpclientsocket.h"


tcpclientsocket::tcpclientsocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnnectd()),this,SLOT(slotDisconnected()));
}
void tcpclientsocket::dataReceived()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[1024];
        read(buf,length);

        QString msg=buf;
        emit updateClients(msg,length);
    }
}

void tcpclientsocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
