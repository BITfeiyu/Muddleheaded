#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

#include <QLineEdit>

#include <QPushButton>
class Widget : public QWidget
{
    Q_OBJECT
private:

            QLabel *userNameLabel;

            QLabel *passWordLabel;            QLineEdit *userNameLineEdit;

            QLineEdit *passWordLineEdit;            QPushButton *login;

private slots:

            void slotLogin();
public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
