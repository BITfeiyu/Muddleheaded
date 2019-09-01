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
        QString sql;

        if(db.open()){
            qDebug() << "Database opened!";

            sql = "select ID from user";
            QSqlQuery findLastIDQuery(db);
            findLastIDQuery.exec(sql);
            int lastID = findLastIDQuery.last();

            sql = "insert into user values(";
            sql.append(QString::number(lastID + 1));
            sql.append(", '127.0.0.1', '");
            sql.append(pcUserNickName);
            sql.append("', '");
            sql.append(pcPasswd);
            sql.append("', false, 'null');");

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
