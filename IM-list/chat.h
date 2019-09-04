#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent, QString name);
    ~Chat();

private:
    Ui::Chat *ui;
/*
signals:
    void closeWidget();


 public:
    void closeEvent(QCloseEvent*);
*/
};

#endif // CHAT_H
