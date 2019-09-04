#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QString>
#include <string.h>

extern QSqlDatabase db;
extern QString allUserInfo;

bool createDatabase();
bool deletedatabase();
bool initDatadase();

bool addNewUser(QString pcUsername, QString pcPasswd, QString pcUserIP);
bool login(QString pcUsername, QString pcUserpasswd);
bool getAllUserInfo();


#endif // DATABASE_H
