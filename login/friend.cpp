#include "headers.h"
#include "ui_friend.h"

Friend::Friend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Friend)
{
    ui->setupUi(this);

    ui->treeWidget->setHeaderLabels(QStringList() << "NickName" << " IP Address");

    int length = allUserInfo.length();
    QTreeWidgetItem *treeItem;

    for(int i = 0; i < length;i += 3){
        treeItem = new QTreeWidgetItem(QStringList() << allUserInfo.at(i) << allUserInfo.at(i + 1));
        ui->treeWidget->addTopLevelItem(treeItem);

    }
}

Friend::~Friend()
{
    delete ui;
}
