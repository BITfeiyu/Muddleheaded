#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QTreeWidget>
#include<QTreeWidgetItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void item_DblClicked(QTreeWidgetItem *item,int column);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
