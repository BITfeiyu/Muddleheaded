#include "file2.h"
#include "ui_file2.h"

file2::file2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file2)
{
    ui->setupUi(this);
}

file2::~file2()
{
    delete ui;
}
