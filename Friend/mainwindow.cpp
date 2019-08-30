#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->treeWidget->setHeaderLabels(QStringList()<<"NickName"<<" IP Address");

    QTreeWidgetItem *group_1_item = new QTreeWidgetItem(QStringList()<<"group_1");
    QTreeWidgetItem *group_2_item = new QTreeWidgetItem(QStringList()<<"group_2");
    QTreeWidgetItem *group_3_item = new QTreeWidgetItem(QStringList()<<"group_3");
    QTreeWidgetItem *group_4_item = new QTreeWidgetItem(QStringList()<<"group_4");

    ui->treeWidget->addTopLevelItem(group_1_item);
    ui->treeWidget->addTopLevelItem(group_2_item);
    ui->treeWidget->addTopLevelItem(group_3_item);
    ui->treeWidget->addTopLevelItem(group_4_item);

    QStringList friend1;
    friend1 << "friend1" << "ip address";
    QTreeWidgetItem * l1 = new QTreeWidgetItem(friend1);
    group_1_item-> addChild(l1);

    QStringList friend2;
    friend2 << "friend2" << "ip address";
    QTreeWidgetItem * l2 = new QTreeWidgetItem(friend2);
    group_1_item-> addChild(l2);

    QStringList friend3;
    friend3 << "friend3" << "ip address";
    QTreeWidgetItem * l3 = new QTreeWidgetItem(friend3);
    group_2_item-> addChild(l3);

    QStringList friend4;
    friend4 << "friend4" << "ip address";
    QTreeWidgetItem * l4 = new QTreeWidgetItem(friend4);
    group_2_item-> addChild(l4);

    QStringList friend5;
    friend5 << "friend5" << "ip address";
    QTreeWidgetItem * l5 = new QTreeWidgetItem(friend5);
    group_3_item-> addChild(l5);

    QStringList friend6;
    friend6 << "friend6" << "ip address";
    QTreeWidgetItem * l6 = new QTreeWidgetItem(friend6);
    group_3_item-> addChild(l6);

    QStringList friend7;
    friend7 << "friend7" << "ip address";
    QTreeWidgetItem * l7 = new QTreeWidgetItem(friend7);
    group_4_item-> addChild(l7);
    QStringList friend8;
    friend8 << "friend8" << "ip address";
    QTreeWidgetItem * l8 = new QTreeWidgetItem(friend8);
    group_4_item-> addChild(l8);

    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(item_DblClicked(QTreeWidgetItem*,int)));

}

void MainWindow::item_DblClicked(QTreeWidgetItem *item,int column)
{
    QString str=item->text(column);
    QMessageBox::warning(this,"\'"+str+"\'","****",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
}


MainWindow::~MainWindow()
{
    delete ui;
}
