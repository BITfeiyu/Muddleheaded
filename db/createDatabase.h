#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

QSqlDatabase db;

static bool createDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("weChatData.db");
    db.setUserName("root");
    db.setPassword("123456");
    return(true);
}

#endif // CONNECTION_H
