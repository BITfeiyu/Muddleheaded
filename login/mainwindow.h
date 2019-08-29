#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>

#include <QLineEdit>

#include <QPushButton>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

            QLabel *userNameLabel;

            QLabel *passWordLabel;            QLineEdit *userNameLineEdit;

            QLineEdit *passWordLineEdit;            QPushButton *login;
private slots:

            void slotLogin();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
