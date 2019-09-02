#ifndef FRIEND_H
#define FRIEND_H

#include <QObject>
#include "user.h"

class Friend : public User
{
    Q_OBJECT

public:
    Friend(int friendID);

signals:

public slots:
};

#endif // FRIEND_H
