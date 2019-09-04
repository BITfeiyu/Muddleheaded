#ifndef FRIEND_H
#define FRIEND_H

#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "msgpack.h"

namespace Ui {
class Friend;
}

class Friend : public QDialog
{
    Q_OBJECT

public:
    explicit Friend(QWidget *parent = nullptr);
    ~Friend();

private:
    Ui::Friend *ui;

    //QStringList allUserInfo;

public slots:
    //void item_DblClicked(QTreeWidgetItem *item,int column);

};

#endif // FRIEND_H
