#include "database.h"

QSqlDatabase db;
QString allUserInfo;

bool createDatabase(){
//    if(QFile::exists("weChatData.db")){
//        qDebug() << "Database had been established!";
//        db = QSqlDatabase::database("QSQLITE");
//    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("weChatData.db");
        db.setUserName("root");
        db.setPassword("123456");
        qDebug() << "Databse established!";
        if(!QFile::exists("weChatData.db")){
            initDatadase();
        }
//    }
    return true;
}

bool deletedatabase(){
    if(db.open()){
        db.close();
    } else {
        qDebug() << "Database does not exist!";
        return false;
    }
    if(QFile::remove("weChatData.db")){
        qDebug("Database deleted!");
        return true;
    }else {
        return false;
    }
}

bool initDatadase(){
    if(db.open()){
        QSqlQuery initQuery(db);

        QString sql = "create table user ("
            "username char(50) primary key not null, "
            "password char(16) not null, "
            "userIP char(25) not null, "
            "iconHead char(500));";
        //qDebug() << sql;

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

bool checkRegisterInput(QString pcPasswd) {
    if(pcPasswd.length() >= 8 && pcPasswd.length() <= 16){
        return true;
    } else {
        qDebug() << "Password should be between 8 to 16 words.";
        return false;
    }
}

bool addNewUser(QString pcUsername, QString pcPasswd, QString pcUserIP){
    if(checkRegisterInput(pcPasswd)){

        if(db.open()){
            //qDebug() << "Database opened!";

            QString sql;

            int usernameExistFlag = 0;
            sql = "select * from user;";
            QSqlQuery checkUsernameExistQuery(db);
            if(!checkUsernameExistQuery.exec(sql)){
                qDebug() << "Cannot check username!";
            }
            while(checkUsernameExistQuery.next()){
                QString usernameChecked = checkUsernameExistQuery.value(0).toString();
                if(usernameChecked == pcUsername){
                    usernameExistFlag = 1;
                    break;
                }
            }

            if(usernameExistFlag == 0){

                qDebug() << "Username is available.";

                sql = "insert into user values('";
                sql.append(pcUsername);
                sql.append("', '");
                sql.append(pcPasswd);
                sql.append("', '");
                sql.append(pcUserIP);
                sql.append("', '')");
                //qDebug() << sql;

                QSqlQuery registerQuery(db);
                if(registerQuery.exec(sql)){
                    qDebug() << "Register succeeded!";
                }
            } else {
                qDebug() << "Username exsits,try another!";
                db.close();
                return false;
            }

            db.close();
            return true;
        } else {
            qDebug() << "Database cannot open,register failed!";
            return false;
        }

    } else {
    return false;
    }
}

bool checkUserInput(QString pcUsername, QString pcUserpasswd){
    if(db.open()){

        int findUserFlag = 0;
        QString password;

        QString sql;
        sql = "select * from user";
        QSqlQuery loginQuery(db);
        loginQuery.exec(sql);
        while(loginQuery.next()){
            QString usernameCheck = loginQuery.value(0).toString();
            qDebug() << "usernameCheck:" << usernameCheck;
            if(usernameCheck == pcUsername){
                findUserFlag = 1;
                qDebug() << "User Found!";
                password = loginQuery.value(1).toString();
                if(password == pcUserpasswd){
                    qDebug() << "Password correct!";
                    db.close();
                    return true;
                } else {
                    qDebug() << "Password incorrect!";
                    db.close();
                    return false;
                }
            }
        }
        if(findUserFlag == 0){
            qDebug() << "User not Found!";
            db.close();
            return false;
        }
    }else {
        qDebug() << "Database cannot open!";
        return false;
    }

}

bool login(QString pcUsername, QString pcUserpasswd){
    if(checkUserInput(pcUsername, pcUserpasswd)){
        qDebug() << "Login permitted!";
        return(true);
    } else {
        qDebug() << "UserID or passwd wrong!";
        return(false);
    }
}

bool getAllUserInfo()
{
    if(db.open()){
        QString sql = "select * from user";
        QSqlQuery getAllUserInfoQuery;
        if(getAllUserInfoQuery.exec(sql)){
            allUserInfo = "";
            while(getAllUserInfoQuery.next()){
                allUserInfo.append("#").append(getAllUserInfoQuery.value(0).toString());
                allUserInfo.append("#").append(getAllUserInfoQuery.value(2).toString());
                allUserInfo.append("#").append(getAllUserInfoQuery.value(3).toString());
            }
            qDebug() << "All user info got!";
            db.close();
            return true;
        }
        db.close();
        return false;
    } else {
        qDebug() << "Databse cannot open!";
    }
}
