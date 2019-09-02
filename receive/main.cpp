#include "receive_file.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    receive_file w;
    w.show();

    return a.exec();
}
