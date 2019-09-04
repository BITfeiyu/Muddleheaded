#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    Server();
    ~Server();

private:

    QTcpServer *server;
    QTcpSocket *clientSocket;

private slots:
    void initServer();
    void ServerNewConnection();
    void initServerSocket();
    void ServerReadData();
    void ServerSendData(QString permi);
    void ServerDisConnection();
    bool checkInput(QString msgClienttoServer);
};

#endif // SERVER_H
