#ifndef DELETEDATABASE_H
#define DELETEDATABASE_H

#include <QFile>
#include "createDatabase.h"

static bool deletedatabase(){
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

#endif // DELETEDATABASE_H
