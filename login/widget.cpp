#include "widget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("登陆界面"));

    userNameLabel = new QLabel(tr("name:"));
    passWordLabel = new QLabel(tr("Password:"));

    userNameLineEdit =new QLineEdit;
    passWordLineEdit = new QLineEdit;
    passWordLineEdit->setEchoMode(QLineEdit::Password);

    login = new QPushButton(tr("login"));

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(userNameLabel,0,0);
    mainLayout->addWidget(passWordLabel,1,0);
    mainLayout->addWidget(userNameLineEdit,0,1);
    mainLayout->addWidget(passWordLineEdit,1,1);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    mainLayout->addLayout(hBoxLayout,2,0,1,2);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(login);
    connect(login,SIGNAL(clicked()),this,SLOT(slotLogin()));
    connect(passWordLineEdit,SIGNAL(returnPressed()),this,SLOT(slotLogin()));

}


Widget::~Widget()
{

}
void Widget::slotLogin(){

     qDebug() << "输入用户名：" << userNameLineEdit->text();       //输出调试信息

     qDebug() << "输入密码：" << passWordLineEdit->text();
     if (userNameLineEdit->text().operator ==("user") && passWordLineEdit->text().operator ==("1234567890"))

    {

          qDebug() << "登录成功！";

          QMessageBox::information(this,tr("登录提示"),tr("登录成功"));
     }

     else

     {

          qDebug() << "用户名或密码错误！";

          QMessageBox::information(this,tr("登录提示"),tr("用户名或密码错误！"));

     }

}
