#ifndef TCPSEVER_H
#define TCPSEVER_H

#include <QDialog>
#include<QListWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QGridLayout>
#include<QNetworkInterface>

#include"server.h"

namespace Ui {
class TcpSever;
}

class TcpSever : public QDialog
{
    Q_OBJECT

public:
    explicit TcpSever(QWidget *parent = nullptr,Qt::WindowFlags=nullptr);
    ~TcpSever();

private:
    Ui::TcpSever *ui;
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;
    QLabel *IPlabel;

private:
    int port;
    Server *server;

public slots:
    void slotCreateServer();
    void updateServer(QString,int);


private slots:
    void on_pushButton_clicked();
};

#endif // TCPSEVER_H
