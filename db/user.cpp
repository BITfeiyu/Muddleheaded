#include "user.h"
#include "createDatabase.h"
#include <QSqlError>

User::User(int pcUserID)
{
    getUserInfo(pcUserID);
}

int User::getUserID()
{
    return this->userID;
}

QString User::getUserIP()
{
    return this->userIP;
}

QString User::getUserNickName()
{
    return this->nickName;
}

int User::getIState()
{
    return this->iState;
}

QString User::getUSerIconHead()
{
    return this->iconHead;
}

bool User::getUserInfo(int pcUserID){
    if(db.open()){
        QString sql;

        sql = "select * from user where userID = ";
        sql.append(QString::number(pcUserID));
        sql.append(";");
        //qDebug() << sql;

        QSqlQuery getUserInfoQuery;
        if(getUserInfoQuery.exec(sql)){
            getUserInfoQuery.next();
            this->userID = pcUserID;
            this->userIP = getUserInfoQuery.value(1).toString();
            this->nickName = getUserInfoQuery.value(2).toString();
            this->iState = getUserInfoQuery.value(4).toInt();
            this->iconHead = getUserInfoQuery.value(5).toString();
            qDebug() << "User info maintained!";
            return true;
        } else {
            qDebug() << "User not found!";
            return false;
        }

    } else {
        qDebug() << db.lastError();
        qDebug() << "2Database cannot open!";
        return false;
    }
}





