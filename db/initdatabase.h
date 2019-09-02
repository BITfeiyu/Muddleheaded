#ifndef INITDATABASE_H
#define INITDATABASE_H

#include "createDatabase.h"

static bool initDatadase(){
    //QSqlDatabase initDatabase = QSqlDatabase::database("initConnection");
    if(db.open()){
        //qDebug() << "Database opened!";
        QSqlQuery initQuery(db);

        QString sql = "create table user (userID int primary key not null, "
            "userIP char(25) not null, "
            "nickName char(50) not null, "
            "passwd char(16) not null, "
            "iState int, "
            "iconHead char(500));";

        if(initQuery.exec(sql)){
            qDebug() << "User table established!";
            db.close();
            return true;
        } else {
            qDebug() << "User table establishment failed!";
            db.close();
            return false;
        }

    } else {
        return false ;
    }
}

#endif // INITDATABASE_H
