#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QDialog>

namespace Ui {
class DialogList;
}

class DialogList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogList(QDialog *parent = 0);
    ~DialogList();

private:
    Ui::DialogList *ui;
    QVector<bool> isShow;
};

#endif // DIALOGLIST_H
