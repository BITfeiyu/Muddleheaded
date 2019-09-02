#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->treeWidget->setHeaderLabels(QStringList()<<"NickName"<<" IP Address");

    QTreeWidgetItem *friend_1_item = new QTreeWidgetItem(QStringList()<<"friend_1"<<" IP Address");
    QTreeWidgetItem *friend_2_item = new QTreeWidgetItem(QStringList()<<"friend_2"<<" IP Address");
    QTreeWidgetItem *friend_3_item = new QTreeWidgetItem(QStringList()<<"friend_3"<<" IP Address");
    QTreeWidgetItem *friend_4_item = new QTreeWidgetItem(QStringList()<<"friend_4"<<" IP Address");

    ui->treeWidget->addTopLevelItem(friend_1_item);
    ui->treeWidget->addTopLevelItem(friend_2_item);
    ui->treeWidget->addTopLevelItem(friend_3_item);
    ui->treeWidget->addTopLevelItem(friend_4_item);

}



MainWindow::~MainWindow()
{
    delete ui;
}

