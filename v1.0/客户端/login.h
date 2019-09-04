#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtNetwork>
#include "msgpack.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButtonLogin_released();
    void ClientRecvData();
    void on_pushButtonRegister_released();
    void LoginPermitted();

private:
    Ui::Login *ui;

    QTcpSocket *clientSocket;
//    MsgPack *allUserInfo = NULL;
};

#endif // LOGIN_H
