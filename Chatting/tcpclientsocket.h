#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include<QTcpSocket>
#include<QObject>

class tcpclientsocket : public QTcpSocket
{
    Q_OBJECT
public:
    tcpclientsocket(QObject *parent=nullptr);

signals:
    void updateClients(QString,int);
    void disconnected(int);

protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // TCPCLIENTSOCKET_H
