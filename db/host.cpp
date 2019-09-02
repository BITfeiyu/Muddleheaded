#include "host.h"
#include "friend.h"
#include "createDatabase.h"

Host::Host(int pcUserID):User(pcUserID)
{

}

bool Host::addNewFriend(int pcFriendID){
    if(db.open()){
        QString sql;

        Friend *newFriend = new Friend(pcFriendID);
        QString friendIP = newFriend->getUserIP();
        //qDebug() << "friendIP:" << friendIP;
        QString friendNickName = newFriend->getUserNickName();
        //qDebug() << "friendNickName:" << friendNickName;

        if(friendIP == NULL || friendNickName == NULL){
            qDebug() << "Friend not found!";
            return false;
        }

        sql = "insert into FriendList";
        sql.append(QString::number(this->getUserID()));
        sql.append(" values (");
        sql.append(QString::number(pcFriendID));
        sql.append(", '");
        sql.append(friendIP);
        sql.append("', '");
        sql.append(friendNickName);
        sql.append("');");
        //qDebug() << sql;

        QSqlQuery addNewFriendQuery;
        if(addNewFriendQuery.exec(sql)){
            qDebug() << "New friend added!";
        }

        db.close();
        return true;
    } else {
        qDebug() << "Database cannot open!";
        return false;
    }
}


bool Host::deleteFriend(int pcFriendID){
    if(db.open()){
        QString sql;

        sql = "delete from FriendList";
        sql.append(QString::number(this->getUserID()));
        sql.append(" where friendID = ");
        sql.append(QString::number(pcFriendID));
        sql.append(";");
        //qDebug() << sql;

        QSqlQuery deleteQuery;
        if(deleteQuery.exec(sql)){
            qDebug() << "Friend deleted!";
            db.close();
            return true;
        }

        db.close();
        return false;

    } else {
        qDebug() << "Database cannot open!";
        return false;
    }
}

