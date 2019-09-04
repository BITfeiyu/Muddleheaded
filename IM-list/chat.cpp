#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent,QString name) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}
/*
void Chat::closeEvent(QCloseEvent*)
{
    emit this -> closeWidget();
}
*/

Chat::~Chat()
{
    delete ui;
}
