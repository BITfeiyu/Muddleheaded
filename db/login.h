#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include <string.h>
#include "createDatabase.h"

static bool checkUserInput(QString pcUserID, QString pcUserpasswd){
    if(db.open()){
        QString sql;

        sql = "select * from user where userID = ";
        sql.append(pcUserID);
        sql.append(";");

        QSqlQuery loginQuery(db);
        if(!loginQuery.exec(sql)){
            qDebug() << "Guy not found!";
        }

        loginQuery.next();
        if(pcUserpasswd == loginQuery.value(3).toString()){
            qDebug() << "Passwords are the same!";
            db.close();
            return(true);
        } else {
            qDebug() << "Passwords are different!";
            db.close();
            return(false);
        }
    }else {
        qDebug() << "Database cannot open!";
        return false;
    }

}

static bool login(QString pcUserID, QString pcUserpasswd){
    if(checkUserInput(pcUserID, pcUserpasswd)){
        qDebug() << "Login permitted!";
        return(true);
    } else {
        qDebug() << "UserID or passwd wrong!";
        return(false);
    }
}

#endif // LOGIN_H
