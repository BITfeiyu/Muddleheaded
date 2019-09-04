#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("IM");//设置标题；
    setWindowIcon(QPixmap(":/imags/qq.png"));

}

Widget::~Widget()
{
    delete ui;
}
