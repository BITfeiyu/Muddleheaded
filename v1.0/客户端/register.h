#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private:
    QString getLocalIPv4();

private slots:
    void on_pushButtonSubmit_released();
    void ClientRecvData();

private:
    Ui::Register *ui;

    QTcpSocket *clientSocket;
};

#endif // REGISTER_H
