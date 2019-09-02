#ifndef REGISTER_H
#define REGISTER_H

#include <QString>
#include "createDatabase.h"

static bool checkRegisterInput(QString pcPasswd) {
    if(pcPasswd.length() >= 8 && pcPasswd.length() <= 16){
        return true;
    } else {
        qDebug() << "Password should be between 8 to 16 words.";
        return false;
    }
}

static bool addNewUser(QString pcUserNickName, QString pcPasswd){
    if(checkRegisterInput(pcPasswd)){

        if(db.open()){
            //qDebug() << "Database opened!";

            QString sql;

            sql = "select userID from user";
            QSqlQuery findLastIDQuery(db);
            findLastIDQuery.exec(sql);
            int lastID = findLastIDQuery.last();
            int thisID = lastID + 1;
            //qDebug() << "thisID:" << thisID;

            sql = "create table FriendList";
            sql.append(QString::number(thisID));
            sql.append(" (friendID int primary key not null, "
                       "friendIP char(25) not null, "
                       "friendNickName char(50) not null);");
            //qDebug() << sql;

            QSqlQuery newFriendListQuery(db);
            if(newFriendListQuery.exec(sql)){
                qDebug() << "Friend list table established!";
            }

            sql = "insert into user values(";
            sql.append(QString::number(thisID));
            sql.append(", '127.0.0.1', '");
            sql.append(pcUserNickName);
            sql.append("', '");
            sql.append(pcPasswd);
            sql.append("', false, '');");
            //qDebug() << sql;

            QSqlQuery registerQuery(db);
            if(registerQuery.exec(sql)){
                qDebug() << "Register succeeded!";
            }

            db.close();
        } else {
            qDebug() << "Database cannot open,register failed!";
            return false;
        }

    } else {
    return false;
    }
}

#endif // REGISTER_H
