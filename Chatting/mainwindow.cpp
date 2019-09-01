#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FileButton_clicked()
{
    file2 file;
    file.exec();
}



