#include "createDatabase.h"

QSqlDatabase db;

bool createDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("weChatData.db");
    db.setUserName("root");
    db.setPassword("123456");
    return(true);
}
