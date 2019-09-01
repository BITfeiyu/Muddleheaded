#include <QApplication>
#include <QString>
#include "initdatabase.h"
#include "register.h"
#include "login.h"
#include "deletedatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createDatabase();
    initDatadase();
    addNewUser("username", "password");
    login("1", "password");
    deletedatabase();

    return a.exec();
}

