#ifndef HOST_H
#define HOST_H

#include <QObject>
#include "user.h"
#include "createDatabase.h"

class Host : public User
{
    Q_OBJECT
public:
    Host(int pcUserID);

    bool addNewFriend(int pcFriendID);
    bool deleteFriend(int pcFriendID);

signals:

public slots:
};

#endif // HOST_H
