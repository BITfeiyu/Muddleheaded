#ifndef FILE2_H
#define FILE2_H

#include <QDialog>

namespace Ui {
class file2;
}

class file2 : public QDialog
{
    Q_OBJECT

public:
    explicit file2(QWidget *parent = nullptr);
    ~file2();

private:
    Ui::file2 *ui;
};

#endif // FILE2_H
