#ifndef SEVER_H
#define SEVER_H

#include<QTcpServer>
#include<QObject>

#include"tcpclientsocket.h"

class Server :public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent=nullptr,int port=0);

    QList<tcpclientsocket*> tcpclientSocketList;

signals:
    void updateSever(QString,int);
public slots:
    void updateClients(QString,int);
    void slotDisconnected(int);

protected:
    void incomingConnection(int socketDescriptor);


};



#endif // SEVER_H
