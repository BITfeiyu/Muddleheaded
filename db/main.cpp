#include <QApplication>
#include <QString>
#include "createDatabase.h"
#include "initdatabase.h"
#include "register.h"
#include "login.h"
#include "deletedatabase.h"
#include "host.h"
#include "friend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createDatabase();
    initDatadase();
    addNewUser("username", "password");
    addNewUser("root", "adminpasswd");
    login(1, "password");
    Host *host = new Host(1);
    host->addNewFriend(2);
    host->deleteFriend(2);
    deletedatabase();

    return a.exec();
}

