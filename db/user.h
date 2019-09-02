#ifndef USER_H
#define USER_H

#include <QObject>
#include "createDatabase.h"

class User : public QObject
{
    Q_OBJECT

private:
    int userID;
    QString userIP;
    QString nickName;
    int iState = 0;
    QString iconHead = "";

public:
    User(int pcUserID);
    int getUserID();
    QString getUserIP();
    QString getUserNickName();
    int getIState();
    QString getUSerIconHead();

private:
    bool getUserInfo(int pcUserID);

signals:

public slots:
};

#endif // USER_H
